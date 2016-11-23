/*
** flamme.h for flamme.h in /home/pinche/Documents/gfx_incendie/include
**
** Made by julien pinchelimouroux
** Login   <pinche_j@epitech.net>
**
** Started on  Fri Dec 18 21:24:23 2015 julien pinchelimouroux
** Last update Wed Mar  9 19:18:37 2016 Adrien Chaix
*/

#ifndef PLASMA_H_
# define PLASMA_H_
#define _FILE_OFFSET_BITS 64
#include <sys/time.h>
# include <lapin.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
# include "tinyfiledialogs.h"
#include <fmodex/fmod.h>
# include "my_str.h"
# define X 0
# define Y 1
# define C 0
# define S 1
# define R 0
# define V 1
# define B 2
# define W_TAB(tab) (tab->clipable.clip_width)
# define H_TAB(tab) (tab->clipable.clip_height)
# define COL_OF_TAB(t, x, y) (((unsigned int *)(t)->pixels)[y * W_TAB(t) + x])
# define ABS(value) (((value) < 0) ? (value) * -1 : (value))
# define RAD(a) (((double)(a) / 180) * M_PI)
# define COS(a) (cos(RAD(a)))
# define SIN(a) (sin(RAD(a)))
# define CENTER 0
# define RADIUS 1
# define HAUTEUR 2
# define BASSE 0
# define MEDIUM 1
# define AIGUE 2
# define SPECTRE 0
# define PLAYER 1
# define BORDER_L(s) (s[CENTER] - s[RADIUS])
# define BORDER_R(s) (s[CENTER] + s[RADIUS])
typedef unsigned int	u_int;
typedef t_bunny_pixelarray t_pix;
typedef t_bunny_position t_pos;
typedef struct	s_param
{
  float		zoom;
  int		density;
  int		vitesse;
  int		mode;
}		t_param;

typedef struct		s_all
{
  FMOD_SYSTEM *system;
  FMOD_SOUND *musique;
  FMOD_CHANNEL *canal;
  FMOD_RESULT resultat;
  t_bunny_window	*win;
  struct s_param	param;
  u_int			*palette;
  double		rad[2][360];
  t_bunny_pixelarray	*pix;
  float			sensi[3][3];
  int			selec;
  int			mode;
}			t_all;

void	tekpixel(t_bunny_pixelarray *pic, int *nav, u_int col);
char	**malloc_pic_pal(int w, int h);
int	set_all_plasma(t_all *all, int w, int h);
t_bunny_response	main_loop_plasma(void *_all);
u_int	*palette_plasma(void);
t_bunny_response	keyboard_plasma(t_bunny_event_state	state,
					t_bunny_keysym		keysym,
					t_all			*all);
void	create_cosinus(t_bunny_pixelarray *pix, u_int *palette,
		       double rad[2][360], t_param *param);
#endif /* PLASMA_H */
