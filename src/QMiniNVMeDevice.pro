QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QMiniNVMeControllerInfo.cpp \
    QMiniNVMeControllerState.cpp \
    QMiniNVMeControllerVersion.cpp \
    QMiniNVMeDevice.cpp \
    QMiniNVMeError.cpp \
    QMiniNVMeLogPageHealthInfo.cpp \
    QMiniNVMeNamespaceInfo.cpp

HEADERS += \
    QMiniNVMeCommon.h \
    QMiniNVMeControllerInfo.h \
    QMiniNVMeControllerState.h \
    QMiniNVMeControllerVersion.h \
    QMiniNVMeDevice.h \
    QMiniNVMeError.h \
    QMiniNVMeLogPageHealthInfo.h \
    QMiniNVMeNamespaceInfo.h

INCLUDEPATH += \
    ../../QMiniPCIDevice/src

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
