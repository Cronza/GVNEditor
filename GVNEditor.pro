QT += widgets
QT += xml

FORMS       = \
    GVNEditor.ui
HEADERS     = \
    StoryBuilder/ChapterTable.h \
    StoryBuilder/SettingItem.h \
    GVNEditor.h \
    Utilities/Logger.h
RESOURCES   = \
    Resources/Icons/icons.qrc \
    Resources/Examples/examples.qrc \
    Resources/Templates/templates.qrc
SOURCES     = \
    StoryBuilder/ChapterTable.cpp \
    Main.cpp \
    StoryBuilder/SettingItem.cpp \
    GVNEditor.cpp \
    Utilities/Logger.cpp
