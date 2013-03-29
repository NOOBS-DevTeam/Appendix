#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QtGui>
#include <QSettings>
#include <QColorDialog>
#include <QDebug>

QSettings tweaks2("NOOBS-DevTeam","Appendix");

SettingsDialog::SettingsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);

	QStringList lst;
	QListWidgetItem *pitem = 0;
	ui->listWidget->setIconSize(QSize(48,48));
	lst << "Option_1" << "Option_2" << "Option_3";
	foreach (QString str, lst)
	{
		pitem = new QListWidgetItem(str,ui->listWidget);
		//pitem->setIcon();
	}
	init_colors();
}
void SettingsDialog::init_colors()
{
	//1ая страница
	QVariant qv1 = tweaks2.value("/Settings/SyntaxH/C++/prepr",QColor(Qt::darkGreen));
	qv1.convert(QVariant::Color);
	QColor qc1 = qv1.value<QColor>();
	QVariant qv2 = tweaks2.value("/Settings/SyntaxH/C++/string",QColor(90,55,202));
	qv2.convert(QVariant::Color);
	QColor qc2 = qv2.value<QColor>();
	QVariant qv3 = tweaks2.value("/Settings/SyntaxH/C++/comment",QColor(Qt::darkGray));
	qv3.convert(QVariant::Color);
	QColor qc3 = qv3.value<QColor>();
	QVariant qv4 = tweaks2.value("/Settings/SyntaxH/C++/number",QColor(255,105,180));
	qv4.convert(QVariant::Color);
	QColor qc4 = qv4.value<QColor>();
	QVariant qv5 = tweaks2.value("/Settings/SyntaxH/C++/keyword",QColor(Qt::darkBlue));
	qv5.convert(QVariant::Color);
	QColor qc5 = qv5.value<QColor>();
	ui->plainTextEdit->setPalette(QPalette(qc1));
	ui->plainTextEdit_2->setPalette(QPalette(qc2));
	ui->plainTextEdit_3->setPalette(QPalette(qc3));
	ui->plainTextEdit_4->setPalette(QPalette(qc4));
	ui->plainTextEdit_5->setPalette(QPalette(qc5));

	// 2ая страница
	QVariant qv6 = tweaks2.value("/Settings/SyntaxH/PAS/string",QColor(90,55,202));
	qv1.convert(QVariant::Color);
	QColor qc6 = qv6.value<QColor>();
	QVariant qv7 = tweaks2.value("/Settings/SyntaxH/PAS/comment",QColor(Qt::darkGray));
	qv2.convert(QVariant::Color);
	QColor qc7 = qv7.value<QColor>();
	QVariant qv8 = tweaks2.value("/Settings/SyntaxH/PAS/number",QColor(255,105,180));
	qv8.convert(QVariant::Color);
	QColor qc8 = qv8.value<QColor>();
	QVariant qv9 = tweaks2.value("/Settings/SyntaxH/PAS/keyword",QColor(Qt::darkBlue));
	qv4.convert(QVariant::Color);
	QColor qc9 = qv9.value<QColor>();
	ui->plainTextEdit_6->setPalette(QPalette(qc6));
	ui->plainTextEdit_7->setPalette(QPalette(qc7));
	ui->plainTextEdit_8->setPalette(QPalette(qc8));
	ui->plainTextEdit_9->setPalette(QPalette(qc9));

	//
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}

void SettingsDialog::on_listWidget_itemSelectionChanged()
{
	ui->stackedWidget->setCurrentIndex(ui->listWidget->currentIndex().row());
}


void SettingsDialog::on_pushButton_clicked()
{
	QPalette pal = ui->plainTextEdit->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit->setPalette(pal);
	tweaks2.setValue("/Settings/SyntaxH/C++/prepr",col);
}

void SettingsDialog::on_pushButton_2_clicked()
{
	QPalette pal = ui->plainTextEdit_2->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_2->setPalette(pal);
	tweaks2.setValue("/Settings/SyntaxH/C++/string",col);
}

void SettingsDialog::on_pushButton_3_clicked()
{
	QPalette pal = ui->plainTextEdit_3->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_3->setPalette(pal);
	tweaks2.setValue("/Settings/SyntaxH/C++/comment",col);
}

void SettingsDialog::on_pushButton_4_clicked()
{
	QPalette pal = ui->plainTextEdit_4->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_4->setPalette(pal);
	tweaks2.setValue("/Settings/SyntaxH/C++/number",col);
}

void SettingsDialog::on_pushButton_5_clicked()
{
	QPalette pal = ui->plainTextEdit_5->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_5->setPalette(pal);
	tweaks2.setValue("/Settings/SyntaxH/C++/keyword",col);
}

void SettingsDialog::on_pushButton_6_clicked()
{
	QPalette pal = ui->plainTextEdit_6->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_6->setPalette(pal);
	tweaks2.setValue("/Settings/SyntaxH/PAS/string",col);
}

void SettingsDialog::on_pushButton_7_clicked()
{
	QPalette pal = ui->plainTextEdit_7->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_7->setPalette(pal);
	tweaks2.setValue("/Settings/SyntaxH/PAS/comment",col);
}

void SettingsDialog::on_pushButton_8_clicked()
{
	QPalette pal = ui->plainTextEdit_8->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_8->setPalette(pal);
	tweaks2.setValue("/Settings/SyntaxH/PAS/number",col);
}

void SettingsDialog::on_pushButton_9_clicked()
{
	QPalette pal = ui->plainTextEdit_9->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_9->setPalette(pal);
	tweaks2.setValue("/Settings/SyntaxH/PAS/keyword",col);
}
