#include "eighth.h"
#include "ui_eighth.h"
#include <QFileDialog>
#include <QMessageBox>


#include "OpenCvBridge.h"

Eighth::Eighth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Eighth)
{
    ui->setupUi(this);
}

Eighth::~Eighth()
{
    delete ui;
}


std::vector<std::vector<float> > Eighth::getData(const std::vector<cv::Mat>& channels)
{
    int height = channels[0].rows;
        int width = channels[0].cols;
        std::vector<std::vector<float> > data(height * width);

        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                std::vector<float> x(7);
                for(int k = 0; k < 7; k++)
                {
                    x[k] = channels[k].at<float>(i, j);
                }
                data[i * width + j] = x;
            }
        }

        return data;
}
cv::Mat Eighth::getMu(const std::vector<std::vector<float> >& data)
{
    cv::Mat mu = cv::Mat::zeros(7, 1, CV_32FC1);
        for(int i = 0; i < data.size(); i++)
        {
            mu = mu + cv::Mat(data[i]);
        }
        mu = mu / data.size();
        return mu;
}
cv::Mat Eighth::getC(const std::vector<std::vector<float> >& data, const cv::Mat& mu)
{
    cv::Mat C = cv::Mat::zeros(7, 7, CV_32FC1);
        for(int i = 0; i < data.size(); i++)
        {
            C = C + cv::Mat_<float>((cv::Mat(data[i]) - mu)) *cv::Mat_<float>(cv::Mat(data[i]) - mu).t();
        }

        C = C / data.size();
        return C;
}

std::vector<cv::Mat> Eighth::smallCut(const std::vector<cv::Mat>& bigImgchannels, const cv::Rect& rect)
{
    std::vector<cv::Mat> smallImgChannels(7);
       for(int i = 0; i < 7; i++)
       {
           smallImgChannels[i] = bigImgchannels[i](rect);
       }
       return smallImgChannels;
}


void Eighth::on_pushButton_clicked()
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
           msgBox.setText("Error");
           msgBox.exec();
       }
}
void Eighth::init(const QString& directory)
{
    QDir myDir(directory);
    QStringList filesList = myDir.entryList(QStringList("*.tif"));

    if(filesList.size() != 7)
    {
        throw std::exception("The folder must have only 2 files");
    }


    qDebug("%s \n", "Start 7 lab");

    std::vector<cv::Mat> img(7);

    for(int i = 0; i < 7; ++i)
    {
        QByteArray ba = myDir.filePath(filesList[i]).toLatin1();
        const char* charFileName = ba.data();
        qDebug("%s \n", charFileName);
        img[i] = cv::imread(charFileName, 0);
        normalize(img[i], img[i], 1, 0, CV_MINMAX, CV_32FC1);

    }

    std::vector<std::vector<float> > data_img = getData(img);

    //FOREST
    cv::Rect forest_rect = cv::Rect(366, 489, 50, 50);
    std::vector<cv::Mat> forest = smallCut(img, forest_rect);
    std::vector<std::vector<float> > dataForest = getData(forest);

    cv::Mat muForest = getMu(dataForest);
    cv::Mat cForest = getC(dataForest, muForest);
    //std::cout << mu_forest.t() << "\n\n" << C_forest << std::endl;

    //FIELD
    cv::Rect fieldRect = cv::Rect(421, 240, 50, 50);
    std::vector<cv::Mat> field = smallCut(img, fieldRect);
    std::vector<std::vector<float> > dataField = getData(field);

    cv::Mat muField = getMu(dataField);
    cv::Mat cField = getC(dataField, muField);

    //WATER
    cv::Rect waterRect = cv::Rect(567, 288, 50, 50);
    std::vector<cv::Mat> water = smallCut(img, waterRect);
    std::vector<std::vector<float> > dataWater = getData(water);

    cv::Mat muWater = getMu(dataWater);

    cv::Mat cWater = getC(dataWater, muWater);

    cv::Mat cForestInv = cForest.inv();
    cv::Mat cFieldInv = cField.inv();
    cv::Mat cWaterInv = cWater.inv();

    cv::Mat out = cv::Mat(img[0].cols, img[0].rows, CV_8UC3);

    for(int i = 0 ; i < data_img.size(); i++)
    {
        float forestD =  cv::Mat(( cv::Mat(img[i]) - muForest).t() * cForestInv * ( cv::Mat(img[i]) - muForest)).at<float>(0, 0);
        float fieldD =  cv::Mat(( cv::Mat(img[i]) - muField).t() * cFieldInv * ( cv::Mat(img[i]) - muField)).at<float>(0, 0);
        float waterD =  cv::Mat(( cv::Mat(img[i]) - muWater).t() * cWaterInv * ( cv::Mat(img[i]) - muWater)).at<float>(0, 0);

         cv::Vec3b color(255, 255, 255);
        if(forestD < fieldD && forestD < waterD)
        {
            color = cv::Vec3b(0, 255, 0);
        }
        else if(fieldD < forestD && fieldD < waterD)
        {
            color = cv::Vec3b(0, 0, 255);
        }
        else if(waterD < forestD && waterD < fieldD)
        {
            color = cv::Vec3b(255, 0, 0);
        }

        out.at<cv::Vec3b>(i % img[0].cols, i / img[0].cols) = color;
    }



    ui->resultLabel->setPixmap(QPixmap::fromImage(OpenCvBridge::Mat2QImage(out)));

}
