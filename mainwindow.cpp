#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QResource>
#include <QCryptographicHash>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(771, 508);
    this->move(382, 134);

    ui->lineEdit->setEchoMode(QLineEdit::Password);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);


}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1==2){
        ui->lineEdit->setEchoMode(QLineEdit::Normal);
    }

    else{
        ui->lineEdit->setEchoMode(QLineEdit::Password);
    }

}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1==2){
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    }

    else{
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    }
}



void MainWindow::on_pushButton_2_clicked()
{


    int a = QResource::registerResource(fileNameRCC);

    QFile file(":/File/__Password__.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text) || !a){
        QMessageBox *mg;
        mg->critical(0,"Error!!","Worng \".rcc\" file.");
    }

    QString temp;

    while (!file.atEnd()) {
        temp = file.readLine();
    }

    if(QString(QCryptographicHash::hash(ui->lineEdit->text().toUtf8(),QCryptographicHash::Sha256).toHex()) == temp){

        QMessageBox *mg;
        mg->information(0,"Successful!!","Password confirmed.");

        QDir directory(":/File");
        QStringList ls = directory.entryList(QStringList(),QDir::Files);
        foreach(QString filename, ls) {
            ui->textBrowser->append("       --> "+filename);
        }

        ui->pushButton_2->setText("✓✓✓");

        ui->pushButton_3->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
    }

    else{
        QMessageBox *mg;
        mg->critical(0,"Error!!","Worng Password.");
    }

    ui->lineEdit->setText("");
}

void MainWindow::on_pushButton_3_clicked()
{

    int a = QResource::registerResource(fileNameRCC);

    if (!a){
        QMessageBox *mg;
        mg->critical(0,"Error!!","Worng \".rcc\" file.");

        return;
    }

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        "/home",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);

    QDir directory(":/File");
    QStringList ls = directory.entryList(QStringList(),QDir::Files);

    QString command;
    foreach(QString filename, ls) {

        QFile file(":/File/"+filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            continue;
        }

        else{

            file.copy(dir+"/"+filename);

        }

    }

    QString tmp = "The extraction of files is successful. Please check the "+dir+"/ directory.";

    QMessageBox *mg;
    mg->information(0,"Successful!!",tmp);
}



void MainWindow::on_actionOpen_File_rcc_triggered()
{
    fileNameRCC = QFileDialog::getOpenFileName(this,
        tr("Open .rcc"), "/home", tr(".rcc File (*.rcc)"));

    if(fileNameRCC=="" || fileNameRCC==" "){

        QMessageBox *mg;
        mg->critical(0,"Error!!","Please select \".rcc\" file.");

    }


    else{

        int a = QResource::registerResource(fileNameRCC);

        QFile file(":/File/__Password__.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text) || !a){
            QMessageBox *mg;
            mg->critical(0,"Error!!","Worng \".rcc\" file.");
        }

        else{
            QMessageBox *mg;
            mg->information(0,"Successful!!","File \".rcc\" selected successfully.");

            ui->actionClose_File_rcc->setEnabled(true);
            ui->actionOpen_File_rcc->setEnabled(false);

            ui->pushButton_2->setEnabled(true);
        }
    }
}


void MainWindow::on_actionClose_File_rcc_triggered()
{
    ui->pushButton_2->setText("Unfreeze file");
    fileNameRCC="";

    ui->lineEdit->setText("");

    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);

    ui->textBrowser->setText("\n    Solved files:\n");

    ui->actionClose_File_rcc->setEnabled(false);
    ui->actionOpen_File_rcc->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if(index==0){

        on_actionClose_File_rcc_triggered();

        ui->actionClose_File_rcc->setEnabled(false);
        ui->actionOpen_File_rcc->setEnabled(false);
        ui->actionNew_File_rcc->setEnabled(true);
    }

    else{

        clear_file();
        ui->actionClose_File_rcc->setEnabled(false);
        ui->actionOpen_File_rcc->setEnabled(true);
        ui->actionNew_File_rcc->setEnabled(false);
        ui->actionClose_New_File_rcc->setEnabled(false);
        ui->textBrowser_2->setText("\n    Files to be frozen:\n");
        ui->lineEdit_2->setText("");

    }
}

void MainWindow::on_actionNew_File_rcc_triggered()
{

    dir_new = QFileDialog::getExistingDirectory(this, tr("Open directory"),
                                                        "/home",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);

    QDir directory(dir_new);
    QStringList ls = directory.entryList(QStringList(),QDir::Files);
    foreach(QString filename, ls) {
        ui->textBrowser_2->append("       --> "+filename);
    }

    ui->pushButton->setEnabled(true);
    ui->actionClose_New_File_rcc->setEnabled(true);
    ui->actionNew_File_rcc->setEnabled(false);
}

void MainWindow::on_pushButton_clicked()
{

    QFile file(QString::fromStdString(path)+"/__Password__.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    file.write(qPrintable(QCryptographicHash::hash(ui->lineEdit_2->text().toUtf8(),QCryptographicHash::Sha256).toHex()));
    file.close();

    QString file_str = "";
    file_str+="<RCC>\n";
    file_str+="    <qresource prefix=\"/File\">\n";
    file_str+="        <file>__Password__.txt</file>\n";

    QDir directory(dir_new);
    QStringList ls = directory.entryList(QStringList(),QDir::Files);

    foreach(QString filename, ls) {

        QFile file(dir_new+"/"+filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            continue;
        }

        else{

            file.copy(QString::fromStdString(path)+"/"+filename);
            file_str+="        <file>"+filename+"</file>\n";

        }

    }

    file_str+="    </qresource>\n";
    file_str+="</RCC>";

    QFile file_new(QString::fromStdString(path)+"/temp.qrc");
    file_new.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out_new(&file);
    file_new.write(qPrintable(file_str));
    file_new.close();


    QString run = QFileDialog::getExistingDirectory(this, tr("Select the directory where the .rcc file will be saved."),
                                                            "/home",
                                                            QFileDialog::ShowDirsOnly
                                                            | QFileDialog::DontResolveSymlinks);

    system(qPrintable("rcc -binary "+QString::fromStdString(path)+"/temp.qrc"+" -o "+run+"/myRCC.rcc"));

    clear_file();

    QString message = "Compiling is successful, your files have been encrypted. Do not lose the file named "+run+"/myRCC.rcc"+".";
    QMessageBox *mg;
    mg->information(0,"Successful!!",message);


}


void MainWindow::on_actionClose_New_File_rcc_triggered()
{

    clear_file();
    ui->actionClose_New_File_rcc->setEnabled(false);
    ui->actionNew_File_rcc->setEnabled(true);
    ui->textBrowser_2->setText("\n    Files to be frozen:\n");
    ui->lineEdit_2->setText("");
    dir_new="";

}

void MainWindow::clear_file(){

    QDir directory(dir_new);
    QStringList ls = directory.entryList(QStringList(),QDir::Files);

    foreach(QString filename, ls) {

        QFile file(QString::fromStdString(path)+"/"+filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            continue;
        }

        else{

            file.remove();

        }

    }

}
