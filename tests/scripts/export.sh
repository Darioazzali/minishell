#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    export.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/16 15:20:09 by dazzali           #+#    #+#              #
#    Updated: 2025/07/16 15:20:09 by dazzali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#

EXPORT_DIR=$(dirname "$0")
TEST_DIR="$EXPORT_DIR/../"
ROOT_DIR="$(dirname "$EXPORT_DIR")/.."
EXPORT="$ROOT_DIR/export"
source "$TEST_DIR/test_utils.sh"
make -C $ROOT_DIR "export" >/dev/null

echo_test() {
	$EXPORT
	if [ $? -eq 0 ]; then
		test_pass "Export test"
		tests_passed=$((tests_passed + 1))
	else
		test_fail "Failed"
		tests_failed=$((tests_failed + 1))
	fi

}

tests_passed=0
tests_failed=0
echo_test
resume_test $tests_passed $tests_failed

if [[ $tests_failed -gt 0 ]]; then
	exit 1
fi
