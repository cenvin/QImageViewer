# QT for image viewer
# author    hancq
# date      2016-10-18
QT += widgets
QT       += serialport
TARGET = QImageViewer

SOURCES += \
    main.cpp

RESOURCES += \
    images.qrc

INCLUDEPATH += mainwindow

include(mainwindow/mainwindow.pri)
include(imageviewer/imageviewer.pri)

#win32: LIBS += -L$$PWD/'../../../Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft/' -llibeng

#INCLUDEPATH += $$PWD/'../../../Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft'
#DEPENDPATH += $$PWD/'../../../Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft'

#win32: LIBS += -L$$PWD/'../../../Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft/' -llibmat

#INCLUDEPATH += $$PWD/'../../../Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft'
#DEPENDPATH += $$PWD/'../../../Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft'

#win32: LIBS += -L$$PWD/'../../../Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft/' -llibmx

#INCLUDEPATH += $$PWD/'../../../Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft'
#DEPENDPATH += $$PWD/'../../../Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft'

#win32: LIBS += -L$$PWD/'../../../Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft/' -llibmex

#INCLUDEPATH += $$PWD/'../../../Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft'
#DEPENDPATH += $$PWD/'../../../Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft'
