#/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run_tests.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 17:34:41 by dazzali           #+#    #+#              #
#    Updated: 2025/06/05 17:34:41 by dazzali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#

(cd "$(dirname $0)/tests" && ./all.sh)
