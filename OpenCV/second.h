#ifndef SECOND_H
#define SECOND_H

#include <QWidget>
#include <opencv/cv.h>
#include <QImage>


namespace Ui {
class Second;
}

class Second : public QWidget
{
    Q_OBJECT

public:
    explicit Second(QWidget *parent = 0);
    ~Second();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Second *ui;
 void init(const QString& image);
    IplImage *iplImg;
};

#endif // SECOND_H
