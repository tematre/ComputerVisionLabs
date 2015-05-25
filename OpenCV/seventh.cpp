#include "seventh.h"
#include "ui_seventh.h"
#include <QFileDialog>
#include <QMessageBox>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/flann/flann_base.hpp>
#include <opencv2\calib3d\calib3d.hpp>
#include <opencv2\video\tracking.hpp>


#include "OpenCvBridge.h"

Seventh::Seventh(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Seventh)
{
    ui->setupUi(this);
}

Seventh::~Seventh()
{
    delete ui;
}

void Seventh::on_pushButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    //dialog.setNameFilter("Images (*.jpg)");
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
           msgBox.setText(QString("Error: " )+ error.what());
           msgBox.exec();
       }
}

cv::Mat mix(cv::Mat* channels, int r, int g, int b)
{

   // Q_ASSERT((channels[b - 1] != NULL) &&( channels[r - 1] != NULL) && (channels[g - 1]!= NULL));
    std::vector <cv::Mat> rgb;



    rgb.push_back(channels[b - 1]);
    rgb.push_back(channels[g - 1]);
    rgb.push_back(channels[r - 1]);

    cv::Mat color;

    cv::merge(rgb, color);

    return color;
}


void Seventh::init(const QString& directory)
{


    QDir myDir(directory);
    QStringList filesList = myDir.entryList(QStringList("*.tif"));

    if(filesList.size() != 7)
    {
        throw std::exception("The folder must have only 2 files");
    }


    qDebug("%s \n", "Start 7 lab");

    cv::Mat img[7];

    for(int i = 0; i < 7; ++i)
    {
        QByteArray ba = myDir.filePath(filesList[i]).toLatin1();
        const char* charFileName = ba.data();
        qDebug("%s \n", charFileName);
        img[i] = cv::imread(charFileName, 0);

    }


    for(int i = 0; i < 7; ++i)
    {
         cv::normalize(img[i], img[i], 1, 0, CV_MINMAX, CV_32FC1);
    }



    cv::Mat resultMix = mix(img, 4, 5, 1);

    qDebug("Get NDVI");
    cv::Mat NDVI = (img[3] - img[2]) / (img[3] + img[2]);

    cv::normalize(NDVI, NDVI, 1, 0, CV_MINMAX, CV_32FC1);
    int N = 500;

    qDebug("Draw field");
    cv::Mat drawField(cv::Size(N, N), CV_32FC1);

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                float valX = img[3].at<float>(i, j) * N;
                float valY = img[2].at<float>(i, j) * N;

                if (img[3].at<float>(i, j) != 0 && img[3].at<float>(i, j) != 0)
                {
                    drawField.at<float>(N - valX, valY) += 1;
                }
            }
        }

        cv::normalize(drawField, drawField, 1, 0, CV_MINMAX, CV_32FC1);



        float scaleFactor = 300.0f / NDVI.rows;

        cv::resize(NDVI, NDVI, cv::Size(NDVI.cols * scaleFactor, NDVI.rows * scaleFactor));

        scaleFactor = 300.0f / drawField.rows;
        cv::resize(drawField, drawField, cv::Size(drawField.cols * scaleFactor, drawField.rows * scaleFactor));


        scaleFactor = 300.0f / resultMix.rows;
        cv::resize(resultMix, resultMix, cv::Size(resultMix.cols * scaleFactor, resultMix.rows * scaleFactor));


        ui->ndviLabel->setPixmap(QPixmap::fromImage(OpenCvBridge::Mat2QImage(NDVI)));
        ui->roadLabel->setPixmap(QPixmap::fromImage(OpenCvBridge::Mat2QImage(drawField)));

        ui->resultLabel->setPixmap(QPixmap::fromImage(OpenCvBridge::Mat2QImage(resultMix)));


}
