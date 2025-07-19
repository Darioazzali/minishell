#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    expansion.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/14 10:12:42 by dazzali           #+#    #+#              #
#    Updated: 2025/06/14 10:12:42 by dazzali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_this_dir=$(dirname $0)
source ${_this_dir}/../test_utils.sh
input_dir=${_this_dir}/../input/tokenizer
tokenizer_bin=${_this_dir}/../tokenizer
filename="${input_dir}/test.json"
err_file="${_this_dir}/.error"
tests_passed=0
tests_failed=0

make -C $_this_dir/.. tokenizer >/dev/null

make_test() {
	local input=${1}
	local filename=$(basename $1)

	./${tokenizer_bin} ${input} >${err_file}
	if [[ $? -ne 0 ]]; then
		test_fail "Tokenizer" ""
		cat ${err_file}
		tests_failed=$((tests_failed + 1))
	else
		test_pass "${filename}"
		tests_passed=$((tests_passed + 1))
	fi
}

make_test "${input_dir}/test.json"
make_test "${input_dir}/test1.json"
make_test "${input_dir}/test2.json"
make_test "${input_dir}/test3.json"
resume_test $tests_passed $tests_failed

if [[ $tests_failed -gt 0 ]]; then
	exit 1
fi
