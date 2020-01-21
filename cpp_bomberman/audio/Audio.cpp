//
// Audio.cpp for bomberman in /home/larue_a/Desktop/SOUND
// 
// Made by larue_a
// Login   <larue_a@epitech.net>
// 
// Started on  Wed Jun 11 14:38:03 2014 larue_a
// Last update Sun Jun 15 18:58:22 2014 liron_b
//

#include	"Audio.hh"
#include	<unistd.h>

Audio::Audio()
{}

/* Destructor chargé de free et close le travail avec FMOD */
Audio::~Audio()
{
  this->_freeEverything();
  this->close();
}

/* Fonction à appeller au tout début du travail avec l'audio, UNE fois */
void	Audio::init()
{
  FMOD_System_Create(&this->_system);
  FMOD_System_Init(this->_system, 32, FMOD_INIT_NORMAL, NULL);
  FMOD_System_GetMasterChannelGroup(this->_system, &this->_channels);
}

/* Fonction appellée par le destructor, qui se charge de bien vider la mémoire */
void	Audio::_freeEverything()
{
  for (std::map<Sounds, FMOD_SOUND*>::iterator it = this->_map_sounds.begin();
       it != this->_map_sounds.end(); ++it)
    FMOD_Sound_Release(it->second);

  for (std::map<Musics, FMOD_SOUND*>::iterator it2 = this->_map_musics.begin();
       it2 != this->_map_musics.end(); ++it2)
    FMOD_Sound_Release(it2->second);
}

/* Charge un son en mémoire, l'assignant sur un FMOD_SOUND* */
void	Audio::load(Sounds param, std::string filename)
{
  FMOD_System_CreateSound(this->_system, filename.c_str(),
			  FMOD_CREATESAMPLE, 0,
			  &this->_map_sounds[param]);
}

/* Charge une musique en mémoire, l'assignant sur un FMOD_SOUND* */
void	Audio::load(Musics param, std::string filename)
{
  FMOD_System_CreateSound(this->_system, filename.c_str(),
			  FMOD_SOFTWARE | FMOD_2D
			  | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0,
			  &this->_map_musics[param]);
}

/* Free manuel d'un FMOD_SOUND* dans la map des sons */
void	Audio::free(Sounds param)
{
  FMOD_Sound_Release(this->_map_sounds[param]);
  this->_map_sounds.erase(param);
}

/* Free manuel d'un FMOD_SOUND* dans la map des musiques */
void	Audio::free(Musics param)
{
  FMOD_Sound_Release(this->_map_musics[param]);
  this->_map_musics.erase(param);
}

/* Lecture d'un FMOD_SOUND* depuis la map des sons */
void	Audio::play(Sounds param)
{
  FMOD_System_PlaySound(this->_system, FMOD_CHANNEL_FREE,
			this->_map_sounds[param], 0, NULL);
}

/* Lecture d'un FMOD_SOUND* depuis la map des musiques */
void	Audio::play(Musics param)
{
  FMOD_System_PlaySound(this->_system, FMOD_CHANNEL_FREE,
			this->_map_musics[param], 0, NULL);
  FMOD_Sound_SetLoopCount(this->_map_musics[param], -1);
}

/* Libère le pointeur _system, et ferme ainsi le travail avec FMOD */
void	Audio::close()
{
  FMOD_System_Close(this->_system);
  FMOD_System_Release(this->_system);
}

/* Met en pause tous les sons en lecture */
void			Audio::pause()
{
  FMOD_BOOL		state;

  FMOD_ChannelGroup_GetPaused(this->_channels, &state);
  
  if (state != 1)
    FMOD_ChannelGroup_SetPaused(this->_channels, 1);
}

/* Reprend la lecture de tous les sons en pause*/
void			Audio::resume()
{
  FMOD_BOOL		state;

  FMOD_ChannelGroup_GetPaused(this->_channels, &state);
  
  if (state == 1)
    FMOD_ChannelGroup_SetPaused(this->_channels, 0);
}

/* Stoppe la lecture de tous les sons en cours de lecture */
void	Audio::stop()
{
  FMOD_ChannelGroup_Stop(this->_channels);
}

/* Modifie le volume. Lui passer une valeur entre 0 et 10 */
void			Audio::setVolume(int volume)
{
  float			new_volume;

  new_volume = volume / 10.0;
  if (new_volume > 10)
    new_volume = 10;
  if (new_volume < 0)
    new_volume = 0;

  FMOD_ChannelGroup_SetVolume(this->_channels, new_volume);
}
