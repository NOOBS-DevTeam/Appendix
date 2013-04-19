#include <QtCore>
#include "Editor.h"
#include "SyntaxHighlighter.h"
#include <QFont>
#include <QTextDocument>
#include <QObject>
#include <QFile>

QString src_cpp="#include <iostream>\n\nusing namespace std;\n\nint main()\n\{\n\tcout << \"Hello world!\" << endl;\n\treturn 0;\n}";
QString src_pas="program hello_world;\n\nbegin\n\twriteln('HELLO WORLD!');\nend.";
QString src_apx="int main()\n{\n\tout (\"Hello world!\");\n\treturn 0\n}";
QSettings tweaks4("NOOBS-DevTeam","Appendix");
Editor::Editor(QWidget *parent,lang_t lng) : QPlainTextEdit(parent)
{
	lang = lng;
	changed =false;
	syntax = new SyntaxHighlighter(this->document(),this->lang);

	QVariant qvt = tweaks4.value("/Settings/Text/Font",QVariant(QFont("Consolas",10,QFont::Normal)));
	qvt.convert(QVariant::Font);
	QFont fnt = qvt.value<QFont>();
	this->document()->setDefaultFont(fnt);
	QPalette pal = this->palette();

	QVariant qv13 = tweaks4.value("/Settings/Text/BaseColor",QColor(Qt::white));
	qv13.convert(QVariant::Color);
	QColor qc13 = qv13.value<QColor>();
	pal.setColor(QPalette::Base,qc13);

	this->setPalette(pal);
	this->setTabStopWidth(tweaks4.value("/Settings/Text/TabSize",QVariant(26)).toInt());
	if (lang == CPP)
		this->setPlainText(src_cpp);
    if (lang == PAS)
		this->setPlainText(src_pas);
	if (lang == APX)
		this->setPlainText(src_apx);

	lineNumSpace = new LineNumSpace(this);
	//updateLineNumSpaceWidth(0);
	highlightCurrentLine();
	this->setLineWrapMode(QPlainTextEdit::NoWrap);
	connect(this,SIGNAL(textChanged()), this, SLOT(change()));
	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updatelineNumSpaceWidth(int)));
	connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updatelineNumSpace(QRect,int)));
	connect(this,SIGNAL(updateRequest(QRect,int)),this,SLOT(change()));
	setViewportMargins(30, 0, 0, 0);
	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
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

void Editor::change()
{
	changed=true;
	tabw->setTabText(cur_tab,'*'+findentry(filename));
}

void Editor::saved()
{
	changed = false;
}

void Editor::updateLineNumSpaceWidth(int /* newBlockCount */)
{
	setViewportMargins(30, 0, 0, 0);
}



void Editor::updateLineNumSpace(const QRect &rect, int dy)
{
	if (dy)
		lineNumSpace->scroll(0, dy);
	else
		lineNumSpace->update(0, rect.y(), lineNumSpace->width(), rect.height());

	if (rect.contains(viewport()->rect()))
		updateLineNumSpaceWidth(0);

}



void Editor::resizeEvent(QResizeEvent *e)
{
	QPlainTextEdit::resizeEvent(e);

	QRect cr = contentsRect();
	lineNumSpace->setGeometry(QRect(cr.left(), cr.top(), 29, cr.height()));
}



void Editor::highlightCurrentLine()
{
	QList<QTextEdit::ExtraSelection> extraSelections;

	if (!isReadOnly()) {
		QTextEdit::ExtraSelection selection;

		QColor lineColor = QColor(Qt::yellow).lighter(160);

		selection.format.setBackground(lineColor);
		selection.format.setProperty(QTextFormat::FullWidthSelection, true);
		selection.cursor = textCursor();
		selection.cursor.clearSelection();
		extraSelections.append(selection);
	}

	setExtraSelections(extraSelections);
}



void Editor::lineNumSpacePaintEvent(QPaintEvent *event)
{
	QPainter painter(lineNumSpace);
	painter.fillRect(event->rect(), Qt::lightGray);

	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
	int bottom = top + (int) blockBoundingRect(block).height();

	while (block.isValid() && top <= event->rect().bottom())
	{
		if (block.isVisible() && bottom >= event->rect().top())
		{
			QString number = QString::number(blockNumber + 1)+"   ";
			painter.setPen(Qt::black);
			painter.drawText(0, top, lineNumSpace->width(), fontMetrics().height(),
							 Qt::AlignRight, number);
		}
		block = block.next();
		top = bottom;
		bottom = top + (int) blockBoundingRect(block).height();
		blockNumber++;
	}
}

/*void Editor::scrollContentsBy(int, int)
{
	viewport()->update();
	emit SIGNAL(scrolled());
	//scroll();
}*/
