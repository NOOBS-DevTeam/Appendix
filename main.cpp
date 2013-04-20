#include "mainwindow.h"
#include <QApplication>
#include <QtPrintSupport/QPrinter>

QString strtoint(int a)
{
	char n[100];
	sprintf(n,"%d",a);
	return QString(n);
}

QString readFile(QString filename) //считывание из файла
{
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return NULL;
	}
	QByteArray total;
	QByteArray line;
	while (!file.atEnd())
	{
		 line = file.read(1024);
		 total.append(line);
	}

	return QString(total);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
