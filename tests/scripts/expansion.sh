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

set -e
_this_dir=$(dirname $0)
source ${_this_dir}/../test_utils.sh
input_dir=${_this_dir}/../input/expander
output_dir=${_this_dir}/../output/expander
expander_bin=${_this_dir}/../expander
expected_dir=${_this_dir}/../expected/expander
expansion_tests=(${input_dir}/*)
tests_passed=0
tests_failed=0

mkdir -p $expected_dir $output_dir
mkdir -p $expected_dir
make -C $_this_dir/.. expander >/dev/null

make_test() {
	local filename=$(basename $1)
	local output=${output_dir}/${filename}
	local input=${input_dir}/${filename}
	local expected=${expected_dir}/${filename}

	export HOLA="hola mundo"
	./${expander_bin} ${input} >${output} 2>/dev/null
	if ! diff ${expected_dir}/${filename} ${output}; then
		test_fail "${filename}" "diff"
		tests_failed=$((tests_failed + 1))
	else
		test_pass "${filename}"
		printf "Test passed\n"
		tests_passed=$((tests_passed + 1))
	fi
	unset HOLA
}

make_test_pid() {
	local filename="test_pid"
	local input=${input_dir}/${filename}
	local output=${output_dir}/${filename}
	local expected=${expected_dir}/${filename}

	$expander_bin ${input} >${output} 2>/dev/null &
	local expander_pid=$!
	wait $expander_pid

	echo ${expander_pid} >${expected}
	if ! diff ${expected} ${output}; then
		test_fail "${filename}" "files differ"
		tests_failed=$((tests_failed + 1))
	else
		test_pass "${filename}"
		tests_passed=$((tests_passed + 1))
	fi

}

for file in "${expansion_tests[@]}"; do
	if [[ -f "$file" ]] && [[ "$(basename "$file")" != "test_pid" ]]; then
		make_test "$file"
	fi
done
make_test_pid
resume_test $tests_passed $tests_failed

if [[ $tests_failed -gt 0 ]]; then
	exit 1
fi
