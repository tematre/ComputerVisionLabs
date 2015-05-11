#include "opencvbridge.h"
#include "second.h"
#include "ui_second.h"

#include <QFileDialog>
#include <QMessageBox>

Second::Second(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Second)
{
    ui->setupUi(this);
}

Second::~Second()
{
    delete ui;
}

void Second::on_pushButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("Images (*.jpg)");
    QStringList fileNames;
       if (dialog.exec() == QDialog::Accepted){
           fileNames = dialog.selectedFiles();
       }
       else{
           return;
       }
       try{

          init(fileNames[0]);
       }
       catch(const std::exception& error)
       {
           QMessageBox msgBox;
           msgBox.setText("Error");
           msgBox.exec();
       }
}
cv::Mat mat2gray(const cv::Mat& src)
{
    cv::Mat dst;
    //dst.convertTo(dst, CV_32FC1);
    cv::normalize(src, dst, 0.0, 255.0, cv::NORM_MINMAX, CV_8U);
    return dst;
}

float normer(float a, float b, float xMin, float xMax, float x)
{
    float result = a + (x / (xMax - xMin)) * (b - a);
    //std::cout << result << std::endl;
    return result;

}


void Second::init(const QString& imagePath)
{
    QByteArray ba = imagePath.toLatin1();
    const char* charFileName = ba.data();





    iplImg = cvLoadImage(charFileName);


    float scaleFactor = 300.0f / iplImg->height;

    IplImage* clone = cvCreateImage
            ( cvSize( scaleFactor * iplImg->width, 300 ),  iplImg->depth, iplImg->nChannels );

    cvResize(iplImg, clone);

    cv::Mat img(clone);





    cv::Mat gray;

    const int BINS = 9;



    int histSize = 256;
    float range[] = { 0, 255 };
    const int histChannel[] = { 0 };
    const float *histRange = { range };
    bool uniform = true;
    bool accumulate = false;

    cv::Mat hist, hist2;
    cv::Mat grad_x, grad_y, abs_grad_x, abs_grad_y, grad;
    int ddepth = CV_32F;
    int scale = 1;
    int delta = 0;

    //1
    cvtColor(img, gray, CV_RGB2GRAY);

    cv::Sobel(gray, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT);
    //Sobel(gray, grad_x, CV_32F, 1, 0, 3);
    cv::convertScaleAbs(grad_x, abs_grad_x);
    cv::Sobel(gray, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT);
    //Sobel(gray, grad_y, CV_32F, 1, 0, 3);
    cv::convertScaleAbs(grad_y, abs_grad_y);
    cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);



    //2
    cv::Mat mag, ori;
    cv::magnitude(grad_x, grad_y, mag);
    cv::phase(grad_x, grad_y, ori, true);


    //3

    int startX =qrand()% clone->width;
    int startY = qrand()%clone->height;
    int endX = qrand()% (clone->width - startX);
    int endY = qrand()%(clone->height - startY);

    cv::Rect rec(startX, startY,endX , endY);
    cv::Mat img_part(img.clone(), rec);



    float bins[BINS] = { 0 };
    for (int i = 0; i < img_part.cols; i++)
    {
        for (int j = 0; j < img_part.rows; j++)
        {
            //float dx = grad_x.at<float>(i, j);
            //float dy = grad_y.at<float>(i, j);
            float mg = mag.at<float>(i, j);
            //float magn = sqrt(pow(dx, 2) + pow(dy, 2));
            //int index = (atan2(dx, dy) * 180 / 3.14 + 180) / 45;
            int ind = ori.at<float>(i, j) / 45;
            bins[ind] += mg;
        }
    }
    float max = 0.0;
    float min = INT_MAX;
    for (int i = 0; i < BINS; i++)
    {
        if (bins[i] > max)
        {
            max = bins[i];
        }
        if (bins[i] < min)
        {
            min = bins[i];
        }
        std::cout << bins[i] << std::endl;
    }

    int bin_w = cvRound((float)img_part.cols / BINS);

    for (int i = 0; i < BINS; i++)
    {
        line(img_part, cv::Point(bin_w * i, img_part.cols),
            cv::Point(bin_w * i, normer(60, 100, min, max, (img.cols - bins[i]))),
            cv::Scalar(255, 0, 0), 2, 8, 0);
    }


    //Convert to QImage


    ui->sourceImageLabel->setPixmap(QPixmap::fromImage(OpenCvBridge::Mat2QImage(img)));
    ui->histImageLabel->setPixmap(QPixmap::fromImage(OpenCvBridge::Mat2QImage(img_part)));
    ui->magnitudeImageLabel->setPixmap(QPixmap::fromImage(OpenCvBridge::Mat2QImage(mat2gray(mag))));
    ui->orientationImageLabel->setPixmap(QPixmap::fromImage(OpenCvBridge::Mat2QImage(mat2gray(ori))));
    ui->gradImageLabel->setPixmap(QPixmap::fromImage(OpenCvBridge::Mat2QImage(grad)));




}
