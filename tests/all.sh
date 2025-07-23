#/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    all.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 17:30:24 by dazzali           #+#    #+#              #
#    Updated: 2025/07/26 09:52:20 by dazzali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#/bin/bash

_this_dir=$(dirname $0)
SCRIPT_DIR="$_this_dir/scripts/"
source ${_this_dir}/test_utils.sh
tests_passed=0
tests_failed=0
tests_total=0
failed_tests=()

VERBOSE=${VERBOSE:-false}
QUIET=${QUIET:-false}
SHOW_SUMMARY=${SHOW_SUMMARY:-true}
ALL_TESTS=("echo"
	"pwd"
	"expansion"
	"tokenizer"
	"quote_removal"
	"token_recognition"
	"export"
	"cd"
	"execute_command"
	"ast")

# Check if single test is requested
TESTS_TO_RUN=("${ALL_TESTS[@]}")
if [[ -n "$1" ]]; then
	# Check if the provided test name is valid
	if [[ " ${ALL_TESTS[*]} " =~ " $1 " ]]; then
		TESTS_TO_RUN=("$1")
		printf "${BOLD}${YELLOW}Running single test: $1${NORMAL}\n"
	else
		printf "${RED}Error: Test '$1' not found${NORMAL}\n"
		printf "Available tests: ${ALL_TESTS[*]}\n"
		exit 1
	fi
fi

make_test() {
	local test_name=$1
	printf "${BOLD}${BLUE}Running ${test_name} tests${NORMAL}\n"
	(cd $SCRIPT_DIR && ./${test_name}.sh)
}
run_test() {
	local test_name=$1
	local test_script="${SCRIPT_DIR}${test_name}.sh"

	printf "${BOLD}${BLUE}Running ${test_name} tests...${NORMAL} "

	# Check if test script exists and is executable
	if [[ ! -f "$test_script" ]]; then
		printf "${RED}MISSING${NORMAL}\n"
		printf "  Test script not found: $test_script\n"
		failed_tests+=("$test_name (missing)")
		((tests_failed++))
		return 1
	fi

	if [[ ! -x "$test_script" ]]; then
		chmod +x "$test_script"
	fi

	# Run the test and capture output
	local output
	local exit_code=0

	if output=$(cd "$SCRIPT_DIR" && "./${test_name}.sh" 2>&1); then
		printf "${GREEN}PASS${NORMAL}\n"
		((tests_passed++))
	else
		exit_code=$?
		printf "${RED}FAIL${NORMAL} (exit code: $exit_code)\n"

		# Show the error output indented
		if [[ -n "$output" ]]; then
			printf "  ${RED}Output:${NORMAL}\n"
			echo "$output" | sed 's/^/  /'
		fi

		failed_tests+=("$test_name")
		((tests_failed++))
		return $exit_code
	fi
}

show_summary() {
	local tests_total=$((tests_passed + tests_failed))

	echo
	printf "${BOLD}=== Test Results ===${NORMAL}\n"
	printf "Total tests: %d\n" "$tests_total"
	printf "${GREEN}Passed: %d${NORMAL}\n" "$tests_passed"
	printf "${RED}Failed: %d${NORMAL}\n" "$tests_failed"

	if [[ ${#failed_tests[@]} -gt 0 ]]; then
		printf "\n${RED}Failed tests:${NORMAL}\n"
		for test in "${failed_tests[@]}"; do
			printf "  - %s\n" "$test"
		done
	fi

	# Show success rate
	if [[ $tests_total -gt 0 ]]; then
		local success_rate=$((tests_passed * 100 / tests_total))
		printf "\nSuccess rate: %d%%\n" "$success_rate"
	fi
}
printf "${BOLD}Starting test suite...${NORMAL}\n"

for test_name in "${TESTS_TO_RUN[@]}"; do
	run_test "$test_name" || true # Don't exit on individual test failure
done

show_summary

if [[ $tests_failed -gt 0 ]]; then
	exit 1
else
	printf "\n${GREEN}${BOLD}All tests passed!${NORMAL}\n"
	exit 0
fi
