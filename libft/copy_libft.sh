#!/bin/bash
echo "$PWD"
libft_dir=$(dirname $0)

rsync -avz $libft_dir $PWD --exclude .git --exclude-from=$libft_dir/exclude.txt
