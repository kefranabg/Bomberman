//
// MenuGUI.cpp for MenuGUI.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Mon May 26 17:25:09 2014 CHAUCHET Alan
// Last update Wed Jun  4 16:43:21 2014 abgral_f
//

#include			"GUI/MenuGUI.hh"
#include			"GUI/Sound.hh"
#include			"Menu/AListButton.hh"
#include			"Menu/TextBoxButton.hh"

MenuGUI::MenuGUI(Window *window) : AGUI(window) {}

MenuGUI::~MenuGUI() {}

bool				MenuGUI::initialize()
{
  glViewport(0, 0, _window->getX(), _window->getY());
  if (!_shader.load("LibBomberman_linux_x64/shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("LibBomberman_linux_x64/shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return (false);
  glm::mat4 projection;
  glm::mat4 transformation;
  projection = glm::perspective(40.0, _window->getX() / _window->getY(), 0.1, 100.0);
  transformation = glm::lookAt(glm::vec3(0, 0, 100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  _shader.bind();
  _shader.setUniform("view", transformation);
  _shader.setUniform("projection", projection);
  _menu.loadTextures();
  _menu.createMenu();
  _menu.initKeyList();
  return true;
}

void				MenuGUI::isTextBoxButton()
{
  if ((_menu.getButtonList()[_menu.getCursor()]->getType() == AButton::TextBox
       && static_cast<TextBoxButton *>(_menu.getButtonList()[_menu.getCursor()])->getCanBeModified() == true))
    {
      for (unsigned int i = 0 ; i != _menu.getKeyCodeList().size() ; i++)
	if (_input.getKey(_menu.getKeyCodeList()[i], true))
	  static_cast<TextBoxButton *>(_menu.getButtonList()[_menu.getCursor()])->changeText(*(_menu.getKeyStrList()[i]));
    }
  if (_menu.getButtonList()[_menu.getCursor()]->getType() == AButton::TextBox
      && static_cast<TextBoxButton *>(_menu.getButtonList()[_menu.getCursor()])->getOneCharac() == false)
    {
      for (unsigned int i = 1 ; i != 37 ; i++)
	if (_input.getKey(_menu.getKeyCodeList()[i], true))
	  static_cast<TextBoxButton *>(_menu.getButtonList()[_menu.getCursor()])->changeText(*(_menu.getKeyStrList()[i]));
      if (_input.getKey(SDLK_BACKSPACE, true))
	static_cast<TextBoxButton *>(_menu.getButtonList()[_menu.getCursor()])->changeText("\b");
    }
  if (_menu.getButtonList()[_menu.getCursor()]->getType() == AButton::TextBox
      && static_cast<TextBoxButton *>(_menu.getButtonList()[_menu.getCursor()])->getOneCharac() == true
      && _input.getKey(SDLK_RETURN, true))
    static_cast<TextBoxButton *>(_menu.getButtonList()[_menu.getCursor()])->setCanBeModified(true);
}

void				MenuGUI::isArrowButton()
{
  static bool			releaseArrow;

  if ((_menu.getButtonList()[_menu.getCursor()]->getType() == AButton::Arrow
       || _menu.getButtonList()[_menu.getCursor()]->getType() == AButton::ArrowNb)
      && releaseArrow == true)
    {
      static_cast<AListButton *>(_menu.getButtonList()[_menu.getCursor()])->moovArrow(true, false);
      static_cast<AListButton *>(_menu.getButtonList()[_menu.getCursor()])->moovArrow(false, false);
      releaseArrow = false;
    }
  if ((_menu.getButtonList()[_menu.getCursor()]->getType() == AButton::Arrow
       || _menu.getButtonList()[_menu.getCursor()]->getType() == AButton::ArrowNb)
      && _input.getKey(SDLK_RIGHT, true))
    {
      Sound::playSound(SOUND_MENU);
      releaseArrow = true;
      static_cast<AListButton *>(_menu.getButtonList()[_menu.getCursor()])->moovArrow(false, true);
    }
  if ((_menu.getButtonList()[_menu.getCursor()]->getType() == AButton::Arrow
       || _menu.getButtonList()[_menu.getCursor()]->getType() == AButton::ArrowNb)
      && _input.getKey(SDLK_LEFT, true))
    {
      Sound::playSound(SOUND_MENU);
      releaseArrow = true;
      static_cast<AListButton *>(_menu.getButtonList()[_menu.getCursor()])->moovArrow(true, true);
    }
}

void				MenuGUI::moveCursor()
{
  if (_input.getKey(SDLK_UP, true))
    {
      Sound::playSound(SOUND_MENU);
      _menu.moveCursor(-(_menu.getMoveCursor()));
    }
  if (_input.getKey(SDLK_DOWN, true))
    {
      Sound::playSound(SOUND_MENU);
      _menu.moveCursor(_menu.getMoveCursor());
    }
  if (_input.getKey(SDLK_RIGHT, true)
      && (_menu.getButtonList()[_menu.getCursor()]->getType() == AButton::Normal
	  || _menu.getButtonList()[_menu.getCursor()]->getType() == AButton::TextBox))
    {
      Sound::playSound(SOUND_MENU);
      _menu.moveCursor(1);
    }
  if (_input.getKey(SDLK_LEFT, true)
      && (_menu.getButtonList()[_menu.getCursor()]->getType() == AButton::Normal
	  || _menu.getButtonList()[_menu.getCursor()]->getType() == AButton::TextBox))
    {
      Sound::playSound(SOUND_MENU);
      _menu.moveCursor(-1);
    }
}

bool				MenuGUI::updateScreen()
{
  if (_window->update(_input) == false || _input.getKey(SDLK_KP_ENTER)
      || _input.getKey(SDLK_SPACE))
    return false;
  return true;
}

bool				MenuGUI::update()
{
  if (_window->update(_input) == false || _input.getKey(SDLK_ESCAPE))
    _menu.quitGame();
  if (_menu.getButtonList()[_menu.getCursor()]->getType() == AButton::Normal
      && _input.getKey(SDLK_RETURN, true))
    _menu.doAction();
  isTextBoxButton();
  isArrowButton();
  moveCursor();
  return true;
}

void				MenuGUI::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  glm::mat4 transform(1);
  glm::vec3 _scale(1, 1, 1);
  glm::vec3 _position(0, 0, 0);
  transform = glm::translate(transform, _position);
  transform = glm::scale(transform, _scale);
  _menu.drawMenu(_shader, transform, GL_QUADS);
  _window->flush();
}

Menu				&MenuGUI::getMenu()
{
  return (this->_menu);
}
