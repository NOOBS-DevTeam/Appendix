#include "newfiledialog.h"
#include "ui_newfiledialog.h"

newfiledialog::newfiledialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newfiledialog)
{
    ui->setupUi(this);
}

newfiledialog::~newfiledialog()
{
    delete ui;
}
