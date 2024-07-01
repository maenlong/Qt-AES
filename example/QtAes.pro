#-------------------------------------------------
#
# Project created by QtCreator 2018-09-25T10:03:26
#
#-------------------------------------------------

QT += core
QT -= gui

TEMPLATE = app

#DEFINES += USE_INTEL_AES_IF_AVAILABLE

#-----------------------------------------------------------------------

HEADERS  += \
    aesni/aesni-key-init.h \
    aesni/aesni-key-exp.h \
    aesni/aesni-enc-ecb.h \
    aesni/aesni-enc-cbc.h \
    qaesencryption.h

SOURCES += \
    main.cpp\
    qaesencryption.cpp

FORMS += \

#-----------------------------------------------------------------------
