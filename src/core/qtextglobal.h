// Copyright (C) 2023 Sergey Naumov <sergey@naumov.io>
// SPDX-License-Identifier: 0BSD

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
