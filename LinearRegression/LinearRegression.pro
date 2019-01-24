CONFIG(debug, debug|release){
    DESTDIR = $$PWD/output/debug
    CONFIG += console
}

CONFIG(release, debug|release){
    DESTDIR = $$PWD/output/release
}

SOURCES += \
    main.cpp \
    linearregression.cpp

HEADERS += \
    linearregression.h
