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
		//setSupportedTypes("text/x-vcalendar:");
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
