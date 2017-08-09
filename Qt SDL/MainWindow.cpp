#include "MainWindow.h"

MainWindow::MainWindow() : MainWindowWidget(new QWidget) {
	setWindowTitle("QMainWindow SDL Rendering Example");
	setCentralWidget(MainWindowWidget);	// Basic setup, ensuring that the window has a widget
	setBaseSize(640, 480);				// inside of it that we can render to
	resize(640, 480);

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

MainWindow::~MainWindow() {
	SDL_DestroyRenderer(RendererRef);	// Basic SDL garbage collection
	SDL_DestroyWindow(WindowRef);

	delete Time;

	RendererRef = 0;
	WindowRef = 0;
	Time = 0;
}

void MainWindow::SDLInit() {
	/*
		In order to do rendering, I need to save the window and renderer contexts
		of this window.
		I use SDL_CreateWindowFrom and pass it the winId() of the widget I wish to
		render to. In this case, I want to render to the main central widget.
	*/
	SetWindow(SDL_CreateWindowFrom((void *)centralWidget()->winId()));
	SetRenderer(SDL_CreateRenderer(GetWindow(), -1, SDL_RENDERER_ACCELERATED));
}

void MainWindow::Render() {
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

void MainWindow::SetWindow(SDL_Window * ref) {
	WindowRef = ref;
}

void MainWindow::SetRenderer(SDL_Renderer * ref) {
	RendererRef = ref;
}

SDL_Window * MainWindow::GetWindow() {
	return WindowRef;
}

SDL_Renderer * MainWindow::GetRenderer() {
	return RendererRef;
}