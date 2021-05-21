#-------------------------------------------------
#
# Project created by QtCreator 2019-09-21T15:45:20
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
# qgis的头文件
INCLUDEPATH += /usr/local/include/qgis


# qgis的动态连接库
LIBS += /usr/local/lib/libqgis_core.so.3.9.0
LIBS += /usr/local/lib/libqgis_gui.so.3.9.0
LIBS += /usr/local/lib/libqgis_native.so.3.9.0

# qgis依赖的动态链接库
#LIBS += -lqgis_core -lqgis_gui
#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libsqlite3.so.0.8.6
LIBS += /usr/lib/x86_64-linux-gnu/libsqlite3.so.0.8.6

#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libqca-qt5.so.2.2.1
LIBS += /usr/lib/x86_64-linux-gnu/libqca-qt5.so.2.1.3

#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libqt5keychain.so.0.9.90
LIBS += /usr/lib/x86_64-linux-gnu/libqt5keychain.so.0.7.0

#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libgdal.so.20.5.2
LIBS += /usr/lib/libgdal.so.20

#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libproj.so.15.1.1
LIBS += /usr/lib/x86_64-linux-gnu/libproj.so.12

#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libzip.so.5.0.0
LIBS += /usr/lib/x86_64-linux-gnu/libzip.so.4

#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libgeos_c.so.1.11.2
LIBS += /usr/lib/x86_64-linux-gnu/libgeos_c.so.1.11.1

#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libgeos-3.7.2.so
LIBS += /usr/lib/x86_64-linux-gnu/libgeos-3.7.1.so

#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libexpat.so.1.6.9
LIBS += /usr/lib/x86_64-linux-gnu/libexpat.so

#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libspatialindex.so.4.0.1
LIBS += /usr/lib/x86_64-linux-gnu/libspatialindex.so.4.0.1

#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libspatialindex_c.so.4.0.1
LIBS += /usr/lib/x86_64-linux-gnu/libspatialindex_c.so.4.0.1

#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libspatialite.so.7.0.0
LIBS += /usr/lib/x86_64-linux-gnu/libspatialite.so.7.1.0

#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/mod_spatialite.so.7.0.0
LIBS += /usr/lib/x86_64-linux-gnu/mod_spatialite.so.7.1.0

#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libz.so.1.2.11
LIBS += /usr/lib/x86_64-linux-gnu/libz.so

#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libqscintilla2_qt5.so.15.0.0
LIBS += /usr/lib/libqscintilla2_qt5.so.13

#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libqwt.so.6.1.4
#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libqwt.so.6.1.4

#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libssl.so.1.1
LIBS += /usr/lib/x86_64-linux-gnu/libssl.so.1.1

#LIBS += /opt/QgisLibs_x86_64/libs_x86_64/libcrypto.so.1.1
LIBS += /usr/lib/x86_64-linux-gnu/libcrypto.so.1.1

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        utiltool.cpp \
        exif.cpp

HEADERS += \
        mainwindow.h \
        utiltool.h \
        exif.h
