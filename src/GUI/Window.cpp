//
// Window.cpp for Window.cpp in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Thu May 15 16:54:08 2014 LOEB Thomas
// Last update Sat Jun  7 15:11:08 2014 LOEB Thomas
//

#include	"GUI/Window.hh"

Window::Window(BomberGame *game) : _game(game), _x(1024), _y(768) {}

Window::~Window() {}

bool		Window::initialize() {
  if (!_context.start(_x, _y, "Bomberman | chauch_a, loeb_t, abgral_f, manzan_m, acca_b"))
    return (false);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  return (true);
}

bool		Window::update() {
  _context.updateClock(_clock);
  _context.updateInputs(_input);
  if (_input.getInput(SDL_QUIT))
    return (false);
  return (true);
}

bool		Window::update(gdl::Input &input) {
  _context.updateClock(_clock);
  _context.updateInputs(input);
  if (input.getInput(SDL_QUIT))
    return (false);
  return (true);
}

void		Window::draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void		Window::stop() {
  _context.stop();
}

void		Window::flush() {
  _context.flush();
}

GetGDL		const &Window::getContext() const {
  return (this->_context);
}

gdl::Clock	const &Window::getClock() const {
  return (this->_clock);
}

gdl::Input	Window::getInput() const {
  return (this->_input);
}

BomberGame	*Window::getGame() const {
  return (this->_game);
}

double		Window::getX() const {
  return (this->_x);
}

double		Window::getY() const {
  return (this->_y);
}
