#include "TEST.h"

TEST::TEST(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

TEST::~TEST()
{
}
