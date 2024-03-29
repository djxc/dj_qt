QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addlayercommon.cpp \
    dmapactions.cpp \
    exif.cpp \
    layermanager.cpp \
    main.cpp \
    mainwindow.cpp \
    parsephotolatlon.cpp \
    point_symbol.cpp \
    resource.cpp

HEADERS += \
    addlayercommon.h \
    dmapactions.h \
    layermanager.h \
    mainwindow.h\
    exif.h \
    parsephotolatlon.h \
    point_symbol.h \
    resource.h

FORMS += \
    addlayercommon.ui \
    mainwindow.ui
QT += xml

DEFINES += _USE_MATH_DEFINES

# qgis
INCLUDEPATH += "D:\Program Files (x86)\OSGeo4W64\bin"
INCLUDEPATH += "D:\Program Files (x86)\OSGeo4W64\include"
INCLUDEPATH += "D:\Program Files (x86)\OSGeo4W64\apps\qgis-ltr\include"
LIBS += -L"D:\Program Files (x86)\OSGeo4W64\apps\qgis-ltr\lib" -lqgis_core -lqgis_gui
LIBS += -L"D:\Program Files (x86)\OSGeo4W64\lib" -lgdal_i

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md
