#ifndef SYNCZILLA_H
#define SYNCZILLA_H

#include <QStackedWidget>

class ConfigScreen;
class QtopiaSyncClient;
class SyncProfile;
class QKeyEvent;
class QContent;
class QTextEdit;
class QPushButton;
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
	void selectionChanged();

private:
	QWidget *mainScreen();
	ConfigScreen *configScreen();
	QTextEdit *logScreen();
	QtopiaSyncClient *syncClient();
	SyncProfile *profile();

	QWidget *m_mainScreen;
	ConfigScreen *m_configScreen;
	QTextEdit *m_logScreen;
	QtopiaSyncClient *m_syncClient;
	SyncProfile *m_profile;

	QDocumentSelector *m_selector;
	QPushButton *m_sync;
};

#endif // SYNCZILLA_H
