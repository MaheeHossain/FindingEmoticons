/* Emoticon message cleanser:
 *
 * Skeleton code written by Farhana Choudhury and Jianzhong Qi, April 2020
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STAGE_NUM_ONE 1							/* stage numbers */ 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5
#define STAGE_HEADER "Stage %d\n==========\n"	/* stage header format string */

#define MAX_MSG_LENGTH 280						/* maximum message length */
#define MAX_NUM_MSGS 100						/* maximum number of messages */
#define MAX_EMTCN_LENGTH 50						/* maximum emot. line length */
#define MAX_NUM_EMTCN 50						/* maximum number of emot. */

typedef char msg_t[MAX_MSG_LENGTH+1];			/* a message */
typedef char emtcn_t[MAX_EMTCN_LENGTH+1];		/* an emoticon */

/****************************************************************/

/* function prototypes */
void read_one_msg(msg_t one_msg, int max_len);
void print_stage_header(int stage_num);
int count_tokens(msg_t one_msg);

void stage_one(msg_t one_msg);
void stage_two(msg_t msgs[], int *num_msgs);
void stage_three(msg_t msgs[], int num_msgs);
void stage_four(emtcn_t emtcns[], int *num_emtcns);
void stage_five(msg_t msgs[], int num_msgs, emtcn_t emtcns[], int num_emtcns);

/* add your own function prototypes here */


/****************************************************************/

/* main function controls all the action, do NOT modify this function */
int
main(int argc, char *argv[]) {
	/* to hold all input messages */
	msg_t msgs[MAX_NUM_MSGS];	
	/* to hold the number of input messages */
	int num_msgs = 0;	
	/* to hold all input emoticons in the dictionary */
	emtcn_t emtcns[MAX_NUM_EMTCN];
	/* to hold the number of emoticons in the dictionary */
	int num_emtcns = 0;	
	
	/* stage 1: reading the first message */
	stage_one(msgs[num_msgs]); 
	num_msgs++;
	
	/* stage 2: removing alphanumeric characters */
	stage_two(msgs, &num_msgs);
	
	/* stage 3: removing extra commas */ 
	stage_three(msgs, num_msgs);
	
	/* stage 4: reading the dictionary and finding the longest emoticon */
	stage_four(emtcns, &num_emtcns);
	
	/* stage 5: removing invalid emoticons with the help of the dictionary */
	stage_five(msgs, num_msgs, emtcns, num_emtcns);
	
	/* all done; take some rest */
	return 0;
}

/* read a line of input into one_msg */
void
read_one_msg(msg_t one_msg, int max_len) {
	int i = 0, c;
	while (((c = getchar()) != EOF) && (c != '\n') && (c != '\r')) {
		if (i < max_len) {
			one_msg[i++] = c;
		} else {
			printf("Invalid input line, toooooooo long.\n");
			exit(EXIT_FAILURE);
		}
	}
	one_msg[i] = '\0';
}

/* print stage header given stage number */
void 
print_stage_header(int stage_num) {
	printf(STAGE_HEADER, stage_num);
}

/****************************************************************/
/* add your code below */

/* scan a message and count the number of tokens (separated by commas) in it */
int 
count_tokens(msg_t one_msg) {
	/* add code here to count the number commas in one_msg,
	   and return the count + 1 */
	
	return 1;
}

/* stage 1: reading the first message */
void 
stage_one(msg_t one_msg) {
	/* add code for stage 1 */
	/* print stage header */
	print_stage_header(STAGE_NUM_ONE);
	
	/* read the first message */
    char line[MAX_MSG_LENGTH+1];
    line = read_one_msg(one_msg, MAX_MSG_LENGTH);
	
	/* count and print the number of tokens */
	printf("Number of tokens: %d\n\n", count_tokens(one_msg));
}

/* stage 2: removing alphanumeric characters */
void 
stage_two(msg_t msgs[], int *num_msgs) {
	/* add code for stage 2 */
	/* print stage header */
	print_stage_header(STAGE_NUM_TWO);
	
	printf("\n");
}

/* stage 3: removing extra commas */ 
void 
stage_three(msg_t msgs[], int num_msgs) {
	/* add code for stage 3 */
	/* print stage header */
	print_stage_header(STAGE_NUM_THREE);

	printf("\n");
}
	
/* stage 4: reading the dictionary and finding the longest emoticon */ 
void stage_four(emtcn_t emtcns[], int *num_emtcns) {
	/* add code for stage 4 */
	/* print stage header */
	print_stage_header(STAGE_NUM_FOUR);
	
	printf("\n");
}

/* stage 5: removing invalid emoticons with the help of the dictionary */
void 
stage_five(msg_t msgs[], int num_msgs, emtcn_t emtcns[], int num_emtcns) {
	/* add code for stage 5  */
	/* print stage header */
	print_stage_header(STAGE_NUM_FIVE);
	
	printf("\n");
}
