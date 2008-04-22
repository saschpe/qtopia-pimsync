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

#include "abstractsyncsource.h"

#include <QPimModel>
#include <QPimContext>

AbstractSyncSource::AbstractSyncSource(AbstractSyncSourceConfig *config, SyncManagerConfig* managerConfig)
	: SyncSource(config->getName(), config)
	, m_model(NULL)
	, m_indexAll(0), m_indexNew(0), m_indexUpdated(0), m_indexDeleted(0)
	, m_currentSync(QDateTime()), m_lastSync(QDateTime::fromTime_t(config->lastSync()-1))
{
	managerConfig->setSyncSourceConfig(*config);
}

AbstractSyncSource::~AbstractSyncSource()
{
	delete m_model;
}

int AbstractSyncSource::addItem(SyncItem& item)
{
	QByteArray data((char *)item.getData());
	QUniqueId uid = m_model->addRecord(data, QPimSource(), m_type);
	qDebug() << "AbstractSyncSource::addItem() " /*<< toString(item)*/ << "Id:" << uid.toString();
	if (!uid.isNull())
		return 201;	//ok, the requested item was added
	else
		return 500;	//failed, the recipient encountered an error
}

int AbstractSyncSource::updateItem(SyncItem& item)
{
	QByteArray data((char *)item.getData());
	QString strId;
	strId.append(m_model->defaultSource().context);
	strId.append(":");
	strId.append((char *)item.getKey());
	QUniqueId id(strId);
	qDebug() << "AbstractSyncSource::updateItem()" /*<< toString(item)*/ << "Id:" << id.toString();

	if (m_model->updateRecord(id, data, m_type))
		return 200; //ok, the SyncML command completed successfully
	else
		return 500; //failed, the recipient encountered an error
}

int AbstractSyncSource::deleteItem(SyncItem& item)
{
	QString strId;
	strId.append(m_model->defaultSource().context);
	strId.append(":");
	strId.append((char *)item.getKey());
	QUniqueId id(strId);
	qDebug() << "AbstractSyncSource::deleteItem()" /*<< toString(item) */<< "Id:" << id.toString();
	if (m_model->removeRecord(id))
		return 200; //ok, the SyncML command completed successfully
	else
		return 211; //failed, the recipient encountered an error
}

int AbstractSyncSource::beginSync()
{
	// Get entries which where modified since last sync
	added = m_model->added(m_lastSync);
	modified = m_model->modified(m_lastSync);
	removed = m_model->removed(m_lastSync);

	qDebug() << "AbstractSyncSource::beginSync() Added:";
	for (int i = 0; i < added.size(); i++)
		qDebug() << added[i].toString();
	qDebug() << "AbstractSyncSource::beginSync() Modified:";
	for (int i = 0; i < modified.size(); i++)
		qDebug() << modified[i].toString();
	qDebug() << "AbstractSyncSource::beginSync() Removed:";
	for (int i = 0; i < removed.size(); i++)
		qDebug() << removed[i].toString();

	m_currentSync = QDateTime::currentDateTime().toUTC();
	return 0;
}

int AbstractSyncSource::endSync()
{
	return 0;
}

SyncItem *AbstractSyncSource::getFirst(ItemSet set, bool withData)
{
	qDebug() << "AbstractSyncSource::getFirst() From set" << set << "with data:" << withData;
	QUniqueId id;
	SyncState state = SYNC_STATE_NONE;
	bool endTransaction = false;

	if (!m_model->startSyncTransaction(m_currentSync)) {
		qDebug() << "AbstractSyncSource::getFirst() start sync failed" << m_currentSync;
	} else {
		if (set == All) {
			m_indexAll = 0;
			if (m_indexAll >= m_model->count()) {
				qDebug() << "AbstractSyncSource::getFirst() No item available";
				endTransaction = true;
			} else {
				id = m_model->id(m_indexAll);
			}
		} else if (set == New) {
			m_indexNew = 0;
			if (m_indexNew >= added.size()) {
				qDebug() << "AbstractSyncSource::getFirst() No new item available";
				endTransaction = true;
			} else {
				state = SYNC_STATE_NEW;
				id = added[m_indexNew];
			}
		} else if (set == Updated) {
			m_indexUpdated = 0;
			if (m_indexUpdated >= modified.size()) {
				qDebug() << "AbstractSyncSource::getFirst() No updated item available";
				endTransaction = true;
			} else {
				state = SYNC_STATE_UPDATED;
				id = modified[m_indexUpdated];
			}
		} else if (set == Deleted) {
			m_indexDeleted = 0;
			if (m_indexDeleted >= removed.size()) {
				qDebug() << "AbstractSyncSource::getFirst() No deleted item available";
				endTransaction = true;
			} else {
				state = SYNC_STATE_DELETED;
				id = removed[m_indexDeleted];
			}
		}
	}

	if (endTransaction) {
		if (!m_model->commitSyncTransaction())
			qDebug() << "AbstractSyncSource::getFirst() commit sync failed" << m_currentSync;
	} else {
		if (!id.isNull())
			return createSyncItem(id, withData, state);
		else
			qDebug() << "AbstractSyncSource::getFirst() Invalid Id";
	}
	return NULL;
}

SyncItem *AbstractSyncSource::getNext(ItemSet set, bool withData)
{
	qDebug() << "AbstractSyncSource::getNext() From set" << set << "with data:" << withData;
	QUniqueId id;
	SyncState state = SYNC_STATE_NONE;
	bool endTransaction = false;

	if (set == All) {
		m_indexAll++;
		if (m_indexAll >= m_model->count()) {
			qDebug() << "AbstractSyncSource::getNext() No further item available";
			endTransaction = true;
		} else {
			id = m_model->id(m_indexAll);
		}
	} else if (set == New) {
		m_indexNew++;
		if (m_indexNew >= added.size()) {
			qDebug() << "AbstractSyncSource::getNext() No further new item available";
			endTransaction = true;
		} else {
			state = SYNC_STATE_NEW;
			id = added[m_indexNew];
		}
	} else if (set == Updated) {
		m_indexUpdated++;
		if (m_indexUpdated >= modified.size()) {
			qDebug() << "AbstractSyncSource::getNext() No further updated item available";
			endTransaction = true;
		} else {
			state = SYNC_STATE_UPDATED;
			id = modified[m_indexUpdated];
		}
	} else if (set == Deleted) {
		m_indexDeleted++;
		if (m_indexDeleted >= removed.size()) {
			qDebug() << "AbstractSyncSource::getNext() No further deleted item available";
			endTransaction = true;
		} else {
			state = SYNC_STATE_DELETED;
			id = removed[m_indexDeleted];
		}
	}

	if (endTransaction) {
		if (!m_model->commitSyncTransaction())
			qDebug() << "AbstractSyncSource::endFirst() commit sync failed" << m_currentSync;
	} else {
		if (!id.isNull())
			return createSyncItem(id, withData);
		else
			qDebug() << "AbstractSyncSource::getNext() Invalid Id";
	}
	return NULL;
}

SyncItem *AbstractSyncSource::createSyncItem(const QUniqueId &id, bool wantData, SyncState state) const
{
	QByteArray record = m_model->record(id, m_type);
	SyncItem *item = new SyncItem();
	QString key = id.toString().split(":")[1];
	item->setKey(key.toAscii().data());
	item->setState(state);
	if (wantData) {
		item->setData(record.data(), record.size() - 1); // have to omit '\0'
		item->setDataType(getConfig().getType());
	}
	return item;
}

QString AbstractSyncSource::toString(SyncItem& item)
{
	QByteArray data((char *)item.getData());
	QString ret("Key: ");
	ret += item.getKey();
	ret += " Mod.Time: ";
	ret += QString::number(item.getModificationTime());
	ret += " Encoding: ";
	ret += item.getDataEncoding();
	ret += " Size: ";
	ret += QString::number(item.getDataSize());
	ret += " Type: ";
	ret += item.getDataType();
	ret += " State: ";
	ret += QString::number(item.getState());
	ret += " Data:\n";
	ret += data;
	return ret;
}
