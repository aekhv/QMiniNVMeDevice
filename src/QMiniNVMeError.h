/****************************************************************************
**
** This file is part of the QMiniNVMeDevice library.
** Copyright (C) 2024 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#ifndef QMININVMEERROR_H
#define QMININVMEERROR_H

#include <QtCore>

class QMiniNVMeError
{
public:
    QMiniNVMeError();
    QMiniNVMeError(int statusCodeType, int statusCode, bool more, bool doNotRetry);

    int statusCodeType() const { return m_sct; }
    int statusCode() const { return m_sc; }
    bool moreBit() const { return m_more; }
    bool doNotRetryBit() const { return m_dnr; }

    static QString statusCodeTypeToString(int type);
    static QString statusCodeToString(int type, int code);

private:
    int m_sct;
    int m_sc;
    bool m_more;
    bool m_dnr;
};

#endif // QMININVMEERROR_H
