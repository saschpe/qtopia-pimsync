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

#ifndef APPOINTMENTSYNCSOURCE_H
#define APPOINTMENTSYNCSOURCE_H

#include "abstractsyncsource.h"

#include <QAppointmentModel>

class AppointmentSyncSourceConfig : public AbstractSyncSourceConfig
{
public:
	AppointmentSyncSourceConfig(Mode syncMode, unsigned int lastSync, const char *uri) 
		: AbstractSyncSourceConfig(syncMode, lastSync, uri)
	{
		setName("event");
		setType("text/x-vcalendar");

		//qDebug() << "AppointmentSyncSourceConfig::AppointmentSyncSourceConfig() Name:" << getName() << "Type:" << getType() << "URI:" << getURI() << "Last.Sync:" << lastSync << "Mode:" << getSync();
	}
};

class AppointmentSyncSource : public AbstractSyncSource
{
public:
	AppointmentSyncSource(AppointmentSyncSourceConfig *config, SyncManagerConfig *managerConfig)
		: AbstractSyncSource(config, managerConfig)
	{ 
		m_model = new QAppointmentModel(); 
		m_type = "vCalendar";
	}
};

#endif // APPOINTMENTSYNCSOURCE_H
