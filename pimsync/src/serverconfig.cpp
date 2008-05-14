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

#include <QBuffer>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class ServerConfigXmlReader : public QXmlStreamReader
{
public:
	ServerConfigXmlReader(ServerConfig *parent) : m_parent(parent) {}
	bool read(QIODevice *device);

private:
	void readSource();
	void readTransport();
	void readUnkownElement();

	ServerConfig *m_parent;
};

bool ServerConfigXmlReader::read(QIODevice *device)
{
	setDevice(device);

	while (!atEnd()) {
		readNext();
		
		if (isStartElement()) {
			if (name() == "pimsync-serverconfig") /*&& attributes().value("version") == "1.0")*/ {
				while (!atEnd()) {
					readNext();

					if (isEndElement())
						break;
					if (isStartElement()) {
						if (name() == "name") {
							QString name = readElementText();
							if (!name.isEmpty())
								m_parent->setName(name);

						} else if (name() == "comment") {
							QString comment = readElementText();
							if (!comment.isEmpty())
								m_parent->setComment(comment);

						} else if (name() == "mode") {
							QString mode = readElementText();

							if (mode == "slow")
								m_parent->setMode(ServerConfig::Slow);
							else if (mode == "two-way")
								m_parent->setMode(ServerConfig::TwoWay);
							else if (mode == "one-way-from-server")
								m_parent->setMode(ServerConfig::OneWayFromServer);
							else if (mode == "one-way-from-client")
								m_parent->setMode(ServerConfig::OneWayFromClient);
							else if (mode == "refresh-from-server")
								m_parent->setMode(ServerConfig::RefreshFromServer);
							else if (mode == "refresh-from-client")
								m_parent->setMode(ServerConfig::RefreshFromClient);

						} else if (name() == "source") {
							readSource();
						} else if (name() == "transport") {
							readTransport();
						} else
							readUnkownElement();
					}
				}
			} else
				raiseError(QObject::tr("The file is not a server configuration file."));
		}
	}
	return !error();
}

void ServerConfigXmlReader::readSource()
{
	Q_ASSERT(isStartElement() && name() == "source");

	QString type = attributes().value("type").toString(); 
	ServerConfig::Source source;
	if (type.toLower() == "contacts")			source = ServerConfig::Contacts;
	else if (type.toLower() == "tasks")			source = ServerConfig::Tasks;
	else if (type.toLower() == "appointments")	source = ServerConfig::Appointments;
	else if (type.toLower() == "notes")			source = ServerConfig::Notes;
	else 
		return;

	while (!atEnd()) {
		readNext();

		if (isEndElement())
			break;
		if (isStartElement()) {
			if (name() == "enabled") {
				QString enabled = readElementText();
				if (!enabled.isEmpty())
					m_parent->setSourceEnabled(source, enabled == "1" ? true : false);
			} else if (name() == "timestamp") {
				QString timeStamp = readElementText();
				if (!timeStamp.isEmpty())
					m_parent->setSourceLastSync(source, timeStamp.toUInt());
			} else if (name() == "url") {
				QString url = readElementText();
				if (!url.isEmpty())
					m_parent->setSourceUrl(source, url);
			}
		}
	}
}

void ServerConfigXmlReader::readTransport()
{
	Q_ASSERT(isStartElement() && name() == "transport");

	QString type = attributes().value("type").toString();

	while (!atEnd()) {
		readNext();

		if (isEndElement())
			break;
		if (isStartElement()) {
			if (name() == "username") {
				QString user = readElementText();
				if (!user.isEmpty())
					m_parent->setTransportUser(user);
			} else if (name() == "password") {
				QString password = readElementText();
				if (!password.isEmpty())
					m_parent->setTransportPassword(password);
			} else if (name() == "url") {
				QString url = readElementText();
				if (!url.isEmpty())
					m_parent->setTransportUrl(url);
			}
		}
	}
}

void ServerConfigXmlReader::readUnkownElement()
{
	Q_ASSERT(isStartElement());

	while (!atEnd()) {
		readNext();

		if (isEndElement())
			break;
		if (isStartElement())
			readUnkownElement();
	}
}


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
	ServerConfigXmlReader xmlsr(this);

	QIODevice *device = m_currentProfile.open();
	xmlsr.read(device);
	device->close();
	delete device;

	m_saved = false;
	return true;
}

bool ServerConfig::save()
{
	QBuffer buffer;
	QXmlStreamWriter xmlsw;
	xmlsw.setDevice(&buffer);
	xmlsw.setAutoFormatting(true);

	xmlsw.writeStartDocument();
	xmlsw.writeStartElement("pimsync-serverconfig");
	xmlsw.writeAttribute("version", "1.0");

	xmlsw.writeTextElement("name", m_name);
	xmlsw.writeTextElement("comment", m_comment);
	QString mode;
	if (m_mode == Slow)						mode = "slow";
	else if (m_mode == TwoWay)				mode = "two-way";
	else if (m_mode == OneWayFromServer)	mode = "one-way-from-server";
	else if (m_mode == OneWayFromClient)	mode = "one-way-from-client";
	else if (m_mode == RefreshFromServer)	mode = "refresh-from-server";
	else if (m_mode == RefreshFromClient)	mode = "refresh-from-client";
	else									mode = "slow";
	xmlsw.writeTextElement("mode", mode);

	xmlsw.writeStartElement("source");
	xmlsw.writeAttribute("type", "contacts");
	xmlsw.writeTextElement("enabled", m_contactsEnabled ? "1" : "0");
	xmlsw.writeTextElement("timestamp", QString::number(m_contactsLastSync));
	xmlsw.writeTextElement("url", m_contactsUrl);
	xmlsw.writeEndElement();

	xmlsw.writeStartElement("source");
	xmlsw.writeAttribute("type", "tasks");
	xmlsw.writeTextElement("enabled", m_tasksEnabled ? "1" : "0");
	xmlsw.writeTextElement("timestamp", QString::number(m_tasksLastSync));
	xmlsw.writeTextElement("url", m_tasksUrl);
	xmlsw.writeEndElement();

	xmlsw.writeStartElement("source");
	xmlsw.writeAttribute("type", "appointments");
	xmlsw.writeTextElement("enabled", m_appointmentsEnabled ? "1" : "0");
	xmlsw.writeTextElement("timestamp", QString::number(m_appointmentsLastSync));
	xmlsw.writeTextElement("url", m_appointmentsUrl);
	xmlsw.writeEndElement();

	xmlsw.writeStartElement("source");
	xmlsw.writeAttribute("type", "notes");
	xmlsw.writeTextElement("enabled", m_notesEnabled ? "1" : "0");
	xmlsw.writeTextElement("timestamp", QString::number(m_notesLastSync));
	xmlsw.writeTextElement("url", m_notesUrl);
	xmlsw.writeEndElement();

	xmlsw.writeStartElement("transport");
	xmlsw.writeAttribute("type", "http");
	xmlsw.writeTextElement("username", m_transportUser);
	xmlsw.writeTextElement("password", m_transportPassword);
	xmlsw.writeTextElement("url", m_transportUrl);
	xmlsw.writeEndElement();

	xmlsw.writeEndDocument();

	m_currentProfile.setType("application/vnd.trolltech-qsp-xml");
	m_currentProfile.setName(m_name);
	if (!m_currentProfile.save(buffer.data()))
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

void ServerConfig::setSourceEnabled(Source source, bool enabled)
{
	m_saved = false;
	if (source == Contacts)
		m_contactsEnabled = enabled;
	else if (source == Tasks)
		m_tasksEnabled = enabled;
	else if (source == Appointments)
		m_appointmentsEnabled = enabled;
	else if (source == Notes)
		m_notesEnabled = enabled;
}

bool ServerConfig::sourceEnabled(Source source) const
{
	if (source == Contacts)
		return m_contactsEnabled;
	else if (source == Tasks)
		return m_tasksEnabled;
	else if (source == Appointments)
		return m_appointmentsEnabled;
	else if (source == Notes)
		return m_notesEnabled;
	else 
		return false;
}

void ServerConfig::setSourceLastSync(Source source, unsigned int timeStamp)
{
	m_saved = false;
	if (source == Contacts)
		m_contactsLastSync = timeStamp;
	else if (source == Tasks)
		m_tasksLastSync = timeStamp;
	else if (source == Appointments)
		m_appointmentsLastSync = timeStamp;
	else if (source == Notes)
		m_notesLastSync = timeStamp;
}

unsigned int ServerConfig::sourceLastSync(Source source) const
{
	if (source == Contacts)
		return m_contactsLastSync;
	else if (source == Tasks)
		return m_tasksLastSync;
	else if (source == Appointments)
		return m_appointmentsLastSync;
	else if (source == Notes)
		return m_notesLastSync;
	else 
		return -1;
}

void ServerConfig::setSourceUrl(Source source, const QString &url)
{
	m_saved = false;
	if (source == Contacts)
		m_contactsUrl = url;
	else if (source == Tasks)
		m_tasksUrl = url;
	else if (source == Appointments)
		m_appointmentsUrl = url;
	else if (source == Notes)
		m_notesUrl = url;
}

QString ServerConfig::sourceUrl(Source source) const
{
	if (source == Contacts)
		return m_contactsUrl;
	else if (source == Tasks)
		return m_tasksUrl;
	else if (source == Appointments)
		return m_appointmentsUrl;
	else if (source == Notes)
		return m_notesUrl;
	else 
		return QString();
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
