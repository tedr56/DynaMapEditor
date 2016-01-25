#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T16:13:46
#
#-------------------------------------------------

QT       += core gui xml uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DynaMapEditor
TEMPLATE = app


SOURCES += src/main.cpp \
    src/models/softwaremodel.cpp \
    src/editorwindow.cpp \
    src/models/softwaretypedelegate.cpp \
    src/models/qjsonitem.cpp \
    src/models/qjsonmodel.cpp \
    src/instancegroupdialog.cpp \
    src/models/filterjsonproxy.cpp \
    src/controllerscontrolgroupdialog.cpp \
    src/models/extendedjsonmodel.cpp \
    src/models/controlmodel.cpp

HEADERS  += \
    src/models/softwaremodel.h \
    src/editorwindow.h \
    src/models/softwaretypedelegate.h \
    src/models/qjsonitem.h \
    src/models/qjsonmodel.h \
    src/instancegroupdialog.h \
    src/models/filterjsonproxy.h \
    src/controllerscontrolgroupdialog.h \
    src/models/extendedjsonmodel.h \
    src/models/controlmodel.h

FORMS    += src/mainwindow.ui \
    src/instancegroupdialog.ui \
    Controllers/korgmicrocontrol.ui \
    Controllers/korgnanocontrol.ui \
    src/controllerscontrolgroupdialog.ui

DISTFILES +=

RESOURCES += \
    dynamapressources.qrc
