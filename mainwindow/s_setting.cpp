#include "s_setting.h"
#include <QFrame>
#include <QFont>
#include <QVBoxLayout>
#include <QHBoxLayout>

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

    sped0 = new QRadioButton(tr("Low Speed "));
    sped1 = new QRadioButton(tr("Middle Speed"));
    sped2 = new QRadioButton(tr("High Speed"));
    spedGroup = new QButtonGroup(this);
    spedGroup->addButton(sped0,0);
    spedGroup->addButton(sped1,1);
    spedGroup->addButton(sped2,2);

    gap0 = new QRadioButton(tr("Narow Gap "));
    gap1 = new QRadioButton(tr("Middle Gap  "));
    gap2 = new QRadioButton(tr("Wide Gap"));
    gapGroup = new QButtonGroup(this);
    gapGroup->addButton(gap0,0);
    gapGroup->addButton(gap1,1);
    gapGroup->addButton(gap2,2);


    QHBoxLayout *spdLayout = new QHBoxLayout;
    spdLayout->addWidget(sped0);
    spdLayout->addWidget(sped1);
    spdLayout->addWidget(sped2);

    QHBoxLayout *gapLayout = new QHBoxLayout;
    gapLayout->addWidget(gap0);
    gapLayout->addWidget(gap1);
    gapLayout->addWidget(gap2);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addStretch(1);
    mainLayout->addLayout(spdLayout);
    mainLayout->addStretch(2);
    mainLayout->addLayout(gapLayout);
    mainLayout->addStretch(3);

    setLayout(mainLayout);

    sendBtn = new QPushButton(this);
    sendBtn->setText(tr("Scan"));
    sendBtn->setGeometry(SSETTING_WIDGET_WIDTH-60, SSETTING_WIDGET_HEIGHT-40, 40, 20);
    connect(sendBtn, SIGNAL(clicked(bool)), this, SLOT(sendBtnClicked()));
}

