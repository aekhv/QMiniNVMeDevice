/****************************************************************************
**
** This file is part of the QMiniNVMeDevice library.
** Copyright (C) 2024 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#ifndef QMININVMEDEVICE_H
#define QMININVMEDEVICE_H

#include <QMiniPCIDevice.h>
#include <QMiniNVMeError.h>
#include "QMiniNVMeControllerVersion.h"
#include "QMiniNVMeControllerState.h"
#include "QMiniNVMeControllerInfo.h"
#include "QMiniNVMeNamespaceInfo.h"
#include "QMiniNVMeLogPageHealthInfo.h"

class QMiniNVMeDevice : public QMiniPCIDevice
{
public:
    QMiniNVMeDevice();

    static QStringList availableDevices();

    QMiniNVMeError deviceError() { return m_error; }
    QMiniNVMeControllerVersion controllerVersion();
    QMiniNVMeControllerState controllerState();
    QMiniNVMeControllerInfo controllerInfo();
    QMiniNVMeNamespaceInfo namespaceInfo(int nsid = 1);
    QMiniNVMeLogPageHealthInfo logPageHealthInfo();
    bool read(quint64 offset, quint32 count, char *buffer, int length, int nsid = 1);
    bool write(quint64 offset, quint32 count, char *buffer, int length, int nsid = 1);
    bool controllerReset();

private:
    QMiniNVMeError m_error;
    void setLastError(int err, nvme_status_t &status);
    void setLastError(QMiniPCIError err);
};

#endif // QMININVMEDEVICE_H
