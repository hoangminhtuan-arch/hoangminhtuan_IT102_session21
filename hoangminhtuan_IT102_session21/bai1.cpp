#include <stdio.h>
#include <string.h>

struct Car {
    char model[50];   
    int year;         
    float price;      
};

int main() {
    struct Car myCar;
    strcpy(myCar.model, "Toyota Camry");
    myCar.year = 2020;
    myCar.price = 850000000;   

    // In thông tin xe
    printf("Thong tin xe cua ban:\n");
    printf("Model: %s\n", myCar.model);
    printf("Nam san xuat: %d\n", myCar.year);
    printf("Gia xe: %.0f VND\n", myCar.price);

    return 0;
}

