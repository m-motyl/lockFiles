#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

void cleanBuffer(const char* file_name);
int getFileSize(const char* file_name);

int main(int argc, char* argv[]){
	//char* buffer = argv[1];
	char* buffer = "buffer.txt";
	char message[100];
	char messageBack[100];
	int i = 0;

	while(open("lockfile", O_CREAT|O_EXCL, 0) == -1){
		printf("Server busy, please wait\n");
		sleep(5);
	}	

	printf("*CONNECTED TO THE SERVER*\n");
	printf("Write a message (write \\ in new line to end conversation)\n\n");

	FILE *writeToBuffer = fopen(buffer, "w");
	fprintf(writeToBuffer, "client1.txt\n");
	fclose(writeToBuffer);

	while(1){
		writeToBuffer = fopen(buffer, "a");

		fgets(message, 100, stdin);
		message[strcspn(message, "\n")] = 0;

		if(strcmp(message, "\\") == 0){
			printf("\n*Wait for response*\n");
			break;
		}

		fprintf(writeToBuffer, "%s\n", message);
		fclose(writeToBuffer);
	}

	writeToBuffer = fopen(buffer, "a");
	fprintf(writeToBuffer, "\\\n");
	fclose(writeToBuffer);
	
	cleanBuffer("client1.txt");

	while(1){	
		if(getFileSize("client1.txt") != 0){
			FILE *buffer = fopen("client1.txt", "r");

			if(buffer == NULL){
				printf("Failed to open a buffer\n");
				exit(-1);
			}

			fgets(messageBack, 100, buffer);
			cleanBuffer("client1.txt");

			if(strcmp(messageBack, "\\\n") == 0){
				printf("\n*DISCONNECTED*\n");
				break;
			}
			else{
				printf("%s", messageBack);
			}
			fclose(buffer);
		}
	}

	return 0;
}

void cleanBuffer(const char* file_name){
	fclose(fopen(file_name, "w"));
}

int getFileSize(const char* file_name){
	FILE *file = fopen(file_name, "r");
	if(file == NULL){
		printf("File opening problem\n");
		exit(-1);
	}

	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fclose(file);
	return size;
}
