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

#include "exthello.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QDataStream>
#include <QShortcut>
#include <QLoaderTree>

class ExtHelloPrivate
{
public:
    bool imageChanged{};
};

ExtHello::ExtHello(QLoaderSettings *settings, QWidget *parent)
:   QWidget(parent),
    QLoaderSettings(settings),
    d_ptr(new ExtHelloPrivate)
{
    QMainWindow *window = qobject_cast<QMainWindow*>(parent);
    {
        if (window)
            window->setCentralWidget(this);
    }

    QFont font("Arial", 20, QFont::Bold);
    QLabel *hello = new QLabel(this);
    {
        hello->setText(value("text", "Hello World!").toString());
        hello->setFont(font);
        hello->setAlignment(Qt::AlignCenter);
    }

    QLabel *ext = new QLabel(this);
    {
        font.setPointSize(60);
        ext->setText("\u263A");
        ext->setFont(font);
        ext->setAlignment(Qt::AlignCenter);
    }

    QPushButton *button = new QPushButton("Close", this);
    {
        connect(button, &QPushButton::clicked, this, [this] { close(); });
    }

    QVBoxLayout *layout = new QVBoxLayout(this);
    {
        layout->addWidget(hello);
        layout->addWidget(ext);
        layout->addWidget(button, 1, Qt::AlignRight);
    }

    if (contains("saveShortcut") == Value)
    {
        QShortcut *shortcut = new QShortcut(this);
        {
            shortcut->setKey(QKeySequence(value("saveShortcut").toString()));
            QObject::connect(shortcut, &QShortcut::activated, this, [this] { tree()->save(); });
        }
    }

    if (!parent)
        show();

    connect(tree(), &QLoaderTree::loaded, this, [this] { dumpSettingsTree(); });
}

ExtHello::~ExtHello()
{ }

void ExtHello::closeEvent(QCloseEvent*)
{
    hide();
    deleteLater();
}

QLoaderBlob ExtHello::saveBlob(const QString &key) const
{
    if (key == "image")
    {
        if (d_ptr->imageChanged)
        {
            QByteArray ba;
            QDataStream out(&ba, QIODevice::WriteOnly);
            out << QByteArray("multiline binary");

            return ba;
        }
        return {};
    }

    return {};
}
