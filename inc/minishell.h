/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagoairm2 <yagoairm2@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:47:35 by yagoairm2         #+#    #+#             */
/*   Updated: 2025/04/21 11:05:49 by yagoairm2        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Project and types headers
# include "types.h"

// All headers
# include "ast/ast.h"
# include "builtins/cd_cmd.h"
# include "builtins/echo_cmd.h"
# include "builtins/env_cmd.h"
# include "builtins/exit_cmd.h"
# include "builtins/export_cmd.h"
# include "builtins/pwd_cmd.h"
# include "builtins/unset_cmd.h"
# include "core/core.h"
# include "core/dynamic_buffer.h"
# include "env/env.h"
# include "env/env_shlvl.h"
# include "executor/executor.h"
# include "parser/parser.h"
# include "parser/parser_errors.h"
# include "parser/parser_group.h"
# include "parser/parser_input_check.h"
# include "parser/parser_tokens.h"
# include "parser/parser_utils.h"
# include "parser/tokenizer.h"
# include "parser/tokenizer_utils.h"
# include "signals/signals.h"
# include "utils/char_utils.h"
# include "utils/debug_print_ast.h"
# include "utils/get_next_line.h"
# include "utils/mem_utils.h"
# include "utils/num_utils.h"
# include "utils/path_search.h"
# include "utils/path_utils.h"
# include "utils/print.h"
# include "utils/str_utils.h"
# include "utils/str_utils_ext.h"

#endif
