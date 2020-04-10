CC=g++

project_make: code.cpp glad.c
	$(CC) -o a.out code.cpp glad.c -lglfw3 -lGL -lpthread -ldl -lassimp