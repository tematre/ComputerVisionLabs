#include "helper.h"
#include "cv.h"

cv::Mat Helper::mat2gray(const cv::Mat& src)
{
    cv::Mat dst;
    cv::normalize(src, dst, 0.0, 255.0, cv::NORM_MINMAX, CV_8U);
    return dst;
}



