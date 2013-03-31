#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>

namespace Ui {
class newfiledialog;
}

class newfiledialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit newfiledialog(QWidget *parent = 0);
    ~newfiledialog();
    
private:
    Ui::newfiledialog *ui;
};

#endif // NEWFILEDIALOG_H
