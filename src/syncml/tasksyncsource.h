#ifndef TASKSYNCSOURCE_H
#define TASKSYNCSOURCE_H

#include "abstractsyncsource.h"

#include <QTaskModel>

class TaskSyncSourceConfig : public AbstractSyncSourceConfig
{
public:
	TaskSyncSourceConfig(Mode syncMode, unsigned int lastSync, const char *uri) 
		: AbstractSyncSourceConfig(syncMode, lastSync, uri)
	{
		setName("task");
		setType("text/x-vcalendar");

		//qDebug() << "TaskSyncSourceConfig::TaskSyncSourceConfig() Name:" << getName() << "Type:" << getType() << "URI:" << getURI() << "Last.Sync:" << lastSync << "Mode:" << getSync();
	}
};

class TaskSyncSource : public AbstractSyncSource
{
public:
	TaskSyncSource(TaskSyncSourceConfig *config, SyncManagerConfig *managerConfig)
		: AbstractSyncSource(config, managerConfig)
	{
		m_model = new QTaskModel(); 
		m_type = "vCalendar";
	}
};

#endif // TASKSYNCSOURCE_H
