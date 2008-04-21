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
