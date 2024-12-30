/****************************************************************************
**
** This file is part of the QMiniNVMeDevice library.
** Copyright (C) 2024 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#ifndef QMININVMECONTROLLERSTATE_H
#define QMININVMECONTROLLERSTATE_H

#include <QtCore>
#include "../../mininvme/ioctl.h"

class QMiniNVMeControllerState
{
public:
    QMiniNVMeControllerState();
    QMiniNVMeControllerState(const nvme_controller_state_t &state);

    bool enabled() const { return m_enabled; }
    bool ready() const { return m_ready; }
    bool fatal() const { return m_fatal; }

private:
    bool m_enabled, m_ready, m_fatal;
};

#endif // QMININVMECONTROLLERSTATE_H
