#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<time.h>
#include<stdlib.h>
#include<sys/un.h>

#define BUFFER 100

// Function to generate random strings
void RandomStringGenerator(char randomStrings[][6]) {        
    // seed the random number generator using the current time
    srand (time(NULL));
	int i;                            
    // assign an ID to each string
    for (i = 0; i <= 50; i++) {
        randomStrings[i][0] = i;
    }
    
	int j;
    // generate random characters for each string
    for(i = 0; i <= 50; i++) {
		for(j = 1; j <= 5; j++) {
			randomStrings[i][j] = rand() % 26 + 65;
		}
	}
}

int main() {
    int fileDir1, fileDir2, out;
	char randomStrings[51][6] = {{0}};
	char buffer[BUFFER];
	char * myfifo1 = "FIFO1"; char * myfifo2 = "FIFO2";
    
    // generate the random strings
    RandomStringGenerator(randomStrings);

	int i,j,counter=0;
    
    // print the random strings
	for(i = 1; i <= 50; i++) {
		for(j = 0; j < 6; j++) {
			if(j == 0) {
				counter=counter+1;
				printf("%d :", counter);
			}
			else {printf("%c", randomStrings[i][j]);
			}
		}
		printf("\n");
	}

	printf("\n%s\n", "The above strings are random strings created");
	
	int finalIndex = 1;
	
    // create the FIFO pipes
    mkfifo(myfifo1, 0666); mkfifo(myfifo2, 0666);
   
	
	while(1) {
		if(fileDir1 == -1) {
			perror("CAN'T ACCESS FIFO1");
			printf("PLEASE TRY AGAIN!");
		}

		printf("\n");
		printf("Sending Strings FROM %d TO %d\n", finalIndex, finalIndex + 4);
		
		// send the strings through the FIFO pipe
		for(i = finalIndex; i < finalIndex + 5; i++) {
			fileDir1 = open(myfifo1, O_WRONLY);
			out = write(fileDir1, randomStrings[i], sizeof(randomStrings[i]) + 1);
			sleep(1);	
			close(fileDir1);
		}

		// read the response from the server through the other FIFO pipe
		fileDir2 = open(myfifo2, O_RDONLY);
		out = read(fileDir2, buffer, sizeof(buffer));
		
		if(out == -1) {
			perror("ERROR IN READING");
			exit(EXIT_FAILURE);
		}

		close(fileDir2);

		int lastIndex = atoi(buffer);
 		printf("MAX ID SENT BACK BY SERVER = %s\n\n", buffer);

		finalIndex = lastIndex + 1;
		if(finalIndex >= 50) 
			{
				exit(EXIT_SUCCESS);
			}
	}

    return 0;
}