#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 16:31:07 by dazzali           #+#    #+#              #
#    Updated: 2025/06/09 19:41:46 by dazzali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PWD_DIR=$(dirname "$0")
TEST_DIR="$PWD_DIR/../"
ROOT_DIR="$(dirname "$PWD_DIR")/../.."
_PWD="$ROOT_DIR/pwd"
source "$TEST_DIR/test_utils.sh"
make -C $ROOT_DIR echo >/dev/null

# Compare the pwd comand with the one implemented by us.
# If the output is different, report the difference
compare_pwds() {
	$_PWD >$PWD_DIR/basic.txt
	pwd >$PWD_DIR/basic_real.txt
	diff "$PWD_DIR/basic.txt" "$PWD_DIR/basic_real.txt" >"$PWD_DIR/.fail_res"
	diff_err_code=$?
	if [[ $diff_err_code -ne 0 ]]; then
		test_fail "basic pwd" "$(cat $PWD_DIR/.fail_res)"
	else
		test_pass "basic pwd" "basic"
	fi
	return "$diff_err_code"
}

pwd_test() {
	compare_pwds
	if [[ $? -ne 0 ]]; then
		tests_failed=$((tests_failed + 1))
	else
		tests_passed=$((tests_passed + 1))
	fi
}

pwd_no_existent_dir() {
	mkdir -p "prova"
	cd prova
	_cwd=$(pwd)
	rmdir $_cwd
	pwd >/dev/null 2>&1
	if [[ $? == 0 ]]; then
		tests_failed=$((tests_failed + 1))
		test_fail "No existent directory" "No existent directory does not return error"
	else
		tests_passed=$((tests_passed + 1))
		test_pass "basic pwd" "basic"
	fi
	return "$diff_err_code"
}

pwd_no_existent_dir() {
	local test_result
	(
		mkdir -p "prova"
		cd prova
		_cwd=$(pwd)
		rmdir $_cwd
		pwd >/dev/null 2>&1
		exit $? # Pass the pwd exit code to parent
	)
	test_result=$?

	if [[ $test_result == 0 ]]; then
		tests_failed=$((tests_failed + 1))
		test_fail "No existent directory" "No existent directory does not return error"
	else
		test_pass "No existent directory" "basic"
		tests_passed=$((tests_passed + 1))
	fi
}

clean_files() {
	rm -f $PWD_DIR/basic.txt $PWD_DIR/basic_real.txt
}

tests_passed=0
tests_failed=0
pwd_test
pwd_no_existent_dir
resume_test $tests_passed $tests_failed
clean_files
