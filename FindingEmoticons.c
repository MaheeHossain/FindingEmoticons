/* Emoticon message cleanser:
 *
 * Skeleton code written by Farhana Choudhury and Jianzhong Qi, April 2020
 *
 * Further Developed by Mahee Hossain, 1080102
 */

#include <stdio.h>
#include <string.h>
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

/* I will add my own constant definitions here */
#define HASH_LENGTH 4                          /* length of the string "###" */
#define STAGE_TWO_METHOD 2                    /* printing method for stage 2 */
#define STAGE_THREE_METHOD 3                  /* printing method for stage 3 */

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
int hash_check(msg_t one_msg);
void set_msgs(msg_t msgs[], int *num_msgs);
void set_emtcns (emtcn_t emtcns[], int *num_emtcns);
void print_msgs(msg_t msgs[], int num_msgs, int method);
void remove_alphanumeric(msg_t one_msg, int max_len);
void remove_alphanumeric_emtcns(emtcn_t one_msg, int max_len);
void remove_extra_commas(msg_t one_msg, int max_len);
int s_comp(char s1[], char s2[]);
void emtcns_each_line(int truesize[], int truearray[], int sizes[], 
                      int num_msgs);

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
/* add your code below - Will do! */
/* algorithms are fun! */

#define HASH_LENGTH 4 /* length of the string "###" */

/* scan a message and count the number of tokens (separated by commas) in it */
int 
count_tokens(msg_t one_msg) {
	/* Look at all the chars in a single line of a file, if char is 
	   a comma, add one to the count
	*/
	int count=1;
    
	for (int i=0; one_msg[i]; i++) {              //For every char in the line
		if (one_msg[i] == ',') {
			count++;
		}
	}
    
	return count;
}

int hash_check(msg_t one_msg){
	/* Checks if a line is "###"
	*/
	if (strncmp(one_msg, "###", HASH_LENGTH) == 0) {
		return 0;
	}
	else {
		return 1;
	}
}

void set_msgs(msg_t msgs[], int *num_msgs) {
	/* Used for Stage 2
	   Sets msgs[] with all the lines until (and including) "###"
	   msgs[0] is already set as the first line so start with the second line
	*/
	int iterations=1;
    
	for (int i=1; i < (MAX_NUM_MSGS-1); i++) {        // For each line in msgs
    
		read_one_msg(msgs[i], MAX_MSG_LENGTH);
		iterations++;
        
		if (hash_check(msgs[i]) == 0) {
			break;
		}
	}
    
	*num_msgs = iterations;
}

void set_emtcns (emtcn_t emtcns[], int *num_emtcns) {
	/* Used for Stage 4
	   Sets emtcns[] with all the lines from the emoticon dictionary 
	*/
	int iterations=0;
    
	for (int i=0; i < MAX_NUM_EMTCN; i++) {         // For each line in emtcns
		
		read_one_msg(emtcns[i], MAX_MSG_LENGTH);
        
		if (strncmp(emtcns[i], "", 1) == 0) {
			break;
		}
        
		iterations++;
	}
    
	*num_emtcns = iterations;
}

void remove_alphanumeric(msg_t one_msg, int max_len) {
    /* Used for Stage 2
    
       Altered version of read_one_msg that reads a one_msg (a line) and 
       removes all alphanumeric characters
    */
    msg_t new_msg="";
    
    for (int i=0; one_msg[i]; i++) {              // For every char in one_msg
    
    	char c = one_msg[i];
        
		if (i < max_len) {
			/* If a letter isn't an alphanumeral, leave it in the msg */
			if ( (c < '0') || ((c > '9') && (c < 'A')) ||
			     ((c > 'Z') && (c < 'a')) || (c > 'z') ) {
				strncat(new_msg, &c, 1);
            }
		} 
        
		else {
			printf("Invalid input line, toooooooo long.\n");
			exit(EXIT_FAILURE);
		}
	}
    
	strcpy(one_msg, new_msg);
}

void remove_alphanumeric_emtcns(emtcn_t one_emtcn, int max_len) {
    /* Used for Stage 4
    
       Altered version of remove_alphanumeric that reads an emoticon line 
       until it reaches an alphanumeric character, where it stops reading 
    */
    emtcn_t new_emtcn="";
    
    for (int i=0; one_emtcn[i]; i++) {          // For every char in one_emtcn
    
    	char c = one_emtcn[i];
        
		if (i < max_len) {
			if ( ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || 
                 ((c >= '0') && (c <= '9')) ) {
				break;
            }
            else {
				strncat(new_emtcn, &c, 1);
            }
		} 
        
		else {
			printf("Invalid input line, toooooooo long.\n");
			exit(EXIT_FAILURE);
		}
	}
	strcpy(one_emtcn, new_emtcn);
}

void remove_extra_commas(msg_t one_msg, int max_len) {
	/* Used for Stage 3
	
	   Altered version of read_one_msg that reads one_msg and looks for 
	   sections that have multiple consecutive commas, and replaces them with 
	   a single comma, while also removing any commas at the start or end
	*/
    
	/* Set to ',' to account for a comma at the start of a string */
	char last_char=','; 
	msg_t new_msg="";
	
	for (int i=0; one_msg[i]; i++) {               // For each char in one_msg
		char c=one_msg[i]; 
		if (c == ',') {
			if (last_char != ',' ) {
				strncat(new_msg, &c, 1);
			}
			else {
				continue;
			}
		}
		else {
			strncat(new_msg, &c, 1);
		}
		last_char = c;
	}
	strcpy(one_msg, new_msg);
    /* Check if the last character in the line is a comma, and remove it if 
	    if is
	*/
	int len=strlen(one_msg);
	if (one_msg[len-1] == ',') {
		one_msg[len-1] = '\0';
	}
}

void print_msgs(msg_t msgs[], int num_msgs, int method) {
	/* Prints out the msg in the correct format, using the created methods 
	   required - might be a neater way of doing this
	*/
	if (method == STAGE_TWO_METHOD) {
		for (int j=0; j<(num_msgs-1); j++) {          // For each line in msgs
			remove_alphanumeric(msgs[j], MAX_MSG_LENGTH);
			printf("%s\n", msgs[j]);
		}
	}
	else if (method == STAGE_THREE_METHOD) {
		for (int j=0; j<(num_msgs-1); j++) {          // For each line in msgs
			remove_extra_commas(msgs[j], MAX_MSG_LENGTH);
			printf("%s\n", msgs[j]);
		}
	}
    printf("\n");
}

int s_comp(char s1[], char s2[]) {
	/* Compares two strings without using string.h (for part 5)
	*/
	int i=0;
	
	while (s1[i] == s2[i]) {
		/* If the ith char of s1 and s2 is '\0', then the whole string must've 
		   been equal
		*/
		if ((s1[i] == '\0') && s2[i] == '\0') {
			return 0;
		}
		
		//printf("s1[%d] = %s, s2[%d] = %s\n", i, &s1[i], i, &s2[i]);
		i++;
	}    
	return 1;
}

void emtcns_each_line(int truesize[], int truearray[], int sizes[], 
                      int num_msgs) {
	/* Fill the truesize array up, showing the amount of emoticons per line
	   Used for Stage 5
	*/
    int iterations=0;
    
	for (int i=0; i<num_msgs; i++) {      // For the values in sizes
		int sum=0, j=0;
        
		while (j<sizes[i]) {              // For the sized values in truearray
			sum += truearray[j+iterations];
			j++;
		}
        
		iterations += j;
		truesize[i] = sum;
	}
}

/* stage 1: reading the first message */
void 
stage_one(msg_t one_msg) {
	/* add code for stage 1 */
	/* print stage header */
	print_stage_header(STAGE_NUM_ONE);
	
	/* read the first message */
	read_one_msg(one_msg, MAX_MSG_LENGTH);
	
	/* count and print the number of tokens */
	printf("Number of tokens: %d\n\n", count_tokens(one_msg));
}

/* stage 2: removing alphanumeric characters */
void 
stage_two(msg_t msgs[], int *num_msgs){
	/* add code for stage 2 */
	/* print stage header */
	print_stage_header(STAGE_NUM_TWO);
	
	/* Uses set_msgs  to make msgs[] have all the messages in it, and to set
	   the number of messages to num_msgs */
	set_msgs(msgs, num_msgs);
	
	/* Call function remove_alphanumeric for each line, which removes all 
	   alphanumerals for the line */
    print_msgs(msgs, *num_msgs, STAGE_TWO_METHOD);
}

/* stage 3: removing extra commas */ 
void 
stage_three(msg_t msgs[], int num_msgs) {
	/* add code for stage 3 */
	/* print stage header */
	print_stage_header(STAGE_NUM_THREE);
	
	/* Uses remove_extra_commas on each line to remove leading, trailing and 
	   consecutive commas
	*/
	print_msgs(msgs, num_msgs, STAGE_THREE_METHOD);
}
	
/* stage 4: reading the dictionary and finding the longest emoticon */ 
void 
stage_four(emtcn_t emtcns[], int *num_emtcns) {
	/* add code for stage 4 */
	/* print stage header */
	print_stage_header(STAGE_NUM_FOUR);
	
	/* Fill emtcns[] */
	set_emtcns(emtcns, num_emtcns);
	
	/* Set variables to find the maximum length emoticon
	*/
	int cur_len=0, max_len=0;
	emtcn_t max_emtcn="";
	
	/* Call function remove_alphanumeric_emtcns for each line, which removes 
	   the description of the emoticon
	*/
	for (int j=0; j<(*num_emtcns); j++) {           // For each line in emtcns
		remove_alphanumeric_emtcns(emtcns[j], MAX_EMTCN_LENGTH);
		
		/* Find current length, and then remove the comma at the end of the 
		    emoticon
		*/
		cur_len = (strlen(emtcns[j]) - 1);
		emtcns[j][cur_len] = '\0';
		
		/* Check if current length is max, and if it is make this emoticon 
		   the max emoticon */
		if (cur_len > max_len) {
			max_len = cur_len;
			strncpy(max_emtcn, emtcns[j], max_len);
		}
	}
	
	/* Print the necessary information
	*/
	printf("Emoticon total: %d\n", *num_emtcns);
	printf("Longest: %s\n", max_emtcn);
	printf("Length: %d\n", max_len);
	
	printf("\n");
}

/* stage 5: removing invalid emoticons with the help of the dictionary */
void 
stage_five(msg_t msgs[], int num_msgs, emtcn_t emtcns[], int num_emtcns) {
	/* add code for stage 5 - sorry for this mess haha */
	/* print stage header */
	print_stage_header(STAGE_NUM_FIVE);
    
	/* Create an array with the number of emojis in each line in msgs */
	int sizes[num_msgs], size=0;
 	for (int i=0; i<num_msgs; i++) {
		size = count_tokens(msgs[i]);
		sizes[i] = size;
	}
	
	msg_t new_msgs[MAX_MSG_LENGTH+1];
	
	/* Set new_msgs (should be a list with all the emoticons) */
	int ni=0;
	for (int j=0; j<num_msgs; j++) {                  // For each line in msgs
		
		int cons=0; // Create a constant to refresh i in ni
		for (int i=0; i<(MAX_EMTCN_LENGTH+1); i++) { // Each character in line
			int com_check=0;
			if (msgs[j][i] == '\0') {
				break;
			}
			if (msgs[j][i] == ',') {
				ni++;
				cons = i+1;
				com_check = 1;
			}
			if (com_check == 0) {
				new_msgs[ni][i-cons] = msgs[j][i];
			}
		}
		ni++;
	}
	
	/* Check if each member of new_msgs is in the emtcns list or not */
	int truearray[ni];
	for (int n=0; n<ni; n++) {                   // For each emoji in new_msgs
		int check=0, true=1;
		for (int k=0; k<num_emtcns; k++) {         // For each emoji in emtcns
			if (s_comp(emtcns[k], new_msgs[n]) == 0) {
				check = 1;
			}
		}
		if (check == 0) {
			true = 0;
			new_msgs[n][0] = '\0';
		}
		truearray[n] = true;
	}
	
	/* Make an array of the amount of emoticons per line */
	int truesize[num_msgs];
	emtcns_each_line(truesize, truearray, sizes, num_msgs);

	/* Prints out the required input - missing the extra commas */
    int i=0, k=0;      // k is for number of lines (including zero size lines)
	while (i < ni) {                     // i is for the emoticons in new_msgs
		int j=0;                     // j is for num of emoticons in each line
        if (k >= num_msgs) {
            break;
        }
		while (j<truesize[k]) {
			if (s_comp(new_msgs[i], "") == 1) { // not 5, 7, 9
				if (j == 0) {
					printf("%s", new_msgs[i]);
				}
				else {
					printf(",%s", new_msgs[i]);
				}
				j++;
			}
            i++;
		}
		if (j != 0) {
			printf("\n");
		}
		k++;
	}
}