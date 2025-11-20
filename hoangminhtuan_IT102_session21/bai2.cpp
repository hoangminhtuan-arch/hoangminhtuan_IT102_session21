#include <stdio.h>

struct Student {
    char name[50];
    int age;
    float grade;
};

int main() {
    struct Student student1;
    printf("Nhap ten hoc sinh: ");
    fgets(student1.name, sizeof(student1.name), stdin);

    printf("Nhap tuoi: ");
    scanf("%d", &student1.age);

    printf("Nhap diem trung binh: ");
    scanf("%f", &student1.grade);

    printf("\n--- THONG TIN HOC SINH ---\n");
    printf("Ten: %s", student1.name);
    printf("Tuoi: %d\n", student1.age);
    printf("Diem trung binh: %.2f\n", student1.grade);

    return 0;
}

