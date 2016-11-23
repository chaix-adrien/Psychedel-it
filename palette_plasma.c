/*
** palette_plasma.c for palette_plasma in /gfx_incendie/Plasma/test_color
** 
** Made by julien pinchelimouroux
** Login   <pinche_j@epitech.net>
** 
** Started on  Sat Dec 19 10:50:02 2015 julien pinchelimouroux
** Last update Sun Jan 31 16:39:51 2016 Adrien Chaix
*/

#include "plasma.h"

int	decre_color(u_int *tab, int type, int counter, t_color *color)
{
  while (color->argb[type] > 7)
    {
      tab[counter] = color->full;
      color->argb[type] = color->argb[type] - 8;
      counter = counter + 1;
    }
  tab[counter] = color->full;
  counter = counter + 1;
  color->argb[type] = 0;
  return (counter);
}

int	incre_color(u_int *tab, int type, int counter, t_color *color)
{
  while (color->argb[type] < 248)
    {
      tab[counter] = color->full;
      color->argb[type] = color->argb[type] + 8;
      counter = counter + 1;
    }
  tab[counter] = color->full;
  counter = counter + 1;
  color->argb[type] = 255;
  return (counter);
}

#include <stdio.h>

u_int		*palette_plasma(void)
{
  u_int		*tab;
  t_color	color;
  int		counter;
  static unsigned int	start = GREEN;

  counter = 0;
  if ((tab = bunny_malloc(sizeof(u_int) * 162)) == NULL)
    return (NULL);
  color.full = start;
  counter = incre_color(tab, R, counter, &color);
  counter = decre_color(tab, V, counter, &color);
  counter = decre_color(tab, R, counter, &color);
  counter = incre_color(tab, B, counter, &color);
  counter = incre_color(tab, V, counter, &color);
  return (tab);
  start += 50000;
}
