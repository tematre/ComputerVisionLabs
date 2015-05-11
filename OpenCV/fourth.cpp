#include "fourth.h"
#include "ui_fourth.h"
#include "opencvbridge.h"

#include<cv.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <QFileDialog>
#include <QMessageBox>

Fourth::Fourth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fourth)
{
    ui->setupUi(this);
}

Fourth::~Fourth()
{
    delete ui;
}

void Fourth::on_pushButton_clicked()
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


void Fourth::init(const QString& imagePath)
{
    QByteArray ba = imagePath.toLatin1();
    const char* charFileName = ba.data();

    cv::Mat rot_mat(2, 3, CV_32FC1);

    cv::Mat src_dist, dst_dist;
    cv::ORB orb;
    std::vector<cv::KeyPoint> keysPoins;
    std::vector<cv::KeyPoint> dstkeysPoins;

    IplImage* iplImg = cvLoadImage(charFileName);

    cv::Mat src(iplImg, true);


    cv::Mat dst = src.clone();



    /// Compute a rotation matrix with respect to the center of the image
    cv::Point center = cv::Point(src.cols / 2, src.rows / 2);
    double angle = 45.0;
    double scale = 1;
    /// Get the rotation matrix with the specifications above
    rot_mat = cv::getRotationMatrix2D(center, angle, scale);
    /// Rotate the warped image
    cv::warpAffine(src, dst, rot_mat, src.size());

    orb.detect(src, keysPoins);
    orb.compute(src, keysPoins, src_dist);

    orb.detect(dst, dstkeysPoins);
    orb.compute(dst, keysPoins, dst_dist);

    cv::BFMatcher matcher(cv::NORM_HAMMING);
    std::vector<std::vector<cv::DMatch>> matches;
    std::vector<cv::DMatch> Draw_matches;

    matcher.radiusMatch(src_dist, dst_dist, matches, 64);

    for (int i = 0; i < matches.size(); i++)
    {
        cv::DMatch v1;
        cv::DMatch v2;

        if (matches[i].size() >= 2)
        {
            v1 = matches[i][0];
            v2 = matches[i][1];
            if (v1.distance>0.7*v2.distance)
            {
                Draw_matches.push_back(v1);
            }
        }
    }

    cv::Mat img_matheces;

    cv::drawMatches(src, keysPoins, dst, dstkeysPoins, matches, img_matheces);


    ui->FullImageLabel->setPixmap(QPixmap::fromImage(OpenCvBridge::Mat2QImage(img_matheces)));
}

