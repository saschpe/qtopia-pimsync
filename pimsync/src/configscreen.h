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

#ifndef CONFIGSCREEN_H
#define CONFIGSCREEN_H

#include <QTabWidget>
#include <QContent>

class QLineEdit;
class QCheckBox;
class QComboBox;
class QTextEdit;
class QPushButton;
class ServerConfig;

class ConfigScreen : public QTabWidget
{
	Q_OBJECT

public:
	ConfigScreen(QWidget *parent = 0);

	void setProfile(ServerConfig *profile);

signals:
	void syncPressed();

protected:
	void keyPressEvent(QKeyEvent *event);

private slots:
	void slotSyncPressed();

private:
	void saveProfile();

	ServerConfig *m_profile;

	QLineEdit *m_name;
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

	QLineEdit *m_transportUserName;
	QLineEdit *m_transportPassword;	
	QTextEdit *m_transportUrl;
};

#endif
