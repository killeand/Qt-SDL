#include "MdiWindow.h"

MdiWindow::MdiWindow() : MdiArea(new QMdiArea) {
	MdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded); // Show scroll bars as necessary
	MdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	setCentralWidget(MdiArea); // QMainWindow basics
	setWindowTitle("QMainWindow with MdiArea SDL Rendering Example");
	setBaseSize(640, 480);

	QMdiSubWindow * MdiChild = new QMdiSubWindow(this); // Creating a basic QMdiSubWindow to show a standard
	MdiChild->setWindowTitle("MDI Child");				// Mdi window open along side of an SDL Mdi window
	MdiChild->resize(200, 200);
	MdiArea->addSubWindow(MdiChild);

	SDLChild * SdlChild = new SDLChild(this);	// Creating the SDL Window and initializing it. The window
	SdlChild->SDLInit();						// itself must contain an inner widget, or else SDL will draw over
	SdlChild->setWindowTitle("MDI SDL Child");		// the window controls. Not the end of the world, but in this
	SdlChild->resize(200, 200);			// case, its not the desired result. We must also run the SDL
	MdiArea->addSubWindow(SdlChild);			// CreateWindow and CreateRenderer after the constructor.

	MdiChild->show();
	SdlChild->show();
}