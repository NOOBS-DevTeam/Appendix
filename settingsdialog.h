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

private:
	void init_colors();
	Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
