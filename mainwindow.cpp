#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <stdio.h>


int n=0,cur_tab=0;// кол-во табов, текущий таб
QTextEdit *tabs[100];

QString strtoint(int a)
{
    char n[100];
    sprintf(n,"%d",a);
    return QString(n);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->splitter_2->setSizes(QList<int> () << 600 << 200);
	ui->splitter->setSizes(QList<int> () << 700 << 100 );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    delete tabs[index+1];
    cur_tab--;
    n--;
}

void MainWindow::on_pushButton_clicked()
{
    n++;
    tabs[n]= new QTextEdit;
    ui->tabWidget->addTab(tabs[n],QString("Tab")+QString(strtoint(n)));
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->setText(tabs[cur_tab]->toPlainText());
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    cur_tab=index+1;
}

void MainWindow::on_lineEdit_returnPressed()// ввод из поля ввода в поле выхода
{
    ui->textEdit->insertPlainText(ui->lineEdit->text()+"\n");
    ui->lineEdit->clear();
}

void MainWindow::on_pushButton_3_clicked()//очистить поле вывода
{
    ui->textEdit->clear();
}
