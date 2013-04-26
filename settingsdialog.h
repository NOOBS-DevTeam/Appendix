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


#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QtCore>
namespace Ui {
	class SettingsDialog;
}

class SettingsDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit SettingsDialog(QWidget *parent = 0);
	~SettingsDialog();
	
private slots:
	void on_listWidget_itemSelectionChanged();

	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

	void on_pushButton_3_clicked();

	void on_pushButton_4_clicked();

	void on_pushButton_5_clicked();

	void on_pushButton_6_clicked();

	void on_pushButton_7_clicked();

	void on_pushButton_8_clicked();

	void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_buttonBox_accepted();

	void on_pushButton_11_clicked();

	void on_pushButton_12_clicked();

	void on_pushButton_13_clicked();

	void on_pushButton_14_clicked();

    void rfrshclrs();

	void on_pushButton_15_clicked();

	void on_pushButton_16_clicked();
/*public slots:
	void refreshAllTabs();*/
	void on_spinBox_valueChanged(int arg1);

signals:
	void smthChanged();
private:
	void init_colors();
	Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
