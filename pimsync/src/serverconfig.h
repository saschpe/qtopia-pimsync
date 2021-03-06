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

#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include <QString>
#include <QContent>

/*!
 * Responsible for accessing a SyncML server configuration profile.
 */
class ServerConfig
{
public:
    enum Mode {
        Slow = 0x0,
        TwoWay = 0x1,
        OneWayFromServer = 0x2,
        OneWayFromClient = 0x3,
        RefreshFromServer = 0x4,
        RefreshFromClient = 0x5,
    };

    enum Source {
        Contacts = 0x0,
        Tasks = 0x1,
        Appointments = 0x2,
        Notes = 0x3
    };

    ServerConfig();
    virtual ~ServerConfig();

    void newProfile();
    bool load(const QContent &profile);
    bool save();
    bool isSaved() const { return m_saved; }

    void setName(const QString &name);
    QString name() const { return m_name; }

    void setComment(const QString &comment);
    QString comment() const { return m_comment; }

    void setMode(Mode mode);
    Mode mode() const { return m_mode; }

    void setSourceEnabled(Source source, bool enabled);
    bool sourceEnabled(Source source) const;

    void setSourceLastSync(Source source, unsigned int timeStamp);
    unsigned int sourceLastSync(Source source) const;

    void setSourceUrl(Source source, const QString &url);
    QString sourceUrl(Source source) const;

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

    bool m_notesEnabled;
    unsigned int m_notesLastSync;
    QString m_notesUrl;

    QString m_transportUser;
    QString m_transportPassword;
    QString m_transportUrl;
};

#endif
