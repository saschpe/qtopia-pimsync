#include "configscreen.h"
#include "syncprofile.h"

#include <QtGui>
#include <QtXml>
#include <QSoftMenuBar>

ConfigScreen::ConfigScreen(QWidget *parent)
	: QTabWidget(parent)
{
	m_name = new QLineEdit(tr("New profile"), this);
	m_comment = new QTextEdit(tr("Enter comment here"), this);
	m_protocol = new QComboBox(this);
	m_protocol->addItem(tr("SyncML"));
	m_contacts = new QCheckBox(tr("Contacts"), this);
	m_contactsDate = new QLabel(this);
	m_contactsUrl = new QLineEdit(this);
	m_tasks = new QCheckBox(tr("Tasks"), this);
	m_tasksDate = new QLabel(this);
	m_tasksUrl = new QLineEdit(this);
	m_appointments = new QCheckBox(tr("Appointments"), this);
	m_appointmentsDate = new QLabel(this);
	m_appointmentsUrl = new QLineEdit(this);
	m_mode = new QComboBox(this);
	m_mode->addItem(tr("Slow"));
	m_mode->addItem(tr("Two way"));
	m_mode->addItem(tr("One way from client"));
	m_mode->addItem(tr("One way from server"));
	m_mode->addItem(tr("Refresh from client"));
	m_mode->addItem(tr("Refresh from server"));
	m_transportType = new QComboBox(this);
	m_transportType->addItem(tr("Http"));
	m_transportType->addItem(tr("Bluetooth"));
	m_transportUserName = new QLineEdit(this);
	m_transportPassword = new QLineEdit(this);
	m_transportPassword->setEchoMode(QLineEdit::Password);
	m_transportUrl = new QTextEdit(this);

	QGridLayout *profileLayout = new QGridLayout();
	profileLayout->addWidget(new QLabel(tr("Name:")), 0, 0);
	profileLayout->addWidget(m_name, 0, 1);
	profileLayout->addWidget(new QLabel(tr("Type:")), 1, 0);
	profileLayout->addWidget(m_protocol, 1, 1);
	profileLayout->addWidget(m_comment, 2, 0, 1, 3);
	QWidget *profileTab = new QWidget();
	profileTab->setLayout(profileLayout);

	QGridLayout *syncLayout = new QGridLayout();
	syncLayout->addWidget(new QLabel(tr("Mode:")), 0, 0);
	syncLayout->addWidget(m_mode, 0, 1, 1, 2);
	syncLayout->addWidget(m_contacts, 1, 0, 1, 2);
	syncLayout->addWidget(m_contactsUrl, 1, 2);
	syncLayout->addWidget(m_contactsDate, 2, 1, 1, 2);
	syncLayout->addWidget(m_tasks, 3, 0, 1, 2);
	syncLayout->addWidget(m_tasksUrl, 3, 2);
	syncLayout->addWidget(m_tasksDate, 4, 1, 1, 2);
	syncLayout->addWidget(m_appointments, 5, 0, 1, 2);
	syncLayout->addWidget(m_appointmentsUrl, 5, 2);
	syncLayout->addWidget(m_appointmentsDate, 6, 1, 1, 2);
	QWidget *syncTab = new QWidget();
	syncTab->setLayout(syncLayout);

	QGridLayout *transportLayout = new QGridLayout();
	transportLayout->addWidget(new QLabel(tr("Type:")), 0, 0);
	transportLayout->addWidget(m_transportType, 0, 1);
	transportLayout->addWidget(new QLabel(tr("Username:")), 1, 0);
	transportLayout->addWidget(m_transportUserName, 1, 1);
	transportLayout->addWidget(new QLabel(tr("Password:")), 2, 0);
	transportLayout->addWidget(m_transportPassword, 2, 1);
	transportLayout->addWidget(new QLabel(tr("Url:")), 3, 0);
	transportLayout->addWidget(m_transportUrl, 3, 1);
	QWidget *transportTab = new QWidget();
	transportTab->setLayout(transportLayout);

	addTab(profileTab, tr("Profile"));
	addTab(syncTab, tr("Sync"));
	addTab(transportTab, tr("Transport"));
	QSoftMenuBar::menuFor(this);
}

void ConfigScreen::setProfile(SyncProfile *profile)
{
	m_profile = profile;

	m_name->setText(m_profile->name());
	m_comment->setText(m_profile->comment());
	if (m_profile->protocol() == SyncProfile::SyncML)
		m_protocol->setCurrentIndex(m_protocol->findText(tr("SyncML")));

	if (m_profile->mode() == SyncProfile::Slow)
		m_mode->setCurrentIndex(m_mode->findText(tr("Slow")));
	else if(m_profile->mode() == SyncProfile::TwoWay)
		m_mode->setCurrentIndex(m_mode->findText(tr("Two way")));
	else if(m_profile->mode() == SyncProfile::OneWayFromServer)
		m_mode->setCurrentIndex(m_mode->findText(tr("One way from server")));
	else if(m_profile->mode() == SyncProfile::OneWayFromClient)
		m_mode->setCurrentIndex(m_mode->findText(tr("One way from client")));
	else if(m_profile->mode() == SyncProfile::RefreshFromServer)
		m_mode->setCurrentIndex(m_mode->findText(tr("Refresh from server")));
	else if(m_profile->mode() == SyncProfile::RefreshFromClient)
		m_mode->setCurrentIndex(m_mode->findText(tr("Refresh from client")));

	m_contacts->setChecked(m_profile->contactsEnabled());
	m_contactsDate->setText(QDateTime::fromTime_t(m_profile->contactsLastSync()).toString(Qt::LocaleDate));
	m_contactsUrl->setText(m_profile->contactsUrl());
	
	m_tasks->setChecked(m_profile->tasksEnabled());
	m_tasksDate->setText(QDateTime::fromTime_t(m_profile->tasksLastSync()).toString(Qt::LocaleDate));
	m_tasksUrl->setText(m_profile->tasksUrl());
	
	m_appointments->setChecked(m_profile->appointmentsEnabled());
	m_appointmentsDate->setText(QDateTime::fromTime_t(m_profile->appointmentsLastSync()).toString(Qt::LocaleDate));
	m_appointmentsUrl->setText(m_profile->appointmentsUrl());

	if (m_profile->transportType() == SyncProfile::Http)
		m_transportType->setCurrentIndex(m_transportType->findText(tr("Http")));
	else if (m_profile->transportType() == SyncProfile::Bluetooth)
		m_transportType->setCurrentIndex(m_transportType->findText(tr("Bluetooth")));
	m_transportUserName->setText(m_profile->transportUser());
	m_transportPassword->setText(m_profile->transportPassword());
	m_transportUrl->setText(m_profile->transportUrl());

	setCurrentIndex(1);
}

void ConfigScreen::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Back) {

		m_profile->setName(m_name->text());
		m_profile->setComment(m_comment->toPlainText());
		if (m_protocol->currentText() == "SyncML")
			m_profile->setProtocol(SyncProfile::SyncML);

		if (m_mode->currentText() == "Slow")
			m_profile->setMode(SyncProfile::Slow);
		else if (m_mode->currentText() == "Two way")
			m_profile->setMode(SyncProfile::TwoWay);
		else if (m_mode->currentText() == "One way from server")
			m_profile->setMode(SyncProfile::OneWayFromServer);
		else if (m_mode->currentText() == "One way from client")
			m_profile->setMode(SyncProfile::OneWayFromClient);
		else if (m_mode->currentText() == "Refresh from server")
			m_profile->setMode(SyncProfile::RefreshFromServer);
		else if (m_mode->currentText() == "Refresh from client")
			m_profile->setMode(SyncProfile::RefreshFromClient);

		m_profile->setContactsEnabled(m_contacts->isChecked());
		m_profile->setContactsUrl(m_contactsUrl->text());
		m_profile->setTasksEnabled(m_tasks->isChecked());
		m_profile->setTasksUrl(m_tasksUrl->text());
		m_profile->setAppointmentsEnabled(m_appointments->isChecked());
		m_profile->setAppointmentsUrl(m_appointmentsUrl->text());
		if (m_transportType->currentText() == "Http")
			m_profile->setTransportType(SyncProfile::Http);
		else if (m_transportType->currentText() == "Bluetooth")
			m_profile->setTransportType(SyncProfile::Bluetooth);
		m_profile->setTransportUser(m_transportUserName->text());
		m_profile->setTransportPassword(m_transportPassword->text());
		m_profile->setTransportUrl(m_transportUrl->toPlainText());

		if (!m_profile->save()) {
			QMessageBox::critical(this, tr("Error"), 
					tr("Unable to save profile: %1").arg(m_profile->name()),
					QMessageBox::Ok, QMessageBox::Ok);
		}
	}
	QTabWidget::keyPressEvent(event);
}
