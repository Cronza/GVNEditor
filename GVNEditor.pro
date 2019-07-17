QT += widgets
requires(qtConfig(treeview))

FORMS       = \
    MainWindow.ui
HEADERS     = \
    MainWindow.h \
    MainWindow.h \
    MainWindow.h \
    StoryBuilder/ChapterTableItem.h \
    StoryBuilder/ChapterTable.h
RESOURCES   = \
    GVNEditor.qrc
SOURCES     = \
    StoryBuilder/ChapterTableItem.cpp \
    StoryBuilder/ChapterTable.cpp \
    MainWindow.cpp \
    Main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/editabletreemodel
INSTALLS += target
