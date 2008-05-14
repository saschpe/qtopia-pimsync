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

#ifndef PIMSYNC_H
#define PIMSYNC_H

#include <QStackedWidget>

class QKeyEvent;
class QContent;
class QTextEdit;
class QDocumentSelector;
class QWaitWidget;
class ConfigScreen;
class QtopiaSyncClient;
class ServerConfig;
class SyncThread;

class PimSync : public QStackedWidget
{
	Q_OBJECT
	friend class SyncThread;
	
public:
	PimSync(QWidget *parent = 0, Qt::WindowFlags flags = 0);

protected:
	void keyPressEvent(QKeyEvent *event);

private slots:
	void setUp();

	void startSync();
	void finishSync(bool result);

public slots:
	void setDocument(const QString &fileName);

	void newProfile();
	void editProfile(const QContent &content);
	void addDefaultProfiles();

private:
	QDocumentSelector *mainScreen();
	ConfigScreen *configScreen();
	QTextEdit *logScreen();
	QtopiaSyncClient *syncClient();
	ServerConfig *profile();

	QDocumentSelector *m_mainScreen;
	ConfigScreen *m_configScreen;
	QTextEdit *m_logScreen;
	QtopiaSyncClient *m_syncClient;
	ServerConfig *m_profile;

	QWaitWidget *m_waitWidget;
	SyncThread *m_syncThread;
};

#endif
