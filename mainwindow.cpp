#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SyntaxHighlighter.h"
#include "settingsdialog.h"
#include "helpdialog.h"
#include <QInputDialog>
#include "Editor.h"
#include <string.h>
#include <stdio.h>
#include <strstream>
#include <vector>
#include <QFileDialog>
#include <QTabWidget>
#include <QFile>
#include <QFont>
#include <QDebug>
#include <QTextStream>
#include <QProcess>
#include <QSettings>
#include <QMessageBox>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>


int n=0,cur_tab=0;//текущий таб
QTabWidget *tabw;
QString allErrors;
std::vector<Editor*> tabs;
QString cpError;
QProcess *cp;
lang_t cur_lang=CPP;
QSettings tweaks("NOOBS-DevTeam","Appendix");
bool comp_in_progress = false;
QString strtoint(int a);
QString readFile(QString filename);

void readTweaks()
{

}

void MainWindow::saveTab(int i)
{
	QString str = tabs[i]->toPlainText();
	QString filename;
	QString format;
	switch (tabs[i]->getLang())
	{
	case CPP:
		format = ".cpp";
		break;
	case PAS:
		format = ".pas";
		break;
	case APX:
		format = ".apx";
		break;
	}
	filename = QFileDialog::getSaveFileName(this,tr("Save Document"),"",tr("Documents (*")+format+")");
	QFile file(filename);
	file.open(QIODevice::Append | QIODevice::Text);
	QTextStream out(&file);
	out << str;
	out << "\n";
	file.close();
	ui->tabWidget->setTabText(cur_tab,findentry(filename));
	ui->tabWidget->setCurrentIndex(cur_tab);
	tabs[cur_tab]->saved();
	tabs[cur_tab]->filename=filename;
}

void MainWindow::writeTweaks()
{
	tweaks.beginGroup("/Settings");
		tweaks.beginGroup("/Session");
			tweaks.beginGroup("/geometry");
				tweaks.setValue("x",this->geometry().x());
				tweaks.setValue("y",this->geometry().y());
				tweaks.setValue("w",this->geometry().width());
				tweaks.setValue("h",this->geometry().height());
			tweaks.endGroup();
			tweaks.beginGroup("/tabs");
				//TODO: Сохранение вкладок
			tweaks.endGroup();
		tweaks.endGroup();
	tweaks.endGroup();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	tabw = ui->tabWidget;
	ui->splitter_4->setSizes(QList<int> () << 600 << 200);
    ui->splitter->setSizes(QList<int> () << 700 << 170 );
    ui->action_25->setEnabled(false);
	tweaks.beginGroup("/Settings/Session/geometry");
		this->setGeometry(tweaks.value("/x",500).toInt(),tweaks.value("/y",500).toInt(),tweaks.value("/w",740).toInt(),tweaks.value("/h",512).toInt());
	tweaks.endGroup();
	cp = new QProcess(this);
	connect(cp,SIGNAL(readyReadStandardOutput()),SLOT(slotDataOnStdout()));
	connect(cp,SIGNAL(readyReadStandardError()),SLOT(slotDataOnError()));
	connect(cp,SIGNAL(finished(int)),this,SLOT(switchRun()));
}

MainWindow::~MainWindow()
{
	this->writeTweaks();
	for (int i=0;i<n;i++)
		if (dynamic_cast<Editor*> (tabs[i]))
			ui->tabWidget->tabCloseRequested(i);
	delete ui;
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
	if (tabs[index]->changed)
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Сохранить изменения");
		msgBox.setText("Вы хотите сохранить изменения?");
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Cancel);
		msgBox.exec();
		int ret = msgBox.result();
		switch (ret)
		{
		case QMessageBox::Discard:
			ui->tabWidget->removeTab(index);
			delete tabs[index];
			tabs.erase(tabs.begin()+index);
			n--;
			break;
		case QMessageBox::Save:
			saveTab(index);
			ui->tabWidget->removeTab(index);
			delete tabs[index];
			tabs.erase(tabs.begin()+index);
			n--;
			break;
		case QMessageBox::Cancel:

			break;
		}
	}
}

void MainWindow::refreshAllTabs()
{
	for (int i=0;i<tabs.size();i++)
		if (dynamic_cast<Editor*> (tabs[i]))
			tabs[i]->refresh();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
	cur_tab=index;
}

void MainWindow::on_lineEdit_returnPressed()// ввод из поля ввода в поле вывода
{
    ui->textEdit->insertPlainText(ui->lineEdit->text()+"\n");
	cp->write((ui->lineEdit->text().toStdString()+"\n").c_str());
    ui->lineEdit->clear();
}

void MainWindow::on_action_2_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,("Открыть файл"), "", ("Файл Appendix(*.apx *.pas *.cpp)"))+"\n";
	qDebug() << filename.mid(filename.length()-4,3);
	if (filename.mid(filename.length()-4,3)=="cpp")
		tabs.push_back(new Editor(0,CPP));
	if (filename.mid(filename.length()-4,3)=="pas")
		tabs.push_back(new Editor(0,PAS));;
	if (filename.mid(filename.length()-4,3)=="apx")
		tabs.push_back(new Editor(0,APX));
	n++;
	ui->tabWidget->addTab(tabs.back(),QString("Tab")+QString(strtoint(n)));
	tabs.back()->setPlainText(readFile(filename));
	qDebug() << readFile(filename);
}

void MainWindow::on_action_triggered()
{
    QStringList city;
    city << tr("C++") << tr("Pascal") << tr("Appendix");
    bool ok;
    QString item = QInputDialog::getItem(this, tr("Выбор языка"),tr("Выбор языка"), city, 0, false, &ok);
    if (ok && !item.isEmpty())
       {
        if (item=="C++")
            cur_lang=CPP;
        if (item=="Pascal")
            cur_lang=PAS;
		if (item=="Appendix")
			cur_lang=APX;
        //-----------------
        tabs.push_back(new Editor(0,cur_lang));
        ui->tabWidget->addTab(tabs.back(),QString("Tab")+QString(strtoint(n)));
        n++;
       }
}

void MainWindow::on_action_23_triggered()
{
	ui->textEdit->clear();
}

void MainWindow::on_action_24_triggered()
{
    if (n)
    {
        QString format,compiler;
        switch (tabs[cur_tab]->getLang())
        {
        case CPP:
            format = "cpp";
            compiler = "g++ temp.cpp";
            break;
        case PAS:
            format = "pas";
            compiler = "fpc temp.pas";
            break;
		case APX:
			format = "apx";
			compiler = "apx temp.apx";
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
		if (tabs[cur_tab]->getLang()==APX)
		{
			switchRun();
			cp->start(compiler);
			cp->waitForStarted();
		}
		else
		{
			comp_in_progress = true;
			cp->start(compiler);
			cp->waitForFinished();
			comp_in_progress = false;
			if (cp->exitCode())
				ui->textEdit->append(allErrors);
			allErrors = "";
			if (!cp->exitCode())
			{
				cp->start(cur_lang==CPP?"a.exe":"temp.exe");
				cp->waitForStarted();
				switchRun();
				QFile(cur_lang==CPP?"a.exe":"temp.exe").remove();
			}
		}
	}
	else
		QMessageBox::warning(ui->tabWidget,"Error","Возможно вы не открыли/создали ни одного файла",QMessageBox::Yes,QMessageBox::Yes);
}

QString findentry(QString s)
{
    QString str="";
    for (int i=s.length();i>0;i--)
    {
        if (s[i]=='/')
        {
            for (int j=i+1;j<s.length();j++)
                str+=s[j];
            return str;
        }
    }
}

void MainWindow::on_action_3_triggered()
{
	saveTab(cur_tab);
}

void MainWindow::slotDataOnStdout()
{
	if (comp_in_progress)
	{
		allErrors += cp->readAllStandardOutput();
	}
	else
	{
		ui->textEdit->append(cp->readAllStandardOutput());
	}
}

void MainWindow::slotDataOnError()
{
	ui->textEdit->append(cp->readAllStandardError().data());
	//QString error=QString(cp->readAllStandardError());
	//error.remove(0,(error.lastIndexOf("error:")+6));
	//cpError = QString("ERROR:")+(error);
}


void MainWindow::on_toolButton_clicked()
{
    ui->action->trigger();

}

void MainWindow::on_toolButton_3_clicked()
{
    ui->action_3->trigger();

}

void MainWindow::on_toolButton_4_clicked()
{

}

void MainWindow::on_toolButton_5_clicked()
{
    ui->action_24->trigger();
}

void MainWindow::on_action_8_triggered()
{
	SettingsDialog *sd = new SettingsDialog;
	connect(sd,SIGNAL(smthChanged()),this,SLOT(refreshAllTabs()));
	sd->show();
}
void MainWindow::on_action_10_triggered()
{
}

void MainWindow::on_actionPascal_triggered()
{
   cur_lang = PAS;
   tabs[cur_tab]->setLang(CPP);
}

void MainWindow::on_actionC_triggered()
{
    cur_lang = CPP;
    tabs[cur_tab]->setLang(CPP);
}

void MainWindow::on_toolButton_2_clicked()
{
    ui->action_2->trigger();

}

void MainWindow::on_action_25_triggered()
{
	cp->kill();
}


void MainWindow::on_toolButton_6_clicked()
{
	ui->action_25->trigger();
}

void MainWindow::on_action_29_triggered()
{

}

void MainWindow::switchRun()
{
	if (comp_in_progress)
		return;
    ui->action_25->setEnabled(!ui->action_25->isEnabled());
    ui->action_24->setEnabled(!ui->action_24->isEnabled());
}

void MainWindow::on_action_27_triggered()
{
	helpdialog *help = new helpdialog;
	help->show();
}

void MainWindow::on_action_9_triggered()
{
    if (n!=0)
    {
        QApplication a(int argc, char *argv[]);

        QString text =tabs[cur_tab]->toPlainText();

           QPrinter printer;

           QPrintDialog *dialog = new QPrintDialog(&printer);
           dialog->setWindowTitle("Print Document");

           if (dialog->exec() != QDialog::Accepted);
           else
           {

           QPainter painter;
           painter.begin(&printer);

           painter.drawText(100, 100, 500, 500, Qt::AlignLeft|Qt::AlignTop, text);

           painter.end();
    }
       }
    else
        QMessageBox::warning(ui->tabWidget,"Error","Возможно вы не открыли/создали ни одного файла",QMessageBox::Yes,QMessageBox::Yes);
}
