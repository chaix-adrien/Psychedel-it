/*
** plasma.c for plasma in /home/blizzard120/gfx_incendie/Plasma
** 
** Made by Chaix Adrien
** Login   <blizzard120@epitech.net>
** 
** Started on  Sat Dec 19 16:46:44 2015 Chaix Adrien
** Last update Fri Feb 19 12:29:25 2016 Adrien Chaix
*/

#include "plasma.h"

void	set_center(float *sensi, int add)
{
  if (BORDER_L(sensi) + add < 0)
    return ;
  else if (BORDER_R(sensi) + add > 512)
    return ;
  else
    sensi[CENTER] += add;
}

void	set_radius(float *sensi, int add)
{
  if (sensi[RADIUS] + add <= 0 || sensi[RADIUS] + add >= 512)
    return ;
  else if (BORDER_R(sensi) + add > 512)
    {
      sensi[CENTER] -= 1;
      sensi[RADIUS] += 1;
    }
  else if (BORDER_L(sensi) + add * -1 <= 0)
    {
      sensi[CENTER] += 1;
      sensi[RADIUS] += 1;
    }
  else
    sensi[RADIUS] += add;
  
}

void	read_write_file(int file, float sensi[3][3],
			ssize_t (func)(int, void *, size_t))
{
  int	nav[2];
  float tmp;

  nav[0] = -1;
  while (++nav[0] < 3)
    {
      nav[1] = -1;
      while(++nav[1] < 3)
	{
	  tmp = sensi[nav[0]][nav[1]];
	  func(file, &tmp, sizeof(float));
	  sensi[nav[0]][nav[1]] = tmp;
	}
    }
}
			

void	save_sensi(float sensi[3][3])
{
  char const *lTheSaveFileName;
  int   nav[2];
  float	tmp;
  int	file;

  
  lTheSaveFileName = tinyfd_saveFileDialog("Save current configuration",
					    "config_music.pdt", 0, NULL, NULL);
  if ((file = open(lTheSaveFileName, O_WRONLY)) < 3)
    return ;
  read_write_file(file, sensi, write);
  close(file);
}


void	open_sensi(float sensi[3][3])
{
  char const *lTheopenFileName;
  int	file;
  int   nav[2];
  float	tmp;
    
  lTheopenFileName = tinyfd_openFileDialog("Open configuration", ".pdt", 0, NULL,
					   NULL, 0);
  if ((file = open(lTheopenFileName, O_RDONLY)) < 3)
    return ;
  read_write_file(file, sensi, read);
  close(file);
}

t_bunny_response	keyboard_plasma(t_bunny_event_state	state,
					t_bunny_keysym		keysym,
					t_all			*all)
{
  if (state)
    return (GO_ON);
  if (keysym == BKS_RETURN)
    all->mode = !all->mode;
  else if (keysym == BKS_S)
    {
      FMOD_Channel_SetPaused(all->canal, true);
      save_sensi(all->sensi);
      FMOD_Channel_SetPaused(all->canal, false);
    }
  else if (keysym == BKS_O)
    {
      FMOD_Channel_SetPaused(all->canal, true);
      open_sensi(all->sensi);
      FMOD_Channel_SetPaused(all->canal, false);
    }
  else if (all->mode == SPECTRE)
    {
      if (keysym == BKS_A)
	all->selec = (all->selec == AIGUE) ? -1 : AIGUE;
      else if (keysym == BKS_M)
	all->selec = (all->selec == MEDIUM) ? -1 : MEDIUM;
      else if (keysym == BKS_B)
	all->selec = (all->selec == BASSE) ? -1 : BASSE;
      else if (all->selec >= 0)
	{
	  if (keysym == BKS_PAGEUP)
	    all->sensi[all->selec][HAUTEUR] += 0.005;
	  else if (keysym == BKS_PAGEDOWN)
	    all->sensi[all->selec][HAUTEUR] -= 0.005;
	  else if (keysym == BKS_LEFT)
	    set_center(all->sensi[all->selec], -1);
	  else if (keysym == BKS_RIGHT)
	    set_center(all->sensi[all->selec], 1);
	  else if (keysym == BKS_UP)
            set_radius(all->sensi[all->selec], 1);
	  else if (keysym == BKS_DOWN)
            set_radius(all->sensi[all->selec], -1);
	}
    }
  return (GO_ON);
}

#define LARGEUR_FENETRE         512 /* DOIT rester à 512 impérativement car il y a 512 barres
				       (correspondant aux 512 floats) */
#define HAUTEUR_FENETRE         720 /* Vous pouvez la faire varier celle-là par contre */
#define RATIO                   (HAUTEUR_FENETRE / 255.0)
#define TAILLE_SPECTRE          512
# define SENSIBILITE_BASSE 50
# define SENSIBILITE_MEDIUM 300
# define SENSIBILITE_AIGUE TAILLE_SPECTRE
# define SENSIBILITE_GENERALE HAUTEUR_FENETRE
#include <stdio.h>

int	get_state(float *spectre, float sensi[3], int state)
{
  int           nav;
  
  nav = BORDER_L(sensi) - 1;
  while (++nav < BORDER_R(sensi))
    {
      if (spectre[nav] >= sensi[HAUTEUR])
	return (1);
    }
  return (0);
}

void		get_param(t_all *all, float sensi[3][3])
{
  float		spectre[TAILLE_SPECTRE];
  int		nav;
  static int state[3];
  int		szoom;
  
  FMOD_Channel_GetSpectrum(all->canal, spectre, TAILLE_SPECTRE,
			   0,  FMOD_DSP_FFT_WINDOW_RECT);
  nav = -1;
  while (++nav < TAILLE_SPECTRE)
    {
      if (nav >= BORDER_L(sensi[BASSE]) && nav <= BORDER_R(sensi[BASSE])
	  && spectre[nav] >= sensi[BASSE][HAUTEUR] && !state[BASSE])
	{
	  all->param.density = rand() % 7 + 1;
	  state[BASSE] = 1;
	}
      if (nav >= BORDER_L(sensi[MEDIUM]) && nav <= BORDER_R(sensi[MEDIUM])
	  && spectre[nav] >= sensi[MEDIUM][HAUTEUR] && !state[MEDIUM])
	{
	  all->param.vitesse = rand() % 5 + 1;
	  state[MEDIUM] = 1;
	}
      if (nav >= BORDER_L(sensi[AIGUE]) && nav <= BORDER_R(sensi[AIGUE])
	  && spectre[nav] >= sensi[AIGUE][HAUTEUR] && !state[AIGUE])
	{
	  all->param.zoom = rand() % 5 + 1;
	  state[AIGUE] = 1;
	}
    }
  state[BASSE] = get_state(spectre, sensi[BASSE], state[BASSE]);
  state[MEDIUM] = get_state(spectre, sensi[MEDIUM], state[MEDIUM]);
  state[AIGUE] = get_state(spectre, sensi[AIGUE], state[AIGUE]);
}

unsigned int	rgb_to_int(unsigned char r, unsigned char v, unsigned char b)
{
  t_color	col;

  col.argb[0] = r;
  col.argb[1] = v;
  col.argb[2] = b;
  col.argb[3] = 255;
  return (col.full);
}

void	my_fill(t_pix *pix, unsigned int color)
{
  int	nav[2];

  nav[Y] = -1;
  while (++nav[Y] < H_TAB(pix))
    {
      nav[X] = -1;
      while(++nav[X] < W_TAB(pix))
	{
	  tekpixel(pix, nav, color);
	}
    }
}

void	print_param(t_pix *pix, float param[3], unsigned int color)
{
  int	nav[2];
  int	hauteur;

  nav[X] = param[CENTER] - param[RADIUS];
  nav[Y] = H_TAB(pix);
  hauteur = H_TAB(pix) - param[HAUTEUR] * H_TAB(pix);
  while (--nav[Y] > hauteur)
    tekpixel(pix, nav, color);
  nav[X] = param[CENTER] + param[RADIUS];
  nav[Y] = H_TAB(pix);
  while (--nav[Y] > hauteur)
    tekpixel(pix, nav, color);
  nav[X] = param[CENTER] - param[RADIUS];
  nav[Y] = hauteur;
  while (++nav[X] < param[CENTER] + param[RADIUS])
    tekpixel(pix, nav, color);
}

void		print_params(t_pix *pix, float sensi[3][3], int selec)
{
  int		nav;
  unsigned int	color;

  nav = -1;
  while (++nav < 3)
    {
      if (nav == selec)
	color = WHITE;
      else
	{
	  if (nav == AIGUE)
	    color = RED;
	  else if (nav == MEDIUM)
	    color = PURPLE;
	  else if (nav == BASSE)
	    color = BLUE;
	}
      print_param(pix, sensi[nav], color);
    }
}

void	print_spectre(t_pix *pix, t_param *option, t_all *all)
{
  float spectre[TAILLE_SPECTRE];
  int	hauteurBarre;
  int	nav[2];

  FMOD_Channel_GetSpectrum(all->canal, spectre, TAILLE_SPECTRE, 0,
			   FMOD_DSP_FFT_WINDOW_RECT);
  my_fill(pix, BLACK);
  for (nav[0] = 0 ; nav[0] < LARGEUR_FENETRE ; nav[0]++)
    {
      hauteurBarre = spectre[nav[0]] * H_TAB(pix);
      if (hauteurBarre > HAUTEUR_FENETRE)
	hauteurBarre = HAUTEUR_FENETRE;
      for (nav[1] = HAUTEUR_FENETRE - hauteurBarre ;
	   nav[1] < HAUTEUR_FENETRE ; nav[1]++)
	{
	  tekpixel(pix, nav, rgb_to_int(255 - (nav[1] / RATIO),
					 nav[1] / RATIO, 0));
	}
    }
  print_params(pix, all->sensi, all->selec);
}


t_bunny_response	main_loop_plasma(void *_all)
{
  t_all			*all;
  t_bunny_position	pos;
  
  pos.x = 0;
  pos.y = 0;
  all = (t_all *)_all;

  if (all-> mode == SPECTRE)
    print_spectre(all->pix, &all->param, all);
  else if (all->mode == PLAYER)
    {
      get_param(all, all->sensi);
      create_cosinus(all->pix, all->palette, all->rad, &all->param);
    }
  bunny_free(all->palette);
  all->palette = palette_plasma();
  bunny_blit(&all->win->buffer, &all->pix->clipable, &pos);
  bunny_display(all->win);
  return (GO_ON);
}

int	main(int ac, char **av)
{
  t_all	all;

  if (ac < 2)
    {
      fprintf(stderr, "usage : ./xxx music.mp3\n");
      exit(EXIT_FAILURE);
    }
  FMOD_System_Create(&all.system);
  FMOD_System_Init(all.system, 1, FMOD_INIT_NORMAL, NULL);

  all.resultat = FMOD_System_CreateSound(all.system, av[1],
				     FMOD_SOFTWARE | FMOD_2D |
				     FMOD_CREATESTREAM, 0, &all.musique);
  if (all.resultat != FMOD_OK)
    {
      fprintf(stderr, "Impossible de lire le fichier mp3\n");
      exit(EXIT_FAILURE);
    }
  
  FMOD_System_PlaySound(all.system, FMOD_CHANNEL_FREE, all.musique, 0, NULL);
  FMOD_System_GetChannel(all.system, 0, &all.canal);
  
  if (set_all_plasma(&all, 1280, 720 - 2) != 0)
    return (1);
  all.sensi[BASSE][CENTER] = 100;
  all.sensi[BASSE][RADIUS] = 20;
  all.sensi[BASSE][HAUTEUR] = 0.5;
  
  all.sensi[MEDIUM][CENTER] = 200;
  all.sensi[MEDIUM][RADIUS] = 20;
  all.sensi[MEDIUM][HAUTEUR] = 0.5;
  
  all.sensi[AIGUE][CENTER] = 300;
  all.sensi[AIGUE][RADIUS] = 20;
  all.sensi[AIGUE][HAUTEUR] = 0.5;
  all.mode = SPECTRE;
  all.selec = -1;
  bunny_loop(all.win, 100, &all);
  bunny_delete_clipable(&all.pix->clipable);
  return (0);
}
