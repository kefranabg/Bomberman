//
// Sound.cpp for Sound.cpp in /home/chauch_a/rendu/cpp_bomberman
//
// Made by CHAUCHET Alan
// Login   <chauch_a@epitech.net>
//
// Started on  Tue May 27 10:03:31 2014 CHAUCHET Alan
// Last update Sat Jun  7 16:13:55 2014 CHAUCHET Alan
//

#include		"GUI/Sound.hh"

Channel::Channel(FMOD_SYSTEM **system)
{
  this->_isSet = false;
  this->_sound = NULL;
  this->_system = system;
}

void			Channel::load(const std::string &soundName)
{
  if (this->_isSet)
    this->close();
  if (FMOD_System_CreateSound(*(this->_system), (".Sound/" + soundName).c_str(), FMOD_CREATESAMPLE, 0, &(this->_sound)) == FMOD_OK)
    this->_isSet = true;
  else
    this->_isSet = false;
}

void			Channel::close(void)
{
  if (this->_isSet == false || this->_sound == NULL)
    return ;
  FMOD_Sound_Release(this->_sound);
}

void			Channel::play(void)
{
  if (this->_isSet == false || this->_sound == NULL)
    return ;
  FMOD_System_PlaySound(*(this->_system), FMOD_CHANNEL_FREE, this->_sound, 0, NULL);
}

Music::Music(FMOD_SYSTEM **system)
{
  this->_isSet = false;
  this->_music = NULL;
  this->_system = system;
}

void			Music::load(const std::string &musicName)
{
  if (this->_isSet)
    this->close();
  if (FMOD_System_CreateSound(*(this->_system), (".Music/" + musicName).c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &(this->_music)) == FMOD_OK)
    this->_isSet = true;
  else
    this->_isSet = false;
}

void			Music::close(void)
{
  if (this->_isSet == false || this->_music == NULL)
    return ;
  FMOD_Sound_Release(this->_music);
}

void			Music::play(int loop)
{
  if (this->_isSet == false || this->_music == NULL)
    return ;

  FMOD_CHANNEL		*channel;

  FMOD_System_GetChannel(*(this->_system), 0, &channel);
  FMOD_Sound_SetLoopCount(this->_music, loop);
  FMOD_System_PlaySound(*(this->_system), FMOD_CHANNEL_FREE, this->_music, 0, &channel);
}

bool			Sound::_isOk;
std::vector<Music*>	Sound::_musics;
std::vector<Channel*>	Sound::_channels;
FMOD_SYSTEM		*Sound::_systemSound;
FMOD_SYSTEM		*Sound::_systemMusic;

void			Sound::initialize(void)
{
  Sound::_isOk = true;
  FMOD_System_Create(&(Sound::_systemSound));
  FMOD_System_Init(Sound::_systemSound, NB_CHANNELS, FMOD_INIT_NORMAL, NULL);
  FMOD_System_Create(&(Sound::_systemMusic));
  FMOD_System_Init(Sound::_systemMusic, NB_CHANNELS, FMOD_INIT_NORMAL, NULL);
  Sound::_musics.resize(NB_MUSICS);
  Sound::_channels.resize(NB_SOUNDS);
  for (unsigned int count = 0; count < NB_MUSICS; ++count)
    Sound::_musics[count] = new Music(&(Sound::_systemMusic));
  for (unsigned int count = 0; count < NB_SOUNDS; ++count)
    Sound::_channels[count] = new Channel(&(Sound::_systemSound));
}

void			Sound::close(void)
{
  if (!Sound::_isOk)
    return ;
  for (unsigned int count = 0; count < NB_MUSICS; ++count)
    if (Sound::_musics[count])
      {
  	Sound::_musics[count]->close();
  	delete(Sound::_musics[count]);
      }
  for (unsigned int count = 0; count < NB_SOUNDS; ++count)
    if (Sound::_channels[count])
      {
  	Sound::_channels[count]->close();
  	delete(Sound::_channels[count]);
      }
  Sound::_musics.clear();
  Sound::_channels.clear();
  FMOD_System_Close(Sound::_systemSound);
  FMOD_System_Release(Sound::_systemSound);
  FMOD_System_Close(Sound::_systemMusic);
  FMOD_System_Release(Sound::_systemMusic);
}

void			Sound::setVolumeMusic(int percent)
{
  if (!Sound::_isOk)
    return ;

  FMOD_CHANNELGROUP	*group;

  FMOD_System_GetMasterChannelGroup(Sound::_systemMusic, &group);
  FMOD_ChannelGroup_SetVolume(group, static_cast<float>(percent) / 100.0);
}

void			Sound::setVolumeSound(int percent)
{
  if (!Sound::_isOk)
    return ;

  FMOD_CHANNELGROUP	*group;

  FMOD_System_GetMasterChannelGroup(Sound::_systemSound, &group);
  FMOD_ChannelGroup_SetVolume(group, static_cast<float>(percent) / 100.0);
}

void			Sound::pauseMusic(void)
{
  if (!Sound::_isOk)
    return ;

  FMOD_CHANNELGROUP	*group;
  FMOD_BOOL		state;

  FMOD_System_GetMasterChannelGroup(Sound::_systemMusic, &group);
  FMOD_ChannelGroup_GetPaused(group, &state);
  if (state)
    return ;
  FMOD_ChannelGroup_SetPaused(group, 1);
}

void			Sound::pauseSound(void)
{
  if (!Sound::_isOk)
    return ;

  FMOD_CHANNELGROUP	*group;
  FMOD_BOOL		state;

  FMOD_System_GetMasterChannelGroup(Sound::_systemSound, &group);
  FMOD_ChannelGroup_GetPaused(group, &state);
  if (state)
    return ;
  FMOD_ChannelGroup_SetPaused(group, 1);
}

void			Sound::unpauseMusic(void)
{
  if (!Sound::_isOk)
    return ;

  FMOD_CHANNELGROUP	*group;
  FMOD_BOOL		state;

  FMOD_System_GetMasterChannelGroup(Sound::_systemMusic, &group);
  FMOD_ChannelGroup_GetPaused(group, &state);
  if (!state)
    return ;
  FMOD_ChannelGroup_SetPaused(group, 0);
}

void			Sound::unpauseSound(void)
{
  if (!Sound::_isOk)
    return ;

  FMOD_CHANNELGROUP	*group;
  FMOD_BOOL		state;

  FMOD_System_GetMasterChannelGroup(Sound::_systemSound, &group);
  FMOD_ChannelGroup_GetPaused(group, &state);
  if (!state)
    return ;
  FMOD_ChannelGroup_SetPaused(group, 0);
}

void			Sound::addMusic(const std::string &musicName, e_musicType pos)
{
  if (!Sound::_isOk)
    return ;
  if (Sound::_musics[pos])
    Sound::_musics[pos]->close();
  else
    Sound::_musics[pos] = new Music(&(Sound::_systemMusic));
  Sound::_musics[pos]->load(musicName);
}

void			Sound::addSound(const std::string &soundName, e_soundType pos)
{
  if (!Sound::_isOk)
    return ;
  if (Sound::_channels[pos])
    Sound::_channels[pos]->close();
  else
    Sound::_channels[pos] = new Channel(&(Sound::_systemSound));
  Sound::_channels[pos]->load(soundName);
}

void			Sound::playMusic(e_musicType pos, int loop)
{
  if (!Sound::_isOk || ! Sound::_musics[pos])
    return ;
  Sound::_musics[pos]->play(loop);
}

void			Sound::playSound(e_soundType pos)
{
  if (!Sound::_isOk)
    return ;
  if (Sound::_channels[pos])
    Sound::_channels[pos]->play();
}

void			Sound::stop(void)
{
  FMOD_CHANNELGROUP	*group;

  FMOD_System_GetMasterChannelGroup(Sound::_systemMusic, &group);
  FMOD_ChannelGroup_Stop(group);
  FMOD_System_GetMasterChannelGroup(Sound::_systemSound, &group);
  FMOD_ChannelGroup_Stop(group);
}
