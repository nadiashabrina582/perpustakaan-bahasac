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

// fungsi untuk mengembalikan buku
void returnBook(struct Book books[], int num_books, char title[]) {
    int i, found = 0;
    for (i = 0; i < num_books; i++) {
        if (strcmp(books[i].title, title) == 0) {
            if (books[i].is_borrowed) {
                books[i].is_borrowed = 0;
                printf("Book \"%s\" has been returned.\n", title);
            }
            else {
                printf("Book \"%s\" has not been borrowed.\n", title);
            }
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Book \"%s\" not found.\n", title);
    }
}

int main() {
    // inisialisasi array buku
    struct Book books[100];
    int num_books = 0;

    // loop untuk menambahkan buku
    while (num_books < 50) {
        printf("Add Book #%d\n", num_books+1);

        // input informasi buku
        printf("Title: ");
        fgets(books[num_books].title, sizeof(books[num_books].title), stdin);
        books[num_books].title[strcspn(books[num_books].title, "\n")] = '\0';

        printf("Author: ");
        fgets(books[num_books].author, sizeof(books[num_books].author), stdin);
		books[num_books].author[strcspn(books[num_books].author, "\n")] = '\0';
		
		printf("Publisher: ");
    	fgets(books[num_books].publisher, sizeof(books[num_books].publisher), stdin);
    	books[num_books].publisher[strcspn(books[num_books].publisher, "\n")] = '\0';

    printf("Number of Pages: ");
    scanf("%d", &books[num_books].num_pages);

    // set status buku ke available
    books[num_books].is_borrowed = 0;

    num_books++;

    // tanyakan apakah user ingin menambahkan buku lagi
    char add_more[10];
    printf("Add more books? (y/n) ");
    scanf("%s", add_more);
    if (strcmp(add_more, "n") == 0) {
        break;
    }
    // membersihkan input buffer
    while (getchar() != '\n');
}

// tampilkan informasi buku
printf("\nLibrary Catalog\n");
int i;
for (i = 0; i < num_books; i++) {
    printf("\nBook #%d\n", i+1);
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
}

// menu utama
int choice;
char keyword[100], title[100];
do {
    printf("\nMenu\n");
    printf("1. Search Book\n");
    printf("2. Borrow Book\n");
    printf("3. Return Book\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            // mencari buku
            printf("Enter keyword: ");
            getchar(); // membersihkan input buffer
            fgets(keyword, sizeof(keyword), stdin);
            keyword[strcspn(keyword, "\n")] = '\0';
            searchBook(books, num_books, keyword);
            break;
        case 2:
            // meminjam buku
            printf("Enter title: ");
            getchar(); // membersihkan input buffer
            fgets(title, sizeof(title), stdin);
            title[strcspn(title, "\n")] = '\0';
            borrowBook(books, num_books, title);
            break;
        case 3:
            // mengembalikan buku
            printf("Enter title: ");
            getchar(); // membersihkan input buffer
            fgets(title, sizeof(title), stdin);
            title[strcspn(title, "\n")] = '\0';
            returnBook(books, num_books, title);
            break;
        case 4:
            // keluar dari program
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
} while (choice != 4);

return 0;
}

