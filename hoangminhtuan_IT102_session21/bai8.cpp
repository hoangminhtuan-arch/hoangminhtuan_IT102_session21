#include <stdio.h>
#include <string.h>

struct Product {
    char code[20];
    char name[50];
    float importPrice;
    float salePrice;
    int quantity;
};

void printProduct(struct Product p) {
    printf("Ma san pham: %s\n", p.code);
    printf("Ten san pham: %s", p.name); 
    printf("Gia nhap: %.2f\n", p.importPrice);
    printf("Gia ban: %.2f\n", p.salePrice);
    printf("So luong: %d\n", p.quantity);
    printf("---------------------------\n");
}
void displayProducts(struct Product products[], int n) {
    if(n == 0) {
        printf("Chua co san pham trong cua hang.\n");
        return;
    }
    for(int i = 0; i < n; i++) {
        printf("San pham thu %d:\n", i + 1);
        printProduct(products[i]);
    }
}
int findProductByCode(struct Product products[], int n, char code[]) {
    for(int i = 0; i < n; i++) {
        if(strcmp(products[i].code, code) == 0) {
            return i;
        }
    }
    return -1;
}

struct Product inputProduct() {
    struct Product p;
    printf("Nhap ma san pham: ");
    getchar(); 
    fgets(p.code, sizeof(p.code), stdin);

    printf("Nhap ten san pham: ");
    fgets(p.name, sizeof(p.name), stdin);

    printf("Nhap gia nhap: ");
    scanf("%f", &p.importPrice);

    printf("Nhap gia ban: ");
    scanf("%f", &p.salePrice);

    printf("Nhap so luong: ");
    scanf("%d", &p.quantity);

    return p;
}
void updateProduct(struct Product products[], int n, char code[]) {
    int pos = findProductByCode(products, n, code);
    if(pos == -1) {
        printf("Khong tim thay san pham co ma %s\n", code);
        return;
    }
    printf("Nhap thong tin moi cho san pham:\n");
    products[pos] = inputProduct();
}
void sortProductsByPrice(struct Product products[], int n, int order) {
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if((order == 1 && products[i].salePrice > products[j].salePrice) ||
               (order == 2 && products[i].salePrice < products[j].salePrice)) {
                struct Product temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }
}
void searchProductByName(struct Product products[], int n, char name[]) {
    int found = 0;
    for(int i = 0; i < n; i++) {
        if(strstr(products[i].name, name) != NULL) {
            printProduct(products[i]);
            found = 1;
        }
    }
    if(!found) {
        printf("Khong tim thay san pham co ten \"%s\"\n", name);
    }
}

void importProduct(struct Product products[], int *n, float *revenue) {
    struct Product p = inputProduct();
    int pos = findProductByCode(products, *n, p.code);
    if(pos != -1) {
        products[pos].quantity += p.quantity;
    } else {
        products[(*n)++] = p;
    }
    *revenue -= p.quantity * p.importPrice;
    printf("Da nhap san pham va cap nhat doanh thu.\n");
}
void sellProduct(struct Product products[], int n, float *revenue) {
    char code[20];
    int qty;
    printf("Nhap ma san pham can ban: ");
    getchar();
    fgets(code, sizeof(code), stdin);

    int pos = findProductByCode(products, n, code);
    if(pos == -1) {
        printf("Khong tim thay san pham.\n");
        return;
    }

    if(products[pos].quantity == 0) {
        printf("San pham het hang.\n");
        return;
    }

    printf("Nhap so luong can ban: ");
    scanf("%d", &qty);

    if(qty > products[pos].quantity) {
        printf("Khong con du hang.\n");
        return;
    }

    products[pos].quantity -= qty;
    *revenue += qty * products[pos].salePrice;
    printf("Da ban %d san pham.\n", qty);
}

int main() {
    struct Product products[100];
    int n = 0;
    float revenue = 0; 
    int choice;

    do {
        printf("\n--- MENU QUAN LY CUA HANG ---\n");
        printf("1. Nhap so luong va thong tin san pham\n");
        printf("2. Hien thi danh sach san pham\n");
        printf("3. Nhap san pham\n");
        printf("4. Cap nhat thong tin san pham\n");
        printf("5. Sap xep san pham theo gia\n");
        printf("6. Tim kiem san pham\n");
        printf("7. Ban san pham\n");
        printf("8. Doanh thu hien tai\n");
        printf("9. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                int m;
                printf("Nhap so luong san pham can them: ");
                scanf("%d", &m);
                for(int i = 0; i < m; i++) {
                    printf("\nNhap thong tin san pham thu %d:\n", i+1);
                    products[n++] = inputProduct();
                }
                break;
            }
            case 2:
                displayProducts(products, n);
                break;
            case 3:
                importProduct(products, &n, &revenue);
                break;
            case 4: {
                char code[20];
                printf("Nhap ma san pham can cap nhat: ");
                getchar();
                fgets(code, sizeof(code), stdin);
                updateProduct(products, n, code);
                break;
            }
            case 5: {
                int order;
                printf("Chon cach sap xep (1: tang, 2: giam): ");
                scanf("%d", &order);
                if(order != 1 && order != 2) {
                    printf("Lua chon khong hop le.\n");
                    break;
                }
                sortProductsByPrice(products, n, order);
                printf("Da sap xep xong.\n");
                break;
            }
            case 6: {
                char name[50];
                printf("Nhap ten san pham can tim: ");
                getchar();
                fgets(name, sizeof(name), stdin);
                searchProductByName(products, n, name);
                break;
            }
            case 7:
                sellProduct(products, n, &revenue);
                break;
            case 8:
                printf("Doanh thu hien tai: %.2f\n", revenue);
                break;
            case 9:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }

    } while(choice != 9);

    return 0;
}

