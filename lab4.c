#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_first_menu(){
	printf("1. Find all numbers in set range of values\n");
	printf("2. Quit\n");
}

void print_second_menu(){
	printf("1. Randomize numbers\n");
	printf("2. Add your own numbers\n");
	printf("3. Add numbers from file\n");
}

int getMenu(int num){
	int n;
	while (scanf("%d", &n) != 1 || n < 1 || n > num) {
		printf("Incorrect input. Try again: ");
		scanf("%*c");

	}

	return n;
}

void fillArRand(int **str, int *n){
	printf("How many numbers do u want?\n");
	int l;
	while (scanf("%d", &l) != 1 || l<0) {
		printf("Incorrect input. Try again: ");
		scanf("%*c");
	}
	*n = l;
	*str = (int *) malloc(l*sizeof(int));
	int i;
	for(i = 0; i<*n; i++) (*str)[i] = rand()%101;
}

void fillAr(int **str, int *n){
	printf("How many numbers do u want?\n");
	int l;
	while (scanf("%d", &l) != 1 || l<0) {
		printf("Incorrect input. Try again: ");
		scanf("%*c");
	}
	*n = l;	
	*str = (int *) malloc(l*sizeof(int));
	int i;
	printf("Input your numbers\n");
	for(i = 0; i<*n; i++){ 
		while (scanf("%d", &(*str)[i]) != 1) {
			printf("Incorrect input. Try again: ");
			scanf("%*c");
		}
	}
}
	
int *sort(int *str, int n){
	str = realloc(str,(2*n)*sizeof(int));
	int i, j = 0, tmp;
	for(i=0; i<n; i++) str[i+n] = str[i];
	for(i = 1; i<n; i++){
		for(j = i-1, tmp = str[i]; j>=0&&tmp<str[j]; str[j+1] = str[j], j--);
		str[j+1] = tmp;
	}
	return str;
}

void printAr(int str[], int begin, int end){
	int i;
	for(i = begin; i<end; i++) printf("%d ", str[i]);
	printf("\n");
}

void delete(int *str, int *n){
	int a, b, i = 0, j, left, right;
	printf("Input left edge\n");
	while (scanf("%d", &left) != 1) {
		printf("Incorrect input. Try again: ");
		scanf("%*c");
	}
	printf("Input right edge\n");
	while (scanf("%d", &right) != 1) {
		printf("Incorrect input. Try again: ");
		scanf("%*c");
	}
	
	while(str[i]<left) i++;
	a = i;
	if(str[*n-1]>right){
		while(str[i]<right) i++;
		b = i;
	}else{
		b = *n;
	}
	int l = *n-b+a;
	int d[l]; 
	for(i = 0; i<a; i++) d[i] = str[i];
	j = i;
	for(i = b; i<*n; i++, j++) d[j] = str[i];
	printf("Quantity of deleted numbers is %d\n", *n - l); 
	*n = l;
	printAr(d, 0, *n);
	
}	
int numberCount(FILE* input) {
	fseek(input, 0, 0);
	int counter = 0;
	while(1){
		int value;
		if (fscanf(input, "%d", &value) == 1) counter++;
		if (feof(input)) break;
	}
	return counter;
}
void read_numbers(FILE* input, int size, int* numbers) {
	fseek(input, 0, SEEK_SET);
	int i;
	for (i = 0; i < size; ++i) {
		fscanf(input, "%d", &numbers[i]);
	}
}

int main(){
	int in1, n, in2;
	int *str =NULL;
	
	do{
		print_first_menu();
		in1 = getMenu(2);
		switch(in1){
			case 1:
				print_second_menu();
				in2 = getMenu(3);
				switch(in2){
					case 1:
						printf("\n");
						fillArRand(&str, &n);
						printf("New array\n");
						printAr(str,0, n);
						printf("\n");
						str=sort(str, n);
						printf("Sorted array\n");
						printAr(str, 0, n);
						printf("Original array\n");
						printAr(str, n, 2*n);
						printf("\n");
						delete(str, &n);
						printf("\n");
					break;
					case 2:
						printf("\n");
						fillAr(&str, &n);
						printf("New array\n");
						printAr(str,0, n);
						printf("\n");
						str=sort(str, n);
						printf("Sorted array\n");
						printAr(str, 0, n);
						printf("Original array\n");
						printAr(str, n, 2*n);
						printf("\n");
						delete(str, &n);
						printf("\n");
					break;
					case 3:
						printf("\n");
						printf("Input file name\n");
						FILE *S;
						int i = 0;
						char file_name[200];
						scanf("%s", file_name);
						S = fopen(file_name, "r");
						if(S == NULL) printf("error\n");
						n = numberCount(S);
						str =(int *) calloc(n, sizeof(int));
						read_numbers(S, n, str);
						fclose(S);
						printf("New array\n");
						printAr(str,0, n);
						printf("\n");
						str=sort(str, n);
						printf("Sorted array\n");
						printAr(str, 0, n);
						printf("Original array\n");
						printAr(str, n, 2*n);
						printf("\n");
						delete(str, &n);
						printf("\n");
					break;
					default:
						printf("Should never be reached\n");
					break;
				}
			break;
			case 2:
			break;
			default:
				printf("Should never be reached\n");
			free(str);
		}
	}while(in1!=2);
	return 0;
}
