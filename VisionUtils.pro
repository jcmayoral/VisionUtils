
#-------------------------------------------------
#
# Project created by QtCreator 2017-06-22T17:29:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = VisionUtils
TEMPLATE = app

INCLUDEPATH += /home/jose/opencv-3.2.0-lib/include/opencv
INCLUDEPATH += /home/jose/opencv-3.2.0-lib/include/opencv2

LIBS += -L/usr/local/lib -lopencv_shape \
                         -lopencv_stitching \
                         -lopencv_objdetect \
                         -lopencv_superres \
                         -lopencv_videostab \
                         -lopencv_calib3d \
                         -lopencv_features2d \
                         -lopencv_xfeatures2d \
                         -lopencv_highgui \
                         -lopencv_videoio \
                         -lopencv_imgcodecs \
                         -lopencv_video \
                         -lopencv_photo \
                         -lopencv_ml \
                         -lopencv_imgproc \
                         -lopencv_flann \
                         -lopencv_viz \
                         -lopencv_core\
                         -lopencv_plot

SOURCES += main.cpp \
        src/cmdmain.cpp \
        src/Matcher.cpp \
        src/FD.cpp \
        src/tracker.cpp \
        src/myfeaturedetection.cpp \
        src/statistics_tools.cpp \
        qcustomplot/qcustomplot.cpp \
        mainwindow.cpp \
        plotwindow.cpp

HEADERS  += mainwindow.h\
        include/featuredetection/matcher.h \
        include/featuredetection/FD.h \
        include/featuredetection/myfeaturedetection.h \
        include/featuredetection/tracker.h \
        include/statistics/statistics_tools.h \
    qcustomplot/qcustomplot.h \
    plotwindow.h

FORMS += mainwindow.ui \
    plotwindow.ui

CONFIG += c++11

