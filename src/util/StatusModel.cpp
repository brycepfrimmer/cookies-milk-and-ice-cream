/*
 * StatusModel.cpp
 *
 *  Created on: May 1, 2012
 *      Author: aodziemkowski
 */

#include "StatusModel.h"
#include "Logging.h"

namespace util {

StatusModel::StatusModel(QObject *parent) : QObject(parent), initialStatus("Empty...") {
    emit statusChanged();
}

StatusModel::~StatusModel() { }

const QString &StatusModel::getStatus() const {
    if (log.isEmpty()) {
        return initialStatus;
    } else {
        return log.last();
    }
}

QString StatusModel::getFullStatus() const {
    if (log.isEmpty()) {
        return initialStatus;
    } else {
        QString fullStatus;
        for (int i = 0; i < log.size(); i++) {
            fullStatus.append(log.at(i).trimmed());
            fullStatus.append(QString("\n"));
        }
        LOG_DEBUG("Full Status: %s", fullStatus.trimmed().toStdString().c_str());
        return fullStatus.trimmed();
    }
}

void StatusModel::resetStatus() {
    log.clear();
    log << "Reset log.";
    emit statusChanged();
}

void StatusModel::clearStatus() {
    log.clear();
    emit statusChanged();
}

void StatusModel::updateStatus(const QVariant &text) {
    if (text.canConvert(QVariant::String)) {
        LOG_DEBUG("New Status: %s", text.toString().toStdString().c_str());
        log << text.toString();
        emit statusChanged();
    }
}

}
