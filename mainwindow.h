#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Editor.h"
#include <QMainWindow>

extern int cur_tab;
extern QTabWidget *tabw;
namespace Ui {
class MainWindow;
}

QString findentry(QString filename);

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

    void on_action_2_triggered();

    void on_action_triggered();

    void on_action_23_triggered();

    void on_action_24_triggered();

    void on_action_3_triggered();

	void slotDataOnStdout();

	void slotDataOnError();

	void writeTweaks();

    void on_action_10_triggered();

    void on_toolButton_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_4_clicked();

	void on_action_8_triggered();

    void on_actionPascal_triggered();

    void on_actionC_triggered();

    void on_toolButton_2_clicked();

    void on_action_29_triggered();
	void on_action_25_triggered();

	void on_toolButton_6_clicked();

	void on_action_27_triggered();

public slots:

	void refreshAllTabs();

	void switchRun();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

