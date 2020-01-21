//
// Audio.hh for bomberman in /home/larue_a/Desktop/SOUND
// 
// Made by larue_a
// Login   <larue_a@epitech.net>
// 
// Started on  Wed Jun 11 14:18:20 2014 larue_a
// Last update Sun Jun 15 18:47:55 2014 virgile prideaux
//

#ifndef		AUDIO_HH_
# define	AUDIO_HH_

#include	"Includes/fmod.hpp"
#include	<map>
#include	<string>

class	Audio
{
public:
  enum	Sounds
  {
    BOMBPLANT,        /* bombplant.wav        */
    CANCEL,           /* cancel.wav           */
    CHANGESELECT,     /* changeselect.wav     */
    DESTROYEDWALL,    /* destroyedwall.wav    */
    DOUBLEKILL,       /* doublekill.wav       */
    EXPLOSION,        /* explosion.wav        */
    FIRSTBLOOD,       /* firstblood.wav       */
    HUMILIATION,      /* humiliation.wav      */
    LOSS,             /* loss.wav    */
    MULTIKILL,        /* multikill.wav        */
    NEWRECORD,        /* newrecord.wav        */
    OK,               /* ok.wav               */
    PLAYERDEATH,      /* loss.wav             */
    PLAYERHIT,        /* powerdown.wav        */
    POWERUP,          /* powerup.wav          */
    UNSTOPPABLE,      /* unstoppable.wav      */
    WIN               /* win.wav     */
  };

  enum	Musics
  {
    CREATOR,          /* creator.wav */
    GAME,             /* game.wav    */
    INTRO,            /* intro.wav   */
    MENU             /* menu.wav    */
  };

private:
  FMOD_SYSTEM*			_system;
  FMOD_CHANNELGROUP*		_channels;
  std::map<Sounds, FMOD_SOUND*>	_map_sounds;
  std::map<Musics, FMOD_SOUND*> _map_musics;

  Audio(const Audio& src);
  Audio&			operator=(const Audio& src);

  void				_freeEverything();

public:
  Audio();
  ~Audio();

  void	init();

  void	load(Sounds param, std::string filename);
  void	load(Musics param, std::string filename);

  void	free(Sounds param);
  void	free(Musics param);

  void	play(Sounds param);
  void	play(Musics param);

  void	pause();
  void	resume();
  void	stop();

  void	setVolume(int volume);

  void	close();
};

#endif	/* !AUDIO_HH_ */
