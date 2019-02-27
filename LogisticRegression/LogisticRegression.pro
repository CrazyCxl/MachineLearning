CONFIG(debug, debug|release){
    DESTDIR = $$PWD/output/debug
    CONFIG += console
}

CONFIG(release, debug|release){
    DESTDIR = $$PWD/output/release
}

SOURCES += \
    main.cpp \
    logisticregression.cpp

HEADERS += \
    logisticregression.h
