#!/usr/bin/env bash

date
printf "\n"

for i in *.pal
do
	echo "$i"
	/usr/bin/time -v ../../final_code/wordmorph ../dic/portugues.dic $i
	printf "\n"
done

