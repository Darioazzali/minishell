#include "parser.h"

static void ast_to_string_recursive(t_ast_node *node, char **result, int depth);
static void append_indent(char **result, int depth);

char	*deb_ast_to_string(t_ast_node *node)
{
	char	*result;

	if (!node)
		return (ft_strdup("(null)"));
	result = ft_strdup("\n");
	ast_to_string_recursive(node, &result, 0);
	return (result);
}

static void ast_to_string_recursive(t_ast_node *node, char **result, int depth)
{
	char	*temp;
	char	*line;
	int		i;

	if (!node)
		return ;
	line = malloc(256);
	append_indent(&line, depth);

	if (node->type == AST_LOGICAL)
		ft_strlcat(line, "AST_LOGICAL (\"", 256);
	else if (node->type == AST_PIPELINE)
		ft_strlcat(line, "AST_PIPELINE (\"", 256);
	else if (node->type == AST_COMMAND)
		ft_strlcat(line, "AST_COMMAND (\"", 256);

    ft_strlcat(line, node->value, 256);
    ft_strlcat(line, "\")", 256);

    // Añadir argumentos si es comando
    if (node->type == AST_COMMAND && node->args)
    {
        ft_strlcat(line, " [", 256);
        i = 0;
        while (node->args[i])
        {
            ft_strlcat(line, "\"", 256);
            ft_strlcat(line, node->args[i], 256);
            ft_strlcat(line, "\"", 256);
            if (node->args[i + 1])
                ft_strlcat(line, ", ", 256);
            i++;
        }
        ft_strlcat(line, "]", 256);
    }

    ft_strlcat(line, "\n", 256);

    // Concatenar al resultado
    temp = ft_strjoin(*result, line);
    free(*result);
    free(line);
    *result = temp;

    // Recursión para hijos
    if (node->left)
        ast_to_string_recursive(node->left, result, depth + 1);
    if (node->right)
        ast_to_string_recursive(node->right, result, depth + 1);
}

static void append_indent(char **line, int depth)
{
    int i;
    
    ft_strlcpy(*line, "", 256);
    i = 0;
    while (i < depth)
    {
        ft_strlcat(*line, "    ", 256); // 4 espacios por nivel
        i++;
    }
}

void free_ast_node(t_ast_node *node)
{
    int i;

    if (!node)
        return;
    
    free(node->value);
    
    if (node->args)
    {
        i = 0;
        while (node->args[i])
        {
            free(node->args[i]);
            i++;
        }
        free(node->args);
    }
    
    free_ast_node(node->left);
    free_ast_node(node->right);
    free(node);
}
