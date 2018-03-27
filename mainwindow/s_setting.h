#ifndef S_SETTING_H
#define S_SETTING_H

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QTextEdit>

#define SSETTING_WIDGET_WIDTH     320
#define SSETTING_WIDGET_HEIGHT    200

class S_setting : public QWidget
{
    Q_OBJECT
public:
    explicit S_setting(QWidget *parent = 0);
    ~S_setting();

private:
    QPushButton *sendBtn;

    QRadioButton *sped0;
    QRadioButton *sped1;
    QRadioButton *sped2;

    QRadioButton *gap0;
    QRadioButton *gap1;
    QRadioButton *gap2;

    QLabel *spLow;
    QLabel *spMid;
    QLabel *spHgh;

    QLabel *gpNar;
    QLabel *gpMid;
    QLabel *gpWid;

    void scanUiComponent(void);

public slots:
    void sendBtnClicked(void);
};
#endif // S_SETTING_H
