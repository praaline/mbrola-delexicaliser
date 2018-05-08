#-------------------------------------------------
#
# Project created by QtCreator 2018-05-06T15:50:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mbrola-delexicaliser
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += praaline-core-lite

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    PseudoLanguage.cpp \
    praaline-core-lite/annotation/AnnotationDataTable.cpp \
    praaline-core-lite/annotation/AnnotationElement.cpp \
    praaline-core-lite/annotation/AnnotationTier.cpp \
    praaline-core-lite/annotation/AnnotationTierGroup.cpp \
    praaline-core-lite/annotation/Interval.cpp \
    praaline-core-lite/annotation/IntervalTier.cpp \
    praaline-core-lite/annotation/Point.cpp \
    praaline-core-lite/annotation/PointTier.cpp \
    praaline-core-lite/base/DataType.cpp \
    praaline-core-lite/base/RealTime.cpp \
    praaline-core-lite/base/RealValueList.cpp \
    praaline-core-lite/interfaces/InterfaceTextFile.cpp \
    praaline-core-lite/interfaces/praat/PraatTextFile.cpp \
    praaline-core-lite/interfaces/praat/PraatTextGrid.cpp \
    LanguageDefinition.cpp \
    praaline-core-lite/interfaces/praat/PraatPointTierFile.cpp \
    MBROLAResynthesiser.cpp

HEADERS += \
        MainWindow.h \
    PseudoLanguage.h \
    praaline-core-lite/annotation/AnnotationDataTable.h \
    praaline-core-lite/annotation/AnnotationElement.h \
    praaline-core-lite/annotation/AnnotationTier.h \
    praaline-core-lite/annotation/AnnotationTierGroup.h \
    praaline-core-lite/annotation/Interval.h \
    praaline-core-lite/annotation/IntervalTier.h \
    praaline-core-lite/annotation/Point.h \
    praaline-core-lite/annotation/PointTier.h \
    praaline-core-lite/base/BaseTypes.h \
    praaline-core-lite/base/DataType.h \
    praaline-core-lite/base/IDatastore.h \
    praaline-core-lite/base/ISaveable.h \
    praaline-core-lite/base/RealTime.h \
    praaline-core-lite/base/RealValueList.h \
    praaline-core-lite/interfaces/InterfaceTextFile.h \
    praaline-core-lite/interfaces/praat/PraatTextFile.h \
    praaline-core-lite/interfaces/praat/PraatTextGrid.h \
    LanguageDefinition.h \
    praaline-core-lite/interfaces/praat/PraatPointTierFile.h \
    MBROLAResynthesiser.h

FORMS += \
        MainWindow.ui
