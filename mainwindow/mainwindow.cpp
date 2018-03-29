#include "mainwindow.h"

#include <QWidget>
#include <QImage>
#include <QFileDialog>
#include <QPixmap>
#include <QAction>
#include <QMessageBox>
#include <QDebug>
#include <QScrollArea>
#include <QGridLayout>
#include <QErrorMessage>
#include <QApplication>
#include <QVector>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    /* init main window */
    initMainWindow();

    /* init ui */
    initUiComponent();

    /* init resource */
    initImageResource();

    /* create imageViewer */
    imageViewer = new QImageViewer();
}

void MainWindow::initImageResource(void)
{
    imageLabel->clear();
    imageLabel->resize(QSize(1024, 1024));
    setWindowTitle(tr("RadarViewer"));
}

void MainWindow::loadImageResource(void)
{
    //recover here, how to show a grey pic
    imageLabel->setPixmap(imageViewer->pixmap);
    imageLabel->resize(imageViewer->size);
    setWindowTitle(QFileInfo(imageViewer->filename).fileName() + tr(" - RadarViewer"));
//    imageLabel->setPixmap(mp.fromImage(desImage));

}

void MainWindow::openActionTriggered(void)
{
    int ret = imageViewer->openImageFile(tr("Select data:"),
                                         "",
                                         tr("Data (*.csv)"));
    if (ret) {
        QMessageBox::information(this, tr("Error"), tr("Open a file failed!"));
        return ;
    }

    loadImageResource();
}

void MainWindow::saveActionTriggered(void)
{
    //initImageResource();
    loadImageResource();

    imageViewer->saveImageFile();
}

void MainWindow::toLeftActionTriggered(void)
{
    int ret = imageViewer->spinToLeft();
    if (ret) {
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("Open correct data, please!"));
        return ;
    }

    loadImageResource();
}

void MainWindow::toRightActionTriggered(void)
{
    int ret = imageViewer->spinToRight();
    if (ret) {
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("Open correct data, please!"));
        return ;
    }

    loadImageResource();
}

void MainWindow::toEnlargeActionTriggered(void)
{
    int ret = imageViewer->zoomIn();
    if (ret) {
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("Open correct data, please!"));
        return ;
    }

    loadImageResource();
}

void MainWindow::toLessenActionTriggered(void)
{
    int ret = imageViewer->zoomOut();
    if (ret) {
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("Open correct data, please!"));
        return ;
    }

    loadImageResource();
}

void MainWindow::setQImageViewerWidget(void)
{
    /* label show image */
    imageLabel = new QLabel();

    QScrollArea *imageScrollArea = new QScrollArea();
    imageScrollArea->setAlignment(Qt::AlignCenter);
    imageScrollArea->setFrameShape(QFrame::NoFrame);
    imageScrollArea->setWidget(imageLabel);

    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(imageScrollArea, 0, 0);
    centralWidget->setLayout(mainLayout);
}

void MainWindow::setWindowComponet(void)
{
    openAction = new QAction(tr("Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open data."));
    openAction->setIcon(QIcon(":/images/open.png"));

    saveAction = new QAction(tr("Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save image."));
    saveAction->setIcon(QIcon(":/images/save.png"));

    toLeftAction = new QAction(tr("LeftSpin"), this);
    toLeftAction->setStatusTip(tr("To Left."));
    toLeftAction->setIcon(QIcon(":/images/toLeft.png"));

    toRightAction = new QAction(tr("RightSpin"), this);
    toRightAction->setStatusTip(tr("To Right."));
    toRightAction->setIcon(QIcon(":/images/toRight.png"));

    toEnlargeAction = new QAction(tr("Enlarge"), this);
    toEnlargeAction->setStatusTip(tr("To Enlarge."));
    toEnlargeAction->setIcon(QIcon(":/images/large.png"));

    toLessenAction = new QAction(tr("Lessen"), this);
    toLessenAction->setStatusTip(tr("To Lessen."));
    toLessenAction->setIcon(QIcon(":/images/small.png"));

    QAction *exitAction = new QAction(tr("Exit"), this);
    exitAction->setStatusTip(tr("Exit"));
    exitAction->setIcon(QIcon(":/images/quit.png"));
    exitAction->setShortcut(QKeySequence::Quit);

    QAction *aboutQt = new QAction(tr("About Qt"), this);
    aboutQt->setStatusTip(tr("About Qt"));
    aboutQt->setIcon(QIcon(":/images/Qt.png"));

    QAction *about = new QAction(tr("About RadarViewer"), this);
    about->setStatusTip(tr("About RadarViewer"));
    about->setIcon(QIcon(":/images/help.png"));

    QAction *scanSetting = new QAction(tr("Scan Setting"), this);
    scanSetting->setStatusTip(tr("Scan Setting"));
    scanSetting->setIcon(QIcon(":/images/setting.png"));

    QMenu *fileMenu = menuBar->addMenu(tr("File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    QMenu *operationMenu = menuBar->addMenu(tr("Scan"));
    operationMenu->addAction(scanSetting);

    QMenu *helpMenu = menuBar->addMenu(tr("Help"));
    helpMenu->addAction(aboutQt);
    helpMenu->addAction(about);

    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(toLeftAction);
    toolBar->addAction(toRightAction);
    toolBar->addAction(toEnlargeAction);
    toolBar->addAction(toLessenAction);
    toolBar->addAction(about);

    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openActionTriggered()));
    connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(saveActionTriggered()));
    connect(toLeftAction, SIGNAL(triggered(bool)), this, SLOT(toLeftActionTriggered()));
    connect(toRightAction, SIGNAL(triggered(bool)), this, SLOT(toRightActionTriggered()));
    connect(toEnlargeAction, SIGNAL(triggered(bool)), this, SLOT(toEnlargeActionTriggered()));
    connect(toLessenAction, SIGNAL(triggered(bool)), this, SLOT(toLessenActionTriggered()));

    connect(about, SIGNAL(triggered(bool)), this, SLOT(aboutTriggered()));
    connect(aboutQt, SIGNAL(triggered(bool)), this, SLOT(aboutQtTriggered()));
    connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(scanSetting, SIGNAL(triggered(bool)), this, SLOT(scanSettingTriggred()));

}

void MainWindow::aboutQtTriggered(void)
{
    qApp->aboutQt();
}

void MainWindow::aboutTriggered(void)
{
    aboutWidget.setWindowTitle("Help Infomation");
    aboutWidget.setWindowIcon(QIcon(":/images/help.png"));
    aboutWidget.setFixedSize(QABOUT_WIDGET_WIDTH, QABOUT_WIDGET_HEIGHT);

    aboutWidget.show();
}

void MainWindow::scanSettingTriggred(void)
{
    setWidget.setWindowTitle("Scan Setting");
    setWidget.setWindowIcon(QIcon(":/images/setting.png"));
    setWidget.setFixedSize(SSETTING_WIDGET_WIDTH, SSETTING_WIDGET_HEIGHT);

    setWidget.show();
}

void MainWindow::initUiComponent(void)
{
    /* set menu and toolbar */
    setWindowComponet();

    /* image show widget */
    setQImageViewerWidget();
}

void MainWindow::initMainWindow(void)
{
    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    toolBar = new QToolBar(this);
    addToolBar(toolBar);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
}

