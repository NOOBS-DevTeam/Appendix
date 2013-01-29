#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <stdio.h>
#include <vector>


int n=0,cur_tab=0; //текущий таб
std::vector<QTextEdit *> tabs;

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
    ui->tabWidget->removeTab(index);
	delete tabs[index];
	tabs.erase(tabs.begin()+index);
//	for (int i=0;i<=100;i++)
//	{
//		if (dynamic_cast<QTextEdit*>(tabs[i]))
//		{
//			cur_tab=i;
//			break;
//		}
//	}
//	t++;
}

void MainWindow::on_pushButton_clicked()
{
	//tabs[n]= new QTextEdit;
	//ui->tabWidget->addTab(tabs[n],QString("Tab")+QString(strtoint(n)));
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_tabWidget_currentChanged(int index)
{
	cur_tab=index;
}

void MainWindow::on_lineEdit_returnPressed()// ввод из поля ввода в поле вывода
{
    ui->textEdit->insertPlainText(ui->lineEdit->text()+"\n");
    ui->lineEdit->clear();
}

void MainWindow::on_pushButton_3_clicked()//очистить поле вывода
{

}

void MainWindow::on_action_2_activated()
{

}

void MainWindow::on_action_2_activated(int arg1)
{

}

void MainWindow::on_action_2_changed()
{

}

void MainWindow::on_action_2_triggered()
{

}

void MainWindow::on_action_triggered()
{
	tabs.push_back( new QTextEdit);
	ui->tabWidget->addTab(tabs.back(),QString("Tab")+QString(strtoint(n)));
	n++;
}

void MainWindow::on_action_23_triggered()
{
    ui->textEdit->clear();
}

void MainWindow::on_action_24_triggered()
{
	ui->textEdit->insertPlainText(tabs[cur_tab]->toPlainText()+"\n");
}
