#ifndef S_SETTING_H
#define S_SETTING_H

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QLabel>
#include <QLineEdit>

#include "serial.h"

#define SSETTING_WIDGET_WIDTH     340
#define SSETTING_WIDGET_HEIGHT    200

extern char spdid;
extern char gapid;
class S_setting : public QWidget
{
    Q_OBJECT
public:
    explicit S_setting(QWidget *parent = 0);
    ~S_setting();

private:
    QPushButton *sendBtn;

    QButtonGroup *spedGroup;
    QRadioButton *sped0;
    QRadioButton *sped1;
    QRadioButton *sped2;

    QButtonGroup *gapGroup;
    QRadioButton *gap0;
    QRadioButton *gap1;
    QRadioButton *gap2;

    QLabel *serialPort;
    QLineEdit *comPort;

    void scanUiComponent(void);

public slots:
    void sendBtnClicked(void);
    void spedButtonsClicked(int);
    void gapButtonsClicked(int);
};
#endif // S_SETTING_H
