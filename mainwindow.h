#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_tabWidget_tabCloseRequested(int index);

    void on_tabWidget_currentChanged(int index);

    void on_lineEdit_returnPressed();

    void on_action_2_activated();

    void on_action_2_activated(int arg1);

    void on_action_2_changed();

    void on_action_2_triggered();

    void on_action_triggered();

    void on_action_23_triggered();

    void on_action_24_triggered();

    void on_action_3_triggered();

	void slotDataOnStdout();

	void slotDataOnError();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
