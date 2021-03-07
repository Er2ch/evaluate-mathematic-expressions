FILE=a.out
DEPS = main.c \
 lexer/check_valid.c lexer/data.c lexer/lexer.c \
 parser/data.c parser/find_divider_pos.c parser/free_tree.c parser/parser.c \
 solve/mini.c solve/solve.c

$(FILE): $(DEPS)
	gcc main.c -O2 -o $(FILE)

run: all
	-@echo -e "\n\n\n\n"
	./$(FILE)

all: $(FILE)
build: all