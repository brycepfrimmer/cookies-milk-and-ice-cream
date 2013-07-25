/*
 * TerminalHandler.cpp
 *
 *  Created on: Jul 9, 2013
 *      Author: bpfrimmer
 */

#include "TerminalHandler.h"
#include "Logging.h"

TerminalHandler::TerminalHandler(QObject *parent) : util::StatusModel(parent),
                _path("#"), _position(-1) {
    _priorCommands.clear();
}

TerminalHandler::~TerminalHandler() {}

const QString &TerminalHandler::getPath() const {
    return _path;
}

void TerminalHandler::handleCommand(QString command) {
    _priorCommands.prepend(command.remove(command.size() - 1, 1));

    command.prepend(QString(" "));
    command.prepend(_path);
    updateStatus(command);
}

QString TerminalHandler::priorCommand() {
    if (_priorCommands.isEmpty()) {
        return "";
    } else if (_position < _priorCommands.size() - 1) {
        _position++;
        return _priorCommands.at(_position);
    } else {
        return _priorCommands.last();
    }
}

QString TerminalHandler::nextCommand() {
    if (_priorCommands.isEmpty()) {
        return "";
    } else if (_position > 0) {
        _position--;
        return _priorCommands.at(_position);
    } else if (_position == 0) {
        _position--;
    }
    return "";
}
