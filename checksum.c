#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int xCount = 0;

unsigned char _8bitCheckSum(FILE * fptr) {

	char buff[200];
	unsigned char checkSum = 0;


	while (fgets(buff, 100, fptr)) {

	
		int size = strlen(buff);
		int i = 0;
		for (i; i < size; i++) {

			checkSum += (unsigned char)buff[i];

		}

	}

	return checkSum; 
}

unsigned short _16bitCheckSum(FILE * fptr) {

	unsigned short checkSum = 0;
	char c1 = EOF;
	char c2 = EOF;
	while ((c1 = getc(fptr)) != EOF) {

		unsigned short temp = 0;
		



		if ((c2 = fgetc(fptr)) == EOF) {
			c2 = 'X';
			xCount++;
			printf("i am in\n");
		}
		
		temp = (c1 << 8) | c2;
		checkSum += temp;


	}

	return checkSum;
}

unsigned int _32bitCheckSum(FILE * fptr) {

	unsigned int checkSum = 0;
	char c1 = EOF;
	char c2 = EOF;
	char c3 = EOF;
	char c4 = EOF;
	while ((c1 = getc(fptr)) != EOF) {

		unsigned int temp = 0;




		if ((c2 = fgetc(fptr)) == EOF) {
			c2 = 'X';
			xCount++;
			c3 = 'X';
			xCount++;
			c4 = 'X';
			xCount++;
			break;
			printf("i am in\n");
		}


		if ((c3 = fgetc(fptr)) == EOF) {
			c3 = 'X';
			xCount++;
			c4 = 'X';
			xCount++;
			break;
			printf("i am in\n");
		}

		if ((c4 = fgetc(fptr)) == EOF) {
			c4 = 'X';
			xCount++;
			break;
			printf("i am in\n");
		}


		
		temp = (c1 << 24)| (c2 << 16) | (c3 << 8) | c4;
		checkSum += temp;


	}

	return checkSum;
}


int display(FILE * fptr) {

	int count = 0;
	char c;
	int i = 0;
	int flag = 1;
	printf("\n");
	while (flag == 1) {
		i = 0;
		for (i; i < 80; i++) {

			c = fgetc(fptr);

			if (feof(fptr)) {
				flag = 0;
				break;

			}
			if (c != '\n') {
				printf("%c", c);
			}
			count++;
		}
		printf("\n");
	}

	for (; xCount > 0; xCount--) {
		printf("X");
		count++;
	}
	printf("\n");
	
	
	return count;
}


int main(int argc, char * * argv) {


	if (argc != 3) {
		printf("Invalid arguments entered!!\n");
		return -1;
	}

	char * filename = argv[1];
	char * size = argv[2];
	int checkSumSize = atoi(size);

	if (checkSumSize != 8 && checkSumSize != 16 && checkSumSize != 32) {
		fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
		return -1;
	}
	FILE * fptr = fopen(filename, "r");
	if (fptr == NULL) {
		printf("Cannot open the specified file!!\n");
		return -1;
	}

	if (checkSumSize == 8) {
		unsigned char checkSum_8 = _8bitCheckSum(fptr);
		fseek(fptr, 0, SEEK_SET);
		int characterCount = display(fptr);
		printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize,(unsigned long int)checkSum_8, characterCount);
	}
	else if(checkSumSize == 16) {
		unsigned short checkSum_16 = _16bitCheckSum(fptr);
		fseek(fptr, 0, SEEK_SET);
		int characterCount = display(fptr);
		printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize,(unsigned long int)checkSum_16, characterCount);
	}
	else if (checkSumSize == 32) {
		unsigned int checkSum_32 = _32bitCheckSum(fptr);
		fseek(fptr, 0, SEEK_SET);
		int characterCount = display(fptr);
		printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, (unsigned long int)checkSum_32, characterCount);
	}

	fclose(fptr);
	return 0;
}			 

