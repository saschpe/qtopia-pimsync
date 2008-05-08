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

#ifndef NOTESYNCSOURCE_H
#define NOTESYNCSOURCE_H

#include "abstractsyncsource.h"

//#include <QNoteModel>

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
		// SO CALLING THE CONSTRUCTOR SHOULD NOT BE ALLOWED
		//m_model = new QNoteModel(); 
		//m_type = "vCalendar";
	}
};

#endif // TASKSYNCSOURCE_H

