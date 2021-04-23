#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>

extern std::string path;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_actionOpen_File_rcc_triggered();

    void clear_file();

    void on_actionClose_File_rcc_triggered();

    void on_tabWidget_tabBarClicked(int index);

    void on_actionNew_File_rcc_triggered();

    void on_pushButton_clicked();

    void on_checkBox_2_stateChanged(int arg1);

    void on_actionClose_New_File_rcc_triggered();


private:
    Ui::MainWindow *ui;
    QString fileNameRCC;
    QString dir_new;
};
#endif // MAINWINDOW_H
