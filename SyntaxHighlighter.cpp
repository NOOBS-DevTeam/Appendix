#include <QtCore>
#include "SyntaxHighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent) :QSyntaxHighlighter(parent)
{
	keywords
		<< "foreach"   << "bool"    << "int"    << "void"   << "double"
		<< "float"     << "char"    << "delete" << "class"  << "const"
		<< "virtual"   << "mutable" << "this"   << "struct" << "union"
		<< "throw"     << "for"     << "if"     << "else"   << "false"
		<< "namespace" << "new"     << "return" << "using"  << "true";
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
					setFormat(nStart,i-nStart+1, Qt::cyan);
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
			else if (str.mid(i,1)=="#")
			{
				setFormat(i,str.length()-i, Qt::green);
				break;
			}
			else if (str.at(i).isNumber())
			{
				setFormat(i,1, Qt::cyan);
			}
			else if (str.mid(i,2) == "/*")
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
					setFormat(nStart, str.length()-nStart, Qt::blue);
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
