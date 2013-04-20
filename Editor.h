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


#ifndef EDITOR_H
#define EDITOR_H
#include <QPlainTextEdit>
#include "mainwindow.h"
#include "SyntaxHighlighter.h"
#include <QTabWidget>
#include <QObject>

extern int cur_tab;
extern QTabWidget *tabw;

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
class LineNumSpace;

class Editor : public QPlainTextEdit
{
	Q_OBJECT

private:
	SyntaxHighlighter* syntax;
	lang_t lang;
	QWidget *lineNumSpace;

private slots:
	void updateLineNumSpaceWidth(int newBlockCount);
	void highlightCurrentLine();
	void updateLineNumSpace(const QRect &, int);

signals:
	void scrolled();
protected:
	void resizeEvent(QResizeEvent *event);

public slots:
	void change();

public:
	QString filename;
	bool changed;

	explicit Editor(QWidget *parent = 0,lang_t lang = CPP);
	void setLang(lang_t lng);
	void refresh();
	void saved();
	lang_t getLang();
	void lineNumSpacePaintEvent(QPaintEvent *event);
};

class LineNumSpace : public QWidget
{
public:
	LineNumSpace(Editor *edit) : QWidget(edit)
	{
		editor = edit;
	}
	QSize sizeHint() const
	{
		return QSize(28,0);
	}

protected:
	void paintEvent(QPaintEvent *event)
	{
		editor->lineNumSpacePaintEvent(event);
	}

private:
	Editor *editor;
};

#endif // EDITOR_H
