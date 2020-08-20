compile:
	gcc -I ./ main.c -o main

dump:
	xxd -l 20 JimTopia.sc2

run:
	./main
