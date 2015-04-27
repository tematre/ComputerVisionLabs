#include "opencvbridge.h"

#include <QFileDialog>
#include <QMessageBox>


#include "first.h"
#include "ui_first.h"

First::First(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::First)
{
    ui->setupUi(this);
    iplImg = NULL;
}

First::~First()
{
    delete ui;
}

void First::on_openFileButton_clicked()
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
           ui->imageLabel->setText(error.what());
           msgBox.exec();
       }

}

void First::on_getStatistick_clicked()
{
    if(iplImg == NULL)
    {
        QMessageBox msgBox;
        msgBox.setText("Set file please!");
        msgBox.exec();
        return;
    }
    int nl= iplImg->height; // number of lines
         // total number of element per line
         int nc= iplImg->width * iplImg->nChannels;
         int step= iplImg->widthStep; // effective width

         int counter = 0;
         double r, g, b;
         r = g = b = 0.0;

         // get the pointer to the image buffer
         unsigned char *data= reinterpret_cast<unsigned char *>
                                              (iplImg->imageData);

         for (int i=1; i<nl; i++) {
               for (int j=0; j<nc; j+= iplImg->nChannels) {


                   r = data[j];
                   g = data[j+2];
                   b =  data[j+1];
                   if(r == ui->redSpinBox->value() && g == ui->greenSpinBox->value() && b == ui->blueSpinBox->value())
                   {
                       counter++;
                   }

               }

               data+= step;  // next line
         }
         QMessageBox msgBox;
         msgBox.setText(QString("It is about ") + QString::number(counter) + QString(" pixels"));
         msgBox.exec();







}



void First::init(const QString& imagePath)
{

    QByteArray ba = imagePath.toLatin1();
    const char* charFileName = ba.data();


    iplImg = cvLoadImage(charFileName);

    float scaleFactor = 300.0f / iplImg->height;

    IplImage* clone = cvCreateImage
            ( cvSize( scaleFactor * iplImg->width, 300 ),  iplImg->depth, iplImg->nChannels );



    cvResize(iplImg, clone);

    int startX =qrand()% clone->width;
    int startY = qrand()%clone->height;
    int endX = startX + qrand()% (clone->width - startX);
    int endY = startY + qrand()%(clone->height - startY);
    cvRectangle(clone, cvPoint(startX,startY), cvPoint(endX, endY), CV_RGB(255,0,0), 1);





    startX =qrand()% clone->width;
    startY = qrand()%clone->height;
    endX = startX + qrand()% (clone->width - startX);
    endY = startY + qrand()%(clone->height - startY);

    cvLine(clone, cvPoint(startX,startY), cvPoint(endX, endY), CV_RGB(0,255,0), 1, 8,0 );

    startX =qrand()% clone->width;
    startY = qrand()%clone->height;
    cvCircle(clone, cvPoint(startX,startY), qMin(qMin(startX, clone->width - startX), qMin(startY,clone->height - startY )), CV_RGB(0,0,255), 1);


    uchar* data = (uchar *)clone->imageData;

    QImage* image = OpenCvBridge::IplImageToQImage(clone, &data);


    ui->imageLabel->clear();
    ui->imageLabel->setPixmap(QPixmap::fromImage(*image));


}
