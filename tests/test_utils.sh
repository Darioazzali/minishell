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
