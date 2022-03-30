#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct Student {
    char firstName[20], lastName[20];
    double arabicMark, mathMark, scienceMark, englishMark;
}Student;

Student student;
char *fullName;

void presentation(int *);
void full_Name();
void takeMarks();
void setFile();
void isExist();
void oneMark();
void rnm();
void rmv();
void info();

int main () {
    bool loop = 1;
    while (loop) {
        int choice = 0;
        presentation(&choice);
        if (choice == 0) loop = 0;
        else if (choice == 1) takeMarks();
        else if (choice == 2) isExist();
        else if (choice == 3) oneMark();
        else if (choice == 4) rnm();
        else if (choice == 5) rmv();
        else if (choice == 6) info();
        else printf("Incorrect choice!!!\n");
    }
}
void presentation(int *choice) {
    printf("0.Exit\n");
    printf("1.Add new student\n");
    printf("2.Change student's markes\n");
    printf("3.Change one mark\n");
    printf("4.Rename file\n");
    printf("5.Remove file\n");
    printf("6.Get informations\n");
    printf("enter your choice: "); scanf("%d", choice);
}
void full_Name() {
    printf("Enter your first name: "); scanf(" %20s", student.firstName);
    printf("Enter your last name: "); scanf(" %20s", student.lastName);
    fullName = strcat(student.firstName,student.lastName);    
}
void takeMarks() {
    full_Name();
    printf("Arabic\'s mark: "); scanf("%lf", &student.arabicMark);
    printf("Math\'s mark: "); scanf("%lf", &student.mathMark);
    printf("Science\'s mark: "); scanf("%lf", &student.scienceMark);
    printf("English\'s mark: "); scanf("%lf", &student.englishMark);
    setFile();
}
void setFile() {
    FILE *file = fopen(fullName, "w");
    fprintf(file, "%.2lf (Arabic)\n", student.arabicMark);
    fprintf(file, "%.2lf (Math)\n", student.mathMark);
    fprintf(file, "%.2lf (Science)\n", student.scienceMark);
    fprintf(file, "%.2lf (English)\n", student.englishMark);
    fprintf(file, "Grade: %.2lf", (student.arabicMark+student.mathMark+student.scienceMark+student.englishMark)/4);
    fclose(file);
}
void isExist() {
    full_Name(); 
    if (access(fullName, F_OK) == 0) {
        printf("Arabic\'s mark: "); scanf("%lf", &student.arabicMark);
        printf("Math\'s mark: "); scanf("%lf", &student.mathMark);
        printf("Science\'s mark: "); scanf("%lf", &student.scienceMark);
        printf("English\'s mark: "); scanf("%lf", &student.englishMark);  
        setFile();      
    }
    else {
        printf("File doesn't exist\n");
    }
}
void oneMark() {
    full_Name();
    if (access(fullName, F_OK) == 0) {
        char mark[6];
        int counter = 0;
        FILE *file = fopen(fullName, "r");

        while (fgets (mark, sizeof(mark), file) != NULL) {
            counter++;
            if (counter == 1) student.arabicMark = atof(mark);
            else if (counter == 4) student.mathMark = atof(mark);
            else if (counter == 7) student.scienceMark = atof(mark);
            else if (counter == 11) student.englishMark = atof(mark);
        }
        fclose(file);
        int choice;
        do {
            printf("1.Arabic\n2.Math\n3.Science\n4.English\nEnter your choice: "); scanf("%d", &choice);

            if (choice > 0 && choice < 5) {
                double newMark;
                printf("New mark: "); scanf("%lf", &newMark);
                if (choice == 1) student.arabicMark = newMark;
                else if (choice == 2) student.mathMark = newMark;
                else if (choice == 3) student.scienceMark = newMark;
                else if (choice == 4) student.englishMark = newMark;
            }
            else {
                printf("enter a correct choice!!\n");
            }
        }while (!(choice > 0 && choice < 5));
        setFile();
    }
    else {
        printf("File doesn't exist\n");        
    }
}
void rnm() {
    full_Name();
    char newFirstName[20], newLastName[20];

    printf("New first name: "); scanf("%20s", newFirstName);
    printf("New last name: "); scanf("%20s", newLastName);
    char *newFullName = strcat(newFirstName, newLastName); 

    if (rename(fullName, newFullName) == 0) printf("File successfully renamed\n");
    else printf("Error renaming file\n");
} 
void rmv() {
    full_Name();
    if( remove(fullName) != 0 ) printf("Error deleting file\n");
    else printf("File successfully deleted\n");
}
void info() {
    char info[10];
    int counter = 0;
    full_Name();
    FILE *file = fopen(fullName, "r");

    while(fgets(info, sizeof(info), file) != NULL) {
        counter++;
        if (counter%2 == 0) printf("%s", info);
        else printf("%s", info);
    }
    printf("\n");
}