QT       += core gui
QT += charts
QT       += core gui multimedia multimediawidgets
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG  += c++11

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
    AddDialog.cpp \
    Equipment.cpp \
    FourGProbe.cpp \
    LicensePlateMonitoring.cpp \
    MonitoringPoint.cpp \
    NTime.cpp \
    Road.cpp \
    RoadInformationWidget.cpp \
    VideoSurveillance.cpp \
    addnewequipmentdialog.cpp \
    addnewispectiondialog.cpp \
    cardata_searchface.cpp \
    cartimesearch.cpp \
    datasearchui.cpp \
    dialog.cpp \
    fourgfacing.cpp \
    main.cpp \
    mainwindow.cpp \
    people_search.cpp \
    randomdata.cpp \
    showequipmentdialog.cpp \
    showvideo.cpp \
    widget.cpp

HEADERS += \
    AddDialog.h \
    ConnectDataBase.h \
    Equipment.h \
    FourGProbe.h \
    LicensePlateMonitoring.h \
    MonitoringPoint.h \
    NTime.h \
    Road.h \
    RoadInformationWidget.h \
    VideoSurveillance.h \
    addnewequipmentdialog.h \
    addnewispectiondialog.h \
    cardata_searchface.h \
    cartimesearch.h \
    datasearch.h \
    datasearchui.h \
    dialog.h \
    fourgfacing.h \
    mainwindow.h \
    people_search.h \
    randomdata.h \
    readonlyClass.h \
    showequipmentdialog.h \
    showvideo.h \
    widget.h

FORMS += \
    addnewequipmentdialog.ui \
    addnewispectiondialog.ui \
    cardata_searchface.ui \
    cartimesearch.ui \
    datasearchui.ui \
    dialog.ui \
    fourgfacing.ui \
    mainwindow.ui \
    people_search.ui \
    showequipmentdialog.ui \
    showvideo.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
