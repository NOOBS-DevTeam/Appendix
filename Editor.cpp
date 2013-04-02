#include <QtCore>
#include "Editor.h"
#include "SyntaxHighlighter.h"
#include <QFont>

QString src_cpp="#include <iostream>\n\nusing namespace std;\n\nint main()\n\{\n    cout << \"Hello world!\" << endl;\n    return 0;\n}";
QString src_pas="program hello_world;\n\nbegin\n  writeln('HELLO WORLD!');\nend.";
Editor::Editor(QWidget *parent,lang_t lng)
{
	lang = lng;
	syntax = new SyntaxHighlighter(this->document(),this->lang);
	QFont fnt("Consolas",9,QFont::Normal);
	this->document()->setDefaultFont(fnt);
	QPalette pal = this->palette();
	pal.setColor(QPalette::Base, Qt::white);
	pal.setColor(QPalette::Text, Qt::black);
	this->setPalette(pal);
	if (lang == CPP)
		this->append(src_cpp);
    if (lang == PAS)
		this->append(src_pas);
}

void Editor::refresh()
{
	delete syntax;
	syntax = new SyntaxHighlighter(this->document(),this->lang);
}

void Editor::setLang(lang_t lng)
{
	lang = lng;
	this->refresh();
}

lang_t Editor::getLang()
{
	return this->lang;
}
