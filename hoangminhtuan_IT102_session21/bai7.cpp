#include <stdio.h>
#include <string.h>

struct Book {
    char code[20];
    char title[100];
    char author[50];
    float price;
    char category[30];
};
void printBook(struct Book b) {
    printf("Ma sach: %s\n", b.code);
    printf("Ten sach: %s", b.title);
    printf("Tac gia: %s", b.author);
    printf("Gia: %.2f\n", b.price);
    printf("The loai: %s\n", b.category);
    printf("--------------------------\n");
}
void displayBooks(struct Book books[], int n) {
    if(n == 0) {
        printf("Chua co sach trong thu vien.\n");
        return;
    }
    for(int i = 0; i < n; i++) {
        printf("Sach thu %d:\n", i + 1);
        printBook(books[i]);
    }
}
int findBookByCode(struct Book books[], int n, char code[]) {
    for(int i = 0; i < n; i++) {
        if(strcmp(books[i].code, code) == 0) {
            return i;
        }
    }
    return -1; 
}
struct Book inputBook() {
    struct Book b;
    printf("Nhap ma sach: ");
    getchar(); 
    fgets(b.code, sizeof(b.code), stdin);

    printf("Nhap ten sach: ");
    fgets(b.title, sizeof(b.title), stdin);

    printf("Nhap tac gia: ");
    fgets(b.author, sizeof(b.author), stdin);

    printf("Nhap gia tien: ");
    scanf("%f", &b.price);

    printf("Nhap the loai: ");
    getchar(); 
    fgets(b.category, sizeof(b.category), stdin);

    return b;
}
void insertBook(struct Book books[], int *n, int pos, struct Book b) {
    for(int i = *n; i > pos; i--) {
        books[i] = books[i-1];
    }
    books[pos] = b;
    (*n)++;
}
void deleteBook(struct Book books[], int *n, char code[]) {
    int pos = findBookByCode(books, *n, code);
    if(pos == -1) {
        printf("Khong tim thay sach co ma %s\n", code);
        return;
    }
    for(int i = pos; i < *n - 1; i++) {
        books[i] = books[i+1];
    }
    (*n)--;
    printf("Da xoa sach co ma %s\n", code);
}
void updateBook(struct Book books[], int n, char code[]) {
    int pos = findBookByCode(books, n, code);
    if(pos == -1) {
        printf("Khong tim thay sach co ma %s\n", code);
        return;
    }
    printf("Nhap thong tin moi cho sach:\n");
    books[pos] = inputBook();
}
void sortBooksByPrice(struct Book books[], int n, int order) {
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if((order == 1 && books[i].price > books[j].price) ||
               (order == 2 && books[i].price < books[j].price)) {
                struct Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }
}
void searchBookByTitle(struct Book books[], int n, char title[]) {
    int found = 0;
    for(int i = 0; i < n; i++) {
        if(strstr(books[i].title, title) != NULL) {
            printBook(books[i]);
            found = 1;
        }
    }
    if(!found) {
        printf("Khong tim thay sach co ten \"%s\"\n", title);
    }
}
int main() {
    struct Book books[100];
    int n = 0; 
    int choice;

    do {
        printf("\n--- MENU QUAN LY THU VIEN ---\n");
        printf("1. Nhap so luong va thong tin sach\n");
        printf("2. Hien thi thong tin sach\n");
        printf("3. Them sach vao vi tri\n");
        printf("4. Xoa sach theo ma sach\n");
        printf("5. Cap nhat thong tin sach theo ma sach\n");
        printf("6. Sap xep sach theo gia\n");
        printf("7. Tim kiem sach theo ten\n");
        printf("8. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                int m;
                printf("Nhap so luong sach can them: ");
                scanf("%d", &m);
                for(int i = 0; i < m; i++) {
                    printf("\nNhap thong tin sach thu %d:\n", i+1);
                    books[n++] = inputBook();
                }
                break;
            }
            case 2:
                displayBooks(books, n);
                break;
            case 3: {
                int pos;
                printf("Nhap vi tri can them (bat dau tu 0): ");
                scanf("%d", &pos);
                if(pos < 0 || pos > n) {
                    printf("Vi tri khong hop le.\n");
                    break;
                }
                struct Book b = inputBook();
                insertBook(books, &n, pos, b);
                break;
            }
            case 4: {
                char code[20];
                printf("Nhap ma sach can xoa: ");
                getchar();
                fgets(code, sizeof(code), stdin);
                deleteBook(books, &n, code);
                break;
            }
            case 5: {
                char code[20];
                printf("Nhap ma sach can cap nhat: ");
                getchar();
                fgets(code, sizeof(code), stdin);
                updateBook(books, n, code);
                break;
            }
            case 6: {
                int order;
                printf("Chon cach sap xep (1: tang, 2: giam): ");
                scanf("%d", &order);
                if(order != 1 && order != 2) {
                    printf("Lua chon khong hop le.\n");
                    break;
                }
                sortBooksByPrice(books, n, order);
                printf("Da sap xep xong.\n");
                break;
            }
            case 7: {
                char title[100];
                printf("Nhap ten sach can tim: ");
                getchar();
                fgets(title, sizeof(title), stdin);
                searchBookByTitle(books, n, title);
                break;
            }
            case 8:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }

    } while(choice != 8);

    return 0;
}

