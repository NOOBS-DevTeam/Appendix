#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "SyntaxHighlighter.h"
#include "Editor.h"
#include <QtGui>
#include <QObject>
#include <QSettings>
#include <QColorDialog>
#include <QFontDialog>
#include <QDebug>
#include <QColor>


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
	ui->spinBox->setValue(tweaks2.value("/Settings/Text/TabSize",QVariant(26)).toInt());
	QVariant qv = tweaks2.value("/Settings/Text/Font",QVariant(QFont("Consolas",10,QFont::Normal)));
	qv.convert(QVariant::Font);
	QFont fnt = qv.value<QFont>();
	qDebug() << fnt;
	ui->textEdit_4->document()->setDefaultFont(fnt);
	ui->textEdit_4->setText("Example text preview...");
	ui->textEdit_2->setLang(PAS);
	ui->textEdit_3->setLang(APX);
	init_colors();
    rfrshclrs();
}

QColor GetOptimalBkColor(QColor AColor)
{
	int R,G,B;
	R = AColor.red();
	G = AColor.red();
	B = AColor.red();
	if (0.222*R + 0.707*G + 0.071*B <= 127)
		return(QColor(Qt::white));
	else
	  return(QColor(Qt::black));
}

void SettingsDialog::init_colors()
{
    //1ая страница
	QVariant qv0 = tweaks2.value("/Settings/SyntaxH/C++/prepr",QColor(Qt::darkGreen));
	qv0.convert(QVariant::Color);
	QColor qc0 = qv0.value<QColor>();
	//--------------------------------
	QVariant qv1 = tweaks2.value("/Settings/SyntaxH/C++/string",QColor(90,55,202));
	qv1.convert(QVariant::Color);
	QColor qc1 = qv1.value<QColor>();
	//--------------------------------
	QVariant qv2 = tweaks2.value("/Settings/SyntaxH/C++/comment",QColor(Qt::darkGray));
	qv2.convert(QVariant::Color);
	QColor qc2 = qv2.value<QColor>();
	//--------------------------------
	QVariant qv3 = tweaks2.value("/Settings/SyntaxH/C++/number",QColor(255,105,180));
	qv3.convert(QVariant::Color);
	QColor qc3 = qv3.value<QColor>();
	//--------------------------------
	QVariant qv4 = tweaks2.value("/Settings/SyntaxH/C++/keyword",QColor(Qt::darkBlue));
	qv4.convert(QVariant::Color);
	QColor qc4 = qv4.value<QColor>();
	//--------------------------------
	ui->plainTextEdit  ->setPalette(QPalette(qc0));
	ui->plainTextEdit_2->setPalette(QPalette(qc1));
	ui->plainTextEdit_3->setPalette(QPalette(qc2));
	ui->plainTextEdit_4->setPalette(QPalette(qc3));
	ui->plainTextEdit_5->setPalette(QPalette(qc4));

    // 2ая страница
	QVariant qv5 = tweaks2.value("/Settings/SyntaxH/PAS/string",QColor(90,55,202));
	qv5.convert(QVariant::Color);
	QColor qc5 = qv5.value<QColor>();
	//--------------------------------
	QVariant qv6 = tweaks2.value("/Settings/SyntaxH/PAS/comment",QColor(Qt::darkGray));
	qv6.convert(QVariant::Color);
	QColor qc6 = qv6.value<QColor>();
	//--------------------------------
	QVariant qv7 = tweaks2.value("/Settings/SyntaxH/PAS/number",QColor(255,105,180));
	qv7.convert(QVariant::Color);
	QColor qc7 = qv7.value<QColor>();
	//--------------------------------
	QVariant qv8 = tweaks2.value("/Settings/SyntaxH/PAS/keyword",QColor(Qt::darkBlue));
	qv8.convert(QVariant::Color);
	QColor qc8 = qv8.value<QColor>();
	//--------------------------------
	ui->plainTextEdit_6->setPalette(QPalette(qc5));
	ui->plainTextEdit_7->setPalette(QPalette(qc6));
	ui->plainTextEdit_8->setPalette(QPalette(qc7));
	ui->plainTextEdit_9->setPalette(QPalette(qc8));

	//3ая страница
	QVariant qv9 = tweaks2.value("/Settings/SyntaxH/APX/string",QColor(90,55,202));
	qv9.convert(QVariant::Color);
	QColor qc9 = qv9.value<QColor>();
	//--------------------------------
	QVariant qv10 = tweaks2.value("/Settings/SyntaxH/APX/comment",QColor(Qt::darkGray));
	qv10.convert(QVariant::Color);
	QColor qc10 = qv10.value<QColor>();
	//----------------------------------
	QVariant qv11 = tweaks2.value("/Settings/SyntaxH/APX/number",QColor(255,105,180));
	qv11.convert(QVariant::Color);
	QColor qc11 = qv11.value<QColor>();
	//----------------------------------
	QVariant qv12 = tweaks2.value("/Settings/SyntaxH/APX/keyword",QColor(Qt::darkBlue));
	qv12.convert(QVariant::Color);
	QColor qc12 = qv12.value<QColor>();
	//----------------------------------
	ui->plainTextEdit_10->setPalette(QPalette(qc9));
	ui->plainTextEdit_11->setPalette(QPalette(qc10));
	ui->plainTextEdit_12->setPalette(QPalette(qc11));
	ui->plainTextEdit_13->setPalette(QPalette(qc12));

	QVariant qv13 = tweaks2.value("/Settings/Text/BaseColor",QColor(Qt::white));
	qv13.convert(QVariant::Color);
	QColor qc13 = qv13.value<QColor>();
	ui->plainTextEdit_14->setPalette(QPalette(qc13));
	//----------------------------------
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
    rfrshclrs();
	tweaks2.setValue("/Settings/SyntaxH/C++/prepr",col);
}

void SettingsDialog::on_pushButton_2_clicked()
{
	QPalette pal = ui->plainTextEdit_2->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_2->setPalette(pal);
    rfrshclrs();
	tweaks2.setValue("/Settings/SyntaxH/C++/string",col);
}

void SettingsDialog::on_pushButton_3_clicked()
{
	QPalette pal = ui->plainTextEdit_3->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_3->setPalette(pal);
    rfrshclrs();
	tweaks2.setValue("/Settings/SyntaxH/C++/comment",col);
}

void SettingsDialog::on_pushButton_4_clicked()
{
	QPalette pal = ui->plainTextEdit_4->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_4->setPalette(pal);
    rfrshclrs();
	tweaks2.setValue("/Settings/SyntaxH/C++/number",col);
}

void SettingsDialog::on_pushButton_5_clicked()
{
	QPalette pal = ui->plainTextEdit_5->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_5->setPalette(pal);
    rfrshclrs();
	tweaks2.setValue("/Settings/SyntaxH/C++/keyword",col);
}

void SettingsDialog::on_pushButton_6_clicked()
{
	QPalette pal = ui->plainTextEdit_6->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_6->setPalette(pal);
    rfrshclrs();
	tweaks2.setValue("/Settings/SyntaxH/PAS/string",col);
}

void SettingsDialog::on_pushButton_7_clicked()
{
	QPalette pal = ui->plainTextEdit_7->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_7->setPalette(pal);
    rfrshclrs();
	tweaks2.setValue("/Settings/SyntaxH/PAS/comment",col);
}

void SettingsDialog::on_pushButton_8_clicked()
{
	QPalette pal = ui->plainTextEdit_8->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_8->setPalette(pal);
    rfrshclrs();
	tweaks2.setValue("/Settings/SyntaxH/PAS/number",col);
}

void SettingsDialog::on_pushButton_9_clicked()
{
	QPalette pal = ui->plainTextEdit_9->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_9->setPalette(pal);
    rfrshclrs();
	tweaks2.setValue("/Settings/SyntaxH/PAS/keyword",col);
}

void SettingsDialog::on_pushButton_10_clicked()
{
	tweaks2.beginGroup("/Settings");
		tweaks2.beginGroup("/SyntaxH");
			tweaks2.beginGroup("/PAS");
				tweaks2.setValue("/string",QColor(90,55,202));
				tweaks2.setValue("/comment",QColor(Qt::darkGray));
				tweaks2.setValue("/number",QColor(255,105,180));
				tweaks2.setValue("/keyword",QColor(Qt::darkBlue));
			tweaks2.endGroup();
			tweaks2.beginGroup("/C++");
				tweaks2.setValue("/prepr",QColor(Qt::darkGreen));
				tweaks2.setValue("/string",QColor(90,55,202));
				tweaks2.setValue("/comment",QColor(Qt::darkGray));
				tweaks2.setValue("/number",QColor(255,105,180));
				tweaks2.setValue("/keyword",QColor(Qt::darkBlue));
			tweaks2.endGroup();
			tweaks2.beginGroup("/APX");
				tweaks2.setValue("/string",QColor(90,55,202));
				tweaks2.setValue("/comment",QColor(Qt::darkGray));
				tweaks2.setValue("/number",QColor(255,105,180));
				tweaks2.setValue("/keyword",QColor(Qt::darkBlue));
			tweaks2.endGroup();
		tweaks2.endGroup();
		tweaks2.beginGroup("/Session");
			tweaks2.beginGroup("/geometry");
				tweaks2.setValue("x",500);
				tweaks2.setValue("y",500);
				tweaks2.setValue("w",740);
				tweaks2.setValue("h",512);
			tweaks2.endGroup();
			tweaks2.beginGroup("/tabs");
				//TODO: Сохранение вкладок
			tweaks2.endGroup();
		tweaks2.endGroup();
		tweaks2.beginGroup("/Text");
			tweaks2.setValue("/TabSize",26);
			tweaks2.setValue("/BaseColor",QColor(Qt::white));
			tweaks2.setValue("/Settings/Text/Font",QVariant(QFont("Consolas",10,QFont::Normal)));
		tweaks2.endGroup();
	tweaks2.endGroup();
	delete this;
}

void SettingsDialog::on_buttonBox_accepted()
{
	//tweaks2.setValue("/Settings/Text/Font",ui->fontComboBox->);
	tweaks2.setValue("/Settings/Text/TabSize",ui->spinBox->value());
	emit smthChanged();
}

void SettingsDialog::on_pushButton_11_clicked()
{
	QPalette pal = ui->plainTextEdit_10->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_10->setPalette(pal);
    rfrshclrs();
    tweaks2.setValue("/Settings/SyntaxH/APX/string",col);

}

void SettingsDialog::on_pushButton_12_clicked()
{
	QPalette pal = ui->plainTextEdit_11->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_11->setPalette(pal);
    rfrshclrs();
    tweaks2.setValue("/Settings/SyntaxH/APX/comment",col);

}

void SettingsDialog::on_pushButton_13_clicked()
{
	QPalette pal = ui->plainTextEdit_12->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_12->setPalette(pal);
    rfrshclrs();
    tweaks2.setValue("/Settings/SyntaxH/APX/number",col);

}

void SettingsDialog::on_pushButton_14_clicked()
{
	QPalette pal = ui->plainTextEdit_13->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	ui->plainTextEdit_13->setPalette(pal);
    rfrshclrs();
    tweaks2.setValue("/Settings/SyntaxH/APX/keyword",col);

}

void SettingsDialog::rfrshclrs()
{
    QPalette pal2 = ui->plainTextEdit_13->palette();
    QColor col2 = pal2.base().color();
    col2=GetOptimalBkColor(col2);
    pal2.setColor(QPalette::Text,col2);
    ui->plainTextEdit_13->setPalette(pal2);


    QPalette pal3 = ui->plainTextEdit_12->palette();
    QColor col3 = pal3.base().color();
    col3=GetOptimalBkColor(col3);
    pal3.setColor(QPalette::Text,col3);
    ui->plainTextEdit_12->setPalette(pal3);


    QPalette pal4 = ui->plainTextEdit_11->palette();
    QColor col4 = pal4.base().color();
    col4=GetOptimalBkColor(col4);
    pal4.setColor(QPalette::Text,col4);
    ui->plainTextEdit_11->setPalette(pal4);


    QPalette pal5 = ui->plainTextEdit_10->palette();
    QColor col5 = pal5.base().color();
    col5=GetOptimalBkColor(col5);
    pal5.setColor(QPalette::Text,col5);
    ui->plainTextEdit_10->setPalette(pal5);

    QPalette pal6 = ui->plainTextEdit_9->palette();
    QColor col6 = pal6.base().color();
    col6=GetOptimalBkColor(col6);
    pal2.setColor(QPalette::Text,col6);
    ui->plainTextEdit_9->setPalette(pal6);

    QPalette pal7 = ui->plainTextEdit_8->palette();
    QColor col7 = pal7.base().color();
    col7=GetOptimalBkColor(col7);
    pal7.setColor(QPalette::Text,col7);
    ui->plainTextEdit_8->setPalette(pal7);

    QPalette pal8 = ui->plainTextEdit_7->palette();
    QColor col8 = pal8.base().color();
    col8=GetOptimalBkColor(col8);
    pal8.setColor(QPalette::Text,col8);
    ui->plainTextEdit_7->setPalette(pal8);

    QPalette pal9 = ui->plainTextEdit_6->palette();
    QColor col9 = pal9.base().color();
    col9=GetOptimalBkColor(col9);
    pal9.setColor(QPalette::Text,col9);
    ui->plainTextEdit_6->setPalette(pal9);

    QPalette pal10 = ui->plainTextEdit_5->palette();
    QColor col10 = pal10.base().color();
    col10=GetOptimalBkColor(col10);
    pal10.setColor(QPalette::Text,col10);
    ui->plainTextEdit_5->setPalette(pal10);

    QPalette pal11 = ui->plainTextEdit_4->palette();
    QColor col11 = pal11.base().color();
    col11=GetOptimalBkColor(col11);
    pal11.setColor(QPalette::Text,col11);
    ui->plainTextEdit_4->setPalette(pal11);

    QPalette pal12 = ui->plainTextEdit_3->palette();
    QColor col12 = pal12.base().color();
    col12=GetOptimalBkColor(col12);
    pal12.setColor(QPalette::Text,col12);
    ui->plainTextEdit_3->setPalette(pal12);

    QPalette pal13 = ui->plainTextEdit_2->palette();
    QColor col13 = pal13.base().color();
    col13=GetOptimalBkColor(col13);
    pal13.setColor(QPalette::Text,col13);
    ui->plainTextEdit_2->setPalette(pal13);

    QPalette pal14 = ui->plainTextEdit->palette();
    QColor col14 = pal14.base().color();
    col14=GetOptimalBkColor(col14);
    pal14.setColor(QPalette::Text,col14);
    ui->plainTextEdit->setPalette(pal14);
}


void SettingsDialog::on_pushButton_15_clicked()
{
	QPalette pal = ui->plainTextEdit_14->palette();
	QColor col = QColorDialog::getColor();
	pal.setColor(QPalette::Base,col);
	tweaks2.setValue("/Settings/Text/BaseColor",QVariant(col));
	ui->plainTextEdit_14->setPalette(pal);
}

void SettingsDialog::on_pushButton_16_clicked()
{
	bool bok;
	QVariant qv = tweaks2.value("/Settings/Text/Font",QVariant(QFont("Consolas",10,QFont::Normal)));
	qv.convert(QVariant::Font);
	QFont initial = qv.value<QFont>();
	QFont fnt= QFontDialog::getFont(&bok,initial,this,"Выбирите шрифт");
	if (bok)
	{
		tweaks2.setValue("/Settings/Text/Font",fnt);
		ui->textEdit_4->document()->setDefaultFont(fnt);
	}
}
