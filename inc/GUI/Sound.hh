//
// Sound.hh for Sound.hh in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Tue May 27 10:00:31 2014 CHAUCHET Alan
// Last update Mon Jun  2 17:52:42 2014 CHAUCHET Alan
//

#ifndef				SOUND_HH_
# define			SOUND_HH_

# include			<iostream>
# include			<vector>
# include			<fmodex/fmod.h>

class				Channel
{
  bool				_isSet;
  FMOD_SOUND			*_sound;
  FMOD_SYSTEM			**_system;

public:
  Channel(FMOD_SYSTEM **);
  void				load(const std::string &);
  void				close(void);
  void				play(void);
};

class				Music
{
  bool				_isSet;
  FMOD_SOUND			*_music;
  FMOD_SYSTEM			**_system;

public:
  Music(FMOD_SYSTEM **);
  void				load(const std::string &);
  void				close(void);
  void				play(int);
};

# define			NB_CHANNELS	32

# define			NB_MUSICS	4
# define			DIR_MUSICS	".Music/"

typedef	enum			e_musicType
  {
    MUSIC_MENU			= 0,
    MUSIC_GAME			= 1,
    MUSIC_WIN			= 2,
    MUSIC_LOSE			= 3
  }				e_musicType;

# define			NB_SOUNDS	8
# define			DIR_SOUNDS	".Sound/"

typedef enum			e_soundType
  {
    SOUND_MENU			= 0,
    SOUND_MOVE			= 1,
    SOUND_PUT_BOMB		= 2,
    SOUND_EXPLOSE		= 3,
    SOUND_BONUS			= 4,
    SOUND_PAUSE			= 5,
    SOUND_DIE			= 6,
    SOUND_ERROR			= 7
  }				e_soundType;

class				Sound
{
  static bool			_isOk;
  static std::vector<Music*>	_musics;
  static std::vector<Channel*>	_channels;
  static FMOD_SYSTEM		*_systemSound;
  static FMOD_SYSTEM		*_systemMusic;

public:
  static void			initialize(void);
  static void			close(void);
  static void			setVolumeMusic(int);
  static void			setVolumeSound(int);
  static void			pauseSound(void);
  static void			pauseMusic(void);
  static void			unpauseSound(void);
  static void			unpauseMusic(void);
  static void			addMusic(const std::string &, e_musicType);
  static void			addSound(const std::string &, e_soundType);
  static void			playMusic(e_musicType, int loop);
  static void			playSound(e_soundType);
  static void			stop(void);
};

#endif
