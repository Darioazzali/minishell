#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ast.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/25 12:52:48 by dazzali           #+#    #+#              #
#    Updated: 2025/07/25 12:52:48 by dazzali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#

AST_DIR=$(dirname "$0")
TEST_DIR="$AST_DIR/../input/ast"
ROOT_DIR="$(dirname "$CD_DIR")/.."
AST="$ROOT_DIR/ast_parse"
source "$ROOT_DIR/test_utils.sh"
make -C $ROOT_DIR "ast_parse" >/dev/null

$AST "$TEST_DIR/test"
if [[ $? -ne 0 ]]; then
	exit 1
fi
