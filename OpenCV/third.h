#ifndef THIRD_H
#define THIRD_H

#include <QWidget>
#include <opencv/cv.h>
#include <QImage>

namespace Ui {
class Third;
}

class Third : public QWidget
{
    Q_OBJECT

public:
    explicit Third(QWidget *parent = 0);
    ~Third();

private slots:
    void on_openFileButton_clicked();

private:
     void init(const QString& image);
     IplImage *iplImg;
     char* charFileName;
    Ui::Third *ui;
};

#endif // THIRD_H
