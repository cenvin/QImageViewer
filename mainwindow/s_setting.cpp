#include "s_setting.h"
#include <QFrame>
#include <QFont>
#include <QVBoxLayout>
#include <QHBoxLayout>

#define SAFE_FREE(p) {if(p != NULL) {delete p; p = NULL;}}

char spdid = 0;
char gapid = 0;
S_setting::S_setting(QWidget *parent) : QWidget(parent)
{
    scanUiComponent();

}

S_setting::~S_setting()
{
    SAFE_FREE(sped0);
    SAFE_FREE(sped1);
    SAFE_FREE(sped2);
    SAFE_FREE(gap0);
    SAFE_FREE(gap1);
    SAFE_FREE(gap1);
    SAFE_FREE(sendBtn);
}

QString portName;
void S_setting::sendBtnClicked(void)
{
    //TBD
    portName = comPort->text();
    serial mySerial;
    mySerial.sendSerial();

    this->close();
}

void S_setting::scanUiComponent(void)
{

    sped0 = new QRadioButton(tr("Low Speed "));
    sped0->setChecked(true);
    sped1 = new QRadioButton(tr("Middle Speed"));
    sped2 = new QRadioButton(tr("High Speed"));
    spedGroup = new QButtonGroup(this);
    spedGroup->addButton(sped0,0);
    spedGroup->addButton(sped1,1);
    spedGroup->addButton(sped2,2);

    gap0 = new QRadioButton(tr("Narow Gap "));
    gap0->setChecked(true);
    gap1 = new QRadioButton(tr("Middle Gap  "));
    gap2 = new QRadioButton(tr("Wide Gap"));
    gapGroup = new QButtonGroup(this);
    gapGroup->addButton(gap0,0);
    gapGroup->addButton(gap1,1);
    gapGroup->addButton(gap2,2);

    serialPort = new QLabel(tr("Input Your Serial Port(exm.COM4):"));
    comPort = new QLineEdit;
    comPort->setMaximumWidth(60);
    comPort->setText("COM4");

    QHBoxLayout *spdLayout = new QHBoxLayout;
    spdLayout->addWidget(sped0);
    spdLayout->addWidget(sped1);
    spdLayout->addWidget(sped2);

    QHBoxLayout *gapLayout = new QHBoxLayout;
    gapLayout->addWidget(gap0);
    gapLayout->addWidget(gap1);
    gapLayout->addWidget(gap2);

    QHBoxLayout *textLayout = new QHBoxLayout;
    textLayout->addStretch();
    textLayout->addWidget(serialPort);
    textLayout->addWidget(comPort);
    textLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addStretch(1);
    mainLayout->addLayout(spdLayout);
    mainLayout->addStretch(1);
    mainLayout->addLayout(gapLayout);
    mainLayout->addStretch(1);
    mainLayout->addLayout(textLayout);
    mainLayout->addStretch(3);

    setLayout(mainLayout);


    connect(spedGroup, SIGNAL(buttonClicked(int)), this, SLOT(spedButtonsClicked(int)));
    connect(gapGroup, SIGNAL(buttonClicked(int)), this, SLOT(gapButtonsClicked(int)));

    sendBtn = new QPushButton(this);
    sendBtn->setText(tr("Scan"));
    sendBtn->setGeometry(SSETTING_WIDGET_WIDTH-60, SSETTING_WIDGET_HEIGHT-40, 40, 20);
    connect(sendBtn, SIGNAL(clicked(bool)), this, SLOT(sendBtnClicked()));
}

void S_setting::spedButtonsClicked(int id)
{
    qDebug("Clicked_spd: %d", id);
    spdid = id;

}

void S_setting::gapButtonsClicked(int id)
{
    qDebug("Clicked_gap: %d", id);
    gapid = id;

}
