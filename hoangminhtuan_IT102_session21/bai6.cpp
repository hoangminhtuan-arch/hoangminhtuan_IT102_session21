#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int age;
    float grade;
};
void searchStudentByName(struct Student students[], int n, char targetName[]) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(students[i].name, targetName) == 0) {
            printf("\n--- Thong tin hoc sinh ---\n");
            printf("Ten: %s\n", students[i].name);
            printf("Tuoi: %d\n", students[i].age);
            printf("Diem trung binh: %.2f\n", students[i].grade);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay hoc sinh co ten '%s'.\n", targetName);
    }
}

int main() {
	int NUM_STUDENTS ;
    struct Student students[NUM_STUDENTS];
    for (int i = 0; i < NUM_STUDENTS; i++) {
        printf("\nNhap thong tin hoc sinh thu %d:\n", i + 1);

        printf("Ten: ");
        fgets(students[i].name, sizeof(students[i].name), stdin);
        students[i].name[strcspn(students[i].name, "\n")] = '\0';

        printf("Tuoi: ");
        scanf("%d", &students[i].age);

        printf("Diem trung binh: ");
        scanf("%f", &students[i].grade);

        getchar(); 
    }
    char searchName[50];
    printf("\nNhap ten hoc sinh can tim: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    searchStudentByName(students, NUM_STUDENTS, searchName);

    return 0;
}

