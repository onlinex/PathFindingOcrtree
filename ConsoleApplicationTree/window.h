#pragma once

#include <string>
#include <SDL.h>

struct mouse {
	int x;
	int y;
};

class window {
public:
	window(const std::string &title, int width, int height);
	~window();

	std::string pollEvents();
	void DrawPoint(int x, int y, int size, int param);
	void DrawPathPoint(int x, int y, int param, int z);
	void present();
	void clear() const;

	inline bool isClosed() const { return _closed; }

	mouse mouse;

private:
	bool init();

private:
	std::string _title;
	int _width = 800;
	int _height = 600;

	bool _closed = false;

	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
};