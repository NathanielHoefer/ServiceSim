#include "servicesim.h"
#include "ui_servicesim.h"

ServiceSim::ServiceSim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServiceSim)
{
    ui->setupUi(this);
}

ServiceSim::~ServiceSim()
{
    delete ui;
}
