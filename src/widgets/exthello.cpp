/****************************************************************************
**
** Copyright (C) 2021 Sergey Naumov
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

#include "exthello.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

ExtHello::ExtHello(QLoaderSettings *settings, QWidget *parent)
:   QWidget(parent),
    QLoaderSettings(settings)
{
    QLabel *hello = new QLabel(this);
    hello->setText(value("text", "Hello World!").toString());
    QFont font("Arial", 20, QFont::Bold);
    hello->setFont(font);
    hello->setAlignment(Qt::AlignCenter);

    QLabel *ext = new QLabel(this);
    ext->setText("\u263A");
    font.setPointSize(60);
    ext->setFont(font);
    ext->setAlignment(Qt::AlignCenter);

    QPushButton *button = new QPushButton("Close", this);
    connect(button, &QPushButton::clicked, this, [this] { close(); });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(hello);
    layout->addWidget(ext);
    layout->addWidget(button, 1, Qt::AlignRight);

    if (!parent)
        show();
}

void ExtHello::closeEvent(QCloseEvent*)
{
    hide();
    deleteLater();
}
