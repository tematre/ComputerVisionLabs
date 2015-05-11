#include "fifth.h"
#include "ui_fifth.h"
#include <QFileDialog>
#include <QMessageBox>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <iostream>
#include "OpenCvBridge.h"
    using namespace cv;
    using namespace std;

Fifth::Fifth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fifth)
{
    ui->setupUi(this);
}

Fifth::~Fifth()
{
    delete ui;
}

void Fifth::on_pushButton_clicked()
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

void Fifth::init(const QString& imagePath)
{

    QByteArray ba = imagePath.toLatin1();
    const char* charFileName = ba.data();

    Mat src, dst;
    src = imread(charFileName);
    Mat img;
    Mat grey;
    vector<Point2f> detected;
    Size pattern = Size(8, 6);
    TermCriteria termCriteria;
    vector<Point3f> corners;
    float squareSize = 1.f;

    for (int i = 0; i < pattern.height; i++)
    {
    for (int j = 0; j < pattern.width; j++)
    {
    corners.push_back(Point3f(float(j*squareSize),
    float(i*squareSize), 0));
    }
    }

    Mat cam_matrix = Mat(3, 3, CV_64F, Scalar::all(0));
    double m_size = src.cols;
    double m_size_r = src.rows;
    cam_matrix.at<double>(0, 0) = m_size;
    cam_matrix.at<double>(0, 2) = m_size / 2;
    cam_matrix.at<double>(1, 1) = m_size;
    cam_matrix.at<double>(1, 2) = m_size_r / 2;
    cam_matrix.at<double>(2, 2) = 1.0f;

    Mat distCoeffs(4, 1, DataType<double>::type);
    distCoeffs.at<double>(0) = 0;
    distCoeffs.at<double>(1) = 0;
    distCoeffs.at<double>(2) = 0;
    distCoeffs.at<double>(3) = 0;

    Mat rvect(3, 1, DataType<double>::type);
    Mat tvect(3, 1, DataType<double>::type);

    bool found = findChessboardCorners(src, pattern, detected, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);
    drawChessboardCorners(src, pattern, Mat(detected), found);
    cout << corners.size() << endl;
    cout << detected.size() << endl;

//    solvePnP(corners, detected, cam_matrix, distCoeffs, rvect, tvect);
    vector<Point2f> projectedPoints;
    vector<Point3f> pts;
    pts.push_back(Point3d(0, 0, 0));
    pts.push_back(Point3d(1, 0, 0));
    pts.push_back(Point3d(0, 1, 0));
    pts.push_back(Point3d(0, 0, 1));

    projectPoints(pts, rvect, tvect, cam_matrix, distCoeffs, projectedPoints);
    vector<Point> basis;

    line(src, projectedPoints[0], projectedPoints[1], (255, 255, 255), 3);
    line(src, projectedPoints[0], projectedPoints[2], (0, 0, 255), 3);
    line(src, projectedPoints[0], projectedPoints[3], (0, 0, 255), 3);


    ui->imageLabel->setPixmap(QPixmap::fromImage(OpenCvBridge::Mat2QImage(src)));

}
