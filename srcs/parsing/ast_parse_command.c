/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ast_parse_command.c								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/23 17:32:55 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/23 17:40:55 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "ast.h"

static bool				process_redirection(t_command_parts *parts,
							t_list **current);
static bool				process_token(t_command_parts *parts,
							t_token_category category, t_list **current);
static void				*_parse_error(char *message, t_command_parts *parts);
static bool				process_word(t_command_parts *parts, t_list **current);

t_ast_node	*parse_command(t_list **current)
{
	t_command_parts		*parts;
	t_token				*token;
	t_token_category	category;
	t_ast_node			*node;

	parts = init_command_parts();
	if (!parts)
		return (_parse_error("Failed to allocate command parts\n", NULL));
	while (*current)
	{
		token = (*current)->content;
		if (!(*token->value))
		{
			*current = (*current)->next;
			continue ;
		}
		category = classify_token(token);
		if (category == TOKEN_COMMAND_END)
			break ;
		if (!process_token(parts, category, current))
			return (_parse_error("Failed to process token\n", parts));
	}
	node = build_ast_node(parts);
	return (free_command_parts(parts), node);
}

static bool	process_token(t_command_parts *parts,
		t_token_category category, t_list **current)
{
	if (category == TOKEN_COMMAND_END)
		return (false);
	if (category == TOKEN_WORD)
		return (process_word(parts, current));
	if (category == TOKEN_REDIRECTION)
		return (process_redirection(parts, current));
	return (false);
}

/**
 * @brief Processes a redirection token pair and adds it to command parts
 * 
 * This function handles redirection operators by extracting the redirection
 * token and its associated filename token, validating the sequence, and
 * adding the redirection to the command's redirection list.
 * 
 * @param parts Pointer to the command parts structure to be populated
 * @param current Pointer to pointer of the current position in the token list.
 *                Gets advanced by two positions after successful processing.
 * 
 * @return true on successful processing of the redirection pair
 * @return false on missing filename token, invalid token type, or allocation
 *         failure
 * 
 * @note The function expects a redirection operator followed by a word token
 * @note The current pointer is advanced twice: once past the redirection
 *       operator and once past the filename
 * @note On failure, an error message is printed for missing filenames
 * 
 * @warning The function assumes the current token is a valid redirection
 *          operator
 * @warning No validation is performed on the redirection token itself
 */
static bool	process_redirection(t_command_parts *parts, t_list **current)
{
	t_token	*redir_token;
	t_token	*file_token;
	t_list	*redir_node;

	redir_token = (*current)->content;
	*current = (*current)->next;
	if (!*current)
		return (false);
	file_token = (*current)->content;
	if (classify_token(file_token) != TOKEN_WORD)
		return (print_shell_error_ret_int(
				"Expected filename after redirection operator\n", false));
	redir_node = init_redir_node(redir_token, file_token);
	if (!redir_node)
		return (false);
	ft_lstadd_back(&parts->redirections, redir_node);
	*current = (*current)->next;
	return (true);
}

/**
 * @brief Processes a word token and adds it to command parts structure
 * 
 * This function handles word tokens by either setting the command name (if not
 * already set) or adding the word as an argument to the command's argument 
 * list. It manages memory allocation for both the command name and arguments,
 * with proper error handling.
 * 
 * @param parts Pointer to the command parts structure to be populated
 * @param current Pointer to pointer of the current position in the token list.
 *                Gets advanced to the next token after processing.
 * 
 * @return true (1) on successful processing of the word token
 * @return false (0) on memory allocation failure
 * 
 * @note The function modifies the current pointer to advance to the next token
 * @note Memory is allocated for command name and arguments - caller responsible
 *       for cleanup
 * @note On allocation failure, any partially allocated memory is freed before
 *       returning
 * 
 * @warning The function assumes valid input pointers and proper token structure
 */
static bool	process_word(t_command_parts *parts, t_list **current)
{
	t_list	*arg_node;
	char	*arg;

	if (!parts->com_name)
	{
		parts->com_name = ft_strdup(((t_token *)(*current)->content)->value);
		if (!parts->com_name)
			return (print_shell_error_ret_int(MALLOC_ERROR_MSG, false));
	}
	else
	{
		arg = ft_strdup(((t_token *)(*current)->content)->value);
		if (!arg)
			return (print_shell_error_ret_int(MALLOC_ERROR_MSG, false));
		arg_node = ft_lstnew(arg);
		if (!arg_node)
		{
			free(arg);
			return (print_shell_error_ret_int(MALLOC_ERROR_MSG, false));
		}
		ft_lstadd_back(&parts->args_list, arg_node);
	}
	*current = (*current)->next;
	return (1);
}

static	void	*_parse_error(char *message, t_command_parts *parts)
{
	log_error(message);
	if (parts)
		free_command_parts(parts);
	return (NULL);
}
