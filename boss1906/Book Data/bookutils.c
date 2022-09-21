#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"

struct BookData addNewBook(){
    struct BookData book;
    //Initializing statements.
    book.noOfPages = -1;
    book.price = -1;

    printf("Title? ");
    scanf(" "); // Skip any spaces, tabs, newlines
	gets (book.title);

    printf("No. of pages? ");
    scanf("%d", &book.noOfPages);

    printf("Price? ");
    scanf("%lf", &book.price);
  	
    return  book;
};