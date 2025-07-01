#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    cd.sh                                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/18 11:15:10 by dazzali           #+#    #+#              #
#    Updated: 2025/07/18 11:15:10 by dazzali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#
CD_DIR=$(dirname "$0")
TEST_DIR="$CD_DIR/../"
ROOT_DIR="$(dirname "$CD_DIR")/../"
_CD="$ROOT_DIR/cd"
source "$TEST_DIR/test_utils.sh"
make -C $ROOT_DIR "cd" >/dev/null

builtin_cd() {
	$_CD
	err_code=$?
	if [[ $err_code -ne 0 ]]; then
		test_fail "cd"
		tests_failed=$((tests_failed + 1))
	else
		test_pass "cd"
		tests_passed=$((tests_passed + 1))
	fi
	return "$err_code"
}

tests_passed=0
tests_failed=0
builtin_cd
