#ifndef EDITOR_H
#define EDITOR_H
#include <QTextEdit>
#include "mainwindow.h"
#include "SyntaxHighlighter.h"

class Editor : public QTextEdit
{
	Q_OBJECT
private:
	SyntaxHighlighter* syntax;
	lang_t lang;
public:
	Editor(lang_t lang);
	void setLang(lang_t lng);
	void refresh();
	lang_t getLang();

};

#endif // EDITOR_H
