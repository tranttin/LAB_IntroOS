/*  This program implements the following disck-scheduling algorithms:
FCFS, SSTF, SCAN, C-SCAN, LOOK, and C-LOOK
The program services a disk of 5,000 cylinders numbered 0 to 4999.
It generates a random series of 1000 cylinder requests and services 
them according to each of he algorithms listed above. The program
will be passed the initial position of the disk head (as a parameter
on the command line) and report the total amount of head movement 
required by each algorithm. 
To run:
gcc -o diskAlgorithms diskAlgorithms.c
./file_name followed by number from 0-4999 for index (see below for example)
./diskAlgorithms 423
*/


#include <stdio.h>
#include <stdlib.h>

#define CYLINDERS 5000
#define REQUESTS 1000

int start = 0;

int ran_array[REQUESTS];
int test_array[REQUESTS];

int* sort_array() {

	int temp = 0, i = 0, j = 0;

	for (i = 0; i < REQUESTS; ++i) {

       	for (j = i + 1; j < REQUESTS; ++j) {

            if (ran_array[i] > ran_array[j]) {

                temp =  ran_array[i];
                ran_array[i] = 	ran_array[j];
                ran_array[j] = temp;
            }
        }
    }

    return ran_array;
}


/* First-Come-First-Serve (fcfs) starts from the index after the starting
index and continually adds the headmovement from the starting index in 
order recieved. If at end of array, start from index zero and continually 
add until starting index */
int fcfs(int *ran_array) {

	int i = 0, head_movement = 0, this_start = ran_array[start];

    for(i = start; i < REQUESTS; i++) {

    	head_movement += abs(ran_array[i] - this_start);
    }

    for(i = 0; i < start; i++) {

    	head_movement += abs(this_start - ran_array[i]);
    }
        
    return head_movement;
}

/* Shortest-Seek-Time-First (SSTF) takes the current head position, and
adds the position closest to the current head. This new position now becomes
the head, then this system repeats. 
First we sort the array. Then We have counters for above and below start 
index that we decrement if used. Once these equal to REQUEST-2 (excluding 
start index) we exit. */
int sstf(int * ran_array) {

	ran_array = sort_array();

	int small_i = start-1, large_i = start+1;
	int small_diff = 0, large_diff = 0;
	int head_movement = 0, total = REQUESTS-2, new_head = start, head_value = ran_array[start];
	
	while(total >= 0) {

		small_diff = abs(ran_array[new_head] - ran_array[small_i]);
		large_diff = abs(ran_array[large_i] - ran_array[new_head]);

		if(small_diff < large_diff) {

			head_movement += small_diff;
			new_head = small_i;
			small_i--;
			
		} else {

			head_movement += large_diff;
			new_head = large_i;
			large_i++;
		}

		total--;

	}

	return head_movement;

}

/* SCAN - array is already sorted from sstf. SCAN starts from one left of start, 
and continually goes down to zero (if included in randome array or not). Then 
starts at one higher than start and continually goes up to highest value (not 5000) */
int scan(int * ranArray) {

	int i = 0, curr_val = 0, sav_val = ran_array[start], difference = 0;
	int head_movement = 0, curr_i = 0;

	for(i = start-1; i >= 0; --i) {

		curr_val = ran_array[i];
		difference = abs(sav_val - curr_val);
		head_movement += difference;
		sav_val = curr_val;

	}

	/* used to subtract value from zero, or just add same value */
	head_movement += sav_val;
	sav_val = 0;

	for(i = start+1; i < REQUESTS; i++) {

		curr_val = ran_array[i];
		difference = abs(curr_val - sav_val);
		head_movement += difference;
		sav_val = curr_val;

	}

	return head_movement;

}

/* Circular Scan (C-SCAN) - start at start index, increase to upper boundary 
(even if no value at boundary), save boundary value, go to start boundary 
(zero value) increase till last value before start value */
int cscan(int * ranArray) {

	int i = 0, curr_val = 0, sav_val = ran_array[start], difference = 0;
	int head_movement = 0, curr_i = 0, upper_bound = 4999;

	for(i = start+1; i < REQUESTS; i++) {

		curr_val = ran_array[i];
		difference = abs(sav_val - curr_val);
		head_movement += difference;
		sav_val = curr_val;

	}

	/* add last val - upper bound, go to and add zero bounday (4999)*/
	head_movement += upper_bound - sav_val;
	sav_val = 0;
	head_movement += 4999;

	for(i = 0; i < start; i++) {

		curr_val = ran_array[i];
		difference = abs(curr_val - sav_val);
		head_movement += difference;
		sav_val = curr_val;

	}

	return head_movement;
}

/* Look - start from value above start, increase to highest value. 
Then goes to value below start value and decreases until smallest value */
int look(int* ranArray) {

	int i = 0, curr_val = 0, sav_val = ran_array[start], difference = 0;
	int head_movement = 0, curr_i = 0;

	for(i = start+1; i < REQUESTS; i++) {

		curr_val = ran_array[i];
		difference = abs(sav_val - curr_val);
		head_movement += difference;
		sav_val = curr_val;

	}

	for(i = start-1; i >= 0; --i) {

		curr_val = ran_array[i];
		difference = abs(curr_val - sav_val);
		head_movement += difference;
		sav_val = curr_val;

	}

	return head_movement;
}

/* C-Look - Starts from value after start value, goes to highest value, 
then goes to smallest value and increases until value before start value */
int clook(int* ranArray) {

	int i = 0, curr_val = 0, sav_val = ran_array[start], difference = 0;
	int head_movement = 0, curr_i = 0;

	for(i = start+1; i < REQUESTS; i++) {

		curr_val = ran_array[i];
		difference = abs(sav_val - curr_val);
		head_movement += difference;
		sav_val = curr_val;

	}

	for(i = 0; i < start; i++) {

		curr_val = ran_array[i];
		difference = abs(curr_val - sav_val);
		head_movement += difference;
		sav_val = curr_val;

	}	

	return head_movement;
}


int main (int argc, char *argv[]) {


	int i = 0;
	start = atoi(argv[1]);

	if(argc != 2) {

		printf("Please compile program with starting index from 0-4999. Ex. ./diskAlgorithms 423\n");
		exit(-1);
	}

	for(i = 0; i < REQUESTS; i++) {

		ran_array[i] = rand() % 5000;
	}

	printf("\nStart index: %d, start value: %d\n\n", start, ran_array[start]);

	printf("FCFS head movements: %d\n", fcfs(ran_array));
	printf("SSTF head movements: %d\n", sstf(ran_array));
	printf("SCAN head movements: %d\n", scan(ran_array));
	printf("CSCAN head movements: %d\n", cscan(ran_array));
	printf("LOOK head movements: %d\n", look(ran_array));
	printf("C-LOOK head movements: %d\n\n", clook(ran_array));

	return 0;
}
