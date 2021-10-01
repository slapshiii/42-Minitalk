#!/bin/sh

for i in `seq 1 5000`; do
	./client $1 "test"
	echo "req $i"
done

./client $1 $'\n'

for i in `seq 1 20`; do
	./client $1 "$(cat -e Makefile)"
	echo "req $i"
done

./client $1 $'\n'

for i in `seq 1 50`; do
	./client $1 💯
	echo "req $i"
done

./client $1 $'\n'

for i in `seq 1 50`; do
	./client $1 𐏀𐎬𐏂
	echo "req $i"
done

./client $1 $'\n'
