#include "controlswindow.h"
#include "qcorr.h"


ControlsWindow::ControlsWindow(QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);

	this->setMinimumSize(ui.controlsWindow_frame->size());


	connect(ui.close_pushButton, SIGNAL(clicked()), this, SLOT(close()));

}

ControlsWindow::~ControlsWindow()
{

}



// begin Q_SLOTS vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//void ControlsWindow::closeWindow(){
//      emit reject();
//}


// end Q_SLOTS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
