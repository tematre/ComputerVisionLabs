#ifndef SIXTH_H
#define SIXTH_H

#include <QWidget>

namespace Ui {
class Sixth;
}

class Sixth : public QWidget
{
    Q_OBJECT

public:
    explicit Sixth(QWidget *parent = 0);
    ~Sixth();

private slots:
    void on_pushButton_clicked();

private:
     void init(const QString& directory);
    Ui::Sixth *ui;
};

#endif // SIXTH_H
