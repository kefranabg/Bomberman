//
// Key.cpp for Key.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Mon May 12 12:20:29 2014 CHAUCHET Alan
// Last update Thu May 15 18:30:18 2014 CHAUCHET Alan
//

#include		<SdlContext.hh>
#include		"Game/Key.hh"
#include		"Game/LexerKey.hh"
#include		"Game/ParserKey.hh"

int			Key::_keyPlayer1[6];
int			Key::_keyPlayer2[6];

void			Key::initBasicKey(void)
{
  _keyPlayer1[KEY_UP] = SDLK_UP;
  _keyPlayer1[KEY_DOWN] = SDLK_DOWN;
  _keyPlayer1[KEY_LEFT] = SDLK_LEFT;
  _keyPlayer1[KEY_RIGHT] = SDLK_RIGHT;
  _keyPlayer1[KEY_BOMB] = SDLK_SPACE;
  _keyPlayer1[KEY_PAUSE] = SDLK_DELETE;

  _keyPlayer2[KEY_UP] = SDLK_z;
  _keyPlayer2[KEY_DOWN] = SDLK_s;
  _keyPlayer2[KEY_LEFT] = SDLK_q;
  _keyPlayer2[KEY_RIGHT] = SDLK_d;
  _keyPlayer2[KEY_BOMB] = SDLK_e;
  _keyPlayer2[KEY_PAUSE] = SDLK_ESCAPE;
}

e_keyType		Key::getKeyPlayer1(int key)
{
  for (unsigned int count = 0; count < 6; count++)
    if (_keyPlayer1[count] == key)
      return (static_cast<e_keyType>(count));
  return (BAD_KEY);
}

e_keyType		Key::getKeyPlayer2(int key)
{
  for (unsigned int count = 0; count < 6; count++)
    if (_keyPlayer2[count] == key)
      return (static_cast<e_keyType>(count));
  return (BAD_KEY);
}

int			Key::getKeyPlayer1(e_keyType type)
{
  if (type == BAD_KEY)
    return (-1);
  return (_keyPlayer1[static_cast<int>(type)]);
}

int			Key::getKeyPlayer2(e_keyType type)
{
  if (type == BAD_KEY)
    return (-1);
  return (_keyPlayer2[static_cast<int>(type)]);
}

void			Key::setKeyPlayer1(e_keyType posKey, int key)
{
  if (posKey == BAD_KEY)
    return ;
  for (unsigned int count = 0; count < 6; count++)
    if (_keyPlayer1[count] == key || _keyPlayer2[count] == key)
      return ;
  _keyPlayer1[static_cast<int>(posKey)] = key;
}

void			Key::setKeyPlayer2(e_keyType posKey, int key)
{
  if (posKey == BAD_KEY)
    return ;
  for (unsigned int count = 0; count < 6; count++)
    if (_keyPlayer1[count] == key || _keyPlayer2[count] == key)
      return ;
  _keyPlayer2[static_cast<int>(posKey)] = key;
}

void			Key::parseKeyFile(const std::string &fileName)
{
  LexerKey		lexer;

  lexer.checkFile(fileName);

  ParserKey		parser(lexer.getLines());

  parser.parseFile();
}

void			Key::writeKeyFile(const std::string &fileName)
{
  std::vector<std::string>	param;

  ParserKey		parser(param);

  parser.writeInFile(fileName);
}
