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

#include "synczilla.h"
#include "configscreen.h"
#include "syncprofile.h"
#include "syncml/syncclient.h"

#include <QtGui>
#include <QContentFilter>
#include <QSoftMenuBar>
#include <QtopiaApplication>
#include <QContentSet>
#include <QDocumentSelector>
#include <QWaitWidget>


SyncZilla::SyncZilla(QWidget *parent, Qt::WindowFlags /*flags*/)
	: QStackedWidget(parent)
	, m_mainScreen(NULL)
	, m_configScreen(NULL)
	, m_logScreen(NULL)
	, m_syncClient(NULL)
	, m_profile(NULL)
{
	setCurrentWidget(mainScreen());

	connect(&mainScreen()->documents(), SIGNAL(changed()), this, SLOT(init()));
}

void SyncZilla::init()
{
	/* Do first time initialization. The Qtopia content systems lacks
	 * support for it, so we do it programmatically.
	 */
	QSettings cfg("Trolltech", "SyncZilla");

	QString firstRun = cfg.value("General/firstRun").toString();
	if (firstRun.isNull() || firstRun == "true") {
		// NOTE: Do first time start up customization here or provide the corresponding settings file
		createDefaultProfiles();
		cfg.setValue("General/createDefaultsWhenEmpty","true");
		cfg.setValue("General/firstRun", "false");
	} else if (mainScreen()->documents().isEmpty()) {
		if (cfg.value("General/createDefaultsWhenEmpty").toBool()) {
			createDefaultProfiles();
			cfg.setValue("General/firstRun", "false");
		}
	}
	// Don't forget to disconnect this slot otherwise it's called every time we change contents
	disconnect(&mainScreen()->documents(), SIGNAL(changed()), this, SLOT(init()));
}

QDocumentSelector *SyncZilla::mainScreen()
{
	if (!m_mainScreen) {
		m_mainScreen = new QDocumentSelector(this);
		m_mainScreen->setFilter(QContentFilter::mimeType("application/vnd.trolltech-qsp-xml"));
		m_mainScreen->enableOptions(QDocumentSelector::NewDocument);
		connect(m_mainScreen, SIGNAL(newSelected()), this, SLOT(newProfile()));
		connect(m_mainScreen, SIGNAL(documentSelected(QContent)), this, SLOT(editProfile(QContent)));
		addWidget(m_mainScreen);
	}
	return m_mainScreen;
}

ConfigScreen *SyncZilla::configScreen()
{
	if (!m_configScreen) {
		m_configScreen = new ConfigScreen();
		connect(m_configScreen, SIGNAL(syncPressed()), this, SLOT(sync()));
		addWidget(m_configScreen);
	}
	return m_configScreen;
}

QTextEdit *SyncZilla::logScreen()
{
	if (!m_logScreen) {
		m_logScreen = new QTextEdit();
		m_logScreen->setReadOnly(true);
		QSoftMenuBar::menuFor(m_logScreen)->clear();
		QSoftMenuBar::setLabel(m_logScreen, Qt::Key_Select, "", "", QSoftMenuBar::AnyFocus); 
		QSoftMenuBar::setLabel(m_logScreen, Qt::Key_Back, tr("Back"), tr("Back"), QSoftMenuBar::AnyFocus);
		addWidget(m_logScreen);
	}
	return m_logScreen;
}

QtopiaSyncClient *SyncZilla::syncClient()
{
	if (!m_syncClient) {
		m_syncClient = new QtopiaSyncClient();
	}
	return m_syncClient;
}

SyncProfile *SyncZilla::profile()
{
	if (!m_profile) {
		m_profile = new SyncProfile();
	}
	return m_profile;
}

void SyncZilla::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Back) {
		if (currentIndex() == indexOf(logScreen())) {
			setCurrentWidget(mainScreen());
			return;
		} else if (currentIndex() == indexOf(configScreen())) {
			setCurrentWidget(mainScreen());
			return;
		} else {
			QtopiaApplication::quit();
		}
	} else {
		QStackedWidget::keyPressEvent(event);
	}
}

void SyncZilla::sync()
{
	QContent selected = m_mainScreen->currentDocument();
	setCurrentWidget(logScreen());
	m_logScreen->document()->clear();
	m_logScreen->insertPlainText(tr("Loading profile \"%1\": ").arg(selected.name()));
	if (profile()->load(selected)) {
		m_logScreen->insertPlainText(tr("Ok\n"));
		m_logScreen->insertPlainText(tr("Sync with server: "));

		//QWaitWidget foo = new QWaitWidget(this);
		//foo.show();
		// TODO: put into thread
		bool ret = syncClient()->sync(m_profile);
		//delete foo;
		
		if (ret) {
			m_logScreen->insertPlainText(tr("Ok\n\n"));
			m_logScreen->insertPlainText(m_syncClient->results());
		} else {
			m_logScreen->insertPlainText(tr("Failed\n\n"));
			m_logScreen->insertPlainText(m_syncClient->error());
			m_logScreen->insertPlainText(tr("\n\nPlease have a look at your provided configuration\n"));
		}
		//qDebug() << m_syncClient->syncReport();
	} else
		m_logScreen->insertPlainText(tr("Failed\n"));
}

void SyncZilla::SyncThread::run()
{
	qDebug() << "SyncZilla::SyncThread::run()";
}

void SyncZilla::newProfile()
{
	profile()->newProfile();
	configScreen()->setProfile(m_profile);
	setCurrentWidget(m_configScreen);
}

void SyncZilla::editProfile(const QContent &content)
{
	if (profile()->load(content)) {
		configScreen()->setProfile(m_profile);
		setCurrentWidget(m_configScreen);
	} else {
		QMessageBox::critical(this, tr("Error"), 
				tr("Unable to edit profile: %1").arg(content.name()),
				QMessageBox::Ok, QMessageBox::Ok);
	}
}

void SyncZilla::setDocument(const QString &fileName)
{
	QContent doc(fileName);
	editProfile(doc);
}

void SyncZilla::createDefaultProfiles()
{
	profile()->newProfile();
	profile()->setName("Funambol (local)");
	profile()->setComment("This profile can be used if you have a Funambol DS server running locally.");
	profile()->setContactsUrl("card");
	profile()->setTasksUrl("task");
	profile()->setAppointmentsUrl("event");
	profile()->setNotesUrl("note");
	profile()->setTransportUser("guest");
	profile()->setTransportPassword("guest");
	profile()->setTransportUrl("http://localhost:8080/funambol/ds");
	profile()->save();

	profile()->newProfile();
	profile()->setName("ScheduleWorld (web)");
	profile()->setComment("This profile is suitable for the ScheduleWorld web-service. You need a valid account to use it.");
	profile()->setContactsUrl("card");
	profile()->setTasksUrl("task");
	profile()->setAppointmentsUrl("cal");
	profile()->setNotesUrl("note");
	profile()->setTransportUser("");
	profile()->setTransportPassword("");
	profile()->setTransportUrl("http://sync.scheduleworld.com/funambol/ds");
	profile()->save();

	profile()->newProfile();
	profile()->setName("myFUNAMBOL (web)");
	profile()->setComment("This profile is suitable for the myFUNAMBOl web-service. You need a valid account to use it.");
	profile()->setContactsUrl("card");
	profile()->setTasksUrl("task");
	profile()->setAppointmentsUrl("event");
	profile()->setNotesUrl("");
	profile()->setTransportUser("");
	profile()->setTransportPassword("");
	profile()->setTransportUrl("http://my.funambol.com/sync");
	profile()->save();

	profile()->newProfile();
	profile()->setName("mobical (web)");
	profile()->setComment("This profile is suitable for the mobical web-service. You need a valid account to use it.");
	profile()->setContactsUrl("con");
	profile()->setTasksUrl("task");
	profile()->setAppointmentsUrl("cal");
	profile()->setNotesUrl("vnote");
	profile()->setTransportUser("");
	profile()->setTransportPassword("");
	profile()->setTransportUrl("http://www.mobical.net/sync/server");
	profile()->save();
}
