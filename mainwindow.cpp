#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SyntaxHighlighter.h"
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
std::vector<QTextEdit *> tabs;
QString cpError,source="#include <iostream>\n\nusing namespace std;\n\nint main()\n\{\n    cout << \"Hello world!\" << endl;\n    return 0;\n\}";
QProcess *cp;

QString strtoint(int a)
{
	char n[100];
	sprintf(n,"%d",a);
	return QString(n);
}

void MainWindow::initntab()
{
	tabs.push_back( new QTextEdit);
	ui->tabWidget->addTab(tabs.back(),QString("Tab")+QString(strtoint(n)));
	QFont fnt("Consolas",9,QFont::Normal);
	tabs.back()->document()->setDefaultFont(fnt);
	new SyntaxHighlighter(tabs.back()->document());
	QPalette pal = tabs.back()->palette();
	pal.setColor(QPalette::Base, Qt::white);
	pal.setColor(QPalette::Text, Qt::black);
	tabs.back()->setPalette(pal);
    tabs.back()->append(source);
	n++;
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
	initntab();
    tabs.back()->setText(readFile(QFileDialog::getOpenFileName(this,("Открыть файл"), "", ("Файл Appendix(*.apx)")))+'\n');
}

void MainWindow::on_action_triggered()
{
	initntab();
}

void MainWindow::on_action_23_triggered()
{
    ui->textEdit->clear();
}

void MainWindow::on_action_24_triggered()
{
	QString str = tabs[cur_tab]->toPlainText();
	QFile("temp.cpp").remove();
	QFile file("temp.cpp");
	file.open(QIODevice::Append | QIODevice::Text);
	QTextStream out(&file);
	out << str;
	out << "\n";
	file.close();
	cp->start(("g++ temp.cpp"));
	cp->waitForFinished();
	if (!QFile::exists("a.exe"))
	{
		qDebug() << "Error";
		ui->textEdit->append(cpError);
	}
	else
	{
		cp->start("a.exe");
		cp->waitForStarted();
		//cp->waitForFinished();
		//QFile("a.exe").remove();
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
