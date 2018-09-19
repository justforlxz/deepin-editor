######################################################################
# Automatically generated by qmake (3.0) ?? 2? 4 17:49:37 2017
######################################################################

QT += KSyntaxHighlighting
QT += core
QT += dbus
QT += gui
QT += network
QT += printsupport
QT += svg
QT += widgets
QT += x11extras
QT += KCodecs

TEMPLATE = app
TARGET = deepin-editor

CONFIG += link_pkgconfig
CONFIG += c++11
PKGCONFIG += xcb xcb-util dtkwidget dtkwm
RESOURCES += deepin-editor.qrc

# Input
HEADERS += src/window.h \
           src/startmanager.h \
           src/dbusinterface.h \
           src/texteditor.h \
           src/jumplinebar.h \
           src/findbar.h \
           src/replacebar.h \
           src/linebar.h \
           src/settings.h \
           src/tabwidget.h \
           src/tabbar.h \
           src/editorbuffer.h \
           src/uncommentselection.h \
           src/utils.h \
           src/fileloadthread.h \
           src/theme_module/themepanel.h \
           src/theme_module/themelistview.h \
           src/theme_module/themeitemdelegate.h \
           src/theme_module/themelistmodel.h

SOURCES += src/window.cpp \
           src/startmanager.cpp \
           src/dbusinterface.cpp \
           src/texteditor.cpp \
           src/jumplinebar.cpp \
           src/findbar.cpp \
           src/replacebar.cpp \
           src/linebar.cpp \
           src/settings.cpp \
           src/settingsdialog.cpp \
           src/tabwidget.cpp \
           src/tabbar.cpp \
           src/editorbuffer.cpp \
           src/utils.cpp \
           src/uncommentselection.cpp \
           src/main.cpp \
           src/fileloadthread.cpp \
           src/theme_module/themepanel.cpp \
           src/theme_module/themelistview.cpp \
           src/theme_module/themeitemdelegate.cpp \
           src/theme_module/themelistmodel.cpp

QMAKE_CXXFLAGS += -g
LIBS += -lX11 -lXext -lXtst

isEmpty(BINDIR):BINDIR=/usr/bin
isEmpty(APPDIR):APPDIR=/usr/share/applications
isEmpty(DSRDIR):DSRDIR=/usr/share/deepin-editor

target.path = $$INSTROOT$$BINDIR
desktop.path = $$INSTROOT$$APPDIR
desktop.files = $$PWD/../deepin-editor.desktop

themes.path = $$DSRDIR/themes
themes.files += themes/deepin.theme
themes.files += themes/breeze_dark.theme
themes.files += themes/solarized_dark.theme
themes.files += themes/solarized_light.theme
themes.files += themes/atom_dark.theme

INSTALLS += target desktop themes
