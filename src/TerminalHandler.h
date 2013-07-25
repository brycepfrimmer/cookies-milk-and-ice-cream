/*
 * TerminalHandler.h
 *
 *  Created on: Jul 9, 2013
 *      Author: bpfrimmer
 */

#ifndef TERMINALHANDLER_H_
#define TERMINALHANDLER_H_

#include "StatusModel.h"
#include <QStringList>

class TerminalHandler : public util::StatusModel {
    Q_OBJECT
    Q_PROPERTY(QString path READ getPath NOTIFY pathChanged)
public:
    TerminalHandler(QObject *parent = 0);
    ~TerminalHandler();
    const QString &getPath() const;
    Q_INVOKABLE void handleCommand(QString command);
    Q_INVOKABLE QString priorCommand();
    Q_INVOKABLE QString nextCommand();
Q_SIGNALS:
    void pathChanged();
private:
    QString _path;
    QStringList _priorCommands;
    int _position;
};

#endif /* TERMINALHANDLER_H_ */
