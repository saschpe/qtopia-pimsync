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

#ifndef CONTACTSYNCSOURCE_H
#define CONTACTSYNCSOURCE_H

#include "abstractsyncsource.h"

#include <QContactModel>

class ContactSyncSourceConfig : public AbstractSyncSourceConfig
{
public:
	ContactSyncSourceConfig(Mode syncMode, unsigned int lastSync, const char *uri) 
		: AbstractSyncSourceConfig(syncMode, lastSync, uri)
	{
		setName("contact");
		setType("text/x-vcard");

		//qDebug() << "ContactSyncSourceConfig::ContactSyncSourceConfig() Name:" << getName() << "Type:" << getType() << "URI:" << getURI() << "Last.Sync:" << lastSync << "Mode:" << getSync();
	}
};

class ContactSyncSource : public AbstractSyncSource
{
public:
	ContactSyncSource(ContactSyncSourceConfig *config, SyncManagerConfig *managerConfig)
		: AbstractSyncSource(config, managerConfig)
	{ 
		m_model = new QContactModel(); 

		// Ignore SIM or other sources by default because it's unclear
		// how to sync them (modifying a SIM contact on a server leads to
		// problem when we want to reimport it)
		QSet<QPimSource> sources;
		sources.insert(m_model->defaultSource());
		m_model->setVisibleSources(sources);
		m_type = "vCard";
	}
};

#endif // CONTACTSYNCSOURCE_H
