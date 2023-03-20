#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_readButton_clicked()
{
    QString filter = "All Files (*,*) ;; Text File (*.txt)";
    QString file_name = QFileDialog::getOpenFileName(this, "Выберите файл", "C://", filter);
    QFile file(file_name);

    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не получилось открыть файл");
    }

    QTextStream in(&file);
    QString text = in.readAll();
    ui->plainTextEdit->setPlainText(text);

    file.close();
}


void MainWindow::on_writeButton_clicked()
{
    QString filter = "Text File (*.txt)";
    QString file_name = QFileDialog::getSaveFileName(this, "Выберите файл", "C://", filter);
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не получилось сохранить файл");
    }

    QTextStream out(&file);
    QString text = ui->plainTextEdit->toPlainText();
    out << text;
    file.flush();

    file.close();
}

