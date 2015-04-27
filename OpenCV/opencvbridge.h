#ifndef OPENCVHELPER_H
#define OPENCVHELPER_H
#include <cv.h>
#include <highgui.h>
#include <math.h>
#include <iostream>

#include <cxcore.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QImage>

namespace OpenCvBridge
{
    typedef unsigned short uint16_t;

    QImage *IplImageToQImage(
             const IplImage* iplImage,
             uchar**         data,
             double          mini=0.0,
             double          maxi=0.0);

    QImage Mat2QImage(const cv::Mat& mat);

}

#endif // OPENCVHELPER_H
