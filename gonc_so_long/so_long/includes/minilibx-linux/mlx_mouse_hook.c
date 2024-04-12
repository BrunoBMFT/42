/*
** mlx_mouse_hook.c for MiniLibX in 
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Thu Aug  3 11:49:06 2000 Charlie Root
** Last update Fri Feb 23 17:11:05 2001 Charlie Root
*/


#include	"mlx_int.h"




int		mlx_mouse_hook(t_win_list *win,int (*funct)(),void *varsam)
{
  win->hooks[ButtonPress].hook = funct;
  win->hooks[ButtonPress].varsam = varsam;
  win->hooks[ButtonPress].mask = ButtonPressMask;
}
