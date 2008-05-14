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

#include "serverconfig.h"

#include <QtXml>

ServerConfig::ServerConfig()
	: m_saved(false)
	, m_currentProfile()
{
}

ServerConfig::~ServerConfig()
{
	if (!m_saved)
		save();
}

void ServerConfig::newProfile()
{
	m_name = "New profile";
	m_comment = "Enter a comment here";
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
	m_transportUser = "guest";
	m_transportPassword = "guest";
	m_transportUrl = "http://localhost:8080/funambol/ds";

	m_saved = false;
	m_currentProfile = QContent();
}

bool ServerConfig::load(const QContent &profile)
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
		m_transportUser = transport.firstChildElement("username").text();
		m_transportPassword = transport.firstChildElement("password").text();
		m_transportUrl = transport.firstChildElement("url").text();
	} else {
		m_transportUser = "guest";
		m_transportPassword = "guest";
		m_transportUrl = "http://localhost:8080/funambol/ds";
	}

	m_saved = false;
	return true;
}

bool ServerConfig::save()
{
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

	// TODO: Encoding in base64 would be nice

	QString xml = \
			"<?xml version=\"1.0\"?>\n" \
			"<qtopiasyncprofile version=\"1.0\">\n" \
			"  <name>" + m_name + "</name>\n" \
			"  <comment>" + m_comment + "</comment>\n" \
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

void ServerConfig::setName(const QString &name)
{
	m_saved = false;
	m_name = name;
}

void ServerConfig::setComment(const QString &comment)
{
	m_saved = false;
	m_comment = comment;
}

void ServerConfig::setMode(Mode mode)
{
	m_saved = false;
	m_mode = mode;
}

void ServerConfig::setContactsEnabled(bool enabled)
{
	m_saved = false;
	m_contactsEnabled = enabled;
}

void ServerConfig::setContactsLastSync(unsigned int timeStamp)
{
	m_saved = false;
	m_contactsLastSync = timeStamp;
}

void ServerConfig::setContactsUrl(const QString &url)
{
	m_saved = false;
	m_contactsUrl = url;
}

void ServerConfig::setTasksEnabled(bool enabled)
{
	m_saved = false;
	m_tasksEnabled = enabled;
}

void ServerConfig::setTasksLastSync(unsigned int timeStamp)
{
	m_saved = false;
	m_tasksLastSync = timeStamp;
}

void ServerConfig::setTasksUrl(const QString &url)
{
	m_saved = false;
	m_tasksUrl = url;
}

void ServerConfig::setAppointmentsEnabled(bool enabled)
{
	m_saved = false;
	m_appointmentsEnabled = enabled;
}

void ServerConfig::setAppointmentsLastSync(unsigned int timeStamp)
{
	m_saved = false;
	m_appointmentsLastSync = timeStamp;
}

void ServerConfig::setAppointmentsUrl(const QString &url)
{
	m_saved = false;
	m_appointmentsUrl = url;
}

void ServerConfig::setNotesEnabled(bool enabled)
{
	m_saved = false;
	m_notesEnabled = enabled;
}

void ServerConfig::setNotesLastSync(unsigned int timeStamp)
{
	m_saved = false;
	m_notesLastSync = timeStamp;
}

void ServerConfig::setNotesUrl(const QString &url)
{
	m_saved = false;
	m_notesUrl = url;
}

void ServerConfig::setTransportUser(const QString &userName)
{
	m_saved = false;
	m_transportUser = userName;
}

void ServerConfig::setTransportPassword(const QString &password)
{
	m_saved = false;
	m_transportPassword = password;
}

void ServerConfig::setTransportUrl(const QString &url)
{
	m_saved = false;
	m_transportUrl = url;
}
