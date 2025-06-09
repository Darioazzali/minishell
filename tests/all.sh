# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    all.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 17:30:24 by dazzali           #+#    #+#              #
#    Updated: 2025/06/09 19:24:33 by dazzali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#/bin/bash

_this_dir=$(dirname $0)
ECHO_DIR="$_this_dir/echo/"
PWD_DIR="$_this_dir/pwd/"
(cd $ECHO_DIR && ./test.sh)
(cd $PWD_DIR && ./test.sh)
