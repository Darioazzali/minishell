# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    all.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 17:30:24 by dazzali           #+#    #+#              #
#    Updated: 2025/06/19 08:26:18 by dazzali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#/bin/bash

_this_dir=$(dirname $0)
SCRIPT_DIR="$_this_dir/scripts/"
source ${_this_dir}/test_utils.sh

make_test() {
	local test_name=$1
	printf "${BOLD}${BLUE}Running ${test_name} tests${NORMAL}\n"
	(cd $SCRIPT_DIR && ./${test_name}.sh)
}
make_test "echo"
make_test "pwd"
make_test "expansion"
make_test "tokenizer"
make_test "quote_removal"
make_test "token_recognition"
