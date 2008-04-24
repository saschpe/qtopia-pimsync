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

#ifndef CONFIGSCREEN_H
#define CONFIGSCREEN_H

#include <QTabWidget>
#include <QContent>

class SyncProfile;
class QLineEdit;
class QCheckBox;
class QComboBox;
class QTextEdit;
class QPushButton;

class ConfigScreen : public QTabWidget
{
	Q_OBJECT

public:
	ConfigScreen(QWidget *parent = 0);

	void setProfile(SyncProfile *profile);

signals:
	void syncPressed();

protected:
	void keyPressEvent(QKeyEvent *event);

private:
	void saveProfile();

	SyncProfile *m_profile;

	QLineEdit *m_name;
	QComboBox *m_protocol;
	QTextEdit *m_comment;
	QPushButton *m_sync;

	QComboBox *m_mode;
	QCheckBox *m_contacts;
	QLineEdit *m_contactsUrl;
	QCheckBox *m_tasks;
	QLineEdit *m_tasksUrl;
	QCheckBox *m_appointments;
	QLineEdit *m_appointmentsUrl;
	QCheckBox *m_notes;
	QLineEdit *m_notesUrl;

	QComboBox *m_transportType;
	QLineEdit *m_transportUserName;
	QLineEdit *m_transportPassword;	
	QTextEdit *m_transportUrl;
};

#endif // CONFIGSCREEN_H

