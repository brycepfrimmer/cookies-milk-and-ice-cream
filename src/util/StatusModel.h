/*
 * StatusModel.h
 *
 *  Created on: May 1, 2012
 *      Author: aodziemkowski
 */

#ifndef STATUSMODEL_H_
#define STATUSMODEL_H_

#include <QList>
#include <QString>
#include <QVariant>

namespace util {

class StatusModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString status READ getStatus NOTIFY statusChanged)
    Q_PROPERTY(QString fullStatus READ getFullStatus NOTIFY statusChanged)
public:
    StatusModel(QObject *parent = 0);
    virtual ~StatusModel();
    void updateStatus(const QVariant &text);
    Q_INVOKABLE void clearStatus();
    const QString &getStatus() const;
    QString getFullStatus() const;
Q_SIGNALS:
    void statusChanged();
public Q_SLOTS:
    void resetStatus();
private:
    QList<QString> log;
    QString initialStatus;
};

}

#endif /* STATUSMODEL_H_ */
