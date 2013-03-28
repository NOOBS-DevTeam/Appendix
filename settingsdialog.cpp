#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QtGui>
#include <QDebug>
SettingsDialog::SettingsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);
	//ui->splitter->setSizes(QList<int>() << 160 << 400);
	QStringList lst;
	QListWidgetItem *pitem = 0;
	ui->listWidget->setIconSize(QSize(48,48));
	lst << "Option_1" << "Option_2" << "Option_3";
	foreach (QString str, lst)
	{
		pitem = new QListWidgetItem(str,ui->listWidget);
		//pitem->setIcon();
	}
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}

void SettingsDialog::on_listWidget_itemSelectionChanged()
{
	ui->stackedWidget->setCurrentIndex(ui->listWidget->currentIndex().row());
}
