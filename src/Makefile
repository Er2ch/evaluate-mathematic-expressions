FILE = a.out
DEPS = lexer.o parser.o repl.o solve.o

ifdef DEBUG
 CFLAGS += -g
else
 CFLAGS += -O2
endif

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

$(FILE): $(DEPS)
	$(CC) $(CFLAGS) $^ -o $(FILE)

build: $(FILE)

clean:
	$(RM) $(FILE) $(DEPS)

debug:
	$(MAKE) DEBUG=1 clean build
	gdb $(FILE)

run: build
	-@echo -e "\n\n\n\n"
	./$(FILE)

all: build
