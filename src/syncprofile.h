#ifndef SYNCPROFILE_H
#define SYNCPROFILE_H

#include <QString>
#include <QContent>

/*!
 * Responsible for accessing a sync profile.
 */
class SyncProfile
{
public:
	enum Protocol {
		SyncML = 0x0,
	};

	enum Mode {
		Slow = 0x0,
		TwoWay = 0x1,
		OneWayFromServer = 0x2,
		OneWayFromClient = 0x3,
		RefreshFromServer = 0x4,
		RefreshFromClient = 0x5,
	};

	enum Transport {
		Http = 0x0,
		Bluetooth = 0x1,
	};

	SyncProfile();
	virtual ~SyncProfile();

	void newProfile();
	bool load(const QContent &profile);
	bool save();
	bool isSaved() const { return m_saved; }

	void setName(const QString &name);
	QString name() const { return m_name; }

	void setComment(const QString &comment);
	QString comment() const { return m_comment; }

	void setProtocol(Protocol protocol);
	Protocol protocol() const { return m_protocol; }

	void setMode(Mode mode);
	Mode mode() const { return m_mode; }
	
	void setContactsEnabled(bool enabled);
	bool contactsEnabled() const { return m_contactsEnabled; }

	void setContactsLastSync(unsigned int timeStamp);
	unsigned int contactsLastSync() const { return m_contactsLastSync; }

	void setContactsUrl(const QString &url);
	QString contactsUrl() const { return m_contactsUrl; }

	void setTasksEnabled(bool enabled);
	bool tasksEnabled() const { return m_tasksEnabled; }

	void setTasksLastSync(unsigned int timeStamp);
	unsigned int tasksLastSync() const { return m_tasksLastSync; }

	void setTasksUrl(const QString &url);
	QString tasksUrl() const { return m_tasksUrl; }

	void setAppointmentsEnabled(bool enabled);
	bool appointmentsEnabled() const { return m_appointmentsEnabled; }

	void setAppointmentsLastSync(unsigned int timeStamp);
	unsigned int appointmentsLastSync() const { return m_appointmentsLastSync; }

	void setAppointmentsUrl(const QString &url);
	QString appointmentsUrl() const { return m_appointmentsUrl; }

	void setTransportType(Transport transport);
	Transport transportType() const { return m_transportType; }

	void setTransportUser(const QString &user);
	QString transportUser() const { return m_transportUser; }

	void setTransportPassword(const QString &password);
	QString transportPassword() const { return m_transportPassword; }

	void setTransportUrl(const QString &url);
	QString transportUrl() const { return m_transportUrl; }

private:
	bool m_saved;
	QContent m_currentProfile;

	QString m_name;
	QString m_comment;
	Protocol m_protocol;
	Mode m_mode;

	bool m_contactsEnabled;
	unsigned int m_contactsLastSync;
	QString m_contactsUrl;

	bool m_tasksEnabled;
	unsigned int m_tasksLastSync;
	QString m_tasksUrl;

	bool m_appointmentsEnabled;
	unsigned int m_appointmentsLastSync;
	QString m_appointmentsUrl;

	Transport m_transportType;
	QString m_transportUser;
	QString m_transportPassword;
	QString m_transportUrl;
};

#endif // SYNCPROFILE_H
