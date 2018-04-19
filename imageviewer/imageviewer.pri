HEADERS += \
    $$PWD/qimageviewer.h

SOURCES += \
    $$PWD/qimageviewer.cpp

INCLUDEPATH += $$quote(D:/Program Files/MATLAB/MATLAB Production Server/R2015a/extern/include)

INCLUDEPATH += $$quote(D:/Program Files/MATLAB/MATLAB Production Server/R2015a/extern/include/win64)

LIBS+=-L$$quote(D:/Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft) -llibeng

LIBS+=-L$$quote(D:/Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft) -llibmat

LIBS+=-L$$quote(D:/Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft) -llibmx

LIBS+=-L$$quote(D:/Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft) -llibmex

#LIBS+=-L$$quote(D:/Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft) -lmclmcr

#LIBS+=-L$$quote(D:/Program Files/MATLAB/MATLAB Production Server/R2015a/extern/lib/win64/microsoft) -lmclmcrrt
