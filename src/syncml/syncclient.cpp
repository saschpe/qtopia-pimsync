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

#include "syncclient.h"
#include "../syncprofile.h"
#include "contactsyncsource.h"
#include "appointmentsyncsource.h"
#include "tasksyncsource.h"
#include "notesyncsource.h"

#include <spds/SyncManagerConfig.h>

#include <QtXml>
#include <QContent>
#include <QSettings>
#include <QUuid>

QtopiaSyncClient::QtopiaSyncClient()
	: QObject(), SyncClient()
{	
	m_managerConfig = new SyncManagerConfig();

	// Create a GUID for the current device once, used for identification
	// with SyncML servers
	QSettings cfg("Trolltech", "SyncZilla");
	QUuid id = QUuid(cfg.value("Funambol/Device/Id").toString());
	if (id.isNull()) {
		id = QUuid::createUuid();
		//qDebug() << "QtopiaSyncClient::QtopiaSyncClient() Generate device GUID:" << id.toString();
		cfg.setValue("Device/Id", id.toString());
	} else {
		//qDebug() << "QtopiaSyncClient::QtopiaSyncClient() Using device GUID:" << id.toString();
	}

	AccessConfig* ac = new AccessConfig();
	ac->setUsername             ("");
	ac->setPassword             ("");
	ac->setFirstTimeSyncMode    (SYNC_NONE);
	//ac->setFirstTimeSyncMode    (SYNC_SLOW);
	ac->setUseProxy             (FALSE);
	//ac->setProxyHost            ("");
	//ac->setProxyPort            (8080);
	//ac->setProxyUsername        ("");
	//ac->setProxyPassword        ("");
	ac->setSyncURL              ("http://localhost:8080/funambol/ds");
	ac->setBeginSync            (0);
	ac->setEndSync              (0);
	ac->setServerAuthRequired   (FALSE);
	ac->setClientAuthType       ("syncml:auth-basic");
	ac->setServerAuthType       ("syncml:auth-basic");
	ac->setServerPWD            ("funambol");
	ac->setServerID             ("funambol");
	ac->setServerNonce          ("");
	ac->setClientNonce          ("");
	ac->setMaxMsgSize           (10000);
	ac->setReadBufferSize       (0);
	ac->setUserAgent            ("");
	ac->setCheckConn            (TRUE);
	ac->setResponseTimeout      (0);
	m_managerConfig->setAccessConfig(*ac);
	delete ac;
		
	// Customize for specific device
	DeviceConfig* dc = new DeviceConfig();
	dc->setVerDTD               ("1.1");
	dc->setMan                  ("Trolltech");
	dc->setMod                  ("");
	dc->setOem                  ("");
	dc->setFwv                  ("");
	dc->setSwv                  ("");
	dc->setHwv                  ("");
	dc->setDevID                (id.toString().toAscii());	// This should be a GUID
	dc->setDevType              ("smartphone"); 			// Or pda,handheld,server,workstation,pager,phone
	dc->setDsV                  ("");
	dc->setUtc                  (TRUE);
	dc->setLoSupport            (FALSE);
	dc->setNocSupport           (FALSE);
	dc->setLogLevel             (LOG_LEVEL_NONE);
	//dc->setLogLevel             (LOG_LEVEL_DEBUG);
	dc->setMaxObjSize           (0);
	dc->setDevInfHash           ("");
	m_managerConfig->setDeviceConfig(*dc);
	delete dc;
}

QtopiaSyncClient::~QtopiaSyncClient()
{
	if (m_managerConfig)
		delete m_managerConfig;
}

bool QtopiaSyncClient::sync(SyncProfile *profile)
{
	m_managerConfig->getAccessConfig().setUsername(profile->transportUser().toAscii());
	m_managerConfig->getAccessConfig().setPassword(profile->transportPassword().toAscii());
	m_managerConfig->getAccessConfig().setSyncURL(profile->transportUrl().toAscii());

	// This is more or less a direkt mapping of supported sync modes
	AbstractSyncSourceConfig::Mode mode = AbstractSyncSourceConfig::TwoWay;
	switch (profile->mode()) {
		case SyncProfile::Slow:					mode = AbstractSyncSourceConfig::Slow;				break;
		case SyncProfile::TwoWay:				mode = AbstractSyncSourceConfig::TwoWay;			break;
		case SyncProfile::OneWayFromServer:		mode = AbstractSyncSourceConfig::OneWayFromServer;	break;
		case SyncProfile::OneWayFromClient:		mode = AbstractSyncSourceConfig::OneWayFromClient;	break;
		case SyncProfile::RefreshFromServer:	mode = AbstractSyncSourceConfig::RefreshFromServer;	break;
		case SyncProfile::RefreshFromClient:	mode = AbstractSyncSourceConfig::RefreshFromClient;	break;
	}

	int index = 0;
	SyncSource *sourcesArray[] = {NULL, NULL, NULL, NULL, NULL};	// count sources + 1 -> '\0' terminated array

	ContactSyncSource *contactSource = NULL;
	if (profile->contactsEnabled()) {
		ContactSyncSourceConfig *contactConfig = new ContactSyncSourceConfig(mode, profile->contactsLastSync(), profile->contactsUrl().toAscii());
		contactSource = new ContactSyncSource(contactConfig, m_managerConfig);
		sourcesArray[index++] = contactSource;
	}
	TaskSyncSource *taskSource = NULL;
	if (profile->tasksEnabled()) {
		TaskSyncSourceConfig *taskConfig = new TaskSyncSourceConfig(mode, profile->tasksLastSync(), profile->tasksUrl().toAscii());
		taskSource = new TaskSyncSource(taskConfig, m_managerConfig);
		sourcesArray[index++] = taskSource;
	}
	AppointmentSyncSource *appointmentSource = NULL;
	if (profile->appointmentsEnabled()) {
		AppointmentSyncSourceConfig *appointmentConfig = new AppointmentSyncSourceConfig(mode, profile->appointmentsLastSync(), profile->appointmentsUrl().toAscii());
		appointmentSource = new AppointmentSyncSource(appointmentConfig, m_managerConfig);
		sourcesArray[index++] = appointmentSource;
	}
	NoteSyncSource *noteSource = NULL;
	if (profile->notesEnabled()) {
		NoteSyncSourceConfig *noteConfig = new NoteSyncSourceConfig(mode, profile->notesLastSync(), profile->notesUrl().toAscii());
		noteSource = new NoteSyncSource(noteConfig, m_managerConfig);
		sourcesArray[index++] = noteSource;
	}

	if (SyncClient::sync(*m_managerConfig, sourcesArray) == 0) {
		if (profile->contactsEnabled())
			profile->setContactsLastSync(contactSource->lastSync());
		if (profile->tasksEnabled())
			profile->setTasksLastSync(taskSource->lastSync());
		if (profile->appointmentsEnabled())
			profile->setAppointmentsLastSync(appointmentSource->lastSync());
		if (profile->notesEnabled())
			profile->setNotesLastSync(noteSource->lastSync());
		profile->save();
		return true;
	}
	return false;
}

QString QtopiaSyncClient::syncReport()
{
	StringBuffer res;
	SyncClient::getSyncReport()->toString(res);
	return QString(res);
}

QString QtopiaSyncClient::results()
{
	QString str;
	for (unsigned int i = 0; getSyncReport()->getSyncSourceReport(i); i++) {
		SyncSourceReport *ssr = getSyncReport()->getSyncSourceReport(i);
		if (ssr->getState() == SOURCE_INACTIVE)
			continue;

		str += tr("Results for ") + QString(ssr->getSourceName()) + "s:\n";
		str += tr("  client   server\n");
		str += "  " + QString::number(ssr->getItemReportSuccessfulCount(CLIENT, COMMAND_ADD)) + " / " + QString::number(ssr->getItemReportCount(CLIENT, COMMAND_ADD)) + " | ";
		str += "  " + QString::number(ssr->getItemReportSuccessfulCount(SERVER, COMMAND_ADD)) + " / " + QString::number(ssr->getItemReportCount(SERVER, COMMAND_ADD)) + tr(" new\n");
		str += "  " + QString::number(ssr->getItemReportSuccessfulCount(CLIENT, COMMAND_REPLACE)) + " / " + QString::number(ssr->getItemReportCount(CLIENT, COMMAND_REPLACE)) + " | ";
		str += "  " + QString::number(ssr->getItemReportSuccessfulCount(SERVER, COMMAND_REPLACE)) + " / " + QString::number(ssr->getItemReportCount(SERVER, COMMAND_REPLACE)) + tr(" modified\n");
		str += "  " + QString::number(ssr->getItemReportSuccessfulCount(CLIENT, COMMAND_DELETE)) + " / " + QString::number(ssr->getItemReportCount(CLIENT, COMMAND_DELETE)) + " | ";
		str += "  " + QString::number(ssr->getItemReportSuccessfulCount(SERVER, COMMAND_DELETE)) + " / " + QString::number(ssr->getItemReportCount(SERVER, COMMAND_DELETE)) + tr(" deleted\n\n");
	}
	return str;
}

QString QtopiaSyncClient::error()
{
	return getSyncReport()->getLastErrorMsg();
}
