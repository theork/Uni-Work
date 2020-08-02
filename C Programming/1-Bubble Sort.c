#include <time.h>
exersise1(){
	int sorted = 0;
	int i, temp;
	int numbers[200];
	srand(time(NULL));
	for(i=0; i<200; i++){
		numbers[i] = rand() % 300;
	}
	
	for(i =0; i < 200; i++){
		printf("%d ", numbers[i]);
	}
	i=1;
	int swaps = 0;
	while(sorted == 0){	
		if(i == 200 && swaps > 0){
			i=1;
			swaps =0;
		}
		else if(i == 200 && swaps == 0){
			sorted = 1;
			break;
		}
		
		if(numbers[i-1] > numbers[i]){
			temp = numbers[i-1];
			numbers[i-1] = numbers[i];
			numbers[i] = temp;
			swaps++;
		}
		i++;
		
	}
	printf("\n\n\n");
	for(i =0; i < 200; i++){
		printf("%d ", numbers[i]);
	}

}
