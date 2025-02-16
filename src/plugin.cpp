// Copyright (C) 2025 Sergey Naumov <sergey@naumov.io>
// SPDX-License-Identifier: 0BSD

#include "exthello.h"
#include <QLoaderPluginInterface>
#include <QLoaderSettings>
#include <QLoaderTree>

class Plugin : public QObject, QLoaderPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "QtExt")
    Q_INTERFACES(QLoaderPluginInterface)

public:
    QObject *object(QLoaderSettings *settings, QObject *parent) const override
    {
        const char *shortName = settings->className() + std::char_traits<char>::length("Ext");

        if (!strcmp(shortName, "Hello"))
        {
            QWidget *widget = qobject_cast<QWidget*>(parent);
            if (!parent  || (parent && widget))
                return new ExtHello(settings, widget);

            return parent;
        }

        return settings->tree();
    }
};

#include "plugin.moc"
