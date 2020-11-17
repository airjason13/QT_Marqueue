#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ledscreen.h"
#include <QScreen>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)


{
    ui->setupUi(this);
    ui->ButtonShow->setText("Show Widget");

    timer = new QTimer(this);

    QObject::connect(ui->ButtonShow,SIGNAL(clicked()), this, SLOT(ClickShowButton()));
    QObject::connect(ui->ButtonClose,SIGNAL(clicked()), this, SLOT(ClickCloseButton()));


    connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
    //timer->start(1000);
    //timer->setInterval(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test()
{
    qDebug() << "Jason" << "test";
}

void MainWindow::ClickShowButton()
{
    qDebug() << "Jason" << "ClickButton";

    //QScreen *screen = QGuiApplication::primaryScreen();
    qDebug() << QGuiApplication::screens().count();
    //QScreen *screen = QGuiApplication::screens().at(0);
    //qDebug() << "Text : " << ui->textEdit->toPlainText();
    //QString text = ui->textEdit->toPlainText();

    //led.setlabelText(text);
    //qDebug() << "QString text : " << text;
    //QRect r = screen->geometry();
    /*QRect r = led.geometry();
    QPixmap pix = led.grab(r);
    qDebug() << "x :" << r.x();
    qDebug() << "y :" << r.y();
    qDebug() << "width :" << r.width();
    qDebug() << "height :" << r.height();*/
    //if(!pix.save(QDir::tempPath() + QString("~/Pictures/_%1.jpg").arg(1)))
    //    qDebug() << "ERROR: Unable to update screenshot for screen #" ;
    //led.update();
    qDebug() << "text : " << ui->textEdit->toPlainText();
    emit startbuttonclicked(ui->textEdit->toPlainText());
}

void MainWindow::ClickCloseButton()
{
    qDebug() << "Jason" << "ClickCloseButton";
    emit stopbuttonclicked();
}

void MainWindow::timer_timeout()
{
    qDebug() << "MainWindow timer_timeout";


}
