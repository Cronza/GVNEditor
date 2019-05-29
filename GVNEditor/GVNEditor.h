#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GVNEditor.h"

class GVNEditor : public QMainWindow
{
	Q_OBJECT

public:
	GVNEditor(QWidget *parent = Q_NULLPTR);

private:
	Ui::GVNEditorClass ui;
};
