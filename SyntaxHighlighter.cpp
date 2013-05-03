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


#include <QtCore>
#include <QColor>
#include <QSettings>
#include "SyntaxHighlighter.h"

QSettings tweaks3("NOOBS-DevTeam","Appendix");

QColor what_color(lang_t l,int i)
{
	//================================
	QVariant qv0 = tweaks3.value("/Settings/SyntaxH/C++/prepr",QColor(Qt::darkGreen));
	qv0.convert(QVariant::Color);
	QColor qc0 = qv0.value<QColor>();
	//--------------------------------
	QVariant qv1 = tweaks3.value("/Settings/SyntaxH/C++/string",QColor(90,55,202));
	qv1.convert(QVariant::Color);
	QColor qc1 = qv1.value<QColor>();
	//--------------------------------
	QVariant qv2 = tweaks3.value("/Settings/SyntaxH/C++/comment",QColor(Qt::darkGray));
	qv2.convert(QVariant::Color);
	QColor qc2 = qv2.value<QColor>();
	//--------------------------------
	QVariant qv3 = tweaks3.value("/Settings/SyntaxH/C++/number",QColor(255,105,180));
	qv3.convert(QVariant::Color);
	QColor qc3 = qv3.value<QColor>();
	//--------------------------------
	QVariant qv4 = tweaks3.value("/Settings/SyntaxH/C++/keyword",QColor(Qt::darkBlue));
	qv4.convert(QVariant::Color);
	QColor qc4 = qv4.value<QColor>();
	//--------------------------------

	//================================
	QVariant qv5 = tweaks3.value("/Settings/SyntaxH/PAS/string",QColor(90,55,202));
	qv5.convert(QVariant::Color);
	QColor qc5 = qv5.value<QColor>();
	//--------------------------------
	QVariant qv6 = tweaks3.value("/Settings/SyntaxH/PAS/comment",QColor(Qt::darkGray));
	qv6.convert(QVariant::Color);
	QColor qc6 = qv6.value<QColor>();
	//--------------------------------
	QVariant qv7 = tweaks3.value("/Settings/SyntaxH/PAS/number",QColor(255,105,180));
	qv7.convert(QVariant::Color);
	QColor qc7 = qv7.value<QColor>();
	//--------------------------------
	QVariant qv8 = tweaks3.value("/Settings/SyntaxH/PAS/keyword",QColor(Qt::darkBlue));
	qv8.convert(QVariant::Color);
	QColor qc8 = qv8.value<QColor>();
	//--------------------------------

	//================================
	QVariant qv9 = tweaks3.value("/Settings/SyntaxH/APX/string",QColor(90,55,202));
	qv9.convert(QVariant::Color);
	QColor qc9 = qv9.value<QColor>();
	//--------------------------------
	QVariant qv10 = tweaks3.value("/Settings/SyntaxH/APX/comment",QColor(Qt::darkGray));
	qv10.convert(QVariant::Color);
	QColor qc10 = qv10.value<QColor>();
	//----------------------------------
	QVariant qv11 = tweaks3.value("/Settings/SyntaxH/APX/number",QColor(255,105,180));
	qv11.convert(QVariant::Color);
	QColor qc11 = qv11.value<QColor>();
	//----------------------------------
	QVariant qv12 = tweaks3.value("/Settings/SyntaxH/APX/keyword",QColor(Qt::darkBlue));
	qv12.convert(QVariant::Color);
	QColor qc12 = qv12.value<QColor>();
	//----------------------------------
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
	case APX:
		switch (i)
		{
		case 1:
			return qc9;
		case 2:
			return qc10;
		case 3:
			return qc11;
		case 4:
			return qc12;
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
	case APX:
		keywords
				<< "let"  << "int"  << "double" << "void" << "if"
				<< "then" << "else" << "while"  << "do"   << "out"
				<< "in"   << "return";
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
				setFormat(nStart,i-nStart+2,what_color(lng,2));
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
				setFormat(i,str.length()-i,what_color(lng,0));
				break;
			}
			else if (str.at(i).isNumber())
			{
				setFormat(i,1, what_color(lng,3));
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
				bool f1 = false;
				QString strKeyword = getKeyword(i,str);
				if (!strKeyword.isEmpty())
				{
					if (i && i!=str.length()-1)
					{
						if (isspace((str[i-1]).toLatin1())||ispunct((str[i-1]).toLatin1()))
							f1 = true;
						if (i==strKeyword.length())
							f1=true;
					}
					else if (!i)
					{
						if (i+strKeyword.length()<str.length())
							if (isspace((str[i+strKeyword.length()]).toLatin1())||ispunct((str[i+strKeyword.length()]).toLatin1()))
								f1 = true;
					}
					if (str.length()==i+strKeyword.length())
					{
						f1 = true;
					}
				}
				if (f1)
				{
					setFormat(i, strKeyword.length(), what_color(lng,4));
					i+= strKeyword.length()-1;
				}
			}
		}
	}
	if (nState == InsideCStyleComment)
	{
		setFormat(nStart, str.length() - nStart, what_color(lng,2));
	}
	if (nState == InsideCString)
	{
		setFormat(nStart, str.length() - nStart, what_color(lng,1));
	}
	setCurrentBlockState(nState);
}

QString SyntaxHighlighter::getKeyword(int nPos, const QString& str) const
{
	QString strTemp = "";
	bool f1=false,f2=false;
	if (!nPos)
		f1 = true;
	if (nPos==str.length()-1)
		f2 = true;
	foreach (QString strKeyword, keywords)
	{
		bool f = false;
		if (!f1)
			if (!isspace((str[nPos-1]).toLatin1())&&!ispunct((str[nPos-1]).toLatin1()))
				f=true;
		if (!f2)
			if (nPos+strKeyword.length()<str.length())
				if (!isspace((str[nPos+strKeyword.length()]).toLatin1())&&!ispunct((str[nPos+strKeyword.length()]).toLatin1()))
					f=true;
		if (str.mid(nPos,strKeyword.length()) == strKeyword && !f)
		{
			strTemp = strKeyword;
			break;
		}
	}
	return strTemp;
}
