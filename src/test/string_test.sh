#!/bin/sh

common_strings=(Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.)

functions=(memchr memcmp memcpy memmove memset strcat strncat strchr strcmp strncmp strcpy strncpy strcspn strerror strlen strpbrk strrchr strspn strstr strtok)

current_str=""
str1=""
str2=""
size=0
sym=0
func_num=0

function get_str {
	array_size=${#common_strings[*]}
	randomNumber=$[ $RANDOM % $array_size + 1]
	current_str=${common_strings[$randomNumber]}
}

function get_str_str {
	max_words=$[ $RANDOM % 10 + 1]
	for i in `seq $[ $RANDOM % $max_words ]`
	do
		get_str
		str1+=" ${current_str}"
		get_str
		str2+=" ${current_str}"
	done
}

function get_args {
	get_str_str
	united_str=$str1$str2
	size=$[ $RANDOM % (${#united_str}+1)]
	sym=$[ $RANDOM % 256 ]
	func_num=$[ $RANDOM % 20 + 1 ]
}

function clear_vars {
	current_str=""
	str1=""
	str2=""
	size=0
	sym=0
	func_num=0
}

make rebuild

for test in `seq $[ $1 * 20 ]`
do
	get_args
	
	valgrind --tool=memcheck --leak-check=yes --quiet --leak-resolution=high --error-exitcode=1 ../build/string_test $[ $test % 21 ] "$str1" "$str2" $size $sym "$str1" "$str2"

	echo -e "$(diff -s recieved.txt expected.txt) "
    if [[ !(result -eq 0) || $(diff -q recieved.txt expected.txt) ]]
	then
		echo "____________________________________________________________"
		printf "%s " "The wrong function is"
		printf "%s\n" ${functions[$test % 21 - 1]}
		printf "%s" "Executed command: ./string_test " 
		printf "%d " $test
		printf "%s " \"$str1\"
		printf "%s " \"$str2\"
		printf "%d " $size 
		printf "%d\n" $sym
		echo "____________________________________________________________"
		exit
	else
	printf "function: %s\n\n" ${functions[$test % 20 - 1]}
	fi

	clear_vars
done