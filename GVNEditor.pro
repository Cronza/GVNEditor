QT += widgets
QT += xml
#requires(qtConfig(treeview))

FORMS       = \
    MainWindow.ui
HEADERS     = \
    MainWindow.h \
    MainWindow.h \
    MainWindow.h \
    StoryBuilder/ChapterTable.h \
    StoryBuilder/SettingItem.h
RESOURCES   = \
    Resources/Icons/icons.qrc \
    Resources/Examples/examples.qrc
SOURCES     = \
    StoryBuilder/ChapterTable.cpp \
    MainWindow.cpp \
    Main.cpp \
    StoryBuilder/SettingItem.cpp

# install
# target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/editabletreemodel
# INSTALLS += target
