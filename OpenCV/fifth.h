#ifndef FIFTH_H
#define FIFTH_H

#include <QWidget>

namespace Ui {
class Fifth;
}

class Fifth : public QWidget
{
    Q_OBJECT

public:
    explicit Fifth(QWidget *parent = 0);
    ~Fifth();

private slots:
    void on_pushButton_clicked();

private:
    void init(const QString& imagePath);
    Ui::Fifth *ui;
};

#endif // FIFTH_H
