#ifndef SERVICESIM_H
#define SERVICESIM_H

#include <QMainWindow>

namespace Ui {
class ServiceSim;
}

class ServiceSim : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServiceSim(QWidget *parent = 0);
    ~ServiceSim();

private:
    Ui::ServiceSim *ui;
};

#endif // SERVICESIM_H
