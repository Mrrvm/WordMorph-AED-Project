#!/usr/bin/env bash

for i in *.pal
do
	echo "$i"
	/usr/bin/time -v ../../not_saving_problems_NO_Abstract_types/wordmorph ../dic/portugues.dic $i
	printf "\n"
done

