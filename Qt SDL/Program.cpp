#include <qapplication.h>
#include <SDL.h>

#include "MdiWindow.h"
#include "MainWindow.h"

int main(int argc, char * argv[]) {
	QApplication a(argc, argv); // Basics of QT, start an application

	SDL_Init(SDL_INIT_VIDEO); // Basics of SDL, init what you need to use

	
	MdiWindow MdiExample; // Creating and using a QMainWindow with an Mdi Area
	MdiExample.show();
	
	MainWindow MainWinExample;	// Creating an using a QMainWindow with central SDL widget
	MainWinExample.SDLInit();	// <- Need to run SDL setup after qt window setup
	MainWinExample.show();
	
	int RetVal = a.exec();	// Most examples have this on the return, we
							// need to have it return to a variable cause:

	SDL_Quit();	// We can't put this statement before the exec, or after
				// the return

	return RetVal;
}