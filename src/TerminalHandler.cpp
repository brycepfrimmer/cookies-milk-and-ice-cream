/*
 * TerminalHandler.cpp
 *
 *  Created on: Jul 9, 2013
 *      Author: bpfrimmer
 */

#include "TerminalHandler.h"
#include "Logging.h"

TerminalHandler::TerminalHandler(QObject *parent) : util::StatusModel(parent),
                _path("#") {}

TerminalHandler::~TerminalHandler() {}

QString TerminalHandler::getPath() {
    return _path;
}

void TerminalHandler::handleCommand(QString command) {
    command.prepend(QString("# "));
    updateStatus(command);
}
