#-------------------------------------------------
#
# Project created by QtCreator 2015-04-27T11:43:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCV
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    first.cpp \
    second.cpp \
    opencvbridge.cpp \
    third.cpp

HEADERS  += mainwindow.h \
    first.h \
    second.h \
    opencvbridge.h \
    third.h

FORMS    += mainwindow.ui \
    first.ui \
    second.ui \
    third.ui
INCLUDEPATH+=D:\\opencv\\build\\include
INCLUDEPATH+=D:\\opencv\\build\\include\\opencv
INCLUDEPATH+=D:\\opencv\\build\\include\\opencv2

LIBS+=D:\\opencv\\build\\x64\\vc12\\lib\\opencv_core2410.lib
LIBS+=D:\\opencv\\build\\x64\\vc12\\lib\\opencv_contrib2410.lib
LIBS+=D:\\opencv\\build\\x64\\vc12\\lib\\opencv_features2d2410.lib
LIBS+=D:\\opencv\\build\\x64\\vc12\\lib\\opencv_flann2410.lib
LIBS+=D:\\opencv\\build\\x64\\vc12\\lib\\opencv_highgui2410.lib
LIBS+=D:\\opencv\\build\\x64\\vc12\\lib\\opencv_objdetect2410.lib
LIBS+=D:\\opencv\\build\\x64\\vc12\\lib\\opencv_video2410.lib
LIBS+=D:\\opencv\\build\\x64\\vc12\\lib\\opencv_legacy2410.lib
LIBS+=D:\\opencv\\build\\x64\\vc12\\lib\\opencv_calib3d2410.lib
LIBS+=D:\\opencv\\build\\x64\\vc12\\lib\\opencv_imgproc2410.lib
LIBS+=D:\\opencv\\build\\x64\\vc12\\lib\\opencv_ml2410.lib

LIBS+=-L"D:\\opencv\\build\\x64\\vc12\\bin"
