#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}



QPaintEngine *MainWindow::paintEngine() const
{
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    auto url = event->mimeData()->urls().first();
    qDebug() << url;
    QMimeDatabase db;
    QMimeType type = db.mimeTypeForUrl(url);
    if(type.name().contains("image/"))
    {
        qDebug("Its an image, whod figure");
        event->accept();
    } else {
        event->ignore();
    }

}

void MainWindow::dropEvent(QDropEvent *event)
{
    qDebug() << event;
    event->acceptProposedAction();

    auto url = event->mimeData()->urls().first();
    qDebug() << url;
    auto path = url.toLocalFile();
    QFile file(path);

    qDebug() << file.fileName();

    auto pm = QPixmap();
    pm.load(file.fileName());
    qDebug() << pm;

    QFileInfo fi(file);
    qDebug() << fi.completeSuffix();
    auto outname = QString("%1/%2_stripped.%3").arg(fi.absoluteDir().path()).arg(fi.baseName()).arg(fi.suffix());
    qDebug() << outname;

    // Resaving it magically removes all the EXIF metadata and hopefully XMPP too. 🤷‍♀️
    pm.save(outname, fi.suffix().toStdString().c_str());
}
