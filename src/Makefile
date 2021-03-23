FILE = calc
DEPS_BASE = clex.o cpar.o cvm.o
DEPS_ADD = calc.o crepl.o

AR = ar rcs
RANLIB = ranlib

ifdef DEBUG
 CFLAGS += -g -D DEBUG
else
 CFLAGS += -O2
endif

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# NOTE: Library must be at end!
## https://stackoverflow.com/a/10421543
$(FILE): $(DEPS_ADD) lib$(FILE).a
	$(CC) $(CFLAGS) $^ -o $(FILE)

lib$(FILE).a: $(DEPS_BASE)
	$(AR) $@ $^
	$(RANLIB) $@

build: $(FILE)
lib: lib$(FILE).a

clean:
	$(RM) $(FILE) lib$(FILE).a $(DEPS_BASE) $(DEPS_ADD)

debug:
	$(MAKE) DEBUG=1 clean build
	gdb $(FILE)

run: build
	-@echo -e "\n\n\n\n"
	./$(FILE)

all: build
