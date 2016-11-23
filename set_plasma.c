/*
** set_plasma.c for set_plasma in /home/blizzard120/gfx_incendie/Plasma
** 
** Made by Chaix Adrien
** Login   <blizzard120@epitech.net>
** 
** Started on  Sat Dec 19 16:49:41 2015 Chaix Adrien
** Last update Sun Jan 31 16:49:33 2016 Adrien Chaix
*/

#include "plasma.h"

void	set_cos_sin(double rad[2][360])
{
  int	nav;

  nav = -1;
  while (++nav < 360)
    {
      rad[C][nav] = COS(nav);
      rad[S][nav] = SIN(nav);
    }
}

int	set_all_plasma(t_all *all, int w, int h)
{
  all->param.density = 1;
  all->param.vitesse = 1;
  all->param.zoom = 1;
  all->param.mode = 0;
  if ((all->pix = bunny_new_pixelarray(w, h + 2)) == NULL)
    return (1);
  if ((all->palette = palette_plasma()) == NULL)
    return (1);
  set_cos_sin(all->rad);
  if ((all->win = bunny_start(w, h + 2, false, "flamme")) == NULL)
    return (1);
  bunny_set_loop_main_function(&main_loop_plasma);
  bunny_set_key_response(&keyboard_plasma);
  return (0);
}

void	free_plasma(t_all *all)
{
  bunny_delete_clipable(&all->pix->clipable);
  bunny_stop(all->win);
  bunny_free(all->pix->pixels);
  bunny_free(all->palette);
}
