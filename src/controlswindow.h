#ifndef CONTROLSWINDOW_H
#define CONTROLSWINDOW_H

#include <QtGui/QDialog>
#include "../ui_controlswindow.h"

class Qcorr;   // using this friend class

class ControlsWindow : public QDialog
{
    Q_OBJECT

public:
    ControlsWindow(QWidget *parent = 0);
    ~ControlsWindow();

private Q_SLOTS:
//    void cancelMethod();
//    void chooseMethod();

private:
    Ui::ControlsWindowClass ui;
};

#endif // CONTROLSWINDOW_H
