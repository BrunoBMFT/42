#include <stdio.h>

char	*ft_strcpy(char *s1, char *s2)
{
	int i = 0;

	if (!s1 || !s2)
		return (NULL);
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	while (s1[i])
	{
		s1[i] = '\0';
		i++;
	}
	return (s1);

}

int	main(void)
{
	char *src = "hello";
	char dest[10];
	printf("%s\n", ft_strcpy(dest, src));
}