#include "parser.h"

static t_ast_node	*parse_logical(t_list **current);
static t_ast_node	*parse_pipeline(t_list **current);
static t_ast_node	*parse_command(t_list **current);
static t_ast_node	*create_node(t_ast_type type, char *value);

t_ast_node	*build_ast(t_ctx *ctx)
{
	t_list	*current;
	current = ctx->tokenizer->tokens;
	return (parse_logical(&current));
}

static t_ast_node	*parse_logical(t_list **curent)
{
	t_ast_node	*left;
	t_ast_node	*node;
	t_token		*token;

	left = parse_pipeline(current);
	while(*current)
	{
		token = (t_token *)(*current)->content;
		if (token->type != TOK_AND && token->type != TOK_OR)
			break ;
		node = create_node(AST_LOGICAL, token->value);
		node->left = left;
		*current = (*current)->next;
		node->right = parse_logical(current);
		left = node;
	}
	return (left);
}

static t_ast_node	*parse_pipeline(t_list **curent)
{
	t_ast_node	*left;
	t_ast_node	*node;
	t_token		*token;

	while (*current)
	{
		token = (t_token *)(*current)->content;
		if (token->type != TOK_PIPE)
			break ;
		node = create_node(AST_PIPELINE, token->value);
		node->left = left;
		*current = (*current)->next;
		node->right = parse_command(current);
		left = node;
	}
	return (left);
}

static t_ast_node	*parse_command(t_list **current)
{
	t_ast_node	*cmd;
	t_token		*token;
	t_list		*args;

	if (!*current)
		return (NULL);
	token = (t_token *)(*current)->content;
	if (token->type != TOK_WORD)
		return (NULL);
	cmd = create_node(AST_COMMAND, token->value);
	*current = (*current)->next;
	args = NULL;
	while (*current)
	{
		token = (t_token *)(*current)->content;
		if (token->type != TOK_WORD)
			break ;
		ft_lstaddback(&args, ft_lstnew(ft_strdup(token->value)));
		*current = (*current)->next;
	}
	if (args)
		cmd->args = list_to_array(args);
	return (cmd);
}

static t_ast_node	*create_node(t_ast_type type, char *value)
{
	t_ast_node *node;
	
	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = ft_strdup(value);
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

char **list_to_array (t_list *lst)
{
	int		size;
	char	**array;
	int		i;

	size = ft_lstsize(lst);
	i = 0;
	array = malloc(sizeof(char *) * (size + 1));
	while (lst)
	{
		array[i] = ft_strdup((char *)lst->content);
		lst = lst->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
