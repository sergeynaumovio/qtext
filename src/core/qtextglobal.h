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

#ifndef QTEXTGLOBAL_H
#define QTEXTGLOBAL_H

#include <QtCore/qcompilerdetection.h>

#ifndef QT_STATIC
#  if defined(QT_EXT_LIBRARY)
#    define Q_EXT_EXPORT Q_DECL_EXPORT
#  else
#    define Q_EXT_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define Q_EXT_EXPORT
#endif

#endif // QTEXTGLOBAL_H
