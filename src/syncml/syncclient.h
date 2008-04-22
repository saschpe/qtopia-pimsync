/****************************************************************************
**
** Copyright (C) 2007-2008 TROLLTECH ASA. All rights reserved.
**
** This file is part of the Phone Edition of the Qtopia Toolkit.
**
** $TROLLTECH_DUAL_LICENSE$
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef SYNCCLIENT_H
#define SYNCCLIENT_H

#include "base.h"

#include <client/SyncClient.h>

#include <QObject>

class SyncProfile;
class SyncManagerConfig;
class QString;

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
	bool sync(SyncProfile *profile);

	QString results();

	QString syncReport();

private:
	SyncManagerConfig *m_managerConfig;
};

#endif // QTOPIASYNCCLIENT_H
