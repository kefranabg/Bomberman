//
// MapGUI.cpp for MapGUI.cpp in /home/loeb_t/rendu/cpp_bomberman
//
// Made by LOEB Thomas
// Login   <loeb_t@epitech.net>
//
// Started on  Tue May 20 12:09:12 2014 LOEB Thomas
// Last update Fri Jun 13 18:19:07 2014 LOEB Thomas
//

#include	"FunctionString.hpp"
#include	"Game/Player.hh"
#include	"Game/Key.hh"
#include	"GUI/MapGUI.hh"

MapGUI::MapGUI(Window *window) : AGUI(window), _map(NULL) {
  _score[0] = 0;
  _score[1] = 0;
  _scoreGUI[0] = NULL;
  _scoreGUI[1] = NULL;
  _bombs[0] = 0;
  _bombs[1] = 0;
  _bombsGUI[0] = NULL;
  _bombsGUI[1] = NULL;
  _bombInput[0] = false;
  _bombInput[1] = false;
  _startInput[0] = false;
  _startInput[1] = false;
  _draw = false;
  _forceDraw = 0;
}

MapGUI::~MapGUI() {
  reset();
}

void		MapGUI::reset()
{
  glDisable(GL_DEPTH_TEST);
  for (unsigned int i = 0; i < _objects.size(); ++i)
    if (_objects[i].empty() == false)
      for (unsigned int j = 0; j < _objects[i].size(); ++j)
	delete (_objects[i][j]);
  _objects.clear();
  for (unsigned int i = 0; i < _players.size(); ++i) {
    if (_players[i] != NULL)
      delete (_players[i]);
    delete (_texts[i]);
  }
  _players.clear();
  _texts.clear();

  if (_map != NULL)
    delete (_map);
  _map = NULL;
  if (_scoreGUI[0] != NULL)
    delete (_scoreGUI[0]);
  _scoreGUI[0] = NULL;
  if (_scoreGUI[1] != NULL)
    delete (_scoreGUI[1]);
  _scoreGUI[1] = NULL;
  if (_bombsGUI[0] != NULL)
    delete (_bombsGUI[0]);
  _bombsGUI[0] = NULL;
  if (_bombsGUI[1] != NULL)
    delete (_bombsGUI[1]);

  _bombsGUI[1] = NULL;
  _score[0] = 0;
  _score[1] = 0;
  _bombs[0] = 0;
  _bombs[1] = 0;
}

void		MapGUI::initObjects(int i)
{
  std::vector<e_typeObj> objects;
  double posy = i / _map->getSizeX();
  bool floor = false;
  bool wall = false;

  objects = _map->getObj(i % _map->getSizeX(), i / _map->getSizeX());
  if (!objects.empty())
    {
      for (unsigned int j = 0; j < objects.size(); ++j)
	if (objects[j] == WALL_I)
	  {
	    _objects[i].push_back(new WallIGUI());
	    _objects[i].back()->initialize(glm::vec3(_middleX - i % _map->getSizeX(), 0, -posy));
	    wall = true;
	  }

	else if (objects[j] == WALL_D)
	  {
	    _objects[i].push_back(new WallDGUI());
	    _objects[i].back()->initialize(glm::vec3(_middleX - i % _map->getSizeX(), 0, -posy));
	    wall = true;
	  }

	else if (objects[j] == BOMB)
	  {
	    if (floor == false)
	      {
		_objects[i].push_back(new FloorGUI());
		_objects[i].back()->initialize(glm::vec3(_middleX - i % _map->getSizeX(), 0, -posy));
		floor = true;
	      }
	    _objects[i].push_back(new BombGUI(_window->getGame()->getAnim()));
	    _objects[i].back()->initialize(glm::vec3(_middleX - i % _map->getSizeX(), -0.2, -posy));
	  }

	else if (objects[j] == FIRE)
	  {
	    if (floor == false)
	      {
		_objects[i].push_back(new FloorGUI());
		_objects[i].back()->initialize(glm::vec3(_middleX - i % _map->getSizeX(), 0, -posy));
		floor = true;
	      }
	    _objects[i].push_back(new FireGUI(_window->getGame()->getAnim()));
	    _objects[i].back()->initialize(glm::vec3(_middleX - i % _map->getSizeX(), -0.2, -posy));
	  }

	else if (wall == false) {
	  if (objects[j] == BONUS_NEW_BOMB)
	    {
	      if (floor == false)
		{
		  _objects[i].push_back(new FloorGUI());
		  _objects[i].back()->initialize(glm::vec3(_middleX - i % _map->getSizeX(), 0, -posy));
		  floor = true;
		}
	      _objects[i].push_back(new BonusGUI("bonus_bomb.FBX", _window->getGame()->getAnim()));
	      _objects[i].back()->initialize(glm::vec3(_middleX - i % _map->getSizeX(), 0, -posy));
	    }

	  else if (objects[j] == BONUS_ADD_RANGE)
	    {
	      if (floor == false)
		{
		  _objects[i].push_back(new FloorGUI());
		  _objects[i].back()->initialize(glm::vec3(_middleX - i % _map->getSizeX(), 0, -posy));
		  floor = true;
		}
	      _objects[i].push_back(new BonusGUI("bonus_flame.FBX", _window->getGame()->getAnim()));
	      _objects[i].back()->initialize(glm::vec3(_middleX - i % _map->getSizeX(), 0, -posy));
	    }

	  else if (objects[j] == BONUS_SPEED_UP)
	    {
	      if (floor == false)
		{
		  _objects[i].push_back(new FloorGUI());
		  _objects[i].back()->initialize(glm::vec3(_middleX - i % _map->getSizeX(), 0, -posy));
		  floor = true;
		}
	      _objects[i].push_back(new BonusGUI("bonus_speed.FBX", _window->getGame()->getAnim()));
	      _objects[i].back()->initialize(glm::vec3(_middleX - i % _map->getSizeX(), 0, -posy));
	    }
	}
    }

  else
    {
      _objects[i].push_back(new FloorGUI());
      _objects[i].back()->initialize(glm::vec3(_middleX - i % _map->getSizeX(), 0, -posy));
    }
}

bool		MapGUI::initialize() {

  // VARIABLES

  _isPlayer2 = _window->getGame()->getIsPlayer2();
  _posCamX = 5;
  _negCamX = -5;
  _posCamY = 3;
  _negCamY = -4.5;
  _x = _window->getX();
  _y = _window->getY();
  if (_isPlayer2) {
    _posCamX = 3;
    _negCamX = -3;
    _x /= 2;
  }

  // INIT SHADER + CAMERA + DEPTH_TEST

  if (!_shader.load("LibBomberman_linux_x64/shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("LibBomberman_linux_x64/shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build()
      || !_letters.load("texture/Alphabet.tga"))
    return (false);
  glEnable(GL_DEPTH_TEST);

  glm::mat4 projection = static_cast<glm::mat4>(glm::perspective(60.0, _x / _y, 0.1, 100.0));
  _shader.bind();
  _shader.setUniform("projection", projection);

  // INIT MAP

  _map = new Map(*_window->getGame()->getMap());
  _middleX = static_cast<double>(_map->getSizeX()) / 2;
  _objects.resize(_map->getSizeX() * _map->getSizeY());
  for (unsigned int i = 0; i < _map->getSizeX() * _map->getSizeY(); ++i)
    initObjects(i);

  // INIT PLAYERS

  unsigned int noIA = 0;
  _player1 = NULL;
  _player2 = NULL;
  std::vector<APlayer *> players = *_window->getGame()->getPlayersAccess();

  for (unsigned int i = 0; i < players.size(); ++i) {
    glm::vec3 posPlayer(_middleX - players[i]->getPosX(), -0.5, -players[i]->getPosY());

    if (players[i]->getType() == PLAYER1) {
      _players.push_back(new PlayerGUI());
      _players.back()->initialize(posPlayer);

      _texts.push_back(new TextGUI());
      _texts.back()->initialize(posPlayer + glm::vec3(0, 1, 0), static_cast<Player *>(players[i])->getName());
      _player1 = _players.back();

      _score[0] = players[i]->getScore();
      if (_scoreGUI[0])
	delete (_scoreGUI[0]);
      _scoreGUI[0] = new TextGUI();
      _scoreGUI[0]->initialize(posPlayer + glm::vec3(0, 1.15, 0), std::string("score " + FunctionString::varToString<unsigned int>(_score[0])));

      _bombs[0] = players[i]->getNbBombsAvailable();
      if (_bombsGUI[0])
	delete (_bombsGUI[0]);
      _bombsGUI[0] = new TextGUI();
      _bombsGUI[0]->initialize(posPlayer + glm::vec3(0, 1.3, 0), std::string("bombs x" + FunctionString::varToString<unsigned int>(_bombs[0])));

    } else if (players[i]->getType() == PLAYER2) {
      _players.push_back(new PlayerGUI());
      _players.back()->initialize(posPlayer);

      _texts.push_back(new TextGUI());
      _texts.back()->initialize(posPlayer + glm::vec3(0, 1, 0), static_cast<Player *>(players[i])->getName());
      _player2 = _players.back();

      _score[1] = players[i]->getScore();
      if (_scoreGUI[1])
	delete (_scoreGUI[1]);
      _scoreGUI[1] = new TextGUI();
      _scoreGUI[1]->initialize(posPlayer + glm::vec3(0, 1.15, 0), std::string("score " + FunctionString::varToString<unsigned int>(_score[1])));

      _bombs[1] = players[i]->getNbBombsAvailable();
      if (_bombsGUI[1])
	delete (_bombsGUI[1]);
      _bombsGUI[1] = new TextGUI();
      _bombsGUI[1]->initialize(posPlayer + glm::vec3(0, 1.3, 0), std::string("bombs x" + FunctionString::varToString<unsigned int>(_bombs[1])));

    } else {
      _players.push_back(new EnnemyGUI());
      _players.back()->initialize(posPlayer);

      _texts.push_back(new TextGUI());
      _texts.back()->initialize(posPlayer + glm::vec3(0, 1, 0), std::string("ia" + FunctionString::varToString<unsigned int>(++noIA)));
    }
  }

  return (true);
}

bool		MapGUI::update() {
  if (_window->update(_input) == false)
    return (false);

  _draw = false;
  if (_window->getGame()->isPaused() == false) {
    if (_forceDraw == 0) {
      _draw = false;
    } else {
      _draw = true;
      --_forceDraw;
    }

    // CHECKS DES PLAYERS (MOUVEMENTS + MORTS + ANIMATIONS + SCORES + NB BOMBS)

    std::vector<APlayer *> players = *_window->getGame()->getPlayersAccess();
    for (unsigned int i = 0; i < players.size(); ++i)
      if (_players[i] != NULL) {

	if (_players[i] == _player1) {
	  if (players[i]->getScore() != _score[0]) {
	    _score[0] = players[i]->getScore();
	    delete (_scoreGUI[0]);
	    _scoreGUI[0] = new TextGUI();
	    _scoreGUI[0]->initialize(_player1->getPosition() + glm::vec3(0, 1.15, 0), std::string("score " + FunctionString::varToString<unsigned int>(_score[0])));
	    _draw = true;
	  }

	  if (players[i]->getNbBombsAvailable() != _bombs[0]) {
	    _bombs[0] = players[i]->getNbBombsAvailable();
	    delete (_bombsGUI[0]);
	    _bombsGUI[0] = new TextGUI();
	    _bombsGUI[0]->initialize(_player1->getPosition() + glm::vec3(0, 1.3, 0), std::string("bombs x" + FunctionString::varToString<unsigned int>(_bombs[0])));
	    _draw = true;
	  }

	} else if (_players[i] == _player2) {
	  if (players[i]->getScore() != _score[1]) {
	    _score[1] = players[i]->getScore();
	    delete (_scoreGUI[1]);
	    _scoreGUI[1] = new TextGUI();
	    _scoreGUI[1]->initialize(_player2->getPosition() + glm::vec3(0, 1.15, 0), std::string("score " + FunctionString::varToString<unsigned int>(_score[1])));
	    _draw = true;
	  }

	  if (players[i]->getNbBombsAvailable() != _bombs[1]) {
	    _bombs[1] = players[i]->getNbBombsAvailable();
	    delete (_bombsGUI[1]);
	    _bombsGUI[1] = new TextGUI();
	    _bombsGUI[1]->initialize(_player2->getPosition() + glm::vec3(0, 1.3, 0), std::string("bombs x" + FunctionString::varToString<unsigned int>(_bombs[1])));
	    _draw = true;
	  }
	}

	if (players[i]->isAlive() == false) {
	  if (_players[i] == _player1 || _players[i] == _player2) {

	    if (_players[i] == _player1)
	      _player1 = NULL;
	    else
	      _player2 = NULL;

	    _posCamX = 5;
	    _negCamX = -5;
	    _x *= 2;

	    glm::mat4 projection = static_cast<glm::mat4>(glm::perspective(60.0, _x / _y, 0.1, 100.0));
	    _shader.bind();
	    _shader.setUniform("projection", projection);
	  }

	  delete (_players[i]);
	  _players[i] = NULL;
	  _draw = true;

	} else if (_middleX - players[i]->getPosX() - _players[i]->getPosition().x > 0.01 ||
		   _middleX - players[i]->getPosX() - _players[i]->getPosition().x < -0.01 ||
		   -players[i]->getPosY() - _players[i]->getPosition().z > 0.01 ||
		   -players[i]->getPosY() - _players[i]->getPosition().z < -0.01) {
	  if (_window->getGame()->getAnim() == true)
	    {
	      if (_players[i]->getIdx() == -1)
		_players[i]->setCurrentAnim(0, false);
	      else if (_players[i]->getIdx() == 0)
		_players[i]->setCurrentAnim(1, true);
	    }

	  double transX = _middleX - players[i]->getPosX() - _players[i]->getPosition().x,
	    transY = -players[i]->getPosY() - _players[i]->getPosition().z;
	  double angle;

	  _players[i]->setRotation(glm::vec3(0, 0, 0));
	  if (transY > 0.01)
	    angle = 0;
	  else if (transY < -0.01)
	    angle = 180;
	  if (transX > 0.01)
	    angle = 90;
	  else if (transX < -0.01)
	    angle = -90;

	  if (_players[i] == _player1) {
	    _scoreGUI[0]->translate(glm::vec3(transX, 0, transY));
	    _bombsGUI[0]->translate(glm::vec3(transX, 0, transY));
	  } else if (_players[i] == _player2) {
	    _scoreGUI[1]->translate(glm::vec3(transX, 0, transY));
	    _bombsGUI[1]->translate(glm::vec3(transX, 0, transY));
	  }

	  _players[i]->translate(glm::vec3(transX, 0, transY));
	  _texts[i]->translate(glm::vec3(transX, 0, transY));
	  _players[i]->rotate(glm::vec3(0, 1, 0), angle);
	  _draw = true;

	} else if (_players[i]->getIdx() != -1) {
	  if (_window->getGame()->getAnim() == true)
	    _players[i]->setCurrentAnim(2, false);
	  _players[i]->setIdx(-1);
	  _forceDraw = 30;
	  _draw = true;
	}
      }

    // CHECKS DE LA MAP

    Map &mapGame = *_window->getGame()->getMap();
    if (!(mapGame == *_map)) {
      for (unsigned int i = 0; i < _map->getSizeX() * _map->getSizeY(); ++i)
	if (!((*_map)[i] == mapGame[i]))
	  {
	    (*_map)[i] = mapGame[i];
	    if (_objects[i].empty() == false)
	      {
		for (unsigned int j = 0; j < _objects[i].size(); ++j)
		  delete(_objects[i][j]);
		_objects[i].clear();
	      }
	    initObjects(i);
	  }
      _draw = true;
    }

    // CHECKS DES ALENTOURS DES JOUEURS (ANIMATIONS DES BOMBES, BONUS, ETC)

    if (_player1) {
      glm::vec3 player1 = _player1->getPosition();
      for (unsigned int i = 0; i < _objects.size() && _draw == false; ++i)
	if (_objects[i].empty() == false &&
	    player1.x - _objects[i].front()->getCoord().x <= _posCamX &&
	    player1.x - _objects[i].front()->getCoord().x >= _negCamX &&
	    player1.z - _objects[i].front()->getCoord().z <= _posCamY &&
	    player1.z - _objects[i].front()->getCoord().z >= _negCamY)
	  for (unsigned int j = 0; j < _objects[i].size(); ++j)
	    if (dynamic_cast<BombGUI *>(_objects[i][j]) != NULL ||
		dynamic_cast<FireGUI *>(_objects[i][j]) != NULL ||
		dynamic_cast<BonusGUI *>(_objects[i][j]) != NULL) {
	      _draw = true;
	    }
    }

    if (_isPlayer2 && _player2) {
      glm::vec3 player2 = _player2->getPosition();
      for (unsigned int i = 0; i < _objects.size() && _draw == false; ++i)
	if (_objects[i].empty() == false &&
	    player2.x - _objects[i].front()->getCoord().x <= _posCamX &&
	    player2.x - _objects[i].front()->getCoord().x >= _negCamX &&
	    player2.z - _objects[i].front()->getCoord().z <= _posCamY &&
	    player2.z - _objects[i].front()->getCoord().z >= _negCamY)
	  for (unsigned int j = 0; j < _objects[i].size(); ++j)
	    if (dynamic_cast<BombGUI *>(_objects[i][j]) != NULL ||
		dynamic_cast<FireGUI *>(_objects[i][j]) != NULL ||
		dynamic_cast<BonusGUI *>(_objects[i][j]) != NULL) {
	      _draw = true;
	    }
    }
  }

  // CHECKS DES TOUCHES

  for (unsigned int i = 0; i < 6; ++i) {
    if (_player1) {
      if (i < 4 && _input.getKey(Key::getKeyPlayer1(static_cast<e_keyType>(i)))) {
	_window->getGame()->addActionPlayer1(static_cast<e_action>(i));
      } else if (i == 4) {
	if (_input.getKey(Key::getKeyPlayer1(static_cast<e_keyType>(i))))
	  _bombInput[0] = true;
	else {
	  if (_bombInput[0] == true) {
	    _draw = true;
	    _window->getGame()->addActionPlayer1(static_cast<e_action>(i));
	  }
	  _bombInput[0] = false;
	}
      } else if (i == 5) {
	if (_input.getKey(Key::getKeyPlayer1(static_cast<e_keyType>(i))))
	  _startInput[0] = true;
	else if (_startInput[0] == true && _window->getGame()->isPaused() == false) {
	  _startInput[0] = false;
	  glDisable(GL_DEPTH_TEST);
	  _window->getGame()->pause();
	}
      }
    }

    if (_isPlayer2 && _player2) {
      if (i < 4 && _input.getKey(Key::getKeyPlayer2(static_cast<e_keyType>(i)))) {
	_window->getGame()->addActionPlayer2(static_cast<e_action>(i));
      } else if (i == 4) {
	if (_input.getKey(Key::getKeyPlayer2(static_cast<e_keyType>(i))))
	  _bombInput[1] = true;
	else {
	  if (_bombInput[1] == true) {
	    _draw = true;
	    _window->getGame()->addActionPlayer2(static_cast<e_action>(i));
	  }
	  _bombInput[1] = false;
	}
      } else if (i == 5) {
	if (_input.getKey(Key::getKeyPlayer2(static_cast<e_keyType>(i))))
	  _startInput[1] = true;
	else if (_startInput[1] == true && _window->getGame()->isPaused() == false) {
	  _startInput[1] = false;
	  glDisable(GL_DEPTH_TEST);
	  _window->getGame()->pause();
	}
      }
    }
  }

  if (_window->getGame()->isPaused() == false && _draw == true)
    draw();
  return (true);
}

void		MapGUI::draw() {
  _window->draw();

  glm::mat4 transformation;

  if (_player1) {
    glm::vec3 player1 = _player1->getPosition();
    glViewport(0, 0, _x, _y);

    transformation = glm::lookAt(glm::vec3(0, 4, -1.5) + player1, player1, glm::vec3(0, 1, 0));

    _shader.bind();
    _shader.setUniform("view", transformation);

    for (unsigned int i = 0; i < _objects.size(); ++i)
      if (_objects[i].empty() == false &&
	  player1.x - _objects[i].front()->getCoord().x <= _posCamX &&
	  player1.x - _objects[i].front()->getCoord().x >= _negCamX &&
	  player1.z - _objects[i].front()->getCoord().z <= _posCamY &&
	  player1.z - _objects[i].front()->getCoord().z >= _negCamY)
	for (unsigned int j = 0; j < _objects[i].size(); ++j)
	  _objects[i][j]->draw(_shader, _window->getClock());

    for (unsigned int i = 0; i < _players.size(); ++i)
      if (_players[i] != NULL &&
	  player1.x - _players[i]->getPosition().x <= _posCamX &&
	  player1.x - _players[i]->getPosition().x >= _negCamX &&
	  player1.z - _players[i]->getPosition().z <= _posCamY &&
	  player1.z - _players[i]->getPosition().z >= _negCamY)
	_players[i]->draw(_shader, _window->getClock());

    glDisable(GL_DEPTH_TEST);
    for (unsigned int i = 0; i < _players.size(); ++i)
      if (_players[i] != NULL &&
	  player1.x - _players[i]->getPosition().x <= _posCamX &&
	  player1.x - _players[i]->getPosition().x >= _negCamX &&
	  player1.z - _players[i]->getPosition().z <= _posCamY &&
	  player1.z - _players[i]->getPosition().z >= _negCamY)
	_texts[i]->draw(_shader, _letters);

    _scoreGUI[0]->draw(_shader, _letters);
    _bombsGUI[0]->draw(_shader, _letters);
    if (_player2 &&
	player1.x - _player2->getPosition().x <= _posCamX &&
	player1.x - _player2->getPosition().x >= _negCamX &&
	player1.z - _player2->getPosition().z <= _posCamY &&
	player1.z - _player2->getPosition().z >= _negCamY) {
      _scoreGUI[1]->draw(_shader, _letters);
      _bombsGUI[1]->draw(_shader, _letters);
    }
    glEnable(GL_DEPTH_TEST);
  }

  if (_isPlayer2 && _player2) {
    glm::vec3 player2 = _player2->getPosition();
    if (_player1)
      glViewport(_x, 0, _x, _y);
    else
      glViewport(0, 0, _x, _y);

    transformation = glm::lookAt(glm::vec3(0, 4, -1.5) + player2, player2, glm::vec3(0, 1, 0));
    _shader.bind();
    _shader.setUniform("view", transformation);

    for (unsigned int i = 0; i < _objects.size(); ++i)
      if (_objects[i].empty() == false &&
	  player2.x - _objects[i].front()->getCoord().x <= _posCamX &&
	  player2.x - _objects[i].front()->getCoord().x >= _negCamX &&
	  player2.z - _objects[i].front()->getCoord().z <= _posCamY &&
	  player2.z - _objects[i].front()->getCoord().z >= _negCamY)
	for (unsigned int j = 0; j < _objects[i].size(); ++j)
	  _objects[i][j]->draw(_shader, _window->getClock());

    for (unsigned int i = 0; i < _players.size(); ++i)
      if (_players[i] != NULL &&
	  player2.x - _players[i]->getPosition().x <= _posCamX &&
	  player2.x - _players[i]->getPosition().x >= _negCamX &&
	  player2.z - _players[i]->getPosition().z <= _posCamY &&
	  player2.z - _players[i]->getPosition().z >= _negCamY)
	_players[i]->draw(_shader, _window->getClock());

    glDisable(GL_DEPTH_TEST);
    for (unsigned int i = 0; i < _players.size(); ++i)
      if (_players[i] != NULL &&
	  player2.x - _players[i]->getPosition().x <= _posCamX &&
	  player2.x - _players[i]->getPosition().x >= _negCamX &&
	  player2.z - _players[i]->getPosition().z <= _posCamY &&
	  player2.z - _players[i]->getPosition().z >= _negCamY)
	_texts[i]->draw(_shader, _letters);

    _scoreGUI[1]->draw(_shader, _letters);
    _bombsGUI[1]->draw(_shader, _letters);
    if (_player1 &&
	player2.x - _player1->getPosition().x <= _posCamX &&
        player2.x - _player1->getPosition().x >= _negCamX &&
        player2.z - _player1->getPosition().z <= _posCamY &&
        player2.z - _player1->getPosition().z >= _negCamY) {
      _scoreGUI[0]->draw(_shader, _letters);
      _bombsGUI[0]->draw(_shader, _letters);
    }
    glEnable(GL_DEPTH_TEST);
  }

  _window->flush();
}
