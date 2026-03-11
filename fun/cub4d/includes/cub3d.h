#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "structs.h"
# include "values.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <sys/time.h>

//init
bool	init(int ac, char **av, t_data *data);
bool	parser(int ac, char **av, t_data *data);
bool	save_map(t_data *data);
bool	map_check(t_data *data);
char	*skip_spaces(char *str);
char	*remove_spaces(char *str);
bool	save_texture_path(t_data *data);
bool	texture_check(t_data *data);
bool	init_imgs(t_data *data);
bool	player_init(t_data *data);
int		get_time(void);


//raycast
void	raycast(t_data *data);
void	draw_wall_section(t_data *data, int section, float angle, float hyp, float x, float y, bool vert);
void	create_background(t_data *data);
void	angle_correct(float *angle, int *dir, bool is_h);
float	rad(float deg);

//movement
int	key_press(int keysym, t_data *data);
int	key_release(int keysym, t_data *data);
int	mouse_movement(int x, int y, t_data	*data);
int	game_frame(t_data *data);

//utils
void	create_frame(t_data *data);
void	create_map(t_data *data);
void	put_pixel(t_data *data, int y, int x, int color);
int		get_pixel(t_img *img, int x, int y);
int		input(int keysym, t_data *data);
bool	error(char *str);
void	clean_exit(t_data *data, int exit_code);
int		mlx_clean_exit(t_data *data);

#endif