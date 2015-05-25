#include "sixth.h"
#include "ui_sixth.h"
#include <QFileDialog>
#include <QMessageBox>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>


#include "OpenCvBridge.h"

Sixth::Sixth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sixth)
{
    ui->setupUi(this);
}

Sixth::~Sixth()
{
    delete ui;
}

void Sixth::on_pushButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
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


void Sixth::init(const QString& directory)
{

    const double THRESHOLD = 20;

    QDir myDir(directory);
    QStringList filesList = myDir.entryList(QStringList("*.jpg"));

    if(filesList.size() != 2)
    {
        throw std::exception("The folder must have only 2 files");
    }

    QByteArray ba = myDir.filePath(filesList[1]).toLatin1();
    const char* charFileName = ba.data();


    cv::Mat img1 = cv::imread(charFileName, CV_LOAD_IMAGE_COLOR);

    ba = myDir.filePath(filesList[0]).toLatin1();
    charFileName = ba.data();

    cv::Mat img2 = cv::imread(charFileName, CV_LOAD_IMAGE_COLOR);


     float scaleFactor = 300.0f / img1.rows;

     cv::resize(img1, img1, cv::Size(img1.cols * scaleFactor, img1.rows * scaleFactor));
     cv::resize(img2, img2, cv::Size(img2.cols * scaleFactor, img2.rows * scaleFactor));


    std::vector<uchar> status;
    std::vector<float> err;

    std::vector<cv::KeyPoint> keyPoints;
    std::vector<cv::Point2f> pts1;
    std::vector<cv::Point2f> pts2;


    cv::ORB orb;
    orb.detect(img1, keyPoints);
    for (int i = 0; i < keyPoints.size(); i++)
    {
        pts1.push_back(keyPoints[i].pt);
    }
    cv::calcOpticalFlowPyrLK(img1, img2, pts1, pts2, status, err);

    for (int i = 0; i < pts1.size(); i++)
    {
            if (status[i] && err[i] < THRESHOLD)
            {
                cv::line(img1, pts1[i], pts2[i], cv::Scalar(255, 0, 0));
            }
    }

    ui->resultLabel->setPixmap(QPixmap::fromImage(OpenCvBridge::Mat2QImage(img1)));
}
