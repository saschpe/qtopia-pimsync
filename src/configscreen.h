#ifndef CONFIGSCREEN_H
#define CONFIGSCREEN_H

#include <QTabWidget>
#include <QContent>

class SyncProfile;
class QLabel;
class QLineEdit;
class QCheckBox;
class QComboBox;
class QTextEdit;

class ConfigScreen : public QTabWidget
{
	Q_OBJECT

public:
	ConfigScreen(QWidget *parent = 0);

	void setProfile(SyncProfile *profile);

protected:
	void keyPressEvent(QKeyEvent *event);

private:
	SyncProfile *m_profile;

	QLineEdit *m_name;
	QTextEdit *m_comment;
	QComboBox *m_protocol;
	QComboBox *m_mode;

	QCheckBox *m_contacts;
	QLabel    *m_contactsDate;
	QLineEdit *m_contactsUrl;

	QCheckBox *m_tasks;
	QLabel    *m_tasksDate;
	QLineEdit *m_tasksUrl;

	QCheckBox *m_appointments;
	QLabel    *m_appointmentsDate;
	QLineEdit *m_appointmentsUrl;

	QComboBox *m_transportType;
	QLineEdit *m_transportUserName;
	QLineEdit *m_transportPassword;	
	QTextEdit *m_transportUrl;
};

#endif // CONFIGSCREEN_H

