#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SyntaxHighlighter.h"
#include "Editor.h"
#include <string.h>
#include <stdio.h>
#include <strstream>
#include <vector>
#include <QFileDialog>
#include <QFile>
#include <QFont>
#include <QDebug>
#include <QTextStream>
#include <QProcess>

int n=0,cur_tab=0; //текущий таб
std::vector<Editor*> tabs;
QString cpError;
QProcess *cp;
lang_t cur_lang=CPP;

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
		return NULL;
	QByteArray total;
	QByteArray line;
	while (!file.atEnd())
	{
		 line = file.read(1024);
		 total.append(line);
	}

	return QString(total);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->splitter_2->setSizes(QList<int> () << 600 << 200);
    ui->splitter->setSizes(QList<int> () << 700 << 170 );
	cp = new QProcess(this);
	connect(cp,SIGNAL(readyReadStandardOutput()),SLOT(slotDataOnStdout()));
	connect(cp,SIGNAL(readyReadStandardError()),SLOT(slotDataOnError()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
	delete tabs[index];
	tabs.erase(tabs.begin()+index);
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
	cur_tab=index;
}

void MainWindow::on_lineEdit_returnPressed()// ввод из поля ввода в поле вывода
{
    ui->textEdit->insertPlainText(ui->lineEdit->text()+"\n");
	cp->write((ui->lineEdit->text().toStdString()+"\n").c_str());
	cp->waitForBytesWritten();
    ui->lineEdit->clear();
}

void MainWindow::on_action_2_triggered()
{
	tabs.push_back(new Editor(CPP));
	ui->tabWidget->addTab(tabs.back(),QString("Tab")+QString(strtoint(n)));
	n++;
	tabs.back()->setText(readFile(QFileDialog::getOpenFileName(this,("Открыть файл"), "", ("Файл Appendix(*.apx)")))+'\n');
}

void MainWindow::on_action_triggered()
{
	tabs.push_back(new Editor(cur_lang));
	ui->tabWidget->addTab(tabs.back(),QString("Tab")+QString(strtoint(n)));
	n++;
}

void MainWindow::on_action_23_triggered()
{
	ui->textEdit->clear();
}

void MainWindow::on_action_24_triggered()
{
	QString format,compiler;
	switch (tabs[cur_tab]->getLang())
	{
	case CPP:
		format = "cpp";
		compiler = "g++ temp.cpp";
		break;
	case PASCAL:
		format = "pas";
		compiler = "fpc temp.pas";
		break;
	}

	QString str = tabs[cur_tab]->toPlainText();
	QFile("temp."+format).remove();
	QFile file("temp."+format);
	file.open(QIODevice::Append | QIODevice::Text);
	QTextStream out(&file);
	out << str;
	out << "\n";
	file.close();
	cp->start(compiler);
	cp->waitForFinished();
	if (!(QFile::exists("a.exe")||QFile::exists("temp.exe")))
	{
		qDebug() << "Error";
		ui->textEdit->append(cpError);
	}
	else
	{
		cp->start(cur_lang==CPP?"a.exe":"temp.exe");
		cp->waitForStarted();
		cp->waitForFinished();
		QFile(cur_lang==CPP?"a.exe":"temp.exe").remove();
	}
}

void MainWindow::on_action_3_triggered()
{
    QString str = tabs[cur_tab]->toPlainText();
    QString filename;
	filename = QFileDialog::getSaveFileName(this,tr("Save Document"),"sdfsdf",tr("Documents (*.apx)") );
	QFile file(filename);
	file.open(QIODevice::Append | QIODevice::Text);
	QTextStream out(&file);
	out << str;
	out << "\n";
	file.close();

}

void MainWindow::slotDataOnStdout()
{
	ui->textEdit->append(cp->readAllStandardOutput());
}

void MainWindow::slotDataOnError()
{
    QString error=QString(cp->readAllStandardError());
    error.remove(0,(error.lastIndexOf("error:")+6));
    cpError = QString("ERROR:")+(error);
}

void MainWindow::on_pushButton_clicked()
{
	if (cur_lang == CPP)
		cur_lang = PASCAL;
	else
		cur_lang = CPP;
	tabs[cur_tab]->setLang(CPP);
}
