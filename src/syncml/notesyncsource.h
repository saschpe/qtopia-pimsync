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

#ifndef NOTESYNCSOURCE_H
#define NOTESYNCSOURCE_H

#include "abstractsyncsource.h"

#include <QNoteModel>

class NoteSyncSourceConfig : public AbstractSyncSourceConfig
{
public:
	NoteSyncSourceConfig(Mode syncMode, unsigned int lastSync, const char *uri) 
		: AbstractSyncSourceConfig(syncMode, lastSync, uri)
	{
		setName("note");
		setType("text/plain");
	}
};

class NoteSyncSource : public AbstractSyncSource
{
public:
	NoteSyncSource(NoteSyncSourceConfig *config, SyncManagerConfig *managerConfig)
		: AbstractSyncSource(config, managerConfig)
	{
		// CURRENTLY NOT SUPPORTED BY PIM MODELS, ONE COULD CREATE ONE
		//m_model = new QNoteModel(); 
		//m_type = "vCalendar";
	}
};

#endif // TASKSYNCSOURCE_H

