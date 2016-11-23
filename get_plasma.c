/*
** get_plasma.c for get_plasma in /home/blizzard120/gfx_incendie/Plasma
** 
** Made by Chaix Adrien
** Login   <blizzard120@epitech.net>
** 
** Started on  Sat Dec 19 16:48:39 2015 Chaix Adrien
** Last update Wed Feb 17 01:52:25 2016 Adrien Chaix
*/

#include "plasma.h"

void	tekpixel(t_bunny_pixelarray *pic, int *nav, u_int col)
{
  COL_OF_TAB(pic, nav[X], nav[Y]) = col;
}

void	apply_modif(double	*value,
		    double	rad[2][360],
		    int		*nav,
		    t_param	*param)
{
  if (param->density > 1)
    *value = *value + rad[C][(nav[X] + nav[Y]) % 360];
  if (param->density > 2)
    *value = *value + (rad[S][ABS((nav[Y]) % 360)]);
  if (param->density > 3)
    *value = *value + rad[C][(nav[X] + nav[Y]) % 360];
  if (param->density > 4)
    *value = *value + (rad[S][ABS((nav[X]) % 360)]);
  if (param->density > 5)
    *value = *value + rad[C][ABS((nav[X] - nav[Y])) % 360];
  if (param->density > 6)
    *value = *value + (rad[C][ABS((nav[X] - nav[Y])) % 360]);
  if (param->density > 7)
    *value = *value + (rad[C][ABS((nav[X] - nav[Y])) % 360]);
}

void		create_cosinus(t_bunny_pixelarray	*pix,
			       u_int			*palette,
			       double			rad[2][360],
			       t_param			*param)
{
  int		nav[2];
  double	value;
  static int	size = 0;

  nav[Y] = -1;
  printf("%f\n", param->zoom);
  while (++nav[Y] < H_TAB(pix))
    {
      nav[X] = -1;
      while (++nav[X] < W_TAB(pix))
	{
	  value = rad[C][(int)((nav[X] + ABS(size)) * param->zoom) % 360];
	  value = value +
	    (rad[S][(int)((nav[Y] + ABS(size)) * param->zoom) % 360]);
	  apply_modif(&value, rad, nav, param);
	  value = value / (1 + param->density);
	  value = value * 159;
	  tekpixel(pix, nav, palette[(ABS((int)value) + size) % 160]);
	}
    }
  size += param->vitesse;
}
