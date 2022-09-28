#include "../main.h"

char	*ft_strdup_modif(char *str, char c)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dst)
		return (0);
	while (str[i] != '\0' && str[i] != c)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	**file_to_texture(char *file)
{
	char	**str;

	str = ft_split(file, 32);
	if (!str)
		return (NULL);
	if (ft_strcmp(str[0], "NO") != 0 && ft_strcmp(str[0], "SO") != 0
		&& ft_strcmp(str[0], "WE") != 0 && ft_strcmp(str[0], "EA") != 0)
	{
		printf("infos about texture are not correct");
		return (NULL);
	}
	return (str);
}
