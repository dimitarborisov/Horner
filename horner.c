#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_array(int* arr, int capacity);
void print_array_float(float* arr, int capacity);
int find_multipliers(int* arr,int number);
float fix_div(float* arr, float number, int count);
void human_read_answers(float* arr, int count);
int add_negatives(float* arr, int count);

int main(void){
	int highest_degree = 0;
	//read how many numbers there are going to be by asking for the highest degree number
	printf("Enter highest degree number: ");
	scanf("%d",&highest_degree);
	
	printf("Highest degree is: %d \n",highest_degree);
	
	//allocate appropriate amount of memory for all the numbers to be stored
	int i = 0;
	int* numbers = (int*) malloc(sizeof(int) * (highest_degree + 1));	
	
	//read all numbers
	for(i = highest_degree; i >= 0; i--){
		printf("Enter %d degree number: ", i);
		scanf("%d",numbers+i);
	}	
	
	//print_array(numbers, highest_degree + 1);	
	
	
	//find all multiplier for the first and last number	
	int* highest_degree_multiplier = malloc(sizeof(int) * abs(*(numbers + highest_degree)));
	int* smallest_degree_multiplier = malloc(sizeof(int) * abs(*(numbers)));	
	float* answers = malloc(sizeof(float) * (highest_degree + 1));		
	int answer_count = 0;

	int hdm_count = find_multipliers(highest_degree_multiplier, *(numbers + highest_degree));
	int sdm_count = find_multipliers(smallest_degree_multiplier, *(numbers));

	//allocate memory for all divisors, *2 because of negative counterparts
	float* divisors = malloc(sizeof(float) * (hdm_count + sdm_count) * 2);
 
	//print_array(highest_degree_multiplier, hdm_count);
	//printf("\n");
	//print_array(smallest_degree_multiplier, sdm_count);
	i = 0;
	int j = 0;
	int count = 0;
	for(i = 0; i < sdm_count; i++){
		for(j = 0; j < hdm_count; j++){
			count = fix_div(divisors, (float) *(smallest_degree_multiplier + i) / *(highest_degree_multiplier + j), count);
		}
	}
	count = add_negatives(divisors, count);	
	

	//start of algorithm
	float first_num = 0;
	float answer = 0;
	for(i = 0; i < count; i++){
		first_num = *(numbers + highest_degree);

		for(j = highest_degree; j > 0; j--){
			answer = (first_num * *(divisors + i)) + *(numbers + j - 1);
			first_num = answer;
		}
		//printf("DEBUG::: devisor[%f] answer[%f]\n", *(divisors + i), fabs(answer));	
		if( (int)fabs(answer) == 0){
			//printf("[%f]\n", *(divisors + i));
			*(answers + answer_count) = *(divisors + i);
			answer_count++;
		}	
	}

	human_read_answers(answers, answer_count);
			
	free(highest_degree_multiplier);
	free(smallest_degree_multiplier);
	free(numbers);
	
	return 0;
}

//adds a negative number for all existing numbers in the array, returns the count
int add_negatives(float* arr, int count){
	int i = 0;
	int old_count = count;
	for(i = 0; i < old_count; i++){
		*(arr + count) = -1 * *(arr + i);
		count++;
	}
	
	return count;
}

//prints the answers in easy to read form
void human_read_answers(float* arr, int count){
	int i = 0;
	for(i = 0; i < count; i++){
		printf("(x%+.2f) ",(-1 * *(arr + i)));
	}
	
	if(count == 0){
		printf("no real roots :(");
	}

	printf("\n");
}

//writes down the given number into the array if the numbers is not already there. returns the size of the array
float fix_div(float* arr, float number, int count){
	int inside = 0;
	int i = 0;
	for(i = 0; i < count; i++){
		if(*(arr + i) == number){
			inside = 1;
		}
	}

	if(!inside){
		*(arr + count) = number;
		count++;
	}
	return count;
}


//finds all multipliers for a given number, saves them in *arr and returns their number
int find_multipliers(int* arr, int number){
	int count = 0;
	int i = 1;
	
	number = abs(number);	

	while(i <= number){
		if(number % i == 0){
			*(arr + count) = i;
			count++;
		}
		i++;
	}

	return count;
}

//prints what is in the array
void print_array_float(float* arr, int capacity){
	int i = 0;
	for(i = 0; i < capacity; i++){
		printf("Eelement[%d] is: %f\n", i, *(arr + i));
	}
}

//prints what is in the array
void print_array(int* arr, int capacity){
	int i = 0;
	for(i = 0; i < capacity; i++){
		printf("Eelement[%d] is: %d\n", i, *(arr + i));
	}
}
