# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    check_asm.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adauchy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/18 20:11:05 by adauchy           #+#    #+#              #
#    Updated: 2018/03/23 12:07:43 by yguzman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

PURPLE='\033[0;35m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

for file in files_test/*
do
echo "$YELLOW $file $NC";
valgrind ../asm -a $file 2>&1 | grep 'errors\|indir\|def' 
echo "\n\n"
done

