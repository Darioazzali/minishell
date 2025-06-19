#!/bin/bash
# **************************************************************************** #
#                                                                              #
#    token_recognition.sh                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/16 17:01:31 by dazzali           #+#    #+#              #
#    Updated: 2025/06/19 08:28:48 by dazzali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_this_dir=$(dirname $0)
source ${_this_dir}/../test_utils.sh
input_dir=${_this_dir}/../input/token_recognition
output_dir=${_this_dir}/../output/token_recognition
token_recognition_bin=${_this_dir}/../token_recognition
expected_dir=${_this_dir}/../expected/token_recognition
token_recognition_tests=(${input_dir}/*)
tests_passed=0
tests_failed=0

mkdir -p $expected_dir $output_dir
mkdir -p $expected_dir
make -C $_this_dir/.. token_recognition >/dev/null

make_test() {
	local filename=$(basename $1)
	local output=${output_dir}/${filename}
	local input=${input_dir}/${filename}
	local expected=${expected_dir}/${filename}

	./${token_recognition_bin} ${input} >${output} 2>/dev/null
	if ! diff ${expected_dir}/${filename} ${output}; then
		test_fail "${filename}" "diff"
		tests_failed=$((tests_failed + 1))
	else
		test_pass "${filename}"
		tests_passed=$((tests_passed + 1))
	fi
}

for file in "${token_recognition_tests[@]}"; do
	if [[ -f "$file" ]]; then
		make_test "$file"
	fi
done
resume_test $tests_passed $tests_failed
