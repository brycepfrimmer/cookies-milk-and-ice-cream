/*
 * TerminalHandler.h
 *
 *  Created on: Jul 9, 2013
 *      Author: bpfrimmer
 */

#ifndef TERMINALHANDLER_H_
#define TERMINALHANDLER_H_

#include "StatusModel.h"

class TerminalHandler : public util::StatusModel {
    Q_OBJECT
public:
    TerminalHandler(QObject *parent = 0);
    ~TerminalHandler();
    Q_INVOKABLE QString getPath();
    Q_INVOKABLE void handleCommand(QString command);
private:
    QString _path;
};

#endif /* TERMINALHANDLER_H_ */
