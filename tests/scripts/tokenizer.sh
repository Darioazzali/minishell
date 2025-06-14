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
output_dir=${_this_dir}/../output/tokenizer
tokenizer_bin=${_this_dir}/../tokenizer
expected_dir=${_this_dir}/../expected/tokenizer
expansion_tests=(${input_dir}/*)
tests_passed=0
tests_failed=0

mkdir -p $expected_dir $output_dir
mkdir -p $expected_dir
make -C $_this_dir/.. tokenizer >/dev/null

make_test() {
	local filename=$(basename $1)
	local output=${output_dir}/${filename}
	local input=${input_dir}/${filename}
	local expected=${expected_dir}/${filename}

	./${tokenizer_bin} ${input} >${output} 2>/dev/null
	if ! diff -U 3 ${expected} ${output}; then
		test_fail "${filename}" "diff"
		cat -en ${expected}
		cat -en ${output}
		tests_failed=$((tests_failed + 1))
	else
		test_pass "${filename}"
		tests_passed=$((tests_passed + 1))
	fi
}

for file in "${expansion_tests[@]}"; do
	if [[ -f "$file" ]]; then
		make_test "$file"
	fi
done
resume_test $tests_passed $tests_failed
