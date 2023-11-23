WORKDIR = ..
FUNCDIR = $(WORKDIR)/string_funcs
COMMONDIR = $(WORKDIR)/common
BUILD = $(WORKDIR)/build
FILES = $(FUNCDIR)/s21_mem*.c $(FUNCDIR)/s21_str*.c $(COMMONDIR)/log.c $(COMMONDIR)/file.c

all: main
main:
	gcc $(FILES) string_test.c -o $(BUILD)/string_test -D string
rebuild: clean all
clean:
	rm -rf $(BUILD)/*