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
            printf("Buku #%d\n", i+1);
            printf("Judul: %s\n", books[i].title);
            printf("Penulis: %s\n", books[i].author);
            printf("Penerbit: %s\n", books[i].publisher);
            printf("Jumlah halaman: %d\n", books[i].num_pages);
            if (books[i].is_borrowed) {
                printf("Status: Di pinjam\n");
            }
            else {
                printf("Status: Tersedia\n");
            }
            found = 1;
        }
    }
    if (!found) {
        printf("Tidak ditemukan buku dengan kata kunci \"%s\"\n", keyword);
    }
}

// fungsi untuk meminjam buku
void borrowBook(struct Book books[], int num_books, char title[]) {
    int i, found = 0;
    for (i = 0; i < num_books; i++) {
        if (strcmp(books[i].title, title) == 0) {
            if (books[i].is_borrowed) {
                printf("Buku \"%s\" sudah dipinjam.\n", title);
            }
            else {
                books[i].is_borrowed = 1;
                printf("Buku \"%s\" telah dipinjam.\n", title);
            }
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Buku \"%s\" tidak temukan.\n", title);
    }
}


// fungsi untuk mengembalikan buku
void returnBook(struct Book books[], int num_books, char title[]) {
    int i, found = 0;
    for (i = 0; i < num_books; i++) {
        if (strcmp(books[i].title, title) == 0) {
            if (books[i].is_borrowed) {
                books[i].is_borrowed = 0;
                printf("Buku \"%s\" telah dikembalikan.\n", title);
            }
            else {
                printf("Buku \"%s\" belum dipinjam.\n", title);
            }
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Buku \"%s\" tidak di temukan.\n", title);
    }
}

int main() {
    // inisialisasi array buku
    struct Book books[100];
    int num_books = 0;

    // loop untuk menambahkan buku
    while (num_books < 50) {
        printf("Tambahkan Buku #%d\n", num_books+1);

        // input informasi buku
        printf("Judul: ");
        fgets(books[num_books].title, sizeof(books[num_books].title), stdin);
        books[num_books].title[strcspn(books[num_books].title, "\n")] = '\0';

        printf("Penulis: ");
        fgets(books[num_books].author, sizeof(books[num_books].author), stdin);
		books[num_books].author[strcspn(books[num_books].author, "\n")] = '\0';
		
		printf("Penerbit: ");
    	fgets(books[num_books].publisher, sizeof(books[num_books].publisher), stdin);
    	books[num_books].publisher[strcspn(books[num_books].publisher, "\n")] = '\0';

    printf("Jumlah Halaman: ");
    scanf("%d", &books[num_books].num_pages);

    // set status buku ke available
    books[num_books].is_borrowed = 0;

    num_books++;

    // tanyakan apakah user ingin menambahkan buku lagi
    char add_more[10];
    printf("Tamabahkan buku lagi? (y/n) ");
    scanf("%s", add_more);
    if (strcmp(add_more, "n") == 0) {
        break;
    }
    // membersihkan input buffer
    while (getchar() != '\n');
}

// tampilkan informasi buku
printf("\nKatalog Perpustakaan\n");
int i;
for (i = 0; i < num_books; i++) {
    printf("\nBuku #%d\n", i+1);
    printf("Judul: %s\n", books[i].title);
    printf("Penulis: %s\n", books[i].author);
    printf("Penerbit: %s\n", books[i].publisher);
    printf("Jumlah Halaman: %d\n", books[i].num_pages);
    if (books[i].is_borrowed) {
        printf("Status: Di Pinjam\n");
    }
    else {
        printf("Status: Tersedia\n");
    }
}

// menu utama
int choice;
char keyword[100], title[100];
do {
    printf("\nMenu\n");
    printf("1. Cari Buku\n");
    printf("2. Pinjam Buku\n");
    printf("3. Kembalikan Buku\n");
    printf("4. Keluar\n");
    printf("Masukkan Pilihan Anda: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            // mencari buku
            printf("Masukkan Kata Kunci: ");
            getchar(); // membersihkan input buffer
            fgets(keyword, sizeof(keyword), stdin);
            keyword[strcspn(keyword, "\n")] = '\0';
            searchBook(books, num_books, keyword);
            break;
        case 2:
            // meminjam buku
            printf("Masukkan Judul: ");
            getchar(); // membersihkan input buffer
            fgets(title, sizeof(title), stdin);
            title[strcspn(title, "\n")] = '\0';
            borrowBook(books, num_books, title);
            break;
        case 3:
            // mengembalikan buku
            printf("Masukkan Judul: ");
            getchar(); // membersihkan input buffer
            fgets(title, sizeof(title), stdin);
            title[strcspn(title, "\n")] = '\0';
            returnBook(books, num_books, title);
            break;
        case 4:
            // keluar dari program
            printf("Terima kasih!\n");
            break;
        default:
            printf("Pilihan Salah.\n");
            break;
    }
} while (choice != 4);

return 0;
}
