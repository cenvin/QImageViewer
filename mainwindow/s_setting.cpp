#include "s_setting.h"
#include <QFrame>
#include <QFont>

#define SAFE_FREE(p) {if(p != NULL) {delete p; p = NULL;}}

S_setting::S_setting(QWidget *parent) : QWidget(parent)
{
    scanUiComponent();
}

S_setting::~S_setting()
{
    SAFE_FREE(spLow);
    SAFE_FREE(spMid);
    SAFE_FREE(spHgh);
    SAFE_FREE(gpNar);
    SAFE_FREE(gpMid);
    SAFE_FREE(gpWid);
    SAFE_FREE(sendBtn);
}

void S_setting::sendBtnClicked(void)
{
    //TBD
    this->close();
}

void S_setting::scanUiComponent(void)
{
    spLow = new QLabel(this);
    spLow->setText(tr("Low Speed"));
    spLow->setGeometry(20, 30, 80, 40);
    spMid = new QLabel(this);
    spMid->setText(tr("Middle Speed"));
    spMid->setGeometry(120, 30, 80, 40);
    spHgh = new QLabel(this);
    spHgh->setText(tr("High Speed"));
    spHgh->setGeometry(220, 30, 80, 40);

    gpNar = new QLabel(this);
    gpNar->setText(tr("Narrow Gap"));
    gpNar->setGeometry(20, 100, 60, 40);
    gpMid = new QLabel(this);
    gpMid->setText(tr("Middle Gap"));
    gpMid->setGeometry(120, 100, 60, 40);
    gpWid = new QLabel(this);
    gpWid->setText(tr("Wide Gap"));
    gpWid->setGeometry(220, 100, 60, 40);

    sped0 = new QRadioButton(this);
    sped0->setGeometry(40, 25, 15, 15);
    sped1 = new QRadioButton(this);
    sped1->setGeometry(140, 25, 15, 15);
    sped2 = new QRadioButton(this);
    sped2->setGeometry(240, 25, 15, 15);

    gap0 = new QRadioButton(this);
    gap0->setGeometry(40, 95, 15, 15);
    gap1 = new QRadioButton(this);
    gap1->setGeometry(140, 95, 15, 15);
    gap2 = new QRadioButton(this);
    gap2->setGeometry(240, 95, 15, 15);

    sendBtn = new QPushButton(this);
    sendBtn->setText(tr("OK"));
    sendBtn->setGeometry(260, 160, 40, 20);
    connect(sendBtn, SIGNAL(clicked(bool)), this, SLOT(sendBtnClicked()));
}

