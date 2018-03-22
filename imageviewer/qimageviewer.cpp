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
    index = -1;
    angle = 0;
    size = QSize(0, 0);

    filename.clear();
    path.clear();
}

int QImageViewer::loadImageResource(void)
{
    //qDebug() << QImageReader::supportedImageFormats();
    filename = QFileDialog::getOpenFileName(this, tr("Select image:"),
        "D:\\Documents\\Pictures", tr("Images (*.jpg *.jpeg *.png *.bmp *.gif)"));
    if (filename.isEmpty()) {
        return -1;
    }

    /* get file list */
    getFileInfoList();

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

    /* get file list */
    getFileInfoList();

    /* load file info */
    upgradeFileInfo(filename, angle, 10);

    return 0;
}

int QImageViewer::upgradeFileInfo(QString &filename,int angle,int sizeScale)
{
    QImage imgRotate;
    QMatrix matrix;
    QImage imgScaled;

    if (filename.isEmpty()) {
        return -1;
    }

    fileInfo = QFileInfo(filename);
    if (!image.load(filename)) {
        return -1;
    }

    /* modify angle */
    matrix.rotate(angle * 90);
    imgRotate = image.transformed(matrix);

    if (size == QSize(0, 0)) {
        size = image.size();
    }

    /* modify scale */
    imgScaled = imgRotate.scaled(size.width() * sizeScale / 10,
                                 size.height() * sizeScale / 10,
                                 Qt::KeepAspectRatio);

    /* upgrade pixmap */
    pixmap = QPixmap::fromImage(imgScaled);
    size = pixmap.size();

    /* upgrade index */
    index = getFileCurIndex();

    return 0;
}

int QImageViewer::getFileInfoList(void)
{
    QFileInfo info;
    QFileInfoList infoList;

    path = QFileInfo(filename).absolutePath();
    dir = QFileInfo(filename).absoluteDir();

    /* clear list */
    fileInfoList.clear();

    infoList = dir.entryInfoList(QDir::Files);
    for (int i = 0; i < infoList.count(); i++) {
        info = infoList.at(i);
        QString suffix = info.suffix();

        if (suffix == "jpg" || suffix == "bmp" || suffix == "png"
            || suffix == "gif" || suffix == "jpeg") {
            fileInfoList.append(info);
        }
    }

    return 0;
}

int QImageViewer::getFileCurIndex(void)
{
    QFileInfo info;
    int j;

    if (fileInfoList.count() <= 0) {
        qDebug() << "fileInfoList is NULL!";
        return -1;
    }

    for (j = 0; j < fileInfoList.count(); j++) {
        info = fileInfoList.at(j);
        if (info.fileName() == fileInfo.fileName()) {
            break;
        }
    }

    if (j >= fileInfoList.count()) {
        qDebug() << "Not find current file!";
        return -1;
    }

    index = j;
    //qDebug() << "Current fileInfo index: " << index;

    return index;
}
