// Copyright (C) 2023 Sergey Naumov <sergey@naumov.io>
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
        QByteArray className = settings->className();
        const char *shortName = className.data() + qstrlen("Ext");

        if (!qstrcmp(shortName, "Hello"))
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
