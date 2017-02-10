#ifndef CONTROLLEARN_H
#define CONTROLLEARN_H

#include <QDialog>

namespace Ui {
class ControlLearn;
}

class ControlLearn : public QDialog
{
    Q_OBJECT

public:
    explicit ControlLearn(QWidget *parent = 0);
    ~ControlLearn();

private:
    Ui::ControlLearn *ui;
};

#endif // CONTROLLEARN_H
