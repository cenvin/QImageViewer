#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QFileInfoList>
#include <QImage>
#include <QPixmap>

#include "qabout.h"
#include "qimageviewer.h"
#include "s_setting.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

private:
    QMenuBar *menuBar;
    QToolBar *toolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;
    QLabel *imageLabel;
    QAbout aboutWidget;
    S_setting setWidget;

    QPixmap mp;

    /* new class */
    QImageViewer *imageViewer;

    void initMainWindow(void);
    void initUiComponent(void);
    void setQImageViewerWidget(void);
    void setWindowComponet(void);
    void initImageResource(void);
    void loadImageResource(void);

    QAction *openAction;
    QAction *saveAction;
    QAction *toEnlargeAction;
    QAction *toLessenAction;
    QAction *toLeftAction;
    QAction *toRightAction;

    QAction *scanSetting;

public slots:
    void openActionTriggered(void);
    void saveActionTriggered(void);
    void toEnlargeActionTriggered(void);
    void toLeftActionTriggered(void);
    void toRightActionTriggered(void);

    void toLessenActionTriggered(void);
    void aboutTriggered(void);
    void aboutQtTriggered(void);

    void scanSettingTriggred(void);

};

#endif // MAINWINDOW_H
