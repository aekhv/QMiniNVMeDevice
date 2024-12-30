/****************************************************************************
**
** This file is part of the QMiniNVMeDevice library.
** Copyright (C) 2024 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#ifndef QMININVMENAMESPACEINFO_H
#define QMININVMENAMESPACEINFO_H

#include <QtCore>
#include "QMiniNVMeCommon.h"

class QMiniNVMeNamespaceInfo
{
public:
    QMiniNVMeNamespaceInfo();
    QMiniNVMeNamespaceInfo(const nvme_namespace_info_t &info);

    quint64 totalSize() const { return m_totalSize; }
    quint64 capacity() const { return m_capacity; }
    quint64 utilization() const { return m_utilization; }
    quint16 sectorSize() const { return m_sectorSize; }

private:
    quint64 m_totalSize, m_capacity, m_utilization;
    quint16 m_sectorSize;
};

#endif // QMININVMENAMESPACEINFO_H
