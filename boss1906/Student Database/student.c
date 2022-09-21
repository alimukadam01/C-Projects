/*
Programmer:- Patel Varshit Nimeshkumar
Description:- Student data Base
Version:-1.0
*/

#define _CRT_SECURE_NO_WARNINGS
#include "student.h"
#include "studentutils.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>



int main() {
    const int maxStudents = 500;
    int noOfStudents = 0;    
    char currentOperation;
    int run = 1;
    struct Student students[maxStudents];
    struct Student* ptr;
    int searchId;

    noOfStudents = readStudents(students);
    printMenu();
    

    while (run == 1){

        currentOperation = 'N';
        printf("Enter option: ");
        scanf(" %c", &currentOperation);        
        

        if (currentOperation == 'A' || currentOperation == 'a'){
            students[noOfStudents] = createStudent();
            noOfStudents++;

            printf("\n");
        }

        else if(currentOperation == 'L' || currentOperation == 'l'){
            printf("\tStudent Name\t\tStudent ID\t\tGrade\n");
            printf("---------------------\t\t----------\t\t-----\n");
            for(int i = 0; i < noOfStudents; i++){
                printData(students[i]);
            }

            printf("\n");
        }

        else if(currentOperation == 'C' || currentOperation == 'c'){
            printf("Enter Student Number: ");
            scanf(" %d", &searchId);
            ptr = searchStudent(students, noOfStudents, searchId); //linear search function.
            if(ptr != NULL){
                changeStudentGrade(ptr);    
            }
        }        

        else if(currentOperation == 'E' || currentOperation == 'e'){
            printf("Saving info...\n");
            writeStudents(students, noOfStudents);
            printf("Save successful!\n");
            printf("GOODBYE :)\n");
            run = 0;

        }
        else{
            printf("Please enter a correct option.\n");
        }
    }

    _getch();
    return 0;
}