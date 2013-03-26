#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);
	//ui->splitter->setSizes(QList<int>() << 160 << 400);
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}
