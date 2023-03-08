// Copyright (C) 2023 Sergey Naumov <sergey@naumov.io>
// SPDX-License-Identifier: 0BSD

#ifndef EXTHELLO_H
#define EXTHELLO_H

#include "qtextglobal.h"
#include <QLoaderSettings>
#include <QWidget>

class Q_EXT_EXPORT ExtHello : public QWidget, public QLoaderSettings
{
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent*) override;

public:
    ExtHello(QLoaderSettings *settings, QWidget *parent);
};

#endif // EXTHELLO_H
