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

#ifndef CONTACTSYNCSOURCE_H
#define CONTACTSYNCSOURCE_H

#include "abstractsyncsource.h"

#include <QContactModel>

class ContactSyncSourceConfig : public AbstractSyncSourceConfig2
{
public:
    ContactSyncSourceConfig(Mode syncMode, unsigned int lastSync, const char *uri)
        : AbstractSyncSourceConfig2(syncMode, lastSync, uri)
    {
        setName("contact");
        setType("text/x-vcard");
        //setSupportedTypes("text/x-vcard:,text/vcard");
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
