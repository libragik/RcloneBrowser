#pragma once

#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#include <memory>
#include <vector>
#include <string>

#include <QtCore>
#include <QtDebug>
#include <QtGui>
#include <QtNetwork>
#include <QtWidgets>

// Qt5 platform-specific extras (removed in Qt6)
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    #if defined(Q_OS_WIN32) && defined(HAVE_QT_WINEXTRAS)
        #include <QtWinExtras>
    #endif

    #if defined(Q_OS_MACOS) && defined(HAVE_QT_MACEXTRAS)
        #include <QtMacExtras>
    #endif
#endif

// Qt5/Qt6 compatibility macros
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    #define SKIP_EMPTY_PARTS Qt::SkipEmptyParts
    #define KEEP_EMPTY_PARTS Qt::KeepEmptyParts
#else
    #define SKIP_EMPTY_PARTS QString::SkipEmptyParts
    #define KEEP_EMPTY_PARTS QString::KeepEmptyParts
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif
