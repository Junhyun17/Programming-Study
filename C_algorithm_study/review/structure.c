#include <stdio.h>

typedef struct People {
    char name[12];
    unsigned short int age;
    float height;
    float weight;
} Person;

int main(void) {
    Person data;

    printf("대상자의 정보를 입력하세요\n");

    printf("이름 : ");
    scanf_s("%s", data.name, (unsigned)sizeof(data.name));

    printf("나이 : ");
    scanf_s("%hu", &data.age);

    printf("키 : ");
    scanf_s("%f", &data.height);

    printf("몸무게 : ");
    scanf_s("%f", &data.weight);

    printf("\n입력한 정보는 다음과 같습니다.\n");
    printf("%s : %hu세, %.1fcm, %.1fkg\n",
        data.name, data.age, data.height, data.weight);

    return 0;
}