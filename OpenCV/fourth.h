#ifndef FOURTH_H
#define FOURTH_H

#include <QWidget>

namespace Ui {
class Fourth;
}

class Fourth : public QWidget
{
    Q_OBJECT

public:
    explicit Fourth(QWidget *parent = 0);
    ~Fourth();

private slots:
    void on_pushButton_clicked();

private:
    void init(const QString& image);


    Ui::Fourth *ui;
};

#endif // FOURTH_H
