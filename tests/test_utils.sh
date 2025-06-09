#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_utils.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 16:52:24 by dazzali           #+#    #+#              #
#    Updated: 2025/06/05 16:52:24 by dazzali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED="\e[31m"
GREEN="\e[32m"
BLUE="\e[34m"
NORMAL="\e[0m"
BOLD="\033[1m"
HEAVY_BALLOT='\xE2\x9C\x97'
CHECKMARK='\xE2\x9C\x93'
ARROW='\xE2\x9E\x9D'

print_in_red() {
	printf "${RED}%b${NORMAL}" "$1"
}
print_in_green() {
	printf "${GREEN}%b${NORMAL}" "$1"
}

test_fail() {
	test_name=$1
	description=$2
	RED_HEAVY_BALLOT="${RED}${HEAVY_BALLOT}${NORMAL}"
	printf "${RED_HEAVY_BALLOT} ${test_name}\n${BOLD}${RED}Cause:\n${NORMAL}${description} \n"
}

test_pass() {
	test_name=$1
	description=$2
	printf "${GREEN}${CHECKMARK}${NORMAL} ${test_name} - ${description}\n"
}

resume_test() {
	local tests_passed=$1
	local tests_failed=$2
	local tests_count=$((tests_passed + tests_failed))
	if [[ $tests_failed -eq 0 ]]; then
		printf "${BOLD}${GREEN}ALL Tests passed${NORMAL} $tests_passed/$tests_count\n"
		return
	else
		printf "${BOLD}${GREEN}Tests passed: ${tests_passed}${NORMAL}\n"
		printf "${BOLD}${RED}Tests failed: ${tests_failed}${NORMAL}\n"
	fi
}
