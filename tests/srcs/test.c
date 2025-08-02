/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 test.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/14 12:36:37 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/19 09:12:41 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "test.h"

char	*strip_newline(char *g_line)
{
	char	*last_nl;

	last_nl = ft_strrchr(g_line, '\n');
	if (last_nl)
		*last_nl = '\0';
	return (g_line);
}

char	*read_file(const char *filename)
{
	FILE	*file;
	long	file_size;
	char	*buffer;
	size_t	bytes_read;

	file = fopen(filename, "r");
	if (!file)
	{
		fprintf(stderr, "Error: Cannot open file '%s'\n", filename);
		return (NULL);
	}
	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	buffer = malloc(file_size + 1);
	if (!buffer)
	{
		fprintf(stderr, "Error: Memory allocation failed\n");
		fclose(file);
		return (NULL);
	}
	bytes_read = fread(buffer, 1, file_size, file);
	buffer[bytes_read] = '\0';
	fclose(file);
	return (buffer);
}

char	**extract_string_array(cJSON *json_array, int *array_size)
{
	char	**string_array;
	cJSON	*item;

	*array_size = cJSON_GetArraySize(json_array);
	if (*array_size == 0)
		return (NULL);
	string_array = malloc(sizeof(char *) * (*array_size));
	if (!string_array)
	{
		fprintf(stderr, "Error: Memory allocation failed for string array\n");
		return (NULL);
	}
	for (int i = 0; i < *array_size; i++)
	{
		item = cJSON_GetArrayItem(json_array, i);
		if (!cJSON_IsString(item))
		{
			fprintf(stderr, "Error: Array item %d is not a string\n", i);
			for (int j = 0; j < i; j++)
				free(string_array[j]);
			free(string_array);
			return (NULL);
		}
		string_array[i] = strdup(cJSON_GetStringValue(item));
		if (!string_array[i])
		{
			fprintf(stderr, "Error: Memory allocation"
				"failed for string %d\n", i);
			for (int j = 0; j < i; j++)
				free(string_array[j]);
			free(string_array);
			return (NULL);
		}
	}
	return (string_array);
}

t_json_input_t	*read_json_input(const char *filename)
{
	char			*file_content;
	cJSON			*json;
	const char		*error_ptr;
	t_json_input_t	*result;
	cJSON			*input_line_json;
	cJSON			*input_array_json;

	if (!filename)
	{
		fprintf(stderr, "Error: Filename is NULL\n");
		return (NULL);
	}
	file_content = read_file(filename);
	if (!file_content)
		return (NULL);
	json = cJSON_Parse(file_content);
	free(file_content);
	if (!json)
	{
		error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
			fprintf(stderr, "Error: JSON parse error before: %s\n", error_ptr);
		return (NULL);
	}
	result = malloc(sizeof(t_json_input_t));
	if (!result)
	{
		fprintf(stderr, "Error: Memory allocation failed"
			"for result structure\n");
		cJSON_Delete(json);
		return (NULL);
	}
	result->input_line = NULL;
	result->input_array = NULL;
	result->array_size = 0;
	input_line_json = cJSON_GetObjectItem(json, "input");
	if (cJSON_IsString(input_line_json))
	{
		result->input_line = strdup(cJSON_GetStringValue(input_line_json));
		if (!result->input_line)
		{
			fprintf(stderr, "Error: Memory allocation failed for input_line\n");
			free(result);
			cJSON_Delete(json);
			return (NULL);
		}
	}
	else
		printf("Warning: 'input_line' not found or not a string\n");
	input_array_json = cJSON_GetObjectItem(json, "expected");
	if (cJSON_IsArray(input_array_json))
	{
		result->input_array = extract_string_array(input_array_json, &result->array_size);
		if (!result->input_array && result->array_size > 0)
		{
			free(result->input_line);
			free(result);
			cJSON_Delete(json);
			return (NULL);
		}
	}
	else
		printf("Warning: 'input_array' not found or not an array\n");
	cJSON_Delete(json);
	return (result);
}

void	free_json_input(t_json_input_t *input)
{
	if (!input)
		return ;
	free(input->input_line);
	if (input->input_array)
	{
		for (int i = 0; i < input->array_size; i++)
			free(input->input_array[i]);
		free(input->input_array);
	}
	free(input);
}

// Helper function to print the parsed data
void	print_json_input(const t_json_input_t *input)
{
	if (!input)
	{
		printf("Input is NULL\n");
		return ;
	}
	printf("Input Line: %s\n",
		input->input_line ? input->input_line : "(null)");
	printf("Input Array (%d items):\n", input->array_size);
	if (input->input_array)
	{
		for (int i = 0; i < input->array_size; i++) {
			printf("  [%d]: %s\n", i, input->input_array[i]);
		}
	}
	else
		printf("  (null)\n");
}

t_list	*from_array_to_ll(char **arr, int size)
{
	t_list	*lst;	
	int		i;

	lst = NULL;
	i = 0;
	while (i < size)
	{
		ft_lstadd_back(&lst, ft_lstnew(arr[i]));
		i++;
	}
	return (lst);
}

void	test_fail(char *test_name, char *message)
{
	if (message)
		fprintf(stderr, "%s %s: %s\n", R_BALLOT, test_name, message);
	else
		fprintf(stderr, "%s %s\n", R_BALLOT, test_name);
}

void	test_success(char *test_name, char *message)
{
	if (message)
		printf("%s %s: %s\n", G_CHECKMARK, test_name, message);
	else
		printf("%s %s\n", G_CHECKMARK, test_name);
}

void	_print_test_result(t_cd_t *t)
{
	if (t->t_succ == t->t_total)
	{
		printf("%sALL Test Passed: %s", GREEN_BOLD, NORMAL);
		printf("%zu/%zu\n", t->t_succ, t->t_total);
		return ;
	}
	printf("%sTest Passed: %s", GREEN_BOLD, NORMAL);
	printf("%zu/%zu\n", t->t_succ, t->t_total);
	if (t->t_fail)
		printf("%sFail: %zu%s\n", RED_BOLD, t->t_fail, NORMAL);
}

void	init_test_result(t_cd_t *t)
{
	t->t_fail = 0;
	t->t_succ = 0;
	t->t_total = 0;
	t->status = 0;
}
