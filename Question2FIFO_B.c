#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<time.h>
#include<stdlib.h>
#include<sys/un.h>

#define BUFFER 100

int main() {
    int fileDir1, fileDir2, out;

    char buffer[BUFFER];
	int highestIndex = 0;
	int tempCheckCounter=0;
	
    char * myfifo1 = "FIFO1"; char * myfifo2 = "FIFO2";
	//create the FIFO pipes
    mkfifo(myfifo1, 0666); mkfifo(myfifo2, 0666);
    
	int currentIndex = highestIndex;
	int loop=1;
	while(loop) {
		while(currentIndex < highestIndex + 5) {
			// printf("%d", tempCheckCounter);
			printf("-------");
			sleep(2);
			// open the first FIFO pipe for reading
			fileDir1 = open(myfifo1, O_RDONLY);
			out = read(fileDir1, buffer, sizeof(buffer));
			close(fileDir1);
			if(out == -1) {	
				perror("CAN'T READ FILE!\n");
				printf("PLEASE TRY AGAIN!\n");
				exit(EXIT_FAILURE);
			}
			currentIndex = buffer[0];
			printf("\n");
			printf("String SENT by FIFO1: ");	

			int i;
			for(i = 1; i < 6; i++) {
				printf("%c", buffer[i]);
			}
			printf("\n");
			
			// send the ID of the last string received back through the second FIFO pipe
			sprintf(buffer, "%d", currentIndex);
			printf("id SENT by FIFO1 = %s\n", buffer);	
		}
				
		highestIndex = currentIndex;
		//open the second FIFO pipe for writing
		fileDir2 = open(myfifo2, O_WRONLY);
		out = write(fileDir2, buffer, sizeof(buffer));

		if(highestIndex >= 50) 
		{
			exit(EXIT_SUCCESS);
		};
		close(fileDir2);
	}
    return 0;
}