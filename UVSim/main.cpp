#include "UVSim.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	UVSim w;
	w.show();
	return a.exec();
}
