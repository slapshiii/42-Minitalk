#!/bin/sh

for i in `seq 1 200`; do
	./client $1 "$(cat -e Makefile)"
	echo "req $i"
done
