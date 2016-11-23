/*
** my_str.h for my_str in /home/blizzard120/lib/str/include
** 
** Made by Chaix Adrien
** Login   <blizzard120@epitech.net>
** 
** Started on  Sun Dec 13 02:49:03 2015 Chaix Adrien
** Last update Sun Dec 13 05:10:03 2015 Chaix Adrien
*/

#ifndef STR_H_
# define STR_H_
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>

# define NBR 1
# define LTR 2
# define SGN 3
# define X 0
# define Y 1

# define CL(value) (value + 48)
# define LC(value) (value - 48)
# define ABS(value) (((value) < 0) ? (value) * -1 : (value))

int	my_what_is(int c);
int	my_getnbr(char *str);
#endif	/* STR_H */
