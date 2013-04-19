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
	//void scrollContentsBy(int, int);

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
