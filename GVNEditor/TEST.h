#pragma once

#include <QMainWindow>
#include "ui_TEST.h"

class TEST : public QMainWindow
{
	Q_OBJECT

public:
	TEST(QWidget *parent = Q_NULLPTR);
	~TEST();

private:
	Ui::TEST ui;
};
