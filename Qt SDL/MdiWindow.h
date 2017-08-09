#ifndef _MDI_WINDOW_H
#define _MDI_WINDOW_H

#include <qmainwindow.h>
#include <qmdiarea.h>
#include <qmdisubwindow.h>

#include "SDLChild.h"

/*
	This is a VERY simple example of a QMainWindow set up to contain
	an Mdi Area. We want to show a QT window existing along side an
	SDL window.
*/

class MdiWindow : public QMainWindow {
Q_OBJECT
public:
	MdiWindow();
private:
	QMdiArea * MdiArea;
};

#endif