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

// fungsi untuk menambahkan buku
void addBook(struct Book books[], int *num_books) {
    // cek apakah masih ada ruang di katalog
    if (*num_books >= 100) {
        printf("Katalog penuh. Tidak dapat menambahkan buku.\n");
        return;
    }
    
    printf("Tambahkan Buku #%d\n", *num_books+1);

    // input informasi buku
    printf("Judul: ");
    fgets(books[*num_books].title, 100, stdin);
    books[*num_books].title[strcspn(books[*num_books].title, "\n")] = '\0'; // menghilangkan karakter newline di akhir string
    printf("Penulis: ");
    fgets(books[*num_books].author, 100, stdin);
    books[*num_books].author[strcspn(books[*num_books].author, "\n")] = '\0';
    
    printf("Penerbit: ");
    fgets(books[*num_books].publisher, 100, stdin);
    books[*num_books].publisher[strcspn(books[*num_books].publisher, "\n")] = '\0';
    
    printf("Jumlah halaman: ");
    scanf("%d", &books[*num_books].num_pages);
    getchar(); // mengambil karakter newline yang tersisa setelah input angka

    books[*num_books].is_borrowed = 0;
    (*num_books)++;
    printf("Buku berhasil ditambahkan ke katalog.\n");
}


int main() {
	struct Book books[100]{
		{"The Lord of the Rings", "J.R.R. Tolkien", "George Allen & Unwin", 1178, 0},
        {"To Kill a Mockingbird", "Harper Lee", "J.B. Lippincott & Co.", 281, 0},
        {"1984", "George Orwell", "Secker & Warburg", 328, 0},
        {"Animal Farm", "George Orwell", "Secker & Warburg", 112, 0},
        {"The Catcher in the Rye", "J.D. Salinger", "Little, Brown and Company", 277, 0}
	};
	int num_books = 5, choice;
	char keyword[100], title[100];
	do {
    printf("1. Tambah Buku\n");
    printf("2. Cari Buku\n");
    printf("3. Pinjam Buku\n");
    printf("4. Kembalikan Buku\n");
    printf("5. Lihat Buku yang Tersedia\n");
    printf("6. Keluar\n");
    printf("Pilihan: ");
    scanf("%d", &choice);
    getchar(); // mengambil karakter newline yang tersisa setelah input angka

    switch(choice) {
        case 1:
            addBook(books, &num_books);
            break;
        case 2:
            printf("Masukkan kata kunci: ");
            fgets(keyword, 100, stdin);
            keyword[strcspn(keyword, "\n")] = '\0';
            searchBook(books, num_books, keyword);
            break;
        case 3:
            printf("Masukkan judul buku yang ingin dipinjam: ");
            fgets(title, 100, stdin);
            title[strcspn(title, "\n")] = '\0';
            borrowBook(books, num_books, title);
            break;
        case 4:
            printf("Masukkan judul buku yang ingin dikembalikan: ");
            fgets(title, 100, stdin);
            title[strcspn(title, "\n")] = '\0';
            returnBook(books, num_books, title);
            break;
        case 5: // tambahkan case untuk pilihan nomor 6
        printf("Buku yang tersedia:\n");
        for (int i = 0; i < num_books; i++) {
        	if (!books[i].is_borrowed) { // jika buku tidak sedang dipinjam
           		 printf("Buku #%d\n", i+1);
            	printf("Judul: %s\n", books[i].title);
            	printf("Penulis: %s\n", books[i].author);
            	printf("Penerbit: %s\n", books[i].publisher);
            	printf("Jumlah halaman: %d\n", books[i].num_pages);
            	printf("\n");
        	}
        } break;
        case 6:
            printf("Program berakhir.\n");
            break;
        default:
            printf("Pilihan tidak valid.\n");
            break;
   	 }
	} while (choice != 6);

return 0;
}
