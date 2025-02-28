#include "pipex.h"

static int	count_words(const char *str)
{
	int	i;
	int	counter;
	int	in_word;

	i = 0;
	counter = 0;
	in_word = 0;
	while (str[i])
	{
		if ((str[i] != ' ' && str[i] != '\t') && !in_word)
		{
			in_word = 1;
			counter++;
		}
		else if (str[i] == ' ' || str[i] == '\t')
		{
			in_word = 0;
		}
		i++;
	}
	return (counter);
}
static char	**fill_args(char **arr, const char *str)
{
	int	start;
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		start = i;
		while (str[i] && (str[i] != ' ' && str[i] != '\t'))
			i++;
		if (start < i)
		{
			arr[k] = fill_word(str, start, i);
			if (arr[k++] == NULL)
			{
				free_all(arr);
				return (NULL);
			}
		}
	}
	arr[k] = NULL;
	return (arr);
}

char	**split_tabs_spaces(char *str)
{
	char **arr;

	arr = (char **)malloc(sizeof(char *) * (count_words(str) + 1));
	if (!arr)
		return (NULL);
	arr = fill_args(arr, str);
	return (arr);
}