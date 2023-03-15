#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    tree = BinaryTree<int, std::string>();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Add_clicked()
{
    int key = ui->K->text().toInt();
    std::string data = ui->V->text().toStdString();
    tree.insertItem(key,data);
    Update();
}

void MainWindow::on_Remove_clicked()
{
    tree.deleteItem(ui->K->text().toInt());
    ui->K->clear();
    ui->V->clear();
    Update();
}


void MainWindow::on_Clear_clicked()
{
    tree.clear();
    Update();
}


void MainWindow::Update() {
    ui->listWidget->clear();
    if (tree.empty()) {
        return;
    }
    for (const auto &key: tree.getKeys()) {
        auto value = tree[key];
        QString item =
                QString::number(key) + ' ' +
                QString::fromStdString(value);
        ui->listWidget->addItem(item);

    }
}

void MainWindow::on_actionSave_triggered()
{
    QString file_name =
            QFileDialog::getSaveFileName(this, "Save the file");
    tree.write(file_name.toStdString());
}

void MainWindow::on_actionOpen_triggered()
{
    QString file_name =
            QFileDialog::
            getOpenFileName(this, "Open the file");
    tree.read(file_name.toStdString());
    Update();
}
