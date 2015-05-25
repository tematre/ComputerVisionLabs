#ifndef SEVENTH_H
#define SEVENTH_H

#include <QWidget>

namespace Ui {
class Seventh;
}

class Seventh : public QWidget
{
    Q_OBJECT

public:
    explicit Seventh(QWidget *parent = 0);
    ~Seventh();

private slots:
    void on_pushButton_clicked();

private:
    void init(const QString& imagePath);
    Ui::Seventh *ui;
};

#endif // SEVENTH_H
