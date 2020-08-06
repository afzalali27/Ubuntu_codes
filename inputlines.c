#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int foo(char* s) {
	int valid = 1;
	int len = strlen(s);
	if (len < 3)
		return 0;
	int i = 0;
	if (s[i] == 'E') { 
		i++;
		if (s[i] == '0' || s[i] == '1' || s[i] == '2')
		{
			while (s[i] == '0' || s[i] == '1' || s[i] == '2')
				i++;
			if (s[i] != 'F' || i+1!=len)
				valid = 0;
		}
		else
			valid = 0;
	}
	else
		valid = 0;
	return valid;
}
int eep(char* s) {
	int valid = 1;
	int len = strlen(s);
	//printf("len %d\n", len);
	if (len < 1 || len == 2)
		return 0;
	if (len == 1 && s[0] == 'P')
		return 1;
	int i = 0;
	if (s[i] == 'P') {
		i++;
		while ((i < len) && s[i] == 'B' && s[i + 1] == 'C')
			i+=2;
		if (i==len)
			valid = 1;
		else
			valid = 0;
	}
	else
		valid = 0;
	return valid;
}
int op(char* s) {
	int valid = 1;
	int len = strlen(s);
	if (len < 2 )
		return 0;
	int i = 0;
	int count = 0;
	if (s[i] == 'Q') {
		i++;
		if (s[i] == '6' || s[i] == '7') {
			while (s[i] == '6' || s[i] == '7') {
				if (s[i] == '7')
					count++;
				i++;
			}
			if (i == len)
				valid = 1;
			else
				valid = 0;
		}
		else
			valid = 0;
	}
	else
		valid = 0;
	if ((valid==1) && (count == 0 || count % 2 != 0))
		valid = 1;
	else
		valid = 0;
	return valid;
}
int ork(char* s) {
	int valid = 1;
	int len = strlen(s);
	if (len < 4)
		return 0;
	int i;
	if (s[0] == 'M' && (s[1] >= '0' && s[1] <= '9') && (s[2] >= '0' && s[2] <= '9')) {
		char* ss = malloc((len - 2) * sizeof(char));
		int j = 0;  
		// copy string to check for foo or eep
		for (i = 3; i < len; i++) {
			ss[j] = s[i];
			j++;
		}
		ss[j] = 0;
		valid = foo(ss); // if not foo , check for eep
		if (valid != 1)
			valid = eep(ss);
		// free up the memory
		free(ss);
	}
	else
		valid = 0;
	return valid;
}
int main(int argc, char** argv)
{
	FILE* fp = NULL;
	char* buff = NULL;
	size_t len = 0;

	if (argc > 1)
	{
		fp = fopen(argv[1], "r");

		if (fp == NULL)
		{
			fprintf(stderr, "Can not open %s for reading.\n", argv[1]);
			exit(1);
		}
	}
	else
		fp = stdin;
	int valid;
	/* read manpage for getline.  it allocates and reallocates, as needed
	 * You free  */
	while (getline(&buff, &len, fp) != -1)
	{
		buff[strlen(buff) - 1] = '\0';  /* Overwrite the newline */
		//printf("%lu chars at %p (len %lu): %s\n", strlen(buff), buff, len, buff);
		if (foo(buff) == 1)
			valid = 1;
		else if (eep(buff) == 1)
			valid = 1;
		else if (op(buff) == 1)
			valid = 1;
		else if (ork(buff) == 1)
			valid = 1;
		else
			valid = 0;
		if (valid == 1)
			printf("OK\n");
		else
			printf("FAIL\n");

	}

	free(buff);  /* No memory leaks! */

	buff = NULL;  /* pedantic */
	len = 0;

	return(0);
}

