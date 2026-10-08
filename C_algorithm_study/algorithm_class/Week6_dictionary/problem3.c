#include <stdio.h>
#pragma warning(disable:4996)

int findnumber(int a, int b, char* yn, int length) {
    int left = a, right = b, i;

    for (i = 0; i < length; i++) {
        int mid = (left + right) / 2;
        if (yn[i] == 'Y') {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }

    return left;
}

int main() {
    int a, b, length, result;
    char yn[100];

    scanf("%d %d %d", &a, &b, &length);
    scanf("%s", yn);

    result = findnumber(a, b, yn, length);
    printf("%d\n", result);

    return 0;
}