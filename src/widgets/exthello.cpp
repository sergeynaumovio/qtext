// Copyright (C) 2023 Sergey Naumov <sergey@naumov.io>
// SPDX-License-Identifier: 0BSD

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
            QLoaderBlob bo;
            QDataStream out(&bo.array, QIODevice::WriteOnly);
            out.setVersion(bo.version);
            out << QByteArray("multiline binary");

            return bo;
        }
        return {};
    }

    return {};
}
