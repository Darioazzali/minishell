#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    quote_removal.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/16 17:01:31 by dazzali           #+#    #+#              #
#    Updated: 2025/06/16 17:01:31 by dazzali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_this_dir=$(dirname $0)
source ${_this_dir}/../test_utils.sh
input_dir=${_this_dir}/../input/quote_removal
output_dir=${_this_dir}/../output/quote_removal
quote_removal_bin=${_this_dir}/../quote_removal
expected_dir=${_this_dir}/../expected/quote_removal
quote_removal_tests=(${input_dir}/*)
tests_passed=0
tests_failed=0

mkdir -p $expected_dir $output_dir
mkdir -p $expected_dir
make -C $_this_dir/.. quote_removal >/dev/null

make_test() {
	local filename=$(basename $1)
	local output=${output_dir}/${filename}
	local input=${input_dir}/${filename}
	local expected=${expected_dir}/${filename}

	./${quote_removal_bin} ${input} >${output} 2>/dev/null
	if ! diff ${expected_dir}/${filename} ${output}; then
		test_fail "${filename}" "diff"
		tests_failed=$((tests_failed + 1))
	else
		test_pass "${filename}"
		tests_passed=$((tests_passed + 1))
	fi
}

for file in "${quote_removal_tests[@]}"; do
	if [[ -f "$file" ]]; then
		make_test "$file"
	fi
done
resume_test $tests_passed $tests_failed
