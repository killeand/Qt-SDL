#include "SDLChild.h"

SDLChild::SDLChild(QWidget * parent) : QMdiSubWindow(parent) {
	/*
		If you do not set an inner widget, the SubWindow itself IS
		a widget, so SDL renders over it... AND its controls. Not
		quite the desired behavior, unless you want to hide the
		controls until mouse over. But once the mouse is over, SDL
		writes over the controls again. Keep this in mind.
	*/
	setWidget(new QWidget);

	/*
	I used a timer for animation rendering.
	I tried using update() and repaint() as the slot, but this had
	no effect. I later tried calling update/repaint from within the
	Render() slot, and this caused a flicker. The only thing that I
	can assume is that after the paintEvent override, qt paints the
	grey backgrounds.
	*/
	Time = new QTimer(this);
	connect(Time, SIGNAL(timeout()), this, SLOT(Render()));
	Time->start(1000 / 60);

	RendererRef = 0;
	WindowRef = 0;
	position = 0;
	dir = 1;
}

SDLChild::~SDLChild() {
	SDL_DestroyRenderer(RendererRef);	// Basic SDL garbage collection
	SDL_DestroyWindow(WindowRef);

	delete Time;

	RendererRef = 0;
	WindowRef = 0;
	Time = 0;
}

void SDLChild::SDLInit() {
	/*
		In order to do rendering, I need to save the window and renderer contexts
		of this window.
		I use SDL_CreateWindowFrom and pass it the winId() of the widget I wish to
		render to. In this case, I want to render to a widget that I added.
	*/
	SetWindow(SDL_CreateWindowFrom((void *)widget()->winId()));
	SetRenderer(SDL_CreateRenderer(GetWindow(), -1, SDL_RENDERER_ACCELERATED));
}

void SDLChild::Render() {
	// Basic square bouncing animation
	SDL_Rect spos;
	spos.h = 100;
	spos.w = 100;
	spos.y = height() / 2 - 50;
	spos.x = position;

	SDL_SetRenderDrawColor(RendererRef, 0, 0, 0, 255);
	SDL_RenderFillRect(RendererRef, 0);
	SDL_SetRenderDrawColor(RendererRef, 0xFF, 0x0, 0x0, 0xFF);
	SDL_RenderFillRect(RendererRef, &spos);
	SDL_RenderPresent(RendererRef);
	
	if (position >= width() - 100)
		dir = 0;
	else if (position <= 0)
		dir = 1;

	if (dir)
		position += 5;
	else
		position -= 5;
}

void SDLChild::SetWindow(SDL_Window * ref) {
	WindowRef = ref;
}

void SDLChild::SetRenderer(SDL_Renderer * ref) {
	RendererRef = ref;
}

SDL_Window * SDLChild::GetWindow() {
	return WindowRef;
}

SDL_Renderer * SDLChild::GetRenderer() {
	return RendererRef;
}