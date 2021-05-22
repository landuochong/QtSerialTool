#ifndef SERIALWIDGET_H
#define SERIALWIDGET_H

#include <QWidget>
#include <QSerialPort>

namespace Ui {
class SerialWidget;
}

/**
 * @brief Serial read and write test
 * @author whb
 */
class SerialWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SerialWidget(QWidget *parent = 0);
    ~SerialWidget();

private slots:
    void ReadData();
    void on_SendButton_clicked();
    void on_OpenSerialButton_clicked();
private:
    Ui::SerialWidget *ui;
    QSerialPort *serial;
};

#endif // SERIALWIDGET_H
