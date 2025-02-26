.SUFFIXES:         # remove all the implicit rules (avoid conflicts with our own rules)
.SECONDARY:        # all files are intermediate (keep them, otherwise they are removed)
.PHONY: all clean  # these targets are not files (even if a file named "all" or "clean" exists, the rule is applied)

LDFLAGS=
LIBS=
CFLAGS=-Wall -Werror -g
BIN_POKEMON=army-pokemon
BIN_ZOMBIE=army-zombie

all: $(BIN_POKEMON) $(BIN_ZOMBIE)

$(BIN_POKEMON): main.o monster.o army-pokemon.o
	gcc $(LDFLAGS) -o $@ $^ $(LIBS)

$(BIN_ZOMBIE): main.o monster.o army-zombie.o
	gcc $(LDFLAGS) -o $@ $^ $(LIBS)
 
army-%: main.o monster.o army.o
	gcc $(LDFLAGS) -o $@ $^ $(LIBS)

main.o: main.c monster.h army.h
	gcc $(CFLAGS) -o $@ -c $<

monster.o: monster.c monster.h
	gcc $(CFLAGS) -o $@ -c $<

army-pokemon.o: army-pokemon.c army.h monster.h
	gcc $(CFLAGS) -o $@ -c $<

army-zombie.o: army-zombie.c army.h monster.h
	gcc $(CFLAGS) -o $@ -c $<

%.o: %.c 
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(BIN_POKEMON) $(BIN_ZOMBIE) *.o *~