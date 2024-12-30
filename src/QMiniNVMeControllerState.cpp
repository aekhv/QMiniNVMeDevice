/****************************************************************************
**
** This file is part of the QMiniNVMeDevice library.
** Copyright (C) 2024 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#include "QMiniNVMeControllerState.h"

QMiniNVMeControllerState::QMiniNVMeControllerState()
    : m_enabled(false),
      m_ready(false),
      m_fatal(false)
{

}

QMiniNVMeControllerState::QMiniNVMeControllerState(const nvme_controller_state_t &state)
{
    m_enabled = state.enabled;
    m_ready = state.ready;
    m_fatal = state.fatal;
}
