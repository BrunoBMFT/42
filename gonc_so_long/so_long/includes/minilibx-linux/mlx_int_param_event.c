/*
** mlx_int_varsam_event.c for MinilibX in 
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Mon Jul 31 16:37:50 2000 Charlie Root
** Last update Wed Oct  6 13:14:52 2004 Olivier Crouzet
*/

#include	"mlx_int.h"

int	mlx_int_varsam_undef()
{
}

int	mlx_int_varsam_KeyPress(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
  win->hooks[KeyPress].hook(XkbKeycodeToKeysym(xvar->display,
					       ev->xkey.keycode, 0, 0),
			    win->hooks[KeyPress].varsam);
}

int	mlx_int_varsam_KeyRelease(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
  win->hooks[KeyRelease].hook(XkbKeycodeToKeysym(xvar->display,
						 ev->xkey.keycode, 0, 0),
			      win->hooks[KeyRelease].varsam);
}

int	mlx_int_varsam_ButtonPress(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
  win->hooks[ButtonPress].hook(ev->xbutton.button,ev->xbutton.x,ev->xbutton.y,
			       win->hooks[ButtonPress].varsam);
}

int	mlx_int_varsam_ButtonRelease(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
  win->hooks[ButtonRelease].hook(ev->xbutton.button,
				 ev->xbutton.x, ev->xbutton.y,
				 win->hooks[ButtonRelease].varsam);
}

int	mlx_int_varsam_MotionNotify(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
  win->hooks[MotionNotify].hook(ev->xbutton.x,ev->xbutton.y,
				win->hooks[MotionNotify].varsam);
}

int	mlx_int_varsam_Expose(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
  if (!ev->xexpose.count)
    win->hooks[Expose].hook(win->hooks[Expose].varsam);
}


int	mlx_int_varsam_generic(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
  win->hooks[ev->type].hook(win->hooks[ev->type].varsam);
}

int	(*(mlx_int_varsam_event[]))() =
{
  mlx_int_varsam_undef,   /* 0 */
  mlx_int_varsam_undef,
  mlx_int_varsam_KeyPress,
  mlx_int_varsam_KeyRelease,  /* 3 */
  mlx_int_varsam_ButtonPress,
  mlx_int_varsam_ButtonRelease,
  mlx_int_varsam_MotionNotify,  /* 6 */
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_Expose,   /* 12 */
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic,
  mlx_int_varsam_generic
};
