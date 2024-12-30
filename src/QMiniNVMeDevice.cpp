/****************************************************************************
**
** This file is part of the QMiniNVMeDevice library.
** Copyright (C) 2024 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#include "QMiniNVMeDevice.h"
#include <sys/ioctl.h>  // ioctl()

QMiniNVMeDevice::QMiniNVMeDevice()
{

}

QStringList QMiniNVMeDevice::availableDevices()
{
    return QMiniPCIDevice::availableDevices("mininvme*");
}

void QMiniNVMeDevice::setLastError(int err, nvme_status_t &status)
{
    if (err < 0) {
        // IOCTL error
        setLastError(QMiniPCIError::DeviceIoctlError);
        m_error = QMiniNVMeError();
    } else {
        if (status.timeout) {
            // Timeout
            setLastError(QMiniPCIError::DeviceTimeout);
            m_error = QMiniNVMeError();
        } else {
            if (status.sct || status.sc) {
                // Device error
                setLastError(QMiniPCIError::DeviceError);
                m_error = QMiniNVMeError(status.sct, status.sc, status.more, status.dnr);
            } else {
                // Success
                setLastError(QMiniPCIError::NoError);
                m_error = QMiniNVMeError();
            }
        }
    }
}

void QMiniNVMeDevice::setLastError(QMiniPCIError err)
{
    QMiniPCIDevice::setLastError(err);
}

QMiniNVMeControllerVersion QMiniNVMeDevice::controllerVersion()
{
    nvme_controller_version_t version;
    memset(&version, 0, sizeof(version));
    int err = ioctl(fd(), NVME_IOCTL_GET_CONTROLLER_VERSION, &version);
    if (err < 0)
        setLastError(QMiniPCIError::DeviceIoctlError);
    else
        setLastError(QMiniPCIError::NoError);
    return QMiniNVMeControllerVersion(version);
}

QMiniNVMeControllerState QMiniNVMeDevice::controllerState()
{
    nvme_controller_state_t state;
    memset(&state, 0, sizeof(state));
    int err = ioctl(fd(), NVME_IOCTL_GET_CONTROLLER_STATE, &state);
    if (err < 0)
        setLastError(QMiniPCIError::DeviceIoctlError);
    else
        setLastError(QMiniPCIError::NoError);
    return QMiniNVMeControllerState(state);
}

QMiniNVMeControllerInfo QMiniNVMeDevice::controllerInfo()
{
    nvme_controller_info_t info;
    memset(&info, 0, sizeof(info));

    nvme_command_packet_t packet;
    memset(&packet, 0, sizeof(packet));
    packet.cmd.opc = NVME_ADMIN_IDENTIFY;
    packet.cmd.cdw10 = NVME_ADMIN_IDENTIFY_CONTROLLER;
    packet.buffer.pointer = (uint8_t *)&info;
    packet.buffer.length = sizeof(info);

    int err = ioctl(fd(), NVME_IOCTL_RUN_ADMIN_COMMAND, &packet);
    setLastError(err, packet.status);
    return QMiniNVMeControllerInfo(info);
}

QMiniNVMeNamespaceInfo QMiniNVMeDevice::namespaceInfo(int nsid)
{
    nvme_namespace_info_t info;
    memset(&info, 0, sizeof(info));

    nvme_command_packet_t packet;
    memset(&packet, 0, sizeof(packet));
    packet.cmd.nsid = nsid;
    packet.cmd.opc = NVME_ADMIN_IDENTIFY;
    packet.cmd.cdw10 = NVME_ADMIN_IDENTIFY_NAMESPACE;
    packet.buffer.pointer = (uint8_t *)&info;
    packet.buffer.length = sizeof(info);

    int err = ioctl(fd(), NVME_IOCTL_RUN_ADMIN_COMMAND, &packet);
    setLastError(err, packet.status);
    return QMiniNVMeNamespaceInfo(info);
}

QMiniNVMeLogPageHealthInfo QMiniNVMeDevice::logPageHealthInfo()
{
    nvme_log_page_health_information_t info;
    memset(&info, 0, sizeof(info));

    nvme_command_packet_t packet;
    memset(&packet, 0, sizeof(packet));
    packet.cmd.nsid = -1;
    packet.cmd.opc = NVME_ADMIN_GET_LOG_PAGE;

    nvme_log_page_cdw10_t *cdw10 = (nvme_log_page_cdw10_t*)&packet.cmd.cdw10;
    cdw10->lid = NVME_ADMIN_GET_LOG_PAGE_HEALTH_INFORMATION;
    cdw10->numd = sizeof (info) / sizeof (uint32_t);

    packet.buffer.pointer = (uint8_t *)&info;
    packet.buffer.length = sizeof(info);

    int err = ioctl(fd(), NVME_IOCTL_RUN_ADMIN_COMMAND, &packet);
    setLastError(err, packet.status);
    return QMiniNVMeLogPageHealthInfo(info);
}

bool QMiniNVMeDevice::read(quint64 offset, quint32 count, char *buffer, int length, int nsid)
{
    nvme_lba_packet_t packet;
    memset(&packet, 0, sizeof(packet));
    packet.nsid = nsid;
    packet.lba.offset = offset;
    packet.lba.count = count;
    packet.buffer.pointer = (uint8_t *)buffer;
    packet.buffer.length = length;

    int err = ioctl(fd(), NVME_IOCTL_READ_SECTORS, &packet);
    setLastError(err, packet.status);
    return lastError().success();
}

bool QMiniNVMeDevice::write(quint64 offset, quint32 count, char *buffer, int length, int nsid)
{
    nvme_lba_packet_t packet;
    memset(&packet, 0, sizeof(packet));
    packet.nsid = nsid;
    packet.lba.offset = offset;
    packet.lba.count = count;
    packet.buffer.pointer = (uint8_t *)buffer;
    packet.buffer.length = length;

    int err = ioctl(fd(), NVME_IOCTL_WRITE_SECTORS, &packet);
    setLastError(err, packet.status);
    return lastError().success();
}

bool QMiniNVMeDevice::controllerReset()
{
    int err = ioctl(fd(), NVME_IOCTL_CONTROLLER_RESET);
    if (err < 0)
        setLastError(QMiniPCIError::DeviceIoctlError);
    else
        setLastError(QMiniPCIError::NoError);
    return lastError().success();
}

