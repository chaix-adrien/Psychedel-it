#include <stdlib.h>
#include <stdio.h>
#include <lapin.h>
#include <fmodex/fmod.h>

#define LARGEUR_FENETRE         512 /* DOIT rester à 512 impérativement car il y a 512 barres (correspondant aux 512 floats) */
#define HAUTEUR_FENETRE         400 /* Vous pouvez la faire varier celle-là par contre */
#define RATIO                   (HAUTEUR_FENETRE / 255.0)
#define DELAI_RAFRAICHISSEMENT  25 /* Temps en ms entre chaque mise à jour du graphe. 25 ms est la valeur minimale. */
#define TAILLE_SPECTRE          512


void	print_spectre(t_pix *pix, t_option *option)
{
  FMOD_Channel_GetSpectrum(canal, spectre, TAILLE_SPECTRE, 0,  FMOD_DSP_FFT_WINDOW_RECT);
  for (i = 0 ; i < LARGEUR_FENETRE ; i++)
    {
      hauteurBarre = spectre[i] * HAUTEUR_FENETRE * 2;
      if (hauteurBarre > HAUTEUR_FENETRE)
	hauteurBarre = HAUTEUR_FENETRE;
      for (j = HAUTEUR_FENETRE - hauteurBarre ; j < HAUTEUR_FENETRE ; j++)
	{
	  setPixel(ecran, i, j, SDL_MapRGB(ecran->format, 255 - (j / RATIO), j / RATIO, 0));
	}
    }
}
