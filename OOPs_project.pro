QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Menu.cpp \
    MenuItem.cpp \
    Order.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    muku.cpp

HEADERS += \
    Menu.h \
    MenuItem.h \
    Order.h \
    logindialog.h \
    mainwindow.h \
    muku.h

FORMS += \
    logindialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Downloads/hamburger.png \
    menu.txt

RESOURCES += \
    resources.qrc
