#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T16:13:46
#
#-------------------------------------------------

QT       += core gui xml uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# With C++11 support
greaterThan(QT_MAJOR_VERSION, 4){
CONFIG += c++11
} else {
QMAKE_CXXFLAGS += -std=c++0x
}

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
    src/models/controlmodel.cpp \
    src/router/controls/controlosc.cpp \
    src/router/globalrouter.cpp \
    src/router/controls/controlmidi.cpp \
    src/router/controls/controlkeyboard.cpp \
    src/learn/controllearn.cpp \
    src/router/listeners/listener.cpp \
    src/router/helpers/routereventhelper.cpp \
    src/router/helpers/controleventhelper.cpp \
    src/router/listeners/osc/oscserver.cpp \
    src/router/listeners/listenerkeyboard.cpp \
    src/router/listeners/listenerosc.cpp \
    src/router/listeners/listenermidi.cpp

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
    src/models/controlmodel.h \
    src/router/controls/controlinterface.h \
    src/router/controls/controlosc.h \
    src/router/globalrouter.h \
    src/router/controls/controlmidi.h \
    src/router/controls/controlkeyboard.h \
    src/router/controlglobal.h \
    src/learn/controllearn.h \
    src/router/listeners/listener.h \
    src/router/helpers/routereventhelper.h \
    src/router/helpers/controleventhelper.h \
    src/router/listeners/osc/oscserver.h \
    src/router/listeners/listenerkeyboard.h \
    src/router/listeners/listenerosc.h \
    src/router/listeners/listenermidi.h

FORMS    += src/mainwindow.ui \
    src/instancegroupdialog.ui \
    Controllers/korgmicrocontrol.ui \
    Controllers/korgnanocontrol.ui \
    src/controllerscontrolgroupdialog.ui \
    src/controllearn.ui

DISTFILES +=

RESOURCES += \
    dynamapressources.qrc

unix|win32: LIBS += -llo
