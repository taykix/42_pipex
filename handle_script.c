
#include "ft_pipex.h"

int	ft_countstring(char** script_array)
{
	int	count;

	count = 0;
	while (script_array[count])
	{
		count++;
	}
	return (count);
}

int is_two_quotes(char* str)
{
	int count;
	int i;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			count++;
		i++;
	}
	return (count % 2) == 0;
}

char* str_join_with_free(char* new_script, char* script)
{
	char* temp;
	char* joined;

	temp = ft_strjoin(" ", script);
	joined = ft_strjoin(new_script, temp);
	free(temp);
	free(new_script);

	return joined;
}

// "awk '{print avs $2}'"
char** handle_quotes_in_script(char** script)
{
	int		i;
	int		j;
	char** new_script;

	i = 0;
	j = 0;
	new_script = (char**)malloc(sizeof(char*) * (ft_countstring(script) + 1));
	while (script[i])
	{
		if (ft_strchr(script[i], '\'') && !is_two_quotes(script[i]))
		{
			new_script[j] = ft_strdup(script[i++]);
			while (script[i])
			{
				new_script[j] = str_join_with_free(new_script[j], script[i]);
				//new_script[j] = ft_strjoin(new_script[j], ft_strjoin(" ", script[i]));
				if (ft_strchr(script[i++], '\''))
					break;
			}
		}
		else
			new_script[j] = ft_strdup(script[i++]);
		j++;
	}
	new_script[j] = NULL;
	return (new_script);
}

char* erase_first_and_last_quote(char* str)
{
	char* str_without_quotes;
	int i;
	int len = ft_strlen(str);

	if (str[0] == '\'' && str[len - 1] == '\'')
	{
		str_without_quotes = (char*)malloc(sizeof(char) * (len - 1));
		if (!str_without_quotes)
			return NULL;
		i = 1;
		while (i < len - 1)
		{
			str_without_quotes[i - 1] = str[i];
			i++;
		}
		str_without_quotes[i - 1] = '\0';
		free(str);
		return str_without_quotes;
	}
	return str;
}
