#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class QTextDocument;
enum lang_t
{
	CPP=0,
	PASCAL
};
class SyntaxHighlighter : public QSyntaxHighlighter
{
	Q_OBJECT
private:
	QStringList keywords;
protected:
	lang_t lng;
	enum
	{ NormalState = -1, InsideCStyleComment, InsideCString };
	void highlightBlock(const QString&);
	QString getKeyword(int nPos, const QString& str) const;
public:
	SyntaxHighlighter(QTextDocument* parent = 0,lang_t lang=CPP);
};
#endif // SYNTAXHIGHLIGHTER_H
