#include <stdio.h>  
#include <unistd.h>  
#include <stdlib.h>
void showUsage(){
	printf("Usage: minicalc [-a num] [-d num] [-m num] [-x] value\n");
	exit(1);
}
int main(int argc, char* argv[])
{
    if(argc<3){
	showUsage();
    }
    int add = 1, sub = 1, div = 1, mul = 1, fpower=0;
    int fadd = 0, fsub = 0, fdiv = 0, fmul = 0;
    int value;
    int opt; 
    while ((opt = getopt(argc, argv, "a:d:m:s:x")) != -1)
    {
        switch (opt)
        {
        case 'a':
            fadd = 1;
            add = atoi(optarg);
            break;
        case 's':
            fsub = 1;
            sub = atoi(optarg);
            break;
        case 'd':
            fdiv = 1;
            div = atoi(optarg);
            break;
        case 'm':
            fmul = 1;
            mul = atoi(optarg);
            break;
        case 'x':
            fpower = 1;
            break;
        }
    }
    if(optind<argc)
    	value = atoi(argv[optind]);
    int invalid = 0;
    if (value < 1 || value >50)
        invalid = 1;
    if (mul < 1 || mul>5)
        invalid = 1;
    if (div < 1 || div>5)
        invalid = 1;
    if (add < 1 || add>500)
        invalid = 1;
    if (sub < 1 || sub>500)
        invalid = 1;
    if (invalid == 1) {
        showUsage();
    }
    if (fpower) {
        value = value * value;
    }
    float result = value;
    if (fmul) {
        result = value * mul;
    }
    if (fdiv) {
        result =(float) (div/result) ;
    }
    if (fadd) {
        result = result + add;
    }
    if (fsub) {
        result = result - sub;
    }
    printf("Answer: %.2f\n", result);
    return 0;
}
