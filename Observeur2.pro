QT += core gui sql charts printsupport

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
    angleutilities/angle.cpp \
    angleutilities/date.cpp \
    angleutilities/equatorialposition.cpp \
    angleutilities/horizontalposition.cpp \
    dialogs/instrumentcalculationsdialog.cpp \
    dialogs/objectdialog.cpp \
    dialogs/settingdialog.cpp \
    tables/mapmodificationdialog.cpp \
    tables/mapstable.cpp \
    tables/constellationtable.cpp \
    tables/objecttable.cpp \
    tables/tabledialog.cpp \
    tables/typetable.cpp \
    errorhandler.cpp \
    main.cpp \
    mainwindow.cpp \
    objectform.cpp

HEADERS += \
    angleutilities/angle.h \
    angleutilities/date.h \
    angleutilities/equatorialposition.h \
    angleutilities/horizontalposition.h \
    dialogs/instrumentcalculationsdialog.h \
    dialogs/objectdialog.h \
    dialogs/settingdialog.h \
    tables/mapmodificationdialog.h \
    tables/mapstable.h \
    tables/constellationtable.h \
    tables/objecttable.h \
    tables/tabledialog.h \
    tables/typetable.h \
    errorhandler.h \
    main.h \
    mainwindow.h \
    objectform.h

FORMS += \
    dialogs/instrumentcalculationsdialog.ui \
    mainwindow.ui \
    dialogs/objectdialog.ui \
    dialogs/settingdialog.ui \
    tables/mapmodificationdialog.ui \
    tables/mapstable.ui \
    tables/tabledialog.ui \
    objectform.ui

RESOURCES += \
    ressources.qrc \
    light.qrc \
    dark.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
