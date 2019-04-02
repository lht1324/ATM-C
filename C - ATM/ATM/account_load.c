#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client_info.h"

int account_load()
{	// ���¹�ȣ, �̸�, �ܰ� ����� �ؽ�Ʈ ���Ͽ��� �� ������ �о� ����ü �迭�� �����Ѵ�.
	// ����ü �迭�� �����Ҵ����� �����Ѵ�.
	int count = 1;
	char str_a[30], str_n[30], str_b[30];
	// count : �� �� ��. ������ ������ �д� �ݺ����� ����Ǿ�� �ϴ� ���� ������
	// 1�� �߰��ǰ�, ������ ������ ������ 1�� �� count�� ����Ѵ�. �ݺ������� 
	// feof�� count++���� �տ� �ֱ� ������ count�� �������� 1�� �� �������� �����̴�.
	s = (struct info*) calloc(sizeof(struct info), count);
	// ����ü ��� ���Ͽ��� ����� ����ü ������ ���� s�� count��ŭ 
	// calloc �Լ��� ����� �����Ҵ��Ѵ�.
	FILE *rfp1;
	FILE *rfp2;
	FILE *rfp3;
	// ���������͸� �����Ѵ�.
	fopen_s(&rfp1, "acc.txt", "r");
	fopen_s(&rfp2, "name.txt", "r");
	fopen_s(&rfp3, "balance.txt", "r");
	// ���¹�ȣ, �̸�, �ܰ� �ؽ�Ʈ ������ �б� ���� ����.
	while (1) // ���� �ݺ��ϴ� while���̴�.
	{
		fgets(str_a, sizeof(str_a), rfp1);
		fgets(str_n, sizeof(str_n), rfp2);
		fgets(str_b, sizeof(str_b), rfp3);
		// ���¹�ȣ, �̸�, �ܰ� �ؽ�Ʈ ������ �� �پ� �д´�.
		if (feof(rfp1) && feof(rfp2) && feof(rfp3))
		{
			count--;
			break;
		} // �ؽ�Ʈ ���ϵ��� ���̶�� count���� 1�� �� �� ���ѹݺ��� �����Ѵ�.
		
		str_a[strlen(str_a)] = '\0';
		str_n[strlen(str_n)] = '\0';
		str_b[strlen(str_b)] = '\0';
		// str_a, str_n, str_b�� ������ ���ҿ� NULL ���� �����Ѵ�.
		strcpy_s(s[count - 1].acc, sizeof(str_a), str_a);
		strcpy_s(s[count - 1].name, sizeof(str_n), str_n);
		strcpy_s(s[count - 1].balance, sizeof(str_b), str_b);
		// ����ü�� �о���� �� ������ �����Ѵ�. count�� 0�� �ƴ� 1���� �����ϴ� ���̴�
		// 1�� ���� ����ü�� �ε����� ����Ѵ�.
		count++; // ���� ������ count�� 1�� ���Ѵ�.

		s = (struct info*) realloc(s, sizeof(struct info) * count);
		// 1�� ������ count��ŭ realloc �Լ��� ����� ���� �޸𸮸� ���Ҵ��Ѵ�.
	}

	fclose(rfp1);
	fclose(rfp2);
	fclose(rfp3);
	// ���� ������ rfp1, rfp2, rfp3�� �ݴ´�.
	return count; // �� ���� �� ������ ��Ÿ���� ���� count�� ����Ѵ�.
}