#include "serial.h"
#include <string>

serial::serial(QWidget *parent) : QWidget(parent)
{
    initSerial();
}

serial::~serial()
{
    sserial->clear();
    sserial->close();
    sserial->deleteLater();
}


void serial::initSerial(void)
{

    sserial = new QSerialPort;
    sserial->setPortName("COM4");
    sserial->open(QIODevice::ReadWrite);
    sserial->setBaudRate(QSerialPort::Baud9600);
    sserial->setDataBits(QSerialPort::Data8);
    sserial->setParity(QSerialPort::NoParity);
    sserial->setStopBits(QSerialPort::OneStop);
    sserial->setFlowControl(QSerialPort::NoFlowControl);
    sserial->setDataTerminalReady(true);        //DTR open
    qDebug("initSerial");
    sserial->setDataTerminalReady(false);       //DTR close

}

void serial::sendSerial()
{
    extern char spdid;

    switch (spdid) {
    case 2:
        dataBuf = "03";//speedhigh 65 0x41,shine 3 ,A
        break;
    case 1:
        dataBuf = "02";//speedmid
        break;
    default:
        dataBuf = "01";//speedlow
        break;
    }
    QByteArray sendData = QString2Hex(dataBuf);
    qDebug()<<"sendData:"<<sendData;
    sserial->write(sendData);
    sserial->waitForBytesWritten(1000);         //1s for writting bytes
    qDebug()<<"sended!";

}

QByteArray serial::QString2Hex(QString str)
{
    QByteArray senddata;
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
    return senddata;
}

char serial::ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else return (-1);
}
