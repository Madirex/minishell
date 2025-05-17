/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:44:23 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 10:19:32 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env.h
 * @brief This file contains the definitions and functions related to
 * environment variables in the shell.
 */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"
# include "types.h"
# include <stdlib.h>
# include <stdbool.h>

// Environment initialization
# define INITIAL_BUFFER_SIZE	1024
# define BUFFER_INCREMENT	512
# define DEFAULT_PATH "/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin\
:/usr/local/sbin:/opt/bin:/opt/sbin"

/**
 * @brief Structure to represent the state of quotes in a string.
 * 
 * This structure contains two boolean flags to indicate whether
 * the parser is currently inside single quotes or double quotes.
 * The in_single_quotes flag is set to true if the parser is inside
 * single quotes, and the in_double_quotes flag is set to true
 * if the parser is inside double quotes.
 */
typedef struct s_quote_state
{
	bool	in_single_quotes;
	bool	in_double_quotes;
}				t_quote_state;

/**
 * @brief Structure to represent the context of variable expansion.
 * 
 * This structure contains the source string, destination string,
 * environment variables, current position in the source string,
 * and the state of quotes.
 */
typedef struct s_expansion_ctx
{
	const char		*src;
	char			*dest;
	t_env			*env;
	size_t			pos;
	t_quote_state	quote_state;
}				t_expansion_ctx;

// Core Environment Node Operations
t_env				*env_create_node(const char *key, const char *value);
t_env				*env_create_empty_node(t_env *env, const char *key);
t_env				*env_remove_node(t_env *env, const char *key);
void				env_append_node(t_env **head, const char *key,
						const char *value);
t_env				*env_to_linked_list(char **envp);
void				init_basic_env(t_env **env);
t_env				*create_default_env(void);

// Environment List Operations
void				free_env_list(t_env *head);
void				append_to_list(t_env *head, t_env *new_node);
bool				update_if_duplicate(t_env *head, const char *key,
						const char *value, t_env *new_node);
bool				allocate_key(const char *env, size_t length, char **key);
bool				allocate_value(const char *value_start, char **value);

// Environment Variable Access and Manipulation
t_env				*find_env_variable(t_env *env, const char *key);
char				*get_env_value(const char *key, t_env *env);
void				env_set_value(t_env *env, const char *key,
						const char *value);
int					safe_setenv(t_env **env, const char *name,
						const char *value, int overwrite);

// Environment String Parsing and Validation
bool				is_valid_env_name(const char *name);
char				*get_env_name(const char *var);
char				*get_env_value_from_str(const char *var);

// Variable Expansion and Special Handling
char				*replace_env_variables(const char *token, t_shell *shell);
void				init_expansion_context(t_expansion_ctx *ctx,
						const char *str, char *dest, t_env *env);

// Dynamic Buffer Operations
bool				append_to_buffer(t_dynamic_buffer *buffer,
						const char *data, size_t data_length);
void				handle_single_quotes(t_token_context *ctx,
						t_dynamic_buffer *buffer);
void				handle_env_variable(t_token_context *ctx,
						t_dynamic_buffer *buffer);

// Token Context Handling
void				handle_single_quotes(t_token_context *ctx,
						t_dynamic_buffer *buffer);
void				handle_double_quotes(t_token_context *ctx,
						t_dynamic_buffer *buffer);
void				handle_env_variable(t_token_context *ctx,
						t_dynamic_buffer *buffer);

//Env node utils
void				free_env_node(t_env *node);
t_env				*initialize_env_node(const char *key, const char *value);

#endif
