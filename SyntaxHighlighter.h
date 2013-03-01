#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class QTextDocument;

class SyntaxHighlighter : public QSyntaxHighlighter
{
	Q_OBJECT
private:
	QStringList keywords;
protected:
	enum
	{ NormalState = -1, InsideCStyleComment, InsideCString };
	void highlightBlock(const QString&);
	QString getKeyword(int nPos, const QString& str) const;
public:
	SyntaxHighlighter(QTextDocument* parent = 0);
};

#endif // SYNTAXHIGHLIGHTER_H
