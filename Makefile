FLAGS = -g -lm -Wall -Werror -Wextra
WORKDIR = src
COMMONDIR = $(WORKDIR)/common
TESTDIR = $(WORKDIR)/test
FUNCDIR = $(WORKDIR)
BUILD =$(WORKDIR)

all: test clean_obj

test: string_test.o sprintf_test.o libs
	gcc $(FLAGS) -o $(BUILD)/string_test $(BUILD)/string_test.o \
	-L./src -lcommon -ls21_string -I.
	gcc $(FLAGS) -o $(BUILD)/sprintf_test $(BUILD)/sprintf_test.o \
	-L./src -lcommon -ls21_string -I.
	
libs: libcommon.a libs21_string.a

sprintf_test.o:
	gcc -c $(TESTDIR)/sprintf_test.c $(FLAGS) -o \
	$(BUILD)/sprintf_test.o
string_test.o:
	gcc -c $(TESTDIR)/string_test.c $(FLAGS) -o \
	$(BUILD)/string_test.o
s21_cs_string.o:
	gcc -c $(FUNCDIR)/s21_cs_string.c $(FLAGS) -o \
	$(BUILD)/s21_cs_string.o
s21_string.o:
	gcc -c $(FUNCDIR)/s21_string.c $(FLAGS) -o \
	$(BUILD)/s21_string.o
s21_sprintf.o:
	gcc -c $(FUNCDIR)/s21_sprintf.c $(FLAGS) -o \
	$(BUILD)/s21_sprintf.o
common.o: 
	gcc -c $(COMMONDIR)/file.c $(FLAGS) -o \
	$(BUILD)/file.o
	gcc -c $(COMMONDIR)/log.c $(FLAGS) -o \
	$(BUILD)/log.o

libcommon.a: common.o
	ar cr $(BUILD)/libcommon.a $(BUILD)/file.o $(BUILD)/log.o
libs21_string.a: s21_string.o s21_cs_string.o s21_sprintf.o
	ar cr $(BUILD)/libs21_string.a $(BUILD)/s21_string.o $(BUILD)/s21_cs_string.o $(BUILD)/s21_sprintf.o

rebuild: clean all
clean_obj:
	rm -rf $(BUILD)/*.o $(BUILD)/*.a
clean: 
	rm -rf $(BUILD)/string_test $(BUILD)/sprintf_test