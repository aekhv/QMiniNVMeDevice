/****************************************************************************
**
** This file is part of the QMiniNVMeDevice library.
** Copyright (C) 2024 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#include "QMiniNVMeLogPageHealthInfo.h"

QMiniNVMeLogPageHealthInfo::QMiniNVMeLogPageHealthInfo()
{
    m_cw = 0;
    m_ct = 0;
    m_as = 0;
    m_ast = 0;
    m_pu = 0;
    m_dur = 0;
    m_duw = 0;
    m_hrc = 0;
    m_hwc = 0;
    m_cbt = 0;
    m_pc = 0;
    m_poh = 0;
    m_us = 0;
    m_mdie = 0;
    m_neile = 0;
    m_wctt = 0;
    m_cctt = 0;
    m_tmt1tc = 0;
    m_tmt2tc = 0;
    m_tttmt1 = 0;
    m_tttmt2 = 0;
}

QMiniNVMeLogPageHealthInfo::QMiniNVMeLogPageHealthInfo(const nvme_log_page_health_information_t &info)
{
    m_cw = info.cw;
    m_ct = info.ct[0] + (info.ct[1] << 8);
    m_as = info.as;
    m_ast = info.ast;
    m_pu = info.pu;
    m_dur = info.dur_lo;
    m_duw = info.duw_lo;
    m_hrc = info.hrc_lo;
    m_hwc = info.hwc_lo;
    m_cbt = info.cbt_lo;
    m_pc = info.pc_lo;
    m_poh = info.poh_lo;
    m_us = info.us_lo;
    m_mdie = info.mdie_lo;
    m_neile = info.neile_lo;
    m_wctt = info.wctt;
    m_cctt = info.cctt;

    for (int i = 0; i < 8; i++)
        m_ts.append(info.ts[i]);

    m_tmt1tc = info.tmt1tc;
    m_tmt2tc = info.tmt2tc;
    m_tttmt1 = info.tttmt1;
    m_tttmt2 = info.tttmt2;
}

QStringList QMiniNVMeLogPageHealthInfo::criticalWarningToStringList(qint8 warning)
{
    QStringList list;

    if (warning & 0x01)
        list.append("Available spare capacity has fallen below the threshold");

    if (warning & 0x02)
        list.append("A temperature is greater than or equal to an over temperature threshold");

    if (warning & 0x04)
        list.append("The NVM subsystem reliability has been degraded");

    if (warning & 0x08)
        list.append("The media has been placed in read only mode");

    if (warning & 0x10)
        list.append("The volatile memory backup device has failed");

    if (warning & 0x20)
        list.append("The persistent memory region has become read-only or unreliable");

    if (list.isEmpty())
        list.append("No warning");

    return list;
}
