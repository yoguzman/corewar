# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    check_asm.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adauchy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/18 20:11:05 by adauchy           #+#    #+#              #
#    Updated: 2018/03/22 19:47:52 by adauchy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

PURPLE='\033[0;35m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

for file in *
do
echo "$YELLOW-------------------------------------------$NC"
echo "$YELLOW $file $NC";
echo "$PURPLE MINE ==> $NC"
../../asm $file
echo "$PURPLE RESSOURCE ==> $NC"
../../ressources/VM/asm ../files_test2/$file
echo "\n\n"
done

