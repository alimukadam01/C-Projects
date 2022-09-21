/*
Programmer:- Patel Varshit Nimeshkumar
Description:- Student data Base
Version:-1.0
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

struct Student createStudent(){
    struct Student student_data;
    //Initializing statements.
    student_data.ID = -1;
    student_data.grade = -1;

    printf("Enter Student Number: ");
    scanf("%d", &student_data.ID);
    printf("Enter Student Name: ");
    scanf(" "); // Skip any spaces, tabs, newlines
	gets (student_data.name);

            
    while(!(student_data.grade <= 100 && student_data.grade >= 0)){
        printf("Enter Student grade: ");
        scanf("%lf", &student_data.grade);

                
        if(!(student_data.grade <= 100 && student_data.grade >= 0)){
            printf("Enter the correct grade please.\n");
        } 
    }    	
    return  student_data;
};

void printData(struct Student student_data){
    printf("%20s\t\t%9d\t\t%2.2lf%%\n", student_data.name, student_data.ID, student_data.grade);
    return;
};

struct Student* searchStudent(struct Student arr[], int noOfStudents, int searchID)
{
    struct Student* ptr = NULL;
    int i;
    for (i = 0; i <= noOfStudents; i++){
        if (arr[i].ID == searchID){
            ptr = &arr[i];
            return ptr;
        }
    }

    printf("Student not found!\n\n");
    return NULL;
};

void changeStudentGrade(struct Student* student_data){
    //Initializing statements.
    char opt;
    double grade = -1.00;

    printf("Current Grade: %0.2lf%% \n", student_data->grade);
    printf("Would you like to change the grade?[y/n]: ");
    scanf(" %c", &opt); // Skip any spaces, tabs, newlines
    if (opt == 'y' || opt == 'Y'){
        while(!(grade <= 100 && grade >= 0)){
            printf("Enter Student grade: ");
            scanf("%lf", &grade);
                        
            if(!(grade <= 100 && grade >= 0)){
                printf("Enter the correct grade please.\n");
            } 
        }
        student_data->grade = grade;
        printf("Student grade changed.\n\n");
        return;        
    }
    printf("Student grade not changed.\n\n");
    return;
};

void printMenu(){
    printf("_____________ Student Database _____________ \n\n enter the option char to perform that option \n (A)DD \n (L)IST \n (C)HANGE  \n (E)ND \n\n");
    return;
}

int readStudents(struct Student students[]){
    int noOfStudents = 0;

    //file open statements.
    FILE* file;
    file = fopen("Student.DAT", "rb");
    if(file == NULL){
        printf("No file read.\n\n");
        return 0;
    }
    else{
        fseek(file, 0, SEEK_SET);
        printf("File read successfully.\n\n");
    }
    

    //file read statements.
    fread(&noOfStudents, sizeof(int), 1, file);
    fread(students, sizeof(struct Student), noOfStudents, file);

    //file close.
    fclose(file);
    return noOfStudents;
    
};

void writeStudents(struct Student students[], int noOfStudents){
    //file open statements.
    FILE* file;
    file = fopen("Student.DAT", "wb");
    if (file == NULL){
        printf("No file found or created.");
    }

    //write operations.
    fwrite(&noOfStudents, sizeof(int), 1, file);
    fwrite(students, sizeof(struct Student), noOfStudents, file);

    //file close.
    fclose(file);
};

