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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Editor.h"
#include <QMainWindow>

extern int cur_tab;
extern QTabWidget *tabw;
namespace Ui {
class MainWindow;
}

QString findentry(QString filename);

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_tabWidget_tabCloseRequested(int index);

    void on_tabWidget_currentChanged(int index);

    void on_lineEdit_returnPressed();

    void on_open_triggered();

    void on_new_2_triggered();

    void on_action_23_triggered();

    void on_run_triggered();

    void on_save_as_triggered();

	void slotDataOnStdout();

	void slotDataOnError();

	void writeTweaks();

    void on_action_10_triggered();

    void new_toolButton_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_4_clicked();

    void settings_triggered();

    void on_actionPascal_triggered();

    void on_actionC_triggered();

    void on_toolButton_2_clicked();

    void on_action_29_triggered();

    void on_stop_triggered();

	void on_toolButton_6_clicked();

    void help_triggered();

	void saveTab(int i);

    void on_print_triggered();

    void save_triggered();

    void on_save_all_triggered();

    void close_triggered();

    void close_inactive_triggered();

    void exit_triggered();

    void on_save_triggered();

    void on_action_triggered();

    void on_on_open_triggered();

public slots:

	void refreshAllTabs();

	void switchRun();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

