#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
void displayMenu(){
	printf("\n*****WELCOME TO TYPING TUTOR*****\n");
	printf("Choose an option:\n");
	printf("1. Easy Lesson\n");
	printf("2. Medium Lesson\n");
	printf("3. Your progress\n");
	printf("4. Exit\n");
}
void easyLesson(float *typingAccuracy,float *WPM){
	int i; float errorCount=0.0,correctCount=0.0; 
	FILE *feasy; char data[100],ch;
	feasy=fopen("easy_lesson.txt","r");
	fgets(data,100,feasy);
	clock_t startTime=clock();
	printf("%s\n",data);
	for(i=0;i<strlen(data);i++){
		ch=getch();
		if(ch==data[i]){
			printf("%c",ch);
			correctCount++;
		}else{
			i=i-1;
			errorCount++;
		}
	}
	fclose(feasy);
	clock_t endTime=clock();
	float elapsedTime=((float)(endTime-startTime)/CLOCKS_PER_SEC);
    *typingAccuracy=((correctCount-errorCount)/strlen(data))*100;
    *WPM=(strlen(data)/(elapsedTime/60));
    printf("\nAccuracy:%.2f",*typingAccuracy);
    printf("\nWPM:%.2f\n",*WPM);
}
void mediumLesson(float *typingAccuracy,float *WPM){
	int i; float errorCount=0.0,correctCount=0.0; 
	FILE *fmedium; char data[100],ch;
	fmedium=fopen("medium_lesson.txt","r");
	fgets(data,100,fmedium);
	clock_t startTime=clock();
	printf("%s\n",data);
	for(i=0;i<strlen(data);i++){
		ch=getch();
		if(ch==data[i]){
			printf("%c",ch);
			correctCount++;
		}else{
			i=i-1;
			errorCount++;
		}
	}
	fclose(fmedium);
	clock_t endTime=clock();
	float elapsedTime=((float)(endTime-startTime)/CLOCKS_PER_SEC);
    *typingAccuracy=((correctCount-errorCount)/strlen(data))*100;
    *WPM=(strlen(data)/(elapsedTime/60));
    printf("\nAccuracy:%.2f",*typingAccuracy);
    printf("\nWPM:%.2f\n",*WPM);
}
void saveUserProgress(char *filename,float accuracy,float WPM){
	FILE *file; char data[1000];
	file=fopen(filename,"a");
	if(file==NULL){
		printf("Error Accessing File\n");
		return;
	}
	fprintf(file,"\nAccuracy=%.2f percent",accuracy);
	fprintf(file,"\nWPM=%.2f",WPM);
	fclose(file);
}
void showUserProgress(char *filename){
	FILE *file;char data[1000];
	file=fopen(filename,"r");
	if(file==NULL){
		printf("Error accessing file\n");
		return;
	}
    while(fgets(data, sizeof(data), file) != NULL) {
        printf("%s", data);
    }
	
	fclose(file);
}
int main(){
    float typingAccuracy, WPM;
    int choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                easyLesson(&typingAccuracy, &WPM);
                saveUserProgress("userProgressEasy.txt", typingAccuracy, WPM);
                break;
            case 2:
                mediumLesson(&typingAccuracy, &WPM);
                saveUserProgress("userProgressMedium.txt", typingAccuracy, WPM);
                break;
            case 3:
                printf("Choose which progress to display:\n");
                printf("1. Easy Lesson\n");
                printf("2. Medium Lesson\n");
                int progressChoice;
                printf("Enter your choice: ");
                scanf("%d", &progressChoice);

                if (progressChoice == 1) {
                    showUserProgress("userProgressEasy.txt");
                } else if (progressChoice == 2) {
                    showUserProgress("userProgressMedium.txt");
                } else {
                    printf("Invalid choice for progress.\n");
                }
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 4);

    return 0;
}
