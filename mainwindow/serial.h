#ifndef SERIAL_H
#define SERIAL_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QTime>
#include <QWidget>


class serial : public QWidget
{
    Q_OBJECT
public:
    explicit serial(QWidget *parent = 0);
    ~serial();
    QSerialPort *sserial;
    static void initSerial(void);

};

#endif // SERIAL_H
