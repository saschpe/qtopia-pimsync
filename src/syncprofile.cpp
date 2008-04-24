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

#include "syncprofile.h"

#include <QtXml>

SyncProfile::SyncProfile()
	: m_saved(false)
	, m_fileName()
	, m_currentProfile()
{
}

SyncProfile::~SyncProfile()
{
	if (!m_saved)
		save();
}

void SyncProfile::newProfile()
{
	m_name = "New profile";
	m_comment = "Enter a comment here";
	m_protocol = SyncML;
	m_mode = TwoWay;
	m_contactsEnabled = true;
	m_contactsLastSync = 0;
	m_contactsUrl = "card";
	m_tasksEnabled = true;
	m_tasksLastSync = 0;
	m_tasksUrl = "task";
	m_appointmentsEnabled = true;
	m_appointmentsLastSync = 0;
	m_appointmentsUrl = "event";
	m_notesEnabled = false;
	m_notesLastSync = 0;
	m_notesUrl = "note";
	m_transportType = Http;
	m_transportUser = "guest";
	m_transportPassword = "guest";
	m_transportUrl = "http://localhost:8080/funambol/ds";
	m_saved = false;
	m_currentProfile = QContent();
}

/*void SyncProfile::load(const QString &name)
{
	qDebug() << "SyncProfile::load()" << name;
	QSettings settings("synczilla", name);
	QString tmp;

	m_name = settings.value("name").toString();
	m_comment = settings.value("comment").toString();
	tmp = settings.value("protocol").toString();
	if (tmp == "SyncML")
		m_protocol = SyncML;
	else
		m_protocol = SyncML;
	tmp = settings.value("mode").toString();
	if (tmp == "Slow")
		m_mode = Slow;
	else if (tmp == "TwoWay")
		m_mode = TwoWay;
	else if (tmp == "OneWayFromClient")
		m_mode = OneWayFromClient;
	else if (tmp == "OneWayFromServer")
		m_mode = OneWayFromServer;
	else if (tmp == "RefreshFromClient")
		m_mode = RefreshFromClient;
	else if (tmp == "RefreshFromServer")
		m_mode = RefreshFromServer;
	else
		m_mode = Slow;

	settings.beginGroup("Sources");
	m_contactsEnabled = settings.value("contacts.enabled").toString() == "true" ? true : false;
	m_contactsLastSync = settings.value("contacts.timestamp").toUInt();
	m_contactsUrl = settings.value("contacts.url").toString();
	m_tasksEnabled = settings.value("tasks.enabled").toString() == "true" ? true : false;
	m_tasksLastSync = settings.value("tasks.timestamp").toUInt();
	m_tasksUrl = settings.value("tasks.url").toString();
	m_appointmentsEnabled = settings.value("appointments.enabled").toString() == "true" ? true : false;
	m_appointmentsLastSync = settings.value("appointments.timestamp").toUInt();
	m_appointmentsUrl = settings.value("appointments.url").toString();
	m_notesEnabled = settings.value("notes.enabled").toString() == "true" ? true : false;
	m_notesLastSync = settings.value("notes.timestamp").toUInt();
	m_notesUrl = settings.value("notes.url").toString();
	settings.endGroup();

	settings.beginGroup("Transport");
	tmp = settings.value("type").toString();
	if (tmp == "Http")
		m_transportType = Http;
	else if (tmp == "Bluetooth")
		m_transportType = Bluetooth;
	else
		m_transportType = Http;
	m_transportUser = settings.value("user").toString();
	m_transportPassword = settings.value("password").toString();
	m_transportUrl = settings.value("url").toString();
	settings.endGroup();

	m_fileName = name;
	m_saved = false;
}*/

bool SyncProfile::load(const QContent &profile)
{
	m_currentProfile = profile;

	// TODO: Maybe switch to QXmlStreamreader for performance reasons

	QDomDocument dom;
	QFile *file = static_cast<QFile *>(m_currentProfile.open());
	if (!dom.setContent(file)) {
		file->close();
		return false;
	}
	file->close();
	delete file;

	QDomElement root = dom.firstChildElement("qtopiasyncprofile"); 
	if (root.isNull())
		return false;

	// Load profile settings
	QDomElement el = root.firstChildElement("name");
	if (!el.isNull() && el.text() == m_currentProfile.name())
		m_name = el.text();
	else
		m_name = m_currentProfile.name();

	el = root.firstChildElement("comment");
	if (!el.isNull()) {
		m_comment = el.text();
	}

	el = root.firstChildElement("protocol");
	if (!el.isNull()) {
		if (el.text() == "SyncML")
			m_protocol = SyncML;
		else
			m_protocol = SyncML;
	} else
		m_protocol = SyncML;

	QDomElement options = root.firstChildElement("options");

	el = options.firstChildElement("mode");
	if (!el.isNull()) {
		if (el.text() == "slow")
			m_mode = Slow;
		else if (el.text() == "two-way")
			m_mode = TwoWay;
		else if (el.text() == "one-way-from-server")
			m_mode = OneWayFromServer;
		else if (el.text() == "one-way-from-client")
			m_mode = OneWayFromClient;
		else if (el.text() == "refresh-from-server")
			m_mode = RefreshFromServer;
		else if (el.text() == "refresh-from-client")
			m_mode = RefreshFromClient;
		else
			m_mode = Slow;
	} else
		m_mode = Slow;

	QDomElement sources = options.firstChildElement("sources");
	
	QDomElement contacts = sources.firstChildElement("contacts");
	if (!contacts.isNull()) {
		if (contacts.firstChildElement("enabled").text() == "1")
			m_contactsEnabled = true;
		else
			m_contactsEnabled = false;
		m_contactsLastSync = contacts.firstChildElement("timestamp").text().toUInt();
		if (!contacts.firstChildElement("url").isNull())
			m_contactsUrl = contacts.firstChildElement("url").text();
		else
			m_contactsUrl = "card";
	}
	QDomElement tasks = sources.firstChildElement("tasks");
	if (!tasks.isNull()) {
		if (tasks.firstChildElement("enabled").text() == "1")
			m_tasksEnabled = true;
		else
			m_tasksEnabled = false;
		m_tasksLastSync = tasks.firstChildElement("timestamp").text().toUInt();
		if (!tasks.firstChildElement("url").isNull())
			m_tasksUrl = tasks.firstChildElement("url").text();
		else
			m_tasksUrl = "task";
	}
	QDomElement appointments = sources.firstChildElement("appointments");
	if (!appointments.isNull()) {
		if (appointments.firstChildElement("enabled").text() == "1")
			m_appointmentsEnabled = true;
		else
			m_appointmentsEnabled = false;
		m_appointmentsLastSync = appointments.firstChildElement("timestamp").text().toUInt();
		if (!appointments.firstChildElement("url").isNull())
			m_appointmentsUrl = appointments.firstChildElement("url").text();
		else
			m_appointmentsUrl = "event";
	}
	QDomElement notes = sources.firstChildElement("notes");
	if (!notes.isNull()) {
		if (notes.firstChildElement("enabled").text() == "1")
			m_notesEnabled = true;
		else
			m_notesEnabled = false;
		m_notesLastSync = notes.firstChildElement("timestamp").text().toUInt();
		if (!notes.firstChildElement("url").isNull())
			m_notesUrl = notes.firstChildElement("url").text();
		else
			m_notesUrl = "note";
	}

	// Load transport settings
	QDomElement transport = root.firstChildElement("transport");
	if (!transport.isNull()) {
		QDomElement type = transport.firstChildElement("type");
		if (type.text() == "http")
			m_transportType = Http;
		else if (type.text() == "bluetooth")
			m_transportType = Bluetooth;
		else
			m_transportType = Http;
		m_transportUser = transport.firstChildElement("username").text();
		m_transportPassword = transport.firstChildElement("password").text();
		m_transportUrl = transport.firstChildElement("url").text();
	} else {
		m_transportType = Http;
		m_transportUser = "guest";
		m_transportPassword = "guest";
		m_transportUrl = "http://localhost:8080/funambol/ds";
	}

	m_saved = false;
	return true;
}

bool SyncProfile::save()
{
	QString protocol;
	if (m_protocol == SyncML)
		protocol = "SyncML";

	QString mode;
	if (m_mode == Slow)
		mode = "slow";
	else if (m_mode == TwoWay)
		mode = "two-way";
	else if (m_mode == OneWayFromServer)
		mode = "one-way-from-server";
	else if (m_mode == OneWayFromClient)
		mode = "one-way-from-client";
	else if (m_mode == RefreshFromServer)
		mode = "refresh-from-server";
	else if (m_mode == RefreshFromClient)
		mode = "refresh-from-client";
	else
		mode = "slow";

	QString transport;
	if (m_transportType == Http)
		transport = "http";
	else if (m_transportType == Bluetooth)
		transport = "bluetooth";
	else
		transport = "http";

	// TODO: encoding in base64 would be nice

	QString xml = \
			"<?xml version=\"1.0\"?>\n" \
			"<qtopiasyncprofile version=\"1.0\">\n" \
			"  <name>" + m_name + "</name>\n" \
			"  <comment>" + m_comment + "</comment>\n" \
			"  <protocol>" + protocol + "</protocol>\n" \
			"  <options>\n" \
			"    <mode>" + mode + "</mode>\n" \
			"    <sources>\n" \
			"      <contacts>\n" \
			"        <enabled>";
	xml.append(m_contactsEnabled ? "1" : "0");
	xml.append("</enabled>\n" \
			"        <timestamp>" + QString::number(m_contactsLastSync) + "</timestamp>\n" \
			"        <url>" + m_contactsUrl + "</url>\n" \
			"      </contacts>\n" \
			"      <tasks>\n" \
			"        <enabled>");
	xml.append(m_tasksEnabled ? "1" : "0");
	xml.append("</enabled>\n" \
			"        <timestamp>" + QString::number(m_tasksLastSync) + "</timestamp>\n" \
			"        <url>" + m_tasksUrl + "</url>\n" \
			"      </tasks>\n" \
			"      <appointments>\n" \
			"        <enabled>");
	xml.append(m_appointmentsEnabled ? "1" : "0");
	xml.append("</enabled>\n" \
			"        <timestamp>" + QString::number(m_appointmentsLastSync) + "</timestamp>\n" \
			"        <url>" + m_appointmentsUrl + "</url>\n" \
			"      </appointments>\n" \
			"      <notes>\n" \
			"        <enabled>");
	xml.append(m_notesEnabled ? "1" : "0");
	xml.append("</enabled>\n" \
			"        <timestamp>" + QString::number(m_notesLastSync) + "</timestamp>\n" \
			"        <url>" + m_notesUrl + "</url>\n" \
			"      </notes>\n" \
			"    </sources>\n" \
			"  </options>\n" \
			"  <transport>\n" \
			"    <type>" + transport + "</type>\n" \
			"    <username>" + m_transportUser + "</username>\n" \
			"    <password>" + m_transportPassword + "</password>\n" \
			"    <url>" + m_transportUrl + "</url>\n" \
			"  </transport>\n" \
			"</qtopiasyncprofile>\n");

	m_currentProfile.setType("application/vnd.trolltech-qsp-xml");
	m_currentProfile.setName(m_name);
	if (!m_currentProfile.save(xml.toAscii()))
		return false;
	if (!m_currentProfile.commit())
		return false;
	m_saved = true;
	return true;
}

void SyncProfile::setName(const QString &name)
{
	m_saved = false;
	m_name = name;
}

void SyncProfile::setComment(const QString &comment)
{
	m_saved = false;
	m_comment = comment;
}

void SyncProfile::setProtocol(Protocol protocol)
{
	m_saved = false;
	m_protocol = protocol;
}

void SyncProfile::setMode(Mode mode)
{
	m_saved = false;
	m_mode = mode;
}

void SyncProfile::setContactsEnabled(bool enabled)
{
	m_saved = false;
	m_contactsEnabled = enabled;
}

void SyncProfile::setContactsLastSync(unsigned int timeStamp)
{
	m_saved = false;
	m_contactsLastSync = timeStamp;
}

void SyncProfile::setContactsUrl(const QString &url)
{
	m_saved = false;
	m_contactsUrl = url;
}

void SyncProfile::setTasksEnabled(bool enabled)
{
	m_saved = false;
	m_tasksEnabled = enabled;
}

void SyncProfile::setTasksLastSync(unsigned int timeStamp)
{
	m_saved = false;
	m_tasksLastSync = timeStamp;
}

void SyncProfile::setTasksUrl(const QString &url)
{
	m_saved = false;
	m_tasksUrl = url;
}

void SyncProfile::setAppointmentsEnabled(bool enabled)
{
	m_saved = false;
	m_appointmentsEnabled = enabled;
}

void SyncProfile::setAppointmentsLastSync(unsigned int timeStamp)
{
	m_saved = false;
	m_appointmentsLastSync = timeStamp;
}

void SyncProfile::setAppointmentsUrl(const QString &url)
{
	m_saved = false;
	m_appointmentsUrl = url;
}

void SyncProfile::setNotesEnabled(bool enabled)
{
	m_saved = false;
	m_notesEnabled = enabled;
}

void SyncProfile::setNotesLastSync(unsigned int timeStamp)
{
	m_saved = false;
	m_notesLastSync = timeStamp;
}

void SyncProfile::setNotesUrl(const QString &url)
{
	m_saved = false;
	m_notesUrl = url;
}

void SyncProfile::setTransportType(Transport transport)
{
	m_saved = false;
	m_transportType = transport;
}

void SyncProfile::setTransportUser(const QString &userName)
{
	m_saved = false;
	m_transportUser = userName;
}

void SyncProfile::setTransportPassword(const QString &password)
{
	m_saved = false;
	m_transportPassword = password;
}

void SyncProfile::setTransportUrl(const QString &url)
{
	m_saved = false;
	m_transportUrl = url;
}
