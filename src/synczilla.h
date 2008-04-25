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

#ifndef SYNCZILLA_H
#define SYNCZILLA_H

#include <QStackedWidget>

class ConfigScreen;
class QtopiaSyncClient;
class SyncProfile;
class QKeyEvent;
class QContent;
class QTextEdit;
class QDocumentSelector;

class SyncZilla : public QStackedWidget
{
	Q_OBJECT
	
public:
	SyncZilla(QWidget *parent = 0, Qt::WindowFlags flags = 0);

protected:
	void keyPressEvent(QKeyEvent *event);

private slots:
	void sync();
	void newProfile();
	void editProfile(const QContent &content);
	void createDefaultProfiles();

public slots:
	void setDocument(const QString &fileName);

private:
	QDocumentSelector *mainScreen();
	ConfigScreen *configScreen();
	QTextEdit *logScreen();
	QtopiaSyncClient *syncClient();
	SyncProfile *profile();

	QDocumentSelector *m_mainScreen;
	ConfigScreen *m_configScreen;
	QTextEdit *m_logScreen;
	QtopiaSyncClient *m_syncClient;
	SyncProfile *m_profile;
};

#endif // SYNCZILLA_H
