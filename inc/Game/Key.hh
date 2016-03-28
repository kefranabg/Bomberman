//
// Key.hh for Key.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Mon May 12 12:14:16 2014 CHAUCHET Alan
// Last update Wed May 14 12:35:12 2014 CHAUCHET Alan
//

#ifndef			KEY_HH_
# define		KEY_HH_

# include		<iostream>
# include		<vector>

typedef enum		e_keyType
  {
    KEY_UP		= 0,
    KEY_DOWN		= 1,
    KEY_LEFT		= 2,
    KEY_RIGHT		= 3,
    KEY_BOMB		= 4,
    KEY_PAUSE		= 5,
    BAD_KEY		= 6
  }			e_keyType;

class			Key
{
public:
  static int		_keyPlayer1[6];
  static int		_keyPlayer2[6];

  static void		initBasicKey(void);
  static e_keyType	getKeyPlayer1(int);
  static e_keyType	getKeyPlayer2(int);
  static int		getKeyPlayer1(e_keyType);
  static int		getKeyPlayer2(e_keyType);
  static void		setKeyPlayer1(e_keyType, int);
  static void		setKeyPlayer2(e_keyType, int);
  static void		parseKeyFile(const std::string &fileName = ".KeyConf");
  static void		writeKeyFile(const std::string &fileName = ".KeyConf");
};

#endif
