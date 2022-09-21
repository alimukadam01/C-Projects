/*
Programmer:- Patel Varshit Nimeshkumar
Description:- Student data Base
Version:-1.0
*/
//#pragma once
#ifndef _STUDENT_H
#define _STUDENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct Student{
    int ID;
    double grade;
    char name[100];
};

struct Student createStudent();

void printData(struct Student s1);

struct Student* searchStudent(struct Student arr[], int noOfStudents, int searchID);

void changeStudentGrade(struct Student* s1);

void printMenu();

int readStudents(struct Student students[]);

void writeStudents(struct Student students[], int noOfStudents);


#endif