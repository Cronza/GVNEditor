#include "GVNEditor.h"
#include "TEST.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//Temporarily disabling the main class
	//GVNEditor w;

	//Loading TEST U.I class for the time being
	TEST t;
	
	t.show();
	return a.exec();
}
