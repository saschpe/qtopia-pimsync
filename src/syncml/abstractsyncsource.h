#ifndef ABSTRACTSYNCSOURCE_H
#define ABSTRACTSYNCSOURCE_H

#include "base.h"

#include <spds/SyncSource.h>
#include <spds/SyncManagerConfig.h>

#include <QDateTime>
#include <QUniqueId>
#include <QList>
#include <QDebug>

class QPimModel;

class AbstractSyncSourceConfig : public SyncSourceConfig
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

	AbstractSyncSourceConfig(Mode syncMode = Slow, unsigned int lastSync = 0, const char *uri = "default")
		: SyncSourceConfig()
	{
		setURI(uri);
		setSyncModes("slow,two-way,one-way-from-server,one-way-from-client,refresh-from-server,refresh-from-client");
		setEncoding("b64");	// important, "plain/text" does not always work
		setLast(0);
		setSupportedTypes("");
		setVersion("");
		setEncryption("");

		m_lastSync = lastSync;

		switch (syncMode) {
			case Slow:				setSync("slow");				break;
			case TwoWay:			setSync("two-way");				break;
			case OneWayFromServer:	setSync("one-way-from-server");	break;
			case OneWayFromClient:	setSync("one-way-from-client");	break;
			case RefreshFromServer:	setSync("refresh-from-server");	break;
			case RefreshFromClient: setSync("refresh-from-client");	break;
		}
	}

	unsigned int lastSync() const { return m_lastSync; }

private:
	unsigned int m_lastSync;
};

/*!
 * Base class for all PIM sync sources (PIM model types like tasks, contacts and
 * appointments). Never use this class directly, see the derived classes to have
 * an example if you want to add another sync source.
 */
class AbstractSyncSource : public SyncSource
{
public:
	AbstractSyncSource(AbstractSyncSourceConfig *config, SyncManagerConfig* managerConfig);
	virtual ~AbstractSyncSource();

	// BEGIN FUNAMBOL API SPECIFIC
    SyncItem *getFirstItem() { return getFirst(All); }
    SyncItem *getNextItem() { return getNext(All); }
    SyncItem *getFirstNewItem() { return getFirst(New); }
    SyncItem *getNextNewItem() { return getNext(New); }
    SyncItem *getFirstUpdatedItem() { return getFirst(Updated); }
    SyncItem *getNextUpdatedItem() { return getNext(Updated); }
    SyncItem *getFirstDeletedItem() { return getFirst(Deleted, false); }
    SyncItem *getNextDeletedItem() { return getNext(Deleted, false); }
    SyncItem *getFirstItemKey() { return getFirst(All, false); }
    SyncItem *getNextItemKey() { return getNext(All, false); }
    
    int addItem(SyncItem& item);
    int updateItem(SyncItem& item);
    int deleteItem(SyncItem& item);

	int beginSync();
    int endSync();

    ArrayElement *clone() { return 0; }
    void setItemStatus(const WCHAR *, int) {}
	// END FUNAMBOL API SPECIFIC

	uint lastSync() const { return m_lastSync.toTime_t(); }

	static QString toString(SyncItem& item);

protected:
	QPimModel *m_model;
	const char *m_type;

private:
	enum ItemSet {
		All = 0x0,
		New = 0x1,
		Updated = 0x2,
		Deleted = 0x3
	};

	SyncItem *getFirst(ItemSet set, bool withData = true);
	SyncItem *getNext(ItemSet set, bool withData = true);
	SyncItem *createSyncItem(const QUniqueId &id, bool withData = true, SyncState state = SYNC_STATE_NONE) const;

	int m_indexAll;
	int m_indexNew;
	int m_indexUpdated;
	int m_indexDeleted;

	QList<QUniqueId> added;
	QList<QUniqueId> modified;
	QList<QUniqueId> removed;

	/*!
	 * This one is ecessary because Qtopia does not
	 * encapsulate SQL backend limitations well.
	 */
	static int s_transactionCounter;

	QDateTime m_currentSync;
	QDateTime m_lastSync;
};

#endif // ABSTRACTSYNCSOURCE_H
