#include "qimageviewer.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QImageReader>

QImageViewer::QImageViewer(QWidget *parent) : QWidget(parent)
{
    this->parent = parent;
    initImageResource();
}

QImageViewer::QImageViewer(QWidget *parent,
                           QString &caption,
                           QString &dir,
                           QString &filer)
{
    this->parent = parent;
    initImageResource();
    loadImageResource(caption, dir, filer);
}

QImageViewer::~QImageViewer(void)
{
    this->parent = NULL;
}

int QImageViewer::openImageFile(const QString &caption,
                                const QString &dir,
                                const QString &filer)
{
    initImageResource();
    return loadImageResource(caption, dir, filer);
}

int QImageViewer::saveImageFile(void)
{
    initImageResource();
    return 0;
    /*
     *
     *
     *
     * T
     * B
     * D
     *
     *
     */
}

int QImageViewer::zoomIn(void)
{
    return upgradeFileInfo(filename, angle, 12);
}

int QImageViewer::zoomOut(void)
{
    return upgradeFileInfo(filename, angle, 8);
}

int QImageViewer::spinToRight(void)
{
    angle += 1;
    angle = angle % 4;

    /* load file info */
    return upgradeFileInfo(filename, angle, 10);
}

int QImageViewer::spinToLeft(void)
{
    angle += 3;
    angle = angle % 4;

    /* load file info */
    return upgradeFileInfo(filename, angle, 10);
}

void QImageViewer::initImageResource(void)
{
    angle = 0;
    size = QSize(0, 0);

    filename.clear();
    path.clear();
}

int QImageViewer::loadImageResource(void)
{
    //qDebug() << QImageReader::supportedImageFormats();
    filename = QFileDialog::getOpenFileName(this, tr("Select data:"),
        "D:\\Documents", tr("Data (*.csv)"));
    if (filename.isEmpty()) {
        return -1;
    }

    /* load file info */
    upgradeFileInfo(filename, angle, 10);

    return 0;
}

int QImageViewer::loadImageResource(const QString &caption,
                                    const QString &directory,
                                    const QString &filer)
{
    filename = QFileDialog::getOpenFileName(this,caption,directory,filer);
    if (filename.isEmpty()) {
        return -1;
    }

//    QFileDialog *fd = new QFileDialog(this);
//    QString filename = fd->getOpenFileName(this,caption,directory,filer);//(this,tr("Open File"),"D:\\Documents",tr("Excel(*.csv)"));
//    if(filename==NULL)
//        return -1;

    /* load file info */
    upgradeFileInfo(filename, angle, 10);

    return 0;
}

int QImageViewer::upgradeFileInfo(QString &filename,int angle,int sizeScale)
{
    QImage imgRotate;
    QMatrix matrix;
    QImage imgScaled;

    fileInfo = QFileInfo(filename);

    /* modify angle */
    matrix.rotate(angle * 90);
//    imgRotate = image.transformed(matrix);

    QDir dir = QDir::current();
    QFile file(dir.filePath(filename));
    if(!file.open(QIODevice::ReadOnly))
         qDebug()<<"OPEN FILE FAILED";
    QTextStream * out = new QTextStream(&file);
    QStringList tempOption = out->readAll().split("\n");

    int imgHeight = tempOption.count()-1;
    int imgWidth = tempOption.at(1).split(",").count();
    QVector <QVector<int>> imgDataNew(512);
    for (int i = 0 ; i<imgDataNew.size() ; i++)
        imgDataNew[i].resize(512);

    bool ok;

    for(int i = 0 ; i < tempOption.count()-1 ; i++)
    {
         QStringList tempbar = tempOption.at(i).split(",");
         for(int j = 0 ; j < tempbar.count() ; j++)
         {
             imgDataNew[i][j]=tempbar[j].toInt(&ok, 10);
             //qDebug()<<imgDataNew[i][j]<<i<<","<<j;

         }
    }
    file.close();
    qDebug()<<imgWidth<<","<<imgHeight;

    desImage = QImage(imgWidth,imgHeight,QImage::Format_RGB32); //RGB32

    //RGB
    int b = 0;
    int g = 0;
    int r = 0;

    //pix
    for (int i=0;i<imgHeight;i++)
    {
        for (int j=0;j<imgWidth;j++)
        {
            //b = (int)*(imgDataNew+i*imgWidth+j);
            b = imgDataNew[i][j];
            g = b;
            r = g;
            desImage.setPixel(j,i,qRgb(r,g,b));
        }
    }

    image = desImage;
    imgRotate = desImage.transformed(matrix);


    if (size == QSize(0, 0)) {
        size = image.size();
    }

    /* modify scale */
    if(sizeScale==10)
    {
        imgScaled = imgRotate.scaled(size.height() ,
                                     size.width() ,
                                     Qt::KeepAspectRatio);
    }else{
        imgScaled = imgRotate.scaled(size.width() * sizeScale / 10,
                                     size.height() * sizeScale / 10,
                                     Qt::KeepAspectRatio);
    }

    /* upgrade pixmap */
    pixmap = QPixmap::fromImage(imgScaled);
    size = pixmap.size();

    return 0;
}
