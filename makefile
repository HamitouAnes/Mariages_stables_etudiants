all : main 
	
main : fonctions.c fonctions.h main.c
	gcc -Wall fonctions.c fonctions.h main.c  -o main
