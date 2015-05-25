#ifndef EIGHTH_H
#define EIGHTH_H

#include <QWidget>
#include<opencv.hpp>
namespace Ui {
class Eighth;
}

class Eighth : public QWidget
{
    Q_OBJECT

public:
    explicit Eighth(QWidget *parent = 0);
    ~Eighth();

private slots:
    void on_pushButton_clicked();

private:
    void init(const QString &imagePath);


    std::vector<std::vector<float> > getData(const std::vector<cv::Mat>& channels);
    cv::Mat getMu(const std::vector<std::vector<float> >& data);
    cv::Mat getC(const std::vector<std::vector<float> >& data, const cv::Mat& mu);
    std::vector<cv::Mat> smallCut(const std::vector<cv::Mat>& , const cv::Rect& rect);

    Ui::Eighth *ui;
};

#endif // EIGHTH_H
