#ifndef SERIAL_H
#define SERIAL_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QTime>
#include <QWidget>
#include <QMessageBox>


class serial : public QWidget
{
    Q_OBJECT
public:
    explicit serial(QWidget *parent = 0);
    ~serial();
    QSerialPort *sserial;
    void sendSerial(void);
    static QByteArray QString2Hex(QString);
    static char ConvertHexChar(char);
private:
    void initSerial(void);
    QString dataBuf;

};

#endif // SERIAL_H
