QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia
HEADERS += \
    Sources/Sources/litterales.h \
    Sources/Sources/operande.h \
    Sources/Sources/utils.h \
    Sources/Sources/litteralefactory.h \
    Sources/Sources/pile.h \
    Sources/Sources/controleur.h \
    Sources/Sources/operateurfactory.h \
    Sources/Sources/mainwindow.h \
    Sources/Sources/operateurslogiques.h \
    Sources/Sources/operateur.h \
    Sources/Sources/operateursnumeriques.h \
    Sources/Sources/variable.h \
    Sources/Sources/operateurspile.h \
    Sources/Sources/operateurscond.h \
    Sources/Sources/operateursexpressions.h \
    Sources/Sources/litteraleexception.h \
    Sources/Sources/wordidentifier.h \
    Sources/Sources/parameterwindow.h \
    Sources/Sources/gestionvariablewindow.h \
    Sources/Sources/includers.h
    Sources/Sources/mainwindow.h

SOURCES += \
    Sources/Sources/main.cpp \
    Sources/Sources/litterales.cpp \
    Sources/Sources/litteralefactory.cpp \
    Sources/Sources/pile.cpp \
    Sources/Sources/controleur.cpp \
    Sources/Sources/operateurfactory.cpp \
    Sources/Sources/mainwindow.cpp \
    Sources/Sources/operateurslogiques.cpp \
    Sources/Sources/operateursnumeriques.cpp \
    Sources/Sources/variable.cpp \
    Sources/Sources/enregistrements.cpp \
    Sources/Sources/operateur.cpp \
    Sources/Sources/operateursexpressions.cpp \
    Sources/Sources/wordidentifier.cpp \
    Sources/Sources/parameterwindow.cpp \
    Sources/Sources/gestionvariablewindow.cpp
    Sources/Sources/mainwindow.cpp

FORMS += \
    Sources/Sources/mainwindow.ui \
    Sources/Sources/parameterwindow.ui \
    Sources/Sources/gestionvariablewindow.ui
QT += widgets
