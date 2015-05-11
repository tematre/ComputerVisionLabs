#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


//#include <iostream>
//#include <conio.h>
//#include <opencv2/core/core.hpp>
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//using namespace cv;

//#include "helper.h"

//cv::Mat mat2gray(const cv::Mat& src);

//int main(int argc, char *argv[])
//{

//    Mat image;
//    Mat src, src_gray;
//    Mat grad;
//    char* window_name = "Gradient";
//    int scale = 1;
//    int delta = 0;
//    int ddepth = CV_32F;
//    image = imread("D:\\Lenna.png");
//    src = imread("D:\\Lenna.png");
//    GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
//    cvtColor(src, src_gray, CV_RGB2GRAY);
//    namedWindow(window_name, CV_WINDOW_AUTOSIZE);
//    Mat grad_x, grad_y;
//    Mat abs_grad_x, abs_grad_y;

//    /// Gradient X
//    //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
//    Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
//    convertScaleAbs(grad_x, abs_grad_x);

//    /// Gradient Y
//    //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
//    Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
//    convertScaleAbs(grad_y, abs_grad_y);

//    /// Total Gradient (approximate)
//    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

//    imshow(window_name, grad);

//    //MAGNITUDE
//    Mat mag, ori;
//    magnitude(grad_x, grad_y, mag);
//    phase(grad_x, grad_y, ori, true);

//    if (mag.empty())
//    {
//        cv::waitKey(0);
//        std::cout << "EMPTY";
//        return 0;
//    }

//    Rect rec(0, 0, 100, 100);
//    Mat img_part(image, rec);
//    float bins[8] = {0};
//    for (int i = 0; i < img_part.cols; i++)
//    {
//        for (int j = 0; j < img_part.rows; j++)
//        {
//            float dx = grad_x.at<float>(i, j);
//            float dy = grad_y.at<float>(i, j);
//            float magnitu = sqrt(pow(dx, 2) + pow(dy, 2));
//            //float magnitu = mag.at<float>(i, j);
//            int index = (atan2(dx, dy) * 180 / 3.14 + 180) / 45;
//            //int index = (ori.at<float>(i, j) * 180 / 3.14 + 180) / 45;
//            bins[index] = magnitu;
//        }
//    }
//    for (int i = 0; i < 8; i++)
//        std::cout << bins[i] << std::endl;
//    imshow("Display Window", image);
//    imshow("Magnitude", mat2gray(mag));
//    imshow("Orient", mat2gray(ori));

//    cv::waitKey(0);
//    return 0;
//}



