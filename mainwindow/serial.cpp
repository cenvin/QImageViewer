#include "serial.h"
#include <string>

serial::serial(QWidget *parent) : QWidget(parent)
{
    sserial = new QSerialPort(this);
    initSerial();

}

serial::~serial()
{
//    sserial.clear();
//    sserial.close();
//    sserial.deleteLater();
}


void serial::initSerial(void)
{
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort sserial;
        sserial.setPort(info);
        if(sserial.open(QIODevice::ReadWrite))

        {
//            qDebug() << "Name : " << info.portName();
//            qDebug() << "Description : " << info.description();
//            qDebug() << "Manufacturer: " << info.manufacturer();
//            qDebug() << "Serial Number: " << info.serialNumber();
//            qDebug() << "System Location: " << info.systemLocation();

            qDebug()<<sserial.portName();
            sserial.setBaudRate(9600);
            sserial.setDataBits(QSerialPort::Data8);
            sserial.setParity(QSerialPort::NoParity);
            sserial.setStopBits(QSerialPort::OneStop);
            sserial.setFlowControl(QSerialPort::NoFlowControl);

            extern char spdid;
            QString dataBuf;
            switch (spdid) {
            case 2:
                dataBuf = "speedhigh";             
                break;
            case 1:
                dataBuf = "speedmid";
                break;
            default:
                dataBuf = "speedlow";
                break;
            }

            QByteArray ba = dataBuf.toLocal8Bit();
            const char *spd = ba.constData();
            sserial.write(spd);
            qDebug()<<"speed:"<<spd;

            sserial.close();
        }
    }

//    QSerialPort *sserial;
//    sserial->setPortName("COM4"); //name name TBD
//    sserial->open(QIODevice::WriteOnly);
//    sserial->setBaudRate(460800); //bdr bdr
//    sserial->setDataBits(QSerialPort::Data8);
//    sserial->setParity(QSerialPort::NoParity);
//    sserial->setStopBits(QSerialPort::OneStop);
//    sserial->setFlowControl(QSerialPort::NoFlowControl);

    qDebug("initSerial");



}
