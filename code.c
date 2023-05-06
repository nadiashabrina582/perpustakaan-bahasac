#include <stdio.h>
#include <string.h>

// define struct untuk buku
struct Book {
    char title[100];
    char author[100];
    char publisher[100];
    int num_pages;
    int is_borrowed;
};

// fungsi untuk mencari buku
void searchBook(struct Book books[], int num_books, char keyword[]) {
    int i, found = 0;
    for (i = 0; i < num_books; i++) {
        if (strstr(books[i].title, keyword) != NULL || strstr(books[i].author, keyword) != NULL) {
            printf("Book #%d\n", i+1);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Publisher: %s\n", books[i].publisher);
            printf("Number of Pages: %d\n", books[i].num_pages);
            if (books[i].is_borrowed) {
                printf("Status: Borrowed\n");
            }
            else {
                printf("Status: Available\n");
            }
            found = 1;
        }
    }
    if (!found) {
        printf("No books found with the keyword \"%s\"\n", keyword);
    }
}

// fungsi untuk meminjam buku
void borrowBook(struct Book books[], int num_books, char title[]) {
    int i, found = 0;
    for (i = 0; i < num_books; i++) {
        if (strcmp(books[i].title, title) == 0) {
            if (books[i].is_borrowed) {
                printf("Book \"%s\" is already borrowed.\n", title);
            }
            else {
                books[i].is_borrowed = 1;
                printf("Book \"%s\" has been borrowed.\n", title);
            }
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Book \"%s\" not found.\n", title);
    }
}
