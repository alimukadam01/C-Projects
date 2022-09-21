#define _CRT_SECURE_NO_WARNINGS
#include "books.h"
#include "bookutils.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define Size 150

int main(){
    struct BookData books[Size];
    int noOfBooks = -1;

    books[noOfBooks] = addNewBook();
    noOfBooks++;  

    return 0; 
}