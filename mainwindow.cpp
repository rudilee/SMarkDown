#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "markdownviewer.h"

#include <QFileDialog>
#include <QMdiSubWindow>
#include <QFileInfo>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setUnifiedTitleAndToolBarOnMac(true);
    setCentralWidget(ui->viewers);
    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpenFile_triggered()
{
    createViewer(QFileDialog::getOpenFileName(this, "Open Markdown File"));
}

void MainWindow::createViewer(QString filename)
{
    if (!filename.isEmpty()) {
        MarkdownViewer *viewer = new MarkdownViewer(ui->viewers, filename);
        QMdiSubWindow *subWindow = ui->viewers->addSubWindow(viewer);

        subWindow->setWindowTitle(QFileInfo(filename).fileName());
        subWindow->showMaximized();
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    createViewer(QUrl(event->mimeData()->text()).toString(QUrl::RemoveScheme));
}
