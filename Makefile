FLAGS = -g -lm
WORKDIR = src
SPRINTFDIR = $(WORKDIR)/sprintf
COMMONDIR = $(WORKDIR)/common
TESTDIR = $(WORKDIR)/test
STRDIR = $(WORKDIR)/string_funcs
CSDIR = $(WORKDIR)/cs_funcs
BUILD =$(WORKDIR)/build
FILES=$(STRDIR)/s21_mem*.c \
     $(STRDIR)/s21_str*.c \
 $(COMMONDIR)/log.c \
$(COMMONDIR)/file.c

all: string_test sprintf_test

string_test: string_test.o libs
	gcc $(FLAGS) -o $(BUILD)/string_test $(BUILD)/string_test.o \
	$(BUILD)/common.so $(BUILD)/s21_string.so -Wl,-rpath,.
sprintf_test: sprintf_test.o libs s21_string.so
	gcc $(FLAGS) -o $(BUILD)/sprintf_test $(BUILD)/sprintf_test.o \
	$(BUILD)/common.so $(BUILD)/s21_sprintf.o \
	$(BUILD)/s21_string.so -Wl,-rpath,.
libs: common.so s21_string.so s21_sprintf.o

sprintf_test.o:
	gcc -c -fPIC $(TESTDIR)/sprintf_test.c $(FLAGS) -o \
	$(BUILD)/sprintf_test.o
string_test.o:
	gcc -c -fPIC $(TESTDIR)/string_test.c $(FLAGS) -o \
	$(BUILD)/string_test.o
s21_sprintf.o:
	gcc -c -fPIC $(SPRINTFDIR)/s21_sprintf.c $(FLAGS) -o \
	$(BUILD)/s21_sprintf.o
s21_string.o:
	gcc -c -fPIC $(STRDIR)/s21_*.c $(FLAGS)
common.o: 
	gcc -c -fPIC $(COMMONDIR)/*.c $(FLAGS)

common.so: common.o
	gcc -shared -o $(BUILD)/common.so *.o
	rm -rf *.o
s21_string.so: s21_string.o
	gcc -shared -o $(BUILD)/s21_string.so s21_*.o
	rm -rf s21_*.o

rebuild: clean all clean_obj
clean_obj:
	rm -rf $(BUILD)/*.o
clean:
	rm -rf $(BUILD)/*