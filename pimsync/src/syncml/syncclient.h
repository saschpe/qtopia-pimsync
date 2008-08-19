/****************************************************************************
**
** Copyright (C) 2000-2008 TROLLTECH ASA. All rights reserved.
**
** This file is part of the Phone Edition of the Qtopia Toolkit.
**
** Licensees holding a valid license agreement from Trolltech or any of its
** authorized distributors may use this file in accordance with
** the License Agreement provided with the Licensed Software.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Trolltech's Commercial License Agreements.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef SYNCCLIENT_H
#define SYNCCLIENT_H

#include <fixes.h>
#include <client/SyncClient.h>

#include <QObject>

class QString;
class ServerConfig;
class SyncManagerConfig;

/*!
 * This is the main class which looks at the configuration,
 * activates all enabled sources and executes the synchronization.
 */
class QtopiaSyncClient : public QObject, public SyncClient
{
    Q_OBJECT

public:
    QtopiaSyncClient();
    virtual ~QtopiaSyncClient();

    /*!
     * Trigger the sync with a remote server. Make sure that everything
     * was configured correctly or the sync may fail.
     */
    bool sync(ServerConfig *profile);

    QString results();
    QString error();

    QString syncReport();

private:
    SyncManagerConfig *m_managerConfig;
};

#endif
