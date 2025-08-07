#!/bin/bash

source $(dirname $0)/../test_utils.sh
exit_code=0

for test_file in *.exp; do
	if [[ test_file == common.exp ]]; then
		continue
	fi
	expect "$test_file"
	if [ $? -ne 0 ]; then
		exit_code=1
		printf "${RED}FAIL${NORMAL}\n"
		exit 1
	fi
done

if [[ $exit_code -ne 0 ]]; then
	printf "${RED}FAIL${NORMAL}\n"
fi
exit $exit_code
