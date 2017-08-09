#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H

#include <qmainwindow.h>
#include <qwidget.h>
#include <qtimer.h>
#include <SDL.h>

/*
	This is an old example of setting up the SDL rendering context to be the MainWindow
	itself. Simply replace the MdiWindow reference in Program.cpp with MainWindow.
*/
class MainWindow : public QMainWindow {
Q_OBJECT
public:
	MainWindow();
	~MainWindow();

	void SDLInit();
	void SetWindow(SDL_Window * ref);
	void SetRenderer(SDL_Renderer * ref);
	SDL_Window * GetWindow();
	SDL_Renderer * GetRenderer();
private:
	QWidget * MainWindowWidget;
	SDL_Window * WindowRef;
	SDL_Renderer * RendererRef;
	QTimer * Time;
	int position;
	int dir;
private slots:
	void Render();
};

#endif