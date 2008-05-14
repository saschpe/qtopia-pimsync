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

#include "configscreen.h"
#include "serverconfig.h"

#include <QtGui>
#include <QtXml>
#include <QSoftMenuBar>

ConfigScreen::ConfigScreen(QWidget *parent)
	: QTabWidget(parent)
{
	m_name = new QLineEdit(tr("New profile"), this);
	m_comment = new QTextEdit(tr("Enter comment here"), this);
	m_sync = new QPushButton(tr("Start sync"), this);
	connect(m_sync, SIGNAL(clicked()), this, SLOT(slotSyncPressed()));

	m_mode = new QComboBox(this);
	m_mode->addItem(tr("Slow"));
	m_mode->addItem(tr("Two way"));
	m_mode->addItem(tr("One way from client"));
	m_mode->addItem(tr("One way from server"));
	m_mode->addItem(tr("Refresh from client"));
	m_mode->addItem(tr("Refresh from server"));
	m_contacts = new QCheckBox(tr("Contacts"), this);
	m_contactsUrl = new QLineEdit(this);
	m_tasks = new QCheckBox(tr("Tasks"), this);
	m_tasksUrl = new QLineEdit(this);
	m_appointments = new QCheckBox(tr("Appointments"), this);
	m_appointmentsUrl = new QLineEdit(this);
	m_notes = new QCheckBox(tr("Notes"), this);
	// TODO: Enable notes checkbox and lineedit if Qtopia supports QNoteModel:
	m_notes->setEnabled(false);
	m_notesUrl = new QLineEdit(this);
	m_notesUrl->setEnabled(false);

	m_transportUserName = new QLineEdit(this);
	m_transportPassword = new QLineEdit(this);
	m_transportPassword->setEchoMode(QLineEdit::Password);
	m_transportUrl = new QTextEdit(this);

	QGridLayout *profileLayout = new QGridLayout();
	profileLayout->addWidget(new QLabel(tr("Name:")), 0, 0);
	profileLayout->addWidget(m_name, 0, 1);
	profileLayout->addWidget(m_comment, 2, 0, 1, 3);
	profileLayout->addWidget(m_sync, 3, 0, 1, 3);
	QWidget *profileTab = new QWidget();
	profileTab->setLayout(profileLayout);

	QGridLayout *syncLayout = new QGridLayout();
	syncLayout->addWidget(new QLabel(tr("Mode:")), 0, 0);
	syncLayout->addWidget(m_mode, 0, 1, 1, 2);
	syncLayout->addWidget(m_contacts, 1, 0, 1, 2);
	syncLayout->addWidget(m_contactsUrl, 1, 2);
	syncLayout->addWidget(m_tasks, 2, 0, 1, 2);
	syncLayout->addWidget(m_tasksUrl, 2, 2);
	syncLayout->addWidget(m_appointments, 3, 0, 1, 2);
	syncLayout->addWidget(m_appointmentsUrl, 3, 2);
	syncLayout->addWidget(m_notes, 4, 0, 1, 2);
	syncLayout->addWidget(m_notesUrl, 4, 2);
	QWidget *syncTab = new QWidget();
	syncTab->setLayout(syncLayout);

	QGridLayout *transportLayout = new QGridLayout();
	transportLayout->addWidget(new QLabel(tr("Username:")), 1, 0);
	transportLayout->addWidget(m_transportUserName, 1, 1);
	transportLayout->addWidget(new QLabel(tr("Password:")), 2, 0);
	transportLayout->addWidget(m_transportPassword, 2, 1);
	transportLayout->addWidget(new QLabel(tr("Server URL:")), 3, 0);
	transportLayout->addWidget(m_transportUrl, 4, 0, 1, 2);
	QWidget *transportTab = new QWidget();
	transportTab->setLayout(transportLayout);

	addTab(profileTab, tr("Profile"));
	addTab(syncTab, tr("Options"));
	addTab(transportTab, tr("Transport"));
	QSoftMenuBar::menuFor(this);
}

void ConfigScreen::setProfile(ServerConfig *profile)
{
	m_profile = profile;

	m_name->setText(m_profile->name());
	m_comment->setText(m_profile->comment());

	if (m_profile->mode() == ServerConfig::Slow)
		m_mode->setCurrentIndex(m_mode->findText(tr("Slow")));
	else if(m_profile->mode() == ServerConfig::TwoWay)
		m_mode->setCurrentIndex(m_mode->findText(tr("Two way")));
	else if(m_profile->mode() == ServerConfig::OneWayFromServer)
		m_mode->setCurrentIndex(m_mode->findText(tr("One way from server")));
	else if(m_profile->mode() == ServerConfig::OneWayFromClient)
		m_mode->setCurrentIndex(m_mode->findText(tr("One way from client")));
	else if(m_profile->mode() == ServerConfig::RefreshFromServer)
		m_mode->setCurrentIndex(m_mode->findText(tr("Refresh from server")));
	else if(m_profile->mode() == ServerConfig::RefreshFromClient)
		m_mode->setCurrentIndex(m_mode->findText(tr("Refresh from client")));

	m_contacts->setChecked(m_profile->contactsEnabled());
	m_contactsUrl->setText(m_profile->contactsUrl());
	m_tasks->setChecked(m_profile->tasksEnabled());
	m_tasksUrl->setText(m_profile->tasksUrl());
	m_appointments->setChecked(m_profile->appointmentsEnabled());
	m_appointmentsUrl->setText(m_profile->appointmentsUrl());
	m_notes->setChecked(m_profile->notesEnabled());
	m_notesUrl->setText(m_profile->notesUrl());

	m_transportUserName->setText(m_profile->transportUser());
	m_transportPassword->setText(m_profile->transportPassword());
	m_transportUrl->setText(m_profile->transportUrl());

	setCurrentIndex(0);
	m_sync->setFocus();
}

void ConfigScreen::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Back)
		saveProfile();
	QTabWidget::keyPressEvent(event);
}

void ConfigScreen::slotSyncPressed()
{
	saveProfile();
	emit syncPressed();
}

void ConfigScreen::saveProfile()
{
	m_profile->setName(m_name->text());
	m_profile->setComment(m_comment->toPlainText());

	if (m_mode->currentText() == "Slow")
		m_profile->setMode(ServerConfig::Slow);
	else if (m_mode->currentText() == "Two way")
		m_profile->setMode(ServerConfig::TwoWay);
	else if (m_mode->currentText() == "One way from server")
		m_profile->setMode(ServerConfig::OneWayFromServer);
	else if (m_mode->currentText() == "One way from client")
		m_profile->setMode(ServerConfig::OneWayFromClient);
	else if (m_mode->currentText() == "Refresh from server")
		m_profile->setMode(ServerConfig::RefreshFromServer);
	else if (m_mode->currentText() == "Refresh from client")
		m_profile->setMode(ServerConfig::RefreshFromClient);

	m_profile->setContactsEnabled(m_contacts->isChecked());
	m_profile->setContactsUrl(m_contactsUrl->text());
	m_profile->setTasksEnabled(m_tasks->isChecked());
	m_profile->setTasksUrl(m_tasksUrl->text());
	m_profile->setAppointmentsEnabled(m_appointments->isChecked());
	m_profile->setAppointmentsUrl(m_appointmentsUrl->text());
	m_profile->setNotesEnabled(m_notes->isChecked());
	m_profile->setNotesUrl(m_notesUrl->text());
	m_profile->setNotesEnabled(m_notes->isChecked());
	m_profile->setNotesUrl(m_notesUrl->text());
	m_profile->setTransportUser(m_transportUserName->text());
	m_profile->setTransportPassword(m_transportPassword->text());
	m_profile->setTransportUrl(m_transportUrl->toPlainText());

	if (!m_profile->save()) {
		QMessageBox::critical(this, tr("Error"), 
				tr("Unable to save profile: %1").arg(m_profile->name()),
				QMessageBox::Ok, QMessageBox::Ok);
	}
}
