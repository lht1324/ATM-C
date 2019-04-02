#include <stdio.h>
#include <string.h>
#include "function.h"
#include "client_info.h"

int account_judge(int count) 
{	// �� ������ �Է� �޾� ���� �Է��� ���¹�ȣ�� ������ ��й�ȣ�� �´��� �Ǻ��ϴ� �Լ�.
	char account[17], password[5], temp_a[17], temp_p[3][5];
	// account : ���� �Է��� ���¹�ȣ. 
	// password : ���� �Է��� ��й�ȣ.
	// temp_a : �������� ���� ����ü���� ���¹�ȣ, �̸�, �ܰ��� ��й�ȣ��
	// ���ԵǾ� �ִ�. temp_a�� ��й�ȣ�� �� ���¹�ȣ�� ����ȴ�.
	// temp_p : ����ü�� ����� ���¹�ȣ, �̸�, �ܰ��� ��й�ȣ�� �о�� �����ϴ� 
	// ������ ���ڿ��̴�.
	int i, j, client = 0, judge = 0;
	// i, j : �ݺ��� ����� ���� ������ ����. 
	// client : ���� �� ����Ʈ���� �� ��°���� ����Ǿ� �Լ��� ���� �� ��µǴ� ����.
	// judge : ���¹�ȣ�� ��й�ȣ�� ��� �´ٸ� 1�� �Ǵ� �����̴�. 0���� �ʱ�ȭ.
	printf("���¹�ȣ�� �Է����ּ��� : ");
	scanf_s("%s", account, 17); // ���¹�ȣ�� �Է¹޴´�.
	
	for (i = 0; i < count; i++) // �� ������ŭ �ݺ��ϴ� for���̴�.
	{
		for (j = 0; j < 16; j++)
		{
			temp_a[j] = s[i].acc[j + 5]; // ������ ���� temp_a�� ���� ���¹�ȣ�� �����Ѵ�.
		}
		temp_a[16] = '\0'; // temp_a�� ������ ���Ҹ� NULL ������ �����Ѵ�.

		if (strncmp(account, temp_a, 17) == 0)
			judge = 1;
		else
			judge = 0;
		// ���� �Է��� ���¹�ȣ�� temp_a�� ��ġ�ϸ� judge�� 1�� �����Ѵ�.
		if (judge == 1)
		{
			client = i;
			break;
		} // judge�� 1�̸� client�� 1�� �����ϰ� ���¹�ȣ�� �����ϴ� for���� �����Ѵ�.

		if (i == count - 1 && judge == 0)
		{	// for���� ������ ���� judge�� 0�̶�� ���¹�ȣ�� �߸� �Է��� ���̴�.
			printf("\n");
			printf("���¹�ȣ�� �߸� �Է��ϼ̽��ϴ�.\n");
			return -1;
		}
	}

	printf("\n��й�ȣ�� �Է����ּ��� : ");
	scanf_s("%s", password, 5); // ��й�ȣ�� �Է¹޴´�.
	printf("\n");
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (i == 0) // ���¹�ȣ�� �Բ� ����� ��й�ȣ�� temp_p[0]�� �Է��Ѵ�.
				temp_p[i][j] = s[client].acc[j]; 
			if (i == 1) // �̸��� �Բ� ����� ��й�ȣ�� temp_p[1]�� �Է��Ѵ�.
				temp_p[i][j] = s[client].name[j];
			if (i == 2) // �ܰ�� �Բ� ����� ��й�ȣ�� temp_p[2]�� �Է��Ѵ�.
				temp_p[i][j] = s[client].balance[j];
		}
		temp_p[i][4] = '\0'; // temp_p[i]�� ������ ���ҿ� NULL ���� �����Ѵ�.

		if (strncmp(password, temp_p[i], 5) == 0) 
			judge = 1;
		else
			judge = 0;
		// temp_p[i]�� ���� �Է��� ��й�ȣ�� ������ judge�� 1�� �����Ѵ�.
		// �׷��� ������ judge�� 0�� �����Ѵ�.
	}

	if (judge == 1) // ���¹�ȣ�� ��й�ȣ�� ��� �´ٸ� judge�� 1�̴�.
		return client; // �� ����Ʈ���� ���� �� ��°���� �˷��ִ� ���� client�� ����Ѵ�.
	else // judge�� 1�� �ƴ϶�� ���¹�ȣ�� �°� �Է������� ��й�ȣ�� Ʋ�� ���̴�.
	{
		printf("��й�ȣ�� �߸� �Է��ϼ̽��ϴ�.\n");
		return -1; 
	}	
}