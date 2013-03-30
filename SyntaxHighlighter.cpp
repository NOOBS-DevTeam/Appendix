#include <QtCore>
#include <QColor>
#include <QSettings>
#include "SyntaxHighlighter.h"

QSettings tweaks3("NOOBS-DevTeam","Appendix");

QColor what_color(lang_t l,int i)
{
	QVariant qv0 = tweaks3.value("/Settings/SyntaxH/C++/prepr",QColor(Qt::darkGreen));
	qv0.convert(QVariant::Color);
	QColor qc0 = qv0.value<QColor>();
	QVariant qv1 = tweaks3.value("/Settings/SyntaxH/C++/string",QColor(90,55,202));
	qv1.convert(QVariant::Color);
	QColor qc1 = qv1.value<QColor>();
	QVariant qv2 = tweaks3.value("/Settings/SyntaxH/C++/comment",QColor(Qt::darkGray));
	qv2.convert(QVariant::Color);
	QColor qc2 = qv2.value<QColor>();
	QVariant qv3 = tweaks3.value("/Settings/SyntaxH/C++/number",QColor(255,105,180));
	qv3.convert(QVariant::Color);
	QColor qc3 = qv3.value<QColor>();
	QVariant qv4 = tweaks3.value("/Settings/SyntaxH/C++/keyword",QColor(Qt::darkBlue));
	qv4.convert(QVariant::Color);
	QColor qc4 = qv4.value<QColor>();
	QVariant qv5 = tweaks3.value("/Settings/SyntaxH/PAS/string",QColor(90,55,202));
	qv5.convert(QVariant::Color);
	QColor qc5 = qv5.value<QColor>();
	QVariant qv6 = tweaks3.value("/Settings/SyntaxH/PAS/comment",QColor(Qt::darkGray));
	qv6.convert(QVariant::Color);
	QColor qc6 = qv6.value<QColor>();
	QVariant qv7 = tweaks3.value("/Settings/SyntaxH/PAS/number",QColor(255,105,180));
	qv7.convert(QVariant::Color);
	QColor qc7 = qv7.value<QColor>();
	QVariant qv8 = tweaks3.value("/Settings/SyntaxH/PAS/keyword",QColor(Qt::darkBlue));
	qv8.convert(QVariant::Color);
	QColor qc8 = qv8.value<QColor>();
	switch (l)
	{
	case CPP:
		switch (i)
		{
		case 0:
			return qc0;
		case 1:
			return qc1;
		case 2:
			return qc2;
		case 3:
			return qc3;
		case 4:
			return qc4;
		}
		break;
	case PAS:
		switch (i)
		{
		case 1:
			return qc5;
		case 2:
			return qc6;
		case 3:
			return qc7;
		case 4:
			return qc8;
		}
		break;
	}
}

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent, lang_t lang) :QSyntaxHighlighter(parent)
{
	lng = lang;
	switch(lng)
	{
	case CPP:
		keywords
			<< "foreach"   << "bool"    << "int"    << "void"   << "double"
			<< "float"     << "char"    << "delete" << "class"  << "const"
			<< "virtual"   << "mutable" << "this"   << "struct" << "union"
			<< "throw"     << "for"     << "if"     << "else"   << "false"
			<< "namespace" << "new"     << "return" << "using"  << "true";
		break;
    case PAS:
		keywords
				<< "and"          << "array"     << "as"             << "begin"        << "break"
				<< "case"         << "class"     << "const"          << "constructor"  << "continue"
				<< "destructor"   << "div"       << "do"             << "downto"       << "else"
				<< "end"          << "exit"      << "external"       << "externalsync" << "file"
				<< "finalization" << "for"       << "forward"        << "function"     << "if"
				<< "in"           << "inherited" << "initialization" << "is"           << "mod"
				<< "not"          << "of"        << "or"             << "private"      << "procedure"
				<< "program"      << "property"  << "protected"      << "public"       << "record"
				<< "repeat"       << "set"       << "shl"            << "shr"          << "sizeof"
				<< "string"       << "then"      << "to"             << "type"         << "unit"
				<< "unit"         << "until"     << "uses"           << "var"          << "while"
				<< "with"         << "xor";
		break;
	}
}

void SyntaxHighlighter::highlightBlock(const QString& str)
{
	int nState = previousBlockState();
	int nStart = 0;
	for (int i=0; i<str.length(); i++)
	{
		if (nState == InsideCStyleComment)
		{
			if (str.mid(i,2)=="*/")
			{
				nState = NormalState;
				setFormat(nStart,i-nStart+2,what_color(lng,2));//darkGrey
				i++;
			}
		}
		else if (nState == InsideCString)
		{
			if (str.mid(i,1)=="\"" || str.mid(i,1)=="\'")
			{
				if (str.mid(i-1,2)!="\\\"" && str.mid(i-1,2)!="\\\'")
				{
					nState = NormalState;
					setFormat(nStart,i-nStart+1,what_color(lng,1));
				}
			}
		}
		else
		{
			if (str.mid(i,2)=="//")
			{
                setFormat(i,str.length()-i,what_color(lng,2));
                break;
			}
			else if (str.mid(i,1)=="#" && lng == CPP)
			{
				setFormat(i,str.length()-i,what_color(lng,0));//darkGreen
				break;
			}
			else if (str.at(i).isNumber())
			{
				setFormat(i,1, what_color(lng,3));//QColor(255,105,180)
			}
			else if (str.mid(i,2) == "/*" && lng == CPP)
			{
				nStart = i;
				nState = InsideCStyleComment;
			}
			else if (str.mid(i,1)=="\"" || str.mid(i,1)=="\'")
			{
				nStart = i;
				nState = InsideCString;
			}
			else
			{
				QString strKeyword = getKeyword(i,str);
				if (!strKeyword.isEmpty())
				{
					setFormat(nStart, str.length()-nStart, what_color(lng,4));//darkBlue
					i+= strKeyword.length()-1;
				}
			}
		}
	}
	if (nState == InsideCStyleComment)
	{
		setFormat(nStart, str.length() - nStart, what_color(lng,2));//darkGrey
	}
	if (nState == InsideCString)
	{
		setFormat(nStart, str.length() - nStart, what_color(lng,1));//cyan
	}
	setCurrentBlockState(nState);
}

QString SyntaxHighlighter::getKeyword(int nPos, const QString& str) const
{
	QString strTemp = "";
	foreach (QString strKeyword, keywords)
	{
		if (str.mid(nPos,strKeyword.length()) == strKeyword)
		{
			strTemp = strKeyword;
			break;
		}
	}
	return strTemp;
}
