#ifndef QIMAGEVIEWER_H
#define QIMAGEVIEWER_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QDir>
#include <QSize>
#include <QFileInfo>
#include <math.h>
#include <complex>
#include <stdio.h>
#include <QVector>
#include <engine.h>
#include "mex.h"

class QImageViewer : public QWidget
{
    Q_OBJECT
public:
    explicit QImageViewer(QWidget *parent = 0);
    explicit QImageViewer(QWidget *parent,QString &caption,QString &dir,QString &filer);
    ~QImageViewer();

    QWidget *parent;

    int angle;
    QSize size;
    QString filename;
    QString path;
    QDir dir;
    QFileInfo fileInfo;

    QImage desImage;

    QImage image;
    QPixmap pixmap;

    /* open a file */
    int openImageFile(const QString &caption,const QString &dir,const QString &filer);

    /* save file */
    int saveImageFile(void);

    /* change image */
    int zoomIn(void);
    int zoomOut(void);
    int spinToRight(void);
    int spinToLeft(void);

private:
    /* init param */
    void initImageResource(void);

    /* open a image */
    int loadImageResource(void);
    int loadImageResource(const QString &caption,const QString &dir,const QString &filer);

    int upgradeFileInfo(QString &filename,int angle,int sizeScale);

    void RD_algorithm(QVector <QVector<std::complex<double>>> &imgDataNew);

    int nextpow2(int temp);

public slots:
};

#endif // QIMAGEVIEWER_H
