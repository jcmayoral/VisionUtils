#-------------------------------------------------
#
# Project created by QtCreator 2017-06-22T17:29:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisionUtils
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += /usr/local/include/opencv2

LIBS += -L/usr/local/lib -lopencv_shape \
                         -lopencv_stitching \
                         -lopencv_objdetect \
                         -lopencv_superres \
                         -lopencv_videostab \
                         -lopencv_calib3d \
                         -lopencv_features2d \
                         -lopencv_highgui \
                         -lopencv_videoio \
                         -lopencv_imgcodecs \
                         -lopencv_video \
                         -lopencv_photo \
                         -lopencv_ml \
                         -lopencv_imgproc \
                         -lopencv_flann \
                         -lopencv_viz \
                         -lopencv_core

SOURCES += main.cpp \
        mainwindow.cpp \
        src/Calibration.cpp \
        src/cmdmain.cpp \
        src/GUI.cpp \
        src/Matcher.cpp \
        src/MVO.cpp \
        src/myfeaturedetection.cpp \
        src/Settings.cpp \
        src/tracker.cpp \
        src/visualizer.cpp \
    src/statics_tools.cpp \
    secondarywindow.cpp

HEADERS  += mainwindow.h\
        gui/GUI.h\
        monocularvision/matcher.h \
        monocularvision/MVO.h \
        monocularvision/myfeaturedetection.h \
        monocularvision/tracker.h \
        monocularvision/visualizer.h \
        calibration/Calibration.h \
        calibration/Settings.h \
    statics/statics_tools.h \
    secondarywindow.h

FORMS += mainwindow.ui \
    secondarywindow.ui

OTHER_FILES += \
    camcalibration.xml

CONFIG += c++11

INCLUDEPATH += /usr/include/qwt-qt4
LIBS += -l qwt-qt4
