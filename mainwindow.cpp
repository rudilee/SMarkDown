#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "markdownviewer.h"

#include <QFileDialog>
#include <QMdiSubWindow>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setUnifiedTitleAndToolBarOnMac(true);
    setCentralWidget(ui->viewers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpenFile_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Markdown File");
    if (!filename.isEmpty()) {
        MarkdownViewer *viewer = new MarkdownViewer(ui->viewers, filename);
        QMdiSubWindow *subWindow = ui->viewers->addSubWindow(viewer);

        subWindow->setWindowTitle(QFileInfo(filename).fileName());
        subWindow->showMaximized();
    }
}
