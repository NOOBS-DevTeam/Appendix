#include "helpdialog.h"
#include "ui_helpdialog.h"
#include <QTextBrowser>
#include <QUrl>
#include <QStringList>
#include <QDebug>
#include <QTextCodec>
QString readFile(QString filename);

helpdialog::helpdialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::helpdialog)
{

	QStringList qstl;
	qstl.append(QString(":/doc/"));
	ui->setupUi(this);
	ui->textBrowser->setSearchPaths(QStringList() << ":/doc");
	ui->textBrowser->setSource(QUrl("index.html"));
	qDebug()<< ui->textBrowser->source();
}

helpdialog::~helpdialog()
{
	delete ui;
}
