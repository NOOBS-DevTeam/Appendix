#include <QtCore>
#include <QColor>
#include "SyntaxHighlighter.h"

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
	case PASCAL:
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
				setFormat(nStart,i-nStart+2,Qt::darkGray);
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
                    setFormat(nStart,i-nStart+1,QColor(90,55,202));
				}
			}
		}
		else
		{
			if (str.mid(i,2)=="//")
			{
				setFormat(i,str.length()-i, Qt::darkGray);
				break;
			}
			else if (str.mid(i,1)=="#" && lng == CPP)
			{
                setFormat(i,str.length()-i, Qt::darkGreen);
				break;
			}
			else if (str.at(i).isNumber())
			{
                setFormat(i,1, QColor(255,105,180));
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
                    setFormat(nStart, str.length()-nStart, Qt::darkBlue);
					i+= strKeyword.length()-1;
				}
			}
		}
	}
	if (nState == InsideCStyleComment)
	{
		setFormat(nStart, str.length() - nStart, Qt::darkGray);
	}
	if (nState == InsideCString)
	{
        setFormat(nStart, str.length() - nStart, Qt::cyan);
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
