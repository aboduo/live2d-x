#-------------------------------------------------
#
# Project created by QtCreator 2014-04-05T21:37:14
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = live2d_x_editor
TEMPLATE = app
DEFINES = __QT__

SOURCES += main.cpp\
        EditorWindow.cpp \
    OpenGLView.cpp \ 
    ../live2d_x/sources/Live2dXSprite.cpp \
    cocos2d/PlistParser.cpp \
    cocos2d/CCString.cpp \
    cocos2d/CCDictionary.cpp \
    cocos2d/tinyxml2/tinyxml2.cpp \
    cocos2d/CCObject.cpp \
    cocos2d/CCSprite.cpp \
    cocos2d/CCArray.cpp \
    cocos2d/ccCArray.cpp \
    cocos2d/CCAutoreleasePool.cpp \

HEADERS  += EditorWindow.h \
    OpenGLView.h \ 
    ../live2d_x/sources/live2d_x/Live2dXTypes.h \
    ../live2d_x/sources/Live2dXSprite.h \
    cocos2d/PlistParser.h \
    cocos2d/CCString.h \
    cocos2d/CCDictionary.h \
    cocos2d/tinyxml2/tinyxml2.h \
    cocos2d/CCObject.h \
    cocos2d/CCSprite.h \
    cocos2d/CCArray.h \
    cocos2d/ccCArray.h \
    cocos2d/CCTime.h \
    cocos2d/CCTypes.h \
    cocos2d/uthash.h \
    cocos2d/CCInteger.h \
    cocos2d/CCAutoreleasePool.h \

FORMS    += EditorWindow.ui

RESOURCES += \
    res.qrc \
    shaders.qrc
