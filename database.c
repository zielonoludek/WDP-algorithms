#include <stdio.h>
#include <stdlib.h>

#define scanf scanf_s

typedef struct {
    int id;
    char title[31];
    char author[31];
    int year;
    int categoryID;
    int libraryID;
} Book;

void addBook(Book** database, int* databaseSize) {
    (*databaseSize)++;
    *database = (Book*)realloc(*database, (*databaseSize) * sizeof(Book));
    Book newBook;

    printf("ID: ");
    scanf("%d", &newBook.id);

    printf("Title: ");
    while (getchar() != '\n');
    fgets(newBook.title, sizeof(newBook.title -1), stdin);

    printf("Year: ");
    scanf("%d", &newBook.year);

    printf("Author: ");
    while (getchar() != '\n');
    fgets(newBook.author, sizeof(newBook.author - 1), stdin);

    printf("Category ID: ");
    scanf("%d", &newBook.categoryID);

    printf("Library ID: ");
    scanf("%d", &newBook.libraryID);

    (*database)[(*databaseSize) - 1] = newBook;
    printf("Book added to the database.\n");
}

void delBook(Book** database, int* databaseSize, int bookId) {
    for (int i = 0; i < *databaseSize; i++) {
        if ((*database)[i].id == bookId) {
            (*database)[i] = (*database)[i + 1];
            (*databaseSize)--;

            *database = (Book*)realloc(*database, (*databaseSize) * sizeof(Book));
            printf("Book deleted.\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void bookList(const Book* database, int databaseSize) {
    for (int i = 0; i < databaseSize; i++) {
        printf("\nID: %d\n", database[i].id);
        printf("Title: %s", database[i].title);
        printf("Year: %d\n", database[i].year);
        printf("Author: %s", database[i].author);
        printf("Category ID: %d\n", database[i].categoryID);
        printf("Library ID: %d\n\n", database[i].libraryID);
    }
}

int main() {
    int databaseSize = 0;
    Book* database = NULL;

    int choice;
    int bookId;
    while (1) {
        printf("1. Add book\n");
        printf("2. Delete book\n");
        printf("3. Book list\n");
        printf("0. Exit\n");
        printf("Choose: ");

        scanf("%d", &choice);
        switch (choice) {
        case 1:
            addBook(&database, &databaseSize);
            break;
        case 2:
            printf("Enter ID of the book to remove: ");
            scanf("%d", &bookId);
            delBook(&database, &databaseSize, bookId);
            break;
        case 3:
            bookList(database, databaseSize);
            break;
        case 0:
            free(database);
            return 0;
        default:
            printf("Error\n");
        }
        printf("\n");
    }
    free(database);
    return 0;
}
