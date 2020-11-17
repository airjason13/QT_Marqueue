#include "ledshowa.h"
#include "ui_ledshowa.h"

ledshowa::ledshowa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ledshowa)
{
    ui->setupUi(this);
}

ledshowa::~ledshowa()
{
    delete ui;
}
