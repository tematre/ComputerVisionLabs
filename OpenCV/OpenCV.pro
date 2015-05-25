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
    third.cpp \
    fourth.cpp \
    fifth.cpp \
    helper.cpp \
    sixth.cpp \
    seventh.cpp \
    eighth.cpp

HEADERS  += mainwindow.h \
    first.h \
    second.h \
    opencvbridge.h \
    third.h \
    fourth.h \
    fifth.h \
    helper.h \
    sixth.h \
    seventh.h \
    eighth.h

FORMS    += mainwindow.ui \
    first.ui \
    second.ui \
    third.ui \
    fourth.ui \
    fifth.ui \
    sixth.ui \
    seventh.ui \
    eighth.ui
INCLUDEPATH+=D:\\opencv\\build\\include
INCLUDEPATH+=D:\\opencv\\build\\include\\opencv
INCLUDEPATH+=D:\\opencv\\build\\include\\opencv2

CONFIG(release, debug|release) {

LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_calib3d2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_contrib2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_core2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_features2d2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_flann2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_gpu2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_highgui2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_imgproc2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_legacy2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_ml2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_nonfree2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_objdetect2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_ocl2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_photo2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_stitching2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_superres2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_ts2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_stitching2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_videostab2410.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_video2410.lib
}

CONFIG(debug,debug|release) {

LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_calib3d2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_contrib2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_core2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_features2d2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_flann2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_gpu2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_highgui2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_imgproc2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_legacy2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_ml2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_nonfree2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_objdetect2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_ocl2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_photo2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_stitching2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_superres2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_ts2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_stitching2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_videostab2410d.lib
LIBS+=D:\\opencv\\build\\x86\\vc12\\lib\\opencv_video2410d.lib
}


LIBS+=-L"D:\\opencv\\build\\x86\\vc12\\bin"
