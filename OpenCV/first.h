#ifndef FIRST_H
#define FIRST_H

#include <QWidget>
#include <opencv/cv.h>
#include <QImage>


namespace Ui {
class First;
}

class First : public QWidget
{
    Q_OBJECT

public:
    explicit First(QWidget *parent = 0);
    ~First();

private slots:
    void on_openFileButton_clicked();

    void on_getStatistick_clicked();

private:
    void init(const QString& image);


    Ui::First *ui;

    IplImage *iplImg;
    char* charFileName;

};

#endif // FIRST_H
