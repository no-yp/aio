#include "Window.h"
#include <iostream>

Window::Window() : m_window(nullptr), m_width(0), m_height(0) {}

Window::~Window() {Shutdown();}

bool Window::Initialize(const std::string& title, int width, int height) {
	m_width = width;
	m_height = height;

  m_window = SDL_CreateWindow(
    title.c_str(),
    width, height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

  if (!m_window) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
  	return false;
  }
	return true;
}


void Window::Shutdown() {
  if (m_window) {
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
  }
}
