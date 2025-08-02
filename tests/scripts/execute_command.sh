#!/bin/bash
script_dir="$(dirname $0)"
make -C "$script_dir/.." execute_command >/dev/null
if [[ $? -ne 0 ]]; then
	printf "execute_command: make failed\n"
	exit 1
fi
prog="${script_dir}/../execute_command"
source "$script_dir/../test_utils.sh"

make_test() {
	local input=$1
	local pathname=$(whereis -b $input | cut -d' ' -f2)
	./$prog "${input}" "${pathname}"
	if [[ $? -ne 0 ]]; then
		test_fail "${input}"
		tests_failed=$((tests_failed + 1))
	else
		test_pass "${input}"
		tests_passed=$((tests_passed + 1))
	fi
}

make_test "ls"
make_test "cat"
resume_test $tests_passed $tests_failed

if [[ $tests_failed -gt 0 ]]; then
	exit 1
fi
