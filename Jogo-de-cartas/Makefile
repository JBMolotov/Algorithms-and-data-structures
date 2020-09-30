all: clean
	@g++ -o main pilha.h pilha.c main.c -lglut -lGLU -lGL -lm
run: all 
	./main
clean:
	rm main || true
