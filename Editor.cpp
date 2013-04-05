#include <QtCore>
#include "Editor.h"
#include "SyntaxHighlighter.h"
#include <QFont>
#include <QTextDocument>
QString src_cpp="#include <iostream>\n\nusing namespace std;\n\nint main()\n\{\n\tcout << \"Hello world!\" << endl;\n\treturn 0;\n}";
QString src_pas="program hello_world;\n\nbegin\n\twriteln('HELLO WORLD!');\nend.";
QString src_apx="int main()\n{\n\tout (\"Hello world!\");\n\treturn 0;\n}";
QSettings tweaks4("NOOBS-DevTeam","Appendix");
Editor::Editor(QWidget *parent,lang_t lng)
{
	lang = lng;
	syntax = new SyntaxHighlighter(this->document(),this->lang);
	QVariant qvt = tweaks4.value("/Settings/Text/Font",QVariant(QFont("Consolas",10,QFont::Normal)));
	qvt.convert(QVariant::Font);
	QFont fnt = qvt.value<QFont>();
	this->document()->setDefaultFont(fnt);
	QPalette pal = this->palette();
	//pal.setColor(QPalette::Base, Qt::white);
	QVariant qv13 = tweaks4.value("/Settings/Text/BaseColor",QColor(Qt::white));
	qv13.convert(QVariant::Color);
	QColor qc13 = qv13.value<QColor>();
	pal.setColor(QPalette::Base,qc13);
	this->setPalette(pal);
	this->setTabStopWidth(tweaks4.value("/Settings/Text/TabSize",QVariant(26)).toInt());
	if (lang == CPP)
		this->append(src_cpp);
    if (lang == PAS)
		this->append(src_pas);
	if (lang == APX)
		this->append(src_apx);
}

void Editor::refresh()
{
	delete syntax;
	syntax = new SyntaxHighlighter(this->document(),this->lang);
	QVariant qvt = tweaks4.value("/Settings/Text/Font",QVariant(QFont("Consolas",10,QFont::Normal)));
	qvt.convert(QVariant::Font);
	QFont fnt = qvt.value<QFont>();
	this->document()->setDefaultFont(fnt);
	QPalette pal = this->palette();
	//pal.setColor(QPalette::Base, Qt::white);
	QVariant qv13 = tweaks4.value("/Settings/Text/BaseColor",QColor(Qt::white));
	qv13.convert(QVariant::Color);
	QColor qc13 = qv13.value<QColor>();
	pal.setColor(QPalette::Base,qc13);
	this->setPalette(pal);
	this->setTabStopWidth(tweaks4.value("/Settings/Text/TabSize",QVariant(26)).toInt());
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
