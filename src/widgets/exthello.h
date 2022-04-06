/****************************************************************************
**
** Copyright (C) 2021, 2022 Sergey Naumov
**
** Permission to use, copy, modify, and/or distribute this
** software for any purpose with or without fee is hereby granted.
**
** THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
** WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
** THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
** CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
** LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
** NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
** CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
**
****************************************************************************/

#ifndef EXTHELLO_H
#define EXTHELLO_H

#include "qtextglobal.h"
#include <QWidget>
#include <QLoaderSettings>

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
