/****************************************************************************
**
** This file is part of the QMiniNVMeDevice library.
** Copyright (C) 2024 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#ifndef QMININVMELOGPAGEHEALTHINFO_H
#define QMININVMELOGPAGEHEALTHINFO_H

#include <QtCore>
#include "QMiniNVMeCommon.h"

class QMiniNVMeLogPageHealthInfo
{
public:
    QMiniNVMeLogPageHealthInfo();
    QMiniNVMeLogPageHealthInfo(const nvme_log_page_health_information_t &info);

    qint8 criticalWarning() const { return m_cw; }
    qint16 compositeTemperature() const { return m_ct; }
    qint8 availableSpare() const { return m_as; }
    qint8 availableSpareThreshold() const { return m_ast; }
    qint8 percentageUsed() const { return m_pu; }
    qint64 dataUnitsRead() const { return m_dur; }
    qint64 dataUnitsWritten() const { return m_duw; }
    qint64 hostReadCommands() const { return m_hrc; }
    qint64 hostWriteCommands() const { return m_hwc; }
    qint64 controllerBusyTime() const { return m_cbt; }
    qint64 powerCycles() const { return m_pc; }
    qint64 powerOnHours() const { return m_poh; }
    qint64 unsafeShutdowns() const { return m_us; }
    qint64 mediaAndDataIntegrityErrors() const { return m_mdie; }
    qint64 numberOfErrorInformationLogEntries() const { return m_neile; }
    qint32 warningCompositeTemperatureTime() const { return m_wctt; }
    qint32 criticalCompositeTemperatureTime() const { return m_cctt; }
    QVector<int> temperatureSensors() const { return m_ts; }
    qint32 TMT1TransitionCount() const { return m_tmt1tc; }
    qint32 TMT2TransitionCount() const { return m_tmt2tc; }
    qint32 totalTimeForTMT1() const { return m_tttmt1; }
    qint32 totalTimeForTMT2() const { return m_tttmt2; }

    static QStringList criticalWarningToStringList(qint8 warning);

private:
    qint8 m_cw;
    qint16 m_ct;
    qint8 m_as, m_ast, m_pu;
    qint64 m_dur, m_duw, m_hrc, m_hwc, m_cbt, m_pc, m_poh, m_us, m_mdie, m_neile;
    qint32 m_wctt, m_cctt;
    QVector<int> m_ts;
    qint32 m_tmt1tc, m_tmt2tc, m_tttmt1, m_tttmt2;
};

#endif // QMININVMELOGPAGEHEALTHINFO_H
