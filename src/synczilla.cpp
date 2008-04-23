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

SyncZilla::SyncZilla(QWidget *parent, Qt::WindowFlags /*flags*/)
	: QStackedWidget(parent)
	, m_mainScreen(NULL)
	, m_configScreen(NULL)
	, m_logScreen(NULL)
	, m_syncClient(NULL)
	, m_profile(NULL)
{
	setCurrentWidget(mainScreen());

	/*// Do first time initialization
	QSettings settings("synczilla", "synczilla");
	if (settings.value("firstRun").toString() == "true") {
		// TODO: make this work
		profile()->newFromSettings("profile-funambol-local");
		profile()->save();
		profile()->newFromSettings("profile-myfunambol-web");
		profile()->save();
		profile()->newFromSettings("profile-scheduleworld-web");
		profile()->save();
		profile()->newFromSettings("profile-mobical-web");
		profile()->save();
		settings.setValue("firstRun", "false");
	QSettings foo("synczilla", "foo");
	foo.setValue("foo", "1");
	profile()->load("funambol-local.profile");
	qDebug() << "Profile:" << profile()->name();
	}*/
}

QWidget *SyncZilla::mainScreen()
{
	if (!m_mainScreen) {
		m_selector = new QDocumentSelector(this);
		m_selector->setFilter(QContentFilter::mimeType("application/vnd.trolltech-qsp-xml")
				& QContentFilter(QContentFilter::DRM, "Unprotected"));
		m_selector->enableOptions(QDocumentSelector::NewDocument);
		connect(m_selector, SIGNAL(newSelected()), this, SLOT(newProfile()));
		connect(m_selector, SIGNAL(documentSelected(QContent)), this, SLOT(editProfile(QContent)));
		connect(m_selector, SIGNAL(currentChanged()), this, SLOT(selectionChanged()));

		m_sync = new QPushButton(tr("Sync"), this);
		m_sync->setEnabled(false);
		connect(m_sync, SIGNAL(clicked()), this, SLOT(sync()));
	
		QVBoxLayout *layout = new QVBoxLayout();
		layout->addWidget(m_selector);
		layout->addWidget(m_sync);

		m_mainScreen = new QWidget();
		m_mainScreen->setLayout(layout);
		addWidget(m_mainScreen);
	}
	return m_mainScreen;
}

/*QListWidget *SyncZilla::mainScreen()
{
	if (!m_selectionScreen) {
		m_selectionScreen = new QListWidget(this);

		QAction *newAction = new QAction(tr("New profile"), this);
		QAction *editAction = new QAction(tr("Edit profile"), this);
		QAction *deleteAction = new QAction(tr("Delete profile"), this);
		QAction *syncAction = new QAction(tr("Start sync"), this);

		QMenu *menu = QSoftMenuBar::menuFor(m_selectionScreen);
		menu->addAction(newAction);
		menu->addAction(editAction);
		menu->addAction(deleteAction);
		menu->addSeparator();
		menu->addAction(syncAction);

		addWidget(m_selectionScreen);
	}
	return m_selectionScreen;
}*/

ConfigScreen *SyncZilla::configScreen()
{
	if (!m_configScreen) {
		m_configScreen = new ConfigScreen();
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
	QContent selected = m_selector->currentDocument();
	setCurrentWidget(logScreen());
	m_logScreen->document()->clear();
	m_logScreen->insertPlainText(tr("Loading profile \"%1\": ").arg(selected.name()));
	if (profile()->load(selected)) {
		m_logScreen->insertPlainText(tr("Ok\n"));
		m_logScreen->insertPlainText(tr("Sync with server: "));
		if (syncClient()->sync(m_profile)) {
			m_logScreen->insertPlainText(tr("Ok\n\n"));
			m_logScreen->insertPlainText(m_syncClient->results());
		} else {
			m_logScreen->insertPlainText(tr("Failed\n\n"));
			m_logScreen->insertPlainText(m_syncClient->error());
			m_logScreen->insertPlainText(tr("\n\nPlease have a look at your provided configuration\n"));
		}
		qDebug() << m_syncClient->syncReport();
	} else
		m_logScreen->insertPlainText(tr("Failed\n"));
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

void SyncZilla::selectionChanged()
{
	QContent selected = m_selector->currentDocument();
	if (selected.isNull()) {
		m_sync->setEnabled(false);
	} else {
		m_sync->setEnabled(true);
	}
}

void SyncZilla::setDocument(const QString &fileName)
{
	QContent doc(fileName);
	editProfile(doc);
}
