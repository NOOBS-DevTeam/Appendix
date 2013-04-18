#ifndef EDITOR_H
#define EDITOR_H
#include <QTextEdit>
#include "mainwindow.h"
#include "SyntaxHighlighter.h"
#include <QTabWidget>
#include <QObject>

extern int cur_tab;
extern QTabWidget *tabw;

class Editor : public QTextEdit
{
	Q_OBJECT
private:
	SyntaxHighlighter* syntax;
	lang_t lang;

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

};

#endif // EDITOR_H
