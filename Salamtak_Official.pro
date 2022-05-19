QT       += core gui
QT += sql
#QT += webengine
#QT += webenginewidgets
#QT += widgets quickwidgets
#QT += location
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    doctor_sign_up.cpp \
    main.cpp \
    mainwindow.cpp \
    mapwindow.cpp \
    outpatient.cpp \
    patient_sign_up.cpp \
    service_choice.cpp \
    sign_in.cpp

HEADERS += \
    doctor_sign_up.h \
    mainwindow.h \
    mapwindow.h \
    outpatient.h \
    patient_sign_up.h \
    service_choice.h \
    sign_in.h

FORMS += \
    doctor_sign_up.ui \
    mainwindow.ui \
    mapwindow.ui \
    outpatient.ui \
    patient_sign_up.ui \
    service_choice.ui \
    sign_in.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
