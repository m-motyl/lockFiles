#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int getFileSize(const char* file_name);
void cleanBuffer(const char* file_name);

int main(){
	char filename[20];
	char message[100];
	char messageBack[100];
	int i = 0;

	cleanBuffer("buffer.txt");

	while(1){
		while(1){
			if(getFileSize("buffer.txt") != 0){
				
				FILE *buffer = fopen("buffer.txt", "r");
				
				if(buffer == NULL){
					printf("Failed to open a buffer\n");
					exit(-1);
				}
	
				fgets(message, 100, buffer);
	
				if(i == 0){
					strcpy(filename, message);
					i++;
				}
	
				cleanBuffer("buffer.txt");
	
				if(strcmp(message, "\\\n") == 0){
					i = 0;
					printf("\n*THE END*\n");
					break;
				}
	
				else{
					printf("%s", message);
				}
	
				fclose(buffer);
			}
		}

		//message back
		printf("*RESPONSE*\n");
		printf("(write \\ in new line to end conversation)\n\n");
		while(1){

			filename[strcspn(filename, "\n")] = 0;
			FILE *writeBack = fopen(filename, "a");
			fgets(messageBack, 100, stdin);

			messageBack[strcspn(messageBack, "\n")] = 0;
			fprintf(writeBack, "%s\n", messageBack);

			if(strcmp(messageBack, "\\") == 0){
				fprintf(writeBack, "%s\n", messageBack);
				fclose(writeBack);
				printf("\n*DISCONNECTED*\n");
				unlink("lockfile");
				break;
			}

			fclose(writeBack);
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
