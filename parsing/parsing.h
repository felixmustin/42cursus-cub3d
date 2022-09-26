#ifndef PARSING_H
# define PARSING_H

#include "../main.h"

int		ft_strlen_split(char **str);
char	*ft_strdup_modif(char *str, char c);
int		ft_strcmp(const char *s1, const char *s2);
int		parsing_recover(int ac, char **av, t_data *data);
int		texture(char **file, t_data *data, int i);
int		color_recover(int	i, char **file, t_data *data);
int		map_recover(t_data *data, char **file, int i);
int		malloc_texture(t_data *data);
char	**file_recover(char *str);
int		parse_texture(t_data *data);
int		parser(t_data *data)
int		parse_map(t_data *data);

#endif