#include "SerialWidget.h"
#include "ui_serialwidget.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
/**
 * @brief Serial read and write test
 * @author whb
 */
SerialWidget::SerialWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialWidget)
{
    ui->setupUi(this);

    //查找可用的串口
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->comPortBox->addItem(serial.portName());
            serial.close();
        }
    }
    //设置波特率下拉菜单默认显示第0项:根据自己的情况设置常用值
    ui->BaudBox->setCurrentIndex(0);
}

SerialWidget::~SerialWidget()
{
    delete ui;
}

void SerialWidget::on_OpenSerialButton_clicked()
{
    if(ui->OpenSerialButton->text() == tr("打开串口"))
    {
        serial = new QSerialPort;
        //设置串口名
        serial->setPortName(ui->comPortBox->currentText());
        //打卡串口
        serial->open(QIODevice::ReadWrite);
        //设置波特率
        serial->setBaudRate(ui->BaudBox->currentText().toInt());
        qDebug()<<ui->BaudBox->currentText().toInt();
        qDebug()<<ui->BitBox->currentIndex();
        //设置数据位数
        switch (ui->BitBox->currentIndex())
        {
        case 0:
            serial->setDataBits(QSerialPort::Data8);
            break;
        case 1:
            serial->setDataBits(QSerialPort::Data7);
            break;
        case 2:
            serial->setDataBits(QSerialPort::Data6);
            break;
        case 3:
            serial->setDataBits(QSerialPort::Data5);
            break;
        default:
            break;
        }
        //设置校验位
        switch (ui->ParityBox->currentIndex())
        {
        case 0:
            serial->setParity(QSerialPort::NoParity);
            break;
        case 1:
            serial->setParity(QSerialPort::EvenParity);
            break;
        case 2:
            serial->setParity(QSerialPort::OddParity);
            break;
        case 3:
            serial->setParity(QSerialPort::SpaceParity);
            break;
        case 4:
            serial->setParity(QSerialPort::MarkParity);
            break;
        default:
            serial->setParity(QSerialPort::UnknownParity);
            break;
        }
        //设置停止位
        switch (ui->BitBox->currentIndex())
        {
        case 1:
            serial->setStopBits(QSerialPort::OneStop);
            break;
        case 2:
            serial->setStopBits(QSerialPort::TwoStop);
            break;
        case 3:
            serial->setStopBits(QSerialPort::OneAndHalfStop);
            break;
        default:
            serial->setStopBits(QSerialPort::UnknownStopBits);
            break;
        }
        //设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);

        //关闭设置菜单使能
        ui->comPortBox->setEnabled(false);
        ui->BaudBox->setEnabled(false);
        ui->BitBox->setEnabled(false);
        ui->ParityBox->setEnabled(false);
        ui->StopBox->setEnabled(false);
        ui->OpenSerialButton->setText(tr("关闭串口"));

        //连接信号槽
        connect(serial,SIGNAL(readyRead()),this,SLOT(ReadData()));
    }
    else
    {
        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();

        //恢复设置使能
        ui->comPortBox->setEnabled(true);
        ui->BaudBox->setEnabled(true);
        ui->BitBox->setEnabled(true);
        ui->ParityBox->setEnabled(true);
        ui->StopBox->setEnabled(true);
        ui->OpenSerialButton->setText(tr("打开串口"));
    }
}
//读取接收到的信息
void SerialWidget::ReadData()
{
    QByteArray buf;
    buf = serial->readAll();
    qDebug()<<"ReadData() buf="+  QString::number(buf.count()) + ":"+buf;
    if(!buf.isEmpty())
    {
        QString str = ui->dataTextEdit->toPlainText();
        str+=tr(buf);
        ui->dataTextEdit->clear();
        ui->dataTextEdit->append(str);
    }
    buf.clear();
}

//发送按钮槽函数
void SerialWidget::on_SendButton_clicked()
{
    serial->write(ui->sendTextEdit->toPlainText().toUtf8());
}
