#include "stdafx.h"
#include "window.h"
#include <iostream>
#include <string>


window::window(const std::string &title, int width, int height):
	_title(title), _width(width), _height(height)
{
	_closed = !init();
}

window::~window() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

bool window::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Failed to initialize SDL \n";
		return 0;
	}
	_window = SDL_CreateWindow(
		_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_width, _height,
		0
	);

	if (_window == nullptr) {
		std::cerr << "Failed to create window \n";
		return 0;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr) {
		std::cerr << "Failed to renderer SDL \n";
		return 0;
	}

	return true;
}

std::string window::pollEvents() {
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			_closed = true;
			return "";
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_a:
				return "a";
				break;
			case SDLK_d:
				return "d";
				break;
			case SDLK_s:
				return "s";
				break;
			case SDLK_f:
				return "f";
				break;
			}

		case SDL_MOUSEMOTION:
			//std::cout << event.motion.x << " , " << event.motion.y << "\n";
			mouse.x = event.motion.x;
			mouse.y = event.motion.y;
			break;

		default:
			break;
		}
	}
	return "";
}

void window::clear() const {
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderClear(_renderer);
}

void window::DrawPoint(int x, int y, int size, int param) {
	/*
	SDL_Rect point;
	point.w = 2;
	point.h = 2;
	point.x = x;
	point.y = y;
	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(_renderer, &point); */
	int red = 0;
	int green = 0;
	int blue = 0;
	if (param == 0) {
		green = 255;
	}
	else {
		red = (int)(255/param);
	}

	SDL_Rect line_v;
	line_v.w = 1;
	line_v.h = size*2;
	line_v.x = x;
	line_v.y = 1024 - y - line_v.h/2;
	SDL_SetRenderDrawColor(_renderer, red, green, blue, 255);
	SDL_RenderFillRect(_renderer, &line_v);

	SDL_Rect line_h;
	line_h.w = size*2;
	line_h.h = 1;
	line_h.x = x - line_h.w / 2;
	line_h.y = 1024 - y;
	SDL_SetRenderDrawColor(_renderer, red, green, blue, 255);
	SDL_RenderFillRect(_renderer, &line_h);
}

void window::DrawPathPoint(int x, int y, int param, int z) {
	int red = 0;
	int green = 0;
	int blue = 0;

	if (param == 0) {
		blue = 255;
	}
	else if (param == 1) {
		red = 255;
		blue = 102;
	}
	else if (param == 2) {
	}
	else if (param == 3) {
		red = 252;
		green = 150;
	}

	SDL_Rect PathPoint;
	PathPoint.w = 5;
	PathPoint.h = 5;
	PathPoint.x = x - 2;//PathPoint.w / 2;
	PathPoint.y = 1024 - y - 2;//PathPoint.h / 2;
	SDL_SetRenderDrawColor(_renderer, red, green, blue, 255);
	SDL_RenderFillRect(_renderer, &PathPoint);
}

void window::present() {
	SDL_RenderPresent(_renderer);
}