/****************************************************************************
**
** This file is part of the QMiniNVMeDevice library.
** Copyright (C) 2024 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#include "QMiniNVMeControllerVersion.h"

QMiniNVMeControllerVersion::QMiniNVMeControllerVersion()
    : m_major(0),
      m_minor(0),
      m_tertiary(0)
{

}

QMiniNVMeControllerVersion::QMiniNVMeControllerVersion(const nvme_controller_version_t &version)
{
    m_major = version.major;
    m_minor = version.minor;
    m_tertiary = version.tertiary;

}

QString QMiniNVMeControllerVersion::toString() const
{
    return QString("%1.%2.%3")
            .arg(m_major)
            .arg(m_minor)
            .arg(m_tertiary);
}
