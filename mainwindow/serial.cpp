#include "serial.h"


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
            qDebug()<<sserial.portName();
            sserial.setBaudRate(460800);
            sserial.setDataBits(QSerialPort::Data8);
            sserial.setParity(QSerialPort::NoParity);
            sserial.setStopBits(QSerialPort::OneStop);
            sserial.setFlowControl(QSerialPort::NoFlowControl);
            extern char spdid;
            extern char gapid;
            QString dataBuf = "speed_id" + spdid;
            //sserial.write(dataBuf);
            dataBuf = "gap_id" + gapid;
            //sserial.write(dataBuf);

            qDebug()<<dataBuf;
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
