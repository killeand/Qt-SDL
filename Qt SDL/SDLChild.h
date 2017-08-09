#ifndef _SDL_CHILD_H
#define _SDL_CHILD_H

#include <qmdisubwindow.h>
#include <qwidget.h>
#include <qtimer.h>
#include <qgridlayout.h>
#include <SDL.h>

class SDLChild : public QMdiSubWindow {
	Q_OBJECT
public:
	SDLChild(QWidget * parent);
	~SDLChild();

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