#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 16:31:07 by dazzali           #+#    #+#              #
#    Updated: 2025/06/09 19:32:59 by dazzali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ECHO_DIR=$(dirname "$0")
TEST_DIR="$ECHO_DIR/../"
ROOT_DIR="$(dirname "$ECHO_DIR")/../.."
ECHO="$ROOT_DIR/echo"
source "$TEST_DIR/test_utils.sh"
make -C $ROOT_DIR echo >/dev/null

compare_echos() {
	local original=$2
	local ours=$1
	$ECHO "$ours" >$ECHO_DIR/basic.txt
	echo "$original" >$ECHO_DIR/basic_real.txt
	diff "$ECHO_DIR/basic.txt" "$ECHO_DIR/basic_real.txt" >"$ECHO_DIR/.fail_res"
	diff_err_code=$?
	if [[ $diff_err_code -ne 0 ]]; then
		test_fail "basic echo" "$(cat $ECHO_DIR/.fail_res)"
	else
		test_pass "basic echo" "$original"
	fi
	return "$diff_err_code"
}

echo_test() {
	original=$2
	ours=$1
	compare_echos "$ours" "$original"
	if [[ $? -ne 0 ]]; then
		tests_failed=$((tests_failed + 1))
	else
		tests_passed=$((tests_passed + 1))
	fi
}

clean_up_files() {
	rm -f $ECHO_DIR/basic.txt $ECHO_DIR/basic_real.txt
}

printf "${BOLD}${BLUE}Running echo tests${NORMAL}\n"
tests_passed=0
tests_failed=0
echo_test "hello" "hello"
echo_test "" ""
echo_test "-n" "-n"
echo_test "-n hello" "-n hello"
echo_test "$SHELL" "$SHELL"
resume_test $tests_passed $tests_failed
clean_up_files
