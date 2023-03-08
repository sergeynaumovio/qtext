// Copyright (C) 2023 Sergey Naumov <sergey@naumov.io>
// SPDX-License-Identifier: 0BSD

#ifndef EXTHELLO_H
#define EXTHELLO_H

#include "qtextglobal.h"
#include <QLoaderSettings>
#include <QWidget>

class ExtHelloPrivate;

class Q_EXT_EXPORT ExtHello : public QWidget, public QLoaderSettings
{
    Q_OBJECT

    const QScopedPointer<ExtHelloPrivate> d_ptr;

protected:
    void closeEvent(QCloseEvent*) override;
    QLoaderBlob saveBlob(const QString &key) const override;

public:
    ExtHello(QLoaderSettings *settings, QWidget *parent);
    ~ExtHello();
};

#endif // EXTHELLO_H
