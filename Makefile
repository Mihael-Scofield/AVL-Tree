# Makefile

CC = gcc
CFLAGS = -Wall -g # Flags para compilação.
# LDLIBS = -lSDL2 -lSDL2_gfx -lm

objects = myavl.o manipulacao_avl.o
arq = myavl.c manipulacao_avl.c

# Regra default
all: myavl

# Remove arquivos temporários
clean:
	-rm -f *~ *.o

# Remove tudo o que não for código-fonte original
purge: clean
	-rm -f myavl

myavl: $(objects)
	$(CC) $(CFLAGS) $(arq) -o myavl #$(LDLIBS)