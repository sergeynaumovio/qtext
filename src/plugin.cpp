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

#include <QLoaderInterface>
#include <QLoaderSettings>
#include <ExtHello>

class Plugin : public QObject, QLoaderInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "QtExt")
    Q_INTERFACES(QLoaderInterface)

public:
    QObject *object(QLoaderSettings *settings, QObject *parent) override
    {
        QWidget *widget = qobject_cast<QWidget*>(parent);
        const char *className = settings->className();
        if (((parent && widget) || !parent) && !qstrcmp(className, "ExtHello"))
            return new ExtHello(settings, widget);

        return nullptr;
    }
};

#include "plugin.moc"
