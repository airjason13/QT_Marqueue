#include "ledshow.h"
#include "ui_led.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::accept()
{
    qDebug() << "LED" ;
}
