#include "third.h"
#include "ui_third.h"

#include <QFileDialog>
#include <QMessageBox>

#include "opencvbridge.h"

Third::Third(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Third)
{
    ui->setupUi(this);
}

Third::~Third()
{
    delete ui;
}

void Third::on_openFileButton_clicked()
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
           msgBox.setText(QString("Error: ") + error.what());
           msgBox.exec();
       }

}

void Third::init(const QString& imagePath)
{
    QByteArray ba = imagePath.toLatin1();
    const char* charFileName = ba.data();

    cv::Mat image;

    image = cv::imread(charFileName, CV_LOAD_IMAGE_COLOR);


    cv::Mat gray;
    cvtColor(image, gray, CV_BGR2GRAY);

    ui->grayImageLabel->setPixmap(QPixmap::fromImage(OpenCvBridge::Mat2QImage(gray)));



    int threshold_type = cv::THRESH_BINARY;
    int const max_bin_val = 255;
    int threshold_val = 100;

    cv::Mat dst;
    cv::Mat kernel;
    cv::threshold(gray, dst, threshold_val, max_bin_val, threshold_type);
    cv::dilate(dst, dst, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);
    ui->distanceTransformImageLabel->setPixmap(QPixmap::fromImage(OpenCvBridge::Mat2QImage(dst)));

    cv::Mat DT;
    cv::distanceTransform(dst, DT, CV_DIST_L2, CV_DIST_MASK_PRECISE);
    cv::normalize(DT, DT, 0, 1, cv::NORM_MINMAX);
    cv::threshold(DT, DT, 0.6, 1, 0);



    std::vector<std::vector<cv::Point>> outCont;

    cv::Mat res;
    DT.convertTo(res, CV_8U);
    cv::findContours(res, outCont, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    ui->resultLabel->setText(QString::number(outCont.size()));


    for (int i = 0; i < outCont.size(); i++)
    {
        cv::Scalar scalar(rand() % 255, rand() % 255, rand() % 255);
        cv::drawContours(res, outCont, i, scalar, CV_FILLED, 8);
    }

    ui->resultImageLabel->setPixmap(QPixmap::fromImage(OpenCvBridge::Mat2QImage(res)));

}
