#!/usr/bin/env bash

date
printf "\n"

for i in *.pal
do
	echo "$i"
	/usr/bin/time -v ../../proto/wordmorph ../dic/portugues.dic $i
	printf "\n"
done

