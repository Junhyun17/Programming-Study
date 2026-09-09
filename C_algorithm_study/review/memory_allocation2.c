#include<stdio.h>
#include<malloc.h>

void main() {
	int* p_num_list, count = 0, sum = 0, limit = 0, i;

	printf("사용할 최대 개수를 입력하세요 : ");
	scanf_s("%d", &limit);

	p_num_list = (int*)malloc(sizeof(int) * limit);

	while (count < limit) {
		printf("숫자를 입력하세요 (9999를 누르면 종료) : ");
		scanf_s("%d", p_num_list + count);
		if (*(p_num_list + count) == 9999)break;
		count++;
	}

	for (i = 0;i < count;i++) {
		if (i > 0)printf(" + ");
		printf(" %d ", *(p_num_list + i));
		sum = sum + *(p_num_list + i);
	}

	printf(" = %d\n", sum);
	free(p_num_list);
}