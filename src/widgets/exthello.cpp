// Copyright (C) 2023 Sergey Naumov <sergey@naumov.io>
// SPDX-License-Identifier: 0BSD

#include "exthello.h"
#include <QDataStream>
#include <QLabel>
#include <QLoaderTree>
#include <QMainWindow>
#include <QPushButton>
#include <QShortcut>
#include <QVBoxLayout>

void ExtHello::closeEvent(QCloseEvent *)
{
    hide();
    deleteLater();
}

ExtHello::ExtHello(QLoaderSettings *settings, QWidget *parent)
:   QWidget(parent),
    QLoaderSettings(this, settings)
{
    QMainWindow *window = qobject_cast<QMainWindow *>(parent);
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

    if (!parent)
        show();

    connect(tree(), &QLoaderTree::loaded, this, [this] { dumpSettingsTree(); });
}
