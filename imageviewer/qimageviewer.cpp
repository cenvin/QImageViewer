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
    //initImageResource();
    QString filename1 = QFileDialog::getSaveFileName(this, tr("Save Image:"), "", tr("Images(*.png *.jpg)"));
    image.save(filename1);
//    qDebug()<<"save:"<<image.size();
    return upgradeFileInfo(filename, angle, 10);
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
void QImageViewer::RD_algorithm(QVector <QVector<std::complex<double>>> &imgDataNew){
    double pi = 3.141592;
    double c = 300000000.0;
    double fc = 3000000000.0;
    double wc = 2*pi*fc;
    double lamda = c/fc;
    double Tr = 0.0000015;
    double Br = 150000000.0;
    double Kr = Br/Tr;

    double H = 3000.0;
    double ThetaCenter = 45.0/180*pi;
    double Platform_center[3] = {0,0,H};
    double Y_C = H*tan(ThetaCenter);
    double Scene_center[3] = {0,Y_C,0};
    double delta_X = 150.0;
    double delta_Y = 100.0;
    double Xmin = -delta_X / 2;
    double Xmax = delta_X / 2;
    double Ymin = -delta_Y / 2;
    double Ymax = delta_Y / 2;
    double RC0 = sqrt(pow(Scene_center[0]-Platform_center[0],2)+
            pow(Scene_center[1]-Platform_center[1],2)+
            pow(Scene_center[2]-Platform_center[2],2));

    double rho_R = c/(2*Br);
    double rch_Y = rho_R/sin(ThetaCenter);
    double rho_AT = rho_R;

    double V = 150.0;
    double D = 2*rho_AT;
    double Lsar = lamda * RC0 / D;
    double Tsar = Lsar / V;

    double Rate_Fs = 1.2;
    long int Fs = round(Rate_Fs * Br);
    double Ts = 1.0 / Fs;
    double delta_Rs = Ts * c;
    double Rmin = sqrt(pow((Y_C + Ymin),2) + pow(H,2));
    double Rmax = sqrt(pow((Y_C + Ymax),2) + pow((Lsar/2),2) + pow(H,2));
    double Nfast = ceil((2 * (Rmax-Rmin) / c + Tr) / Ts);
    int Nf = nextpow2(Nfast);
    QVector<double> tf_org;
    QVector<double> tf;
    QVector<double> tr;
    for(int i=0;i<Nf;i++){
        tf_org.push_back((i - Nf/2) * Ts);
        tf.push_back((2 * RC0 / c) + tf_org.at(i));
        tr.push_back(tf.at(i) * c / 2);
    }
    double Ka = -2 * pow(V,2) / (lamda * RC0);
    double Ba = abs(Ka * Tsar);
    double Rate_PRF = 1.25;
    double PRF = round(Rate_PRF * Ba);
    double PRT = 1.0 / PRF;

    double Nslow = ceil((delta_X + Lsar) / V / PRT);
    double Ns  = nextpow2(Nslow);
    QVector<double> ts;
    QVector<double> ta;
    for(int i=0;i<Ns;i++){
        ts.push_back((i - Ns/2) * PRT);
        ta.push_back(ts.at(i) * V);
    }

    QVector<std::complex<double>> h_ref(520);
    for(int i=0;i<Nf;i++){
        double rel = (cos(i * pi * Kr * pow(tf_org.at(i),2)) * (abs(tf_org.at(i)) <= Tr/2));
        double img = (sin(i * pi * Kr * pow(tf_org.at(i),2)) * (abs(tf_org.at(i)) <= Tr/2));
        h_ref[i] = std::complex<double> (rel , img);

        double w=0.54-0.46*cos(2.0*pi*i/(Nf-1));     //hamming window
        h_ref[i] = h_ref.at(i) * w;
        qDebug()<<i<<"h_ref="<<h_ref[i].real();
    }

}

int QImageViewer::nextpow2(int temp)
{
    int t = 0;
    while(1){
        if(pow(2,++t)>temp)
            break;
    }
   return pow(2,t);
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

    //std::complex<double> imgDataNew[520][520];
    QVector <QVector<std::complex<double>>> imgDataNew(520);
    for (int i = 0 ; i<imgDataNew.size() ; i++)
        imgDataNew[i].resize(520);

    //bool ok;

    for(int i = 0 ; i < imgHeight ; i++)
    {
         QStringList tempbar = tempOption.at(i).split(",");
         for(int j = 0 ; j < imgWidth ; j++)
         {             
             //imgDataNew[i][j] = tempbar[j].toInt(&ok, 10);
             //std::complex<double> temp;
             //QString str = "1.12566+2.52551i";
             int plus = tempbar[j].indexOf('+');
             int minus = tempbar[j].indexOf('-',2);
             int conj = tempbar[j].indexOf('i');
             double rel,img;
             if(tempbar[j].indexOf('i') == -1){
                 rel = 0;
                 img = 0;
             }
             else if(tempbar[j].indexOf('-') == 0){

                 if(minus == -1){                                                   //-+
                     rel = -tempbar[j].mid(1,plus-1).toDouble();
                     img = tempbar[j].mid(plus+1,conj-plus-2).toDouble();
                 }
                 else{
                     rel = -tempbar[j].mid(1,minus-1).toDouble();                   //--
                     img = -tempbar[j].mid(minus+1,conj-minus-2).toDouble();
                 }
             }
             else {

                 if(tempbar[j].indexOf('+') == -1){                                 //+-
                    rel = tempbar[j].mid(0,minus-1).toDouble();
                    img = -tempbar[j].mid(minus+1,conj-minus-2).toDouble();
                 }
                 else{                                                              //++
                    rel = tempbar[j].mid(0,plus-1).toDouble();
                    img = tempbar[j].mid(plus+1,conj-plus-2).toDouble();
                    }
             }

             imgDataNew[i][j] = std::complex<double>(rel , img);
             //qDebug()<<"("<<i<<","<<j<<")="<<imgDataNew[i][j].real()<<"+i*"<<imgDataNew[i][j].imag();
         }
    }
    file.close();

    //qDebug()<<imgDataNew[331][130].real();
    RD_algorithm(imgDataNew);

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
            b = imgDataNew[i][j].real()*255;
            g = b;
            r = g;
            desImage.setPixel(j,i,qRgb(r,g,b));
        }
    }

    image = desImage;
    imgRotate = desImage.transformed(matrix);

    qDebug()<<"upgrad:"<<image.size();


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
