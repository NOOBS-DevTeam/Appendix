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


#include "helpdialog.h"
#include "ui_helpdialog.h"
#include <QTextBrowser>
#include <QUrl>
#include <QStringList>
#include <QDebug>
#include <QTextCodec>
QString readFile(QString filename);

helpdialog::helpdialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::helpdialog)
{

	QStringList qstl;
	qstl.append(QString(":/doc/"));
	ui->setupUi(this);
	ui->textBrowser->setSearchPaths(QStringList() << ":/doc");
	ui->textBrowser->setSource(QUrl("index.html"));
	qDebug()<< ui->textBrowser->source();
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(close()));

}

helpdialog::~helpdialog()
{
	delete ui;
}
