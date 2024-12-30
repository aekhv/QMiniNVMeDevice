/****************************************************************************
**
** This file is part of the QMiniNVMeDevice library.
** Copyright (C) 2024 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#ifndef QMININVMECONTROLLERVERSION_H
#define QMININVMECONTROLLERVERSION_H

#include <QtCore>
#include "../../mininvme/ioctl.h"

class QMiniNVMeControllerVersion
{
public:
    QMiniNVMeControllerVersion();
    QMiniNVMeControllerVersion(const nvme_controller_version_t &version);

    int major() const { return m_major; }
    int minor() const { return m_minor; }
    int tertiary() const { return m_tertiary; }

    QString toString() const;

private:
    int m_major, m_minor, m_tertiary;

};

#endif // QMININVMECONTROLLERVERSION_H
