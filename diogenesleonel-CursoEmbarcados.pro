#-------------------------------------------------
#
# Project created by QtCreator 2013-12-04T20:35:01
#
#-------------------------------------------------

QT       += core gui

# Inclui a lib do qwt assim como os includes o que permite o auto-completar
CONFIG += qwt
#INCLUDEPATH +="/usr/local/qwt-6.1.0/include"
#LIBS += -L/usr/local/qwt-6.1.0/lib -lqwt

# Inclui lib da serial e includes
CONFIG += extserialport
#INCLUDEPATH +="/opt/qt/include/QtExtSerialPort/include"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = diogenesleonel-CursoEmbarcados
# Configuração necessaria para trabalhar com deploy remoto
    target.files = <NOME DO EXECUTAVEL>
    target.path = /home/root
    INSTALLS = target

TEMPLATE = app


SOURCES += main.cpp\
        principal.cpp \
    serial.cpp \
    plot.cpp

HEADERS  += principal.h \
    serial.h \
    plot.h

FORMS    += principal.ui

RESOURCES += \
    imagens.qrc
