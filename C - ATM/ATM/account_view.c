#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#include "client_info.h"

int account_view(int client) // ���¸� ��ȸ�ϴ� �Լ��̴�.
{
	int i, len1, len2, len3, end;
	// i : �ݺ����� ���Ǵ� �����̴�. 
	// len1���� len3 : ����ü ���ο��� �̸�, ���¹�ȣ, �ܰ� �����ϴ� ���ڿ��� ����.
	// end : ������ 0�̶�� �Լ��� ������.
	len1 = strlen(s[client].name);
	len2 = strlen(s[client].acc);
	len3 = strlen(s[client].balance);

	printf("���� : ");

	for (i = 5; i < len1; i++)
	{
		if (s[client].name[i] != '\0') 
			printf("%c", s[client].name[i]);

		else if (s[client].name[i] == '\0') 
			break;
	}// ���� �̸��� ������ ���ڿ��� ������ ����Ѵ�.
	// ���ڿ��� ���Ұ� NULL���̶�� for���� �����Ѵ�.
	printf("\n");

	printf("���� ��ȣ : ");

	for (i = 5; i < len2; i++)
	{
		if (s[client].acc[i] != '\0')
			printf("%c", s[client].acc[i]);
			
		else if (s[client].acc[i] == '\0')
				break;
	} // ���� ���¸� ������ ���ڿ��� ������ ����Ѵ�. 
	// ���ڿ��� ���Ұ� NULL���̶�� for���� �����Ѵ�.
	printf("\n");
	
	printf("�ܰ� : ");

	for (i = 5; i < len3; i++)
	{
		if (s[client].balance[i] != '\0')
			printf("%c", s[client].balance[i]);

		if ((len3 - i + 1) % 3 == 0 && i != (len3 - 2)) // ���� �� �ڸ����� ��ǥ�� �����ش�.
			printf(",");

		if (i == (len3 - 2) || s[client].balance[5] == '0')
		{
			printf("��\n\n");
			break;
		} // �ݺ����� �������̰ų�, �ܰ� 0���� ��
		// (��й�ȣ 4�ڸ� + ���� ' ' 1�ڸ� + �ܰ� '0' 1�ڸ�) ������ �ڿ� "��\n\n"�� ����Ѵ�.
	}

	while (1)
	{
		printf("�ʱ� ȭ������ ���÷��� 0�� �Է����ּ��� : ");
		scanf_s("%d", &end);
		if (end == 0) // end�� 0�� �Է¹����� account_view() �Լ��� �����Ѵ�.
			return 0;
		else
			printf("\n�߸� �Է��ϼ̽��ϴ�.\n\n");
	}
}