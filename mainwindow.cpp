/**
    The Appendix project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

  (Проект Appendix - свободная программа: вы можете перераспространять ее и/или изменять
   ее на условиях Стандартной общественной лицензии GNU в том виде, в каком
   она была опубликована Фондом свободного программного обеспечения; либо
   версии 3 лицензии, либо (по вашему выбору) любой более поздней версии.

   Эта программа распространяется в надежде, что она будет полезной,
   но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
   или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Стандартной
   общественной лицензии GNU.

   Вы должны были получить копию Стандартной общественной лицензии GNU
   вместе с этой программой. Если это не так, см.
   <http://www.gnu.org/licenses/>.)
**/

///Copyright 2013 Miloserdov Vladimir (MiloserdOFF) Shabanov Vladimir (ment-ru)

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SyntaxHighlighter.h"
#include "settingsdialog.h"
#include "helpdialog.h"
#include <QInputDialog>
#include "Editor.h"
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <strstream>
#include <iterator>
#include <vector>
#include <algorithm>
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
QString allErrors; //???
QTabWidget *tabw;
std::vector<Editor*> tabs; //Табы
QString cpError; //Ошибка комп.
QProcess *cp; //Процесс (компилятора/apx'a)
lang_t cur_lang=CPP; // Язык тек. вкладки
QSettings tweaks("NOOBS-DevTeam","Appendix"); //Собсна настройки
bool comp_in_progress = false; //Компиляция в процессе?

QString strtoint(int a); //Строку в число
QString readFile(QString filename); //Чтение файла

//Сохранение таба
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
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << str;
    out << "\n";
    file.close();
    tabs[cur_tab]->filename=filename;
    ui->tabWidget->setCurrentIndex(cur_tab);
    tabs[cur_tab]->saved();
    ui->tabWidget->setTabText(cur_tab,findentry(filename));
}

//Запись настроек
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

//Конструктор главного окна
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tabw = ui->tabWidget;
    ui->splitter_4->setSizes(QList<int> () << 600 << 200);
    ui->splitter->setSizes(QList<int> () << 700 << 170 );
    ui->stop->setEnabled(false);

    //Грузим геометрию окна
    tweaks.beginGroup("/Settings/Session/geometry");
        this->setGeometry(tweaks.value("/x",500).toInt(),tweaks.value("/y",500).toInt(),tweaks.value("/w",740).toInt(),tweaks.value("/h",512).toInt());
    tweaks.endGroup();

    cp = new QProcess(this); //Создаем бездействующий процесс
    connect(cp,SIGNAL(readyReadStandardOutput()),SLOT(slotDataOnStdout()));
    connect(cp,SIGNAL(readyReadStandardError()),SLOT(slotDataOnError()));
    connect(cp,SIGNAL(finished(int)),this,SLOT(switchRun()));
}

//Деструктор окна
MainWindow::~MainWindow()
{
    this->writeTweaks(); //Сэйвим геометрию окна
    for (int i=0;i<n;i++)
        if (dynamic_cast<Editor*> (tabs[i])) //Если вкладка существует
            ui->tabWidget->tabCloseRequested(i); //То закрываем!
    delete ui;
}

//Закрытие таба
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

//Обновление всех табов
void MainWindow::refreshAllTabs()
{
    for (unsigned i=0;i<tabs.size();i++)
        if (dynamic_cast<Editor*> (tabs[i]))
            tabs[i]->refresh();
}

//Смена текущего таба
void MainWindow::on_tabWidget_currentChanged(int index)
{
    cur_tab=index;
}

//Ввод из поля ввода в поле вывода
void MainWindow::on_lineEdit_returnPressed()
{
    ui->textEdit->insertPlainText(ui->lineEdit->text()+"\n");
    cp->write((ui->lineEdit->text().toStdString()+"\n").c_str());
    ui->lineEdit->clear();
}

//Открытие файла
void MainWindow::on_open_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,("Открыть файл"), "", ("Файл Appendix(*.apx *.pas *.cpp)"));
    if (filename.mid(filename.length()-3,3)=="cpp")
        tabs.push_back(new Editor(this,CPP));
    if (filename.mid(filename.length()-3,3)=="pas")
        tabs.push_back(new Editor(this,PAS));;
    if (filename.mid(filename.length()-3,3)=="apx")
        tabs.push_back(new Editor(this,APX));
    n++;
    ui->tabWidget->addTab(tabs.back(),QString("Tab")+QString(strtoint(n)));
    tabs.back()->setPlainText(readFile(filename));
}

//Создание нового таба
void MainWindow::on_new_2_triggered()
{
    QStringList lst;
    lst << tr("C++") << tr("Pascal") << tr("Appendix");
    bool ok;
    QString item = QInputDialog::getItem(this, tr("Выбор языка"),tr("Выбор языка"), lst, 0, false, &ok);
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
        tabs.back()->filename=QString("@@@/Tab")+QString(strtoint(n));
        ui->tabWidget->setTabText(cur_tab,findentry(tabs.back()->filename));
    }
}

//Очистка вывода
void MainWindow::on_action_23_triggered()
{
    ui->textEdit->clear();
}

//Запуск программы юзера
void MainWindow::on_run_triggered()
{
    if (n) //Если вкадки открыты
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

        //Запись текста таба во временный файл
        QFile("temp."+format).remove();
        std::ofstream out(std::string("temp."+format.toStdString()).c_str());
        out << str.toStdString();
        out << "\n";
        out.close();

        if (tabs[cur_tab]->getLang()==APX)
        {
            //Запуск интерпретатора (если апх)
            switchRun();
            cp->start(compiler);
            cp->waitForStarted();
        }
        else
        {
            //Компилируем
            comp_in_progress = true;
            cp->start(compiler);
            cp->waitForFinished();
            comp_in_progress = false;

            if (cp->exitCode())
                ui->textEdit->append(allErrors);
            allErrors = "";

            if (!cp->exitCode()) //Если успешно скомпилилось
            {
            #ifdef Q_OS_LINUX
                switchRun();
                cp->start(cur_lang==CPP?"./a.out":"./temp.out");
                cp->waitForStarted();
                QFile(cur_lang==CPP?"./a.out":"./temp.out").remove();//Для Linux
            #endif
            #ifdef Q_OS_WIN
                switchRun();
                cp->start(cur_lang==CPP?"a.exe":"temp.exe");
                cp->waitForStarted();
                QFile(cur_lang==CPP?"a.exe":"temp.exe").remove();//Для Windows
            #endif
            }
        }
    }
    else
        QMessageBox::warning(ui->tabWidget,"Error","Возможно вы не открыли/создали ни одного файла",QMessageBox::Yes,QMessageBox::Yes);
}

//Возвращает подстроку после слеша
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

//Сохрание тек. таба
void MainWindow::on_save_as_triggered()
{
    saveTab(cur_tab);
}

//Чтение стандартного потока запущенного процесса
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

//Чтение потока ошибок запущенного процесса
void MainWindow::slotDataOnError()
{
    ui->textEdit->append(cp->readAllStandardError().data());
}

//Создание новой вкладки
void MainWindow::new_toolButton_clicked()
{
    ui->new_2->trigger();
}

//Сейв тек. вкладки
void MainWindow::on_toolButton_3_clicked()
{
    ui->save_as->trigger();
}

//???
void MainWindow::on_toolButton_4_clicked()
{

}

//???
void MainWindow::on_toolButton_5_clicked()
{
    ui->run->trigger();
}

//Вызов диалога настроек
void MainWindow::on_settings_triggered()
{
    SettingsDialog *sd = new SettingsDialog;
    connect(sd,SIGNAL(smthChanged()),this,SLOT(refreshAllTabs()));
    sd->show();
}

//???
void MainWindow::on_action_10_triggered()
{

}

//Переключение языка вкладки на PAS
void MainWindow::on_actionPascal_triggered()
{
   cur_lang = PAS;
   tabs[cur_tab]->setLang(PAS);
}

//Переключение языка вкладки на CPP
void MainWindow::on_actionC_triggered()
{
    cur_lang = CPP;
    tabs[cur_tab]->setLang(CPP);
}

//Переключение языка вкладки на APX
void MainWindow::on_actionAppendix_triggered()
{
    cur_lang = APX;
    tabs[cur_tab]->setLang(APX);
}

// Открытие файла
void MainWindow::on_toolButton_2_clicked()
{
    ui->open->trigger();
}

//Остановка запущеной программы
void MainWindow::on_stop_triggered()
{
    cp->kill();
}

//Кнопка "стоп"
void MainWindow::on_toolButton_6_clicked()
{
    ui->stop->trigger();
}

//???
void MainWindow::on_action_29_triggered()
{

}

//Переключение кнопок выполнить/остановить
void MainWindow::switchRun()
{
    if (comp_in_progress)
        return;
    ui->stop->setEnabled(!ui->stop->isEnabled());
    ui->run->setEnabled(!ui->run->isEnabled());
}

//Вызов диалога справки
void MainWindow::on_help_triggered()
{
    helpdialog *help = new helpdialog;
    help->show();
}

//Вызов диалога печати
void MainWindow::on_print_triggered()
{
    /// TODO:
    /// Добавь комменты!!!
    if (n!=0)
    {
        QString text =tabs[cur_tab]->toPlainText();
        QPrinter printer;
        QPrintDialog *dialog = new QPrintDialog(&printer);
        dialog->setWindowTitle("Print Document");
        if (dialog->exec() == QDialog::Accepted)
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

void MainWindow::on_save_all_triggered()
{

}

void MainWindow::on_close_triggered()
{

}

void MainWindow::on_exit_triggered()
{

}

void MainWindow::on_save_triggered()
{
    std::string fn;
    QString fn2=tabs[cur_tab]->filename;
    QString str = tabs[cur_tab]->toPlainText();
    fn=tabs[cur_tab]->filename.toStdString();
    if (fn.find("@@@")>fn.length())
    {
        QFile file(fn2);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << str;
        out << "\n";
        file.close();
        tabs[cur_tab]->saved();
    }
    else
        saveTab(cur_tab);

}

void MainWindow::on_action_triggered()
{

}

void MainWindow::on_on_open_triggered()
{

}
