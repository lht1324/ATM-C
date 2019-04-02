#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client_info.h"
#include "function.h"

int transfer(int client, int count) // ��� ����� ����ϴ� �Լ��̴�.
{	// ��ü��� ���� ������, �� ���¿��� ���� ����� �ٸ� ����� ���¿� �Ա��ϴ� ���̴�.
	// ��� �Լ��� �Ϻκа� �Ա� �Լ��� �Ϻκ�, �׸��� 
	// ���¹�ȣ�� ��й�ȣ�� �� ���� ���� ���� �Լ��� �Ϻκ��� ��ģ �ڵ��̴�.
	char account[17], temp[17];
	// account : ��ü�� ���� ���¸� �Է¹��� ���ڿ��̴�.
	// temp : ���¹�ȣ ������ ���� ���� ���¹�ȣ ������ �ӽ÷� �Է¹��� ���ڿ��̴�.
	char c_money[16], d_money[16], b_money[16], bal[21];
	// c_money : client_money(���� �ܰ�)
	// d_money : deposit_money(�Ա��� ��)
	// b_money : balance_money(���� �ܰ� + �Ա��� ��)
	// bal : ������ �ܰ� �н����带 ��ģ ���� ���Ͽ� �Է��ϱ� ���� ���Ǵ� ���ڿ�.
	int i, j, len, result, end, receiver = 0, judge = 0;
	// i, j : �ݺ����� ���Ǵ� ����. len : ���� �ܰ� ��Ÿ�� ���ڿ��� ���̸� ������ ����.
	// result : ��ü �� ����� ������ ����. 
	// end : �ʱ� ȭ������ �� �� �� �� �� ���� �� ���Ǵ� ����.
	// receiver : ����ü �迭 s���� ��ü���� ����� �ε���.
	// judge : �۱��� ����� �Է��� ���¹�ȣ�� ��й�ȣ�� �Ǵ��ϴµ� ���Ǵ� ����.
	FILE *rfp;
	FILE *wfp;
	// ���� �����͸� �����Ѵ�.
	fopen_s(&rfp, "balance.txt", "r");
	fopen_s(&wfp, "balance_temp.txt", "w");
	// balance.txt�� �б� ����, balance_temp.txt�� ���� ���� ����.
	printf("��ü�Ͻ� ���¹�ȣ�� �Է����ּ��� : ");
	scanf_s("%s", account, 17); // ��ü�� ���� ���¹�ȣ�� �Է¹޴´�.

	for (i = 0; i < count; i++)
	{
		for (j = 0; j < 16; j++)
		{
			temp[j] = s[i].acc[j + 5];
		}
		temp[16] = '\0';

		if (strncmp(account, temp, 17) == 0)
			judge = 1;
		// �Է¹��� ���� ��ȣ�� ���� ���¿� ���ٸ� judge�� 1�̴�.
		else
			judge = 0;
		// �Է¹��� �� ���� ���¿� �ٸ��ٸ� judge�� 0�̴�.
		if (judge == 1)
		{
			receiver = i; // ���¹�ȣ�� �´ٸ� ��ü���� ����� �ε��� receiver�� i�� �Ѵ�.
			break;
		}

		if (i == count - 1 && judge == 0) 
		{
			printf("\n");
			printf("���¹�ȣ�� �߸� �Է��ϼ̽��ϴ�.\n");
			return -1;
		}	
		// �ݺ����� ������ ���� judge�� 0�̶�� ���¹�ȣ�� �߸� �Է��� ���̶� �Ǵ� ��
		// �Լ��� �����Ѵ�.
	}

	// 64����� 137������� client�� ���¿��� ����ϴ� �ڵ��̴�.

	for (i = 0; i < 16; i++)
	{
		c_money[i] = s[client].balance[i + 5];
	}

	result = atoi(c_money);

	printf("\n��ü�Ͻ� �ݾ��� �Է����ּ��� : ");
	scanf_s("%s", d_money, 16);

	if (result < atoi(d_money))
	{
		printf("\n�ܰ� �����մϴ�.\n");
		return 0;
	}
	else
		result -= atoi(d_money); 
	// ��ü�� �ݾ��� ���� �ܰ��� ����Ѵ�.

	_itoa_s(result, b_money, sizeof(b_money), 10);

	for (i = 0; i < 16; i++)
		s[client].balance[i + 5] = b_money[i];

	len = strlen(s[client].balance);

	printf("\n��ü�� �Ϸ�Ǿ����ϴ�.\n\n");

	for (i = 5; i < 20; i++)
	{
		if (i == 5)
			printf("������ ���� �ܰ�� ");

		if (s[client].balance[i] != '\0')
			printf("%c", s[client].balance[i]);

		if ((len - i + 2) % 3 == 0 && i != (len - 1))
			printf(",");

		if (i == (len - 1))
		{
			printf("���Դϴ�.\n\n");
			break;
		}
	}

	for (i = 0; ; i++)
	{
		if (i != client)
		{
			fgets(bal, sizeof(bal), rfp); // balance.txt���� �о� bal�� ����.

			if (feof(rfp))
				break;

			bal[strlen(bal)] = '\0';

			fprintf(wfp, "%s", bal); // client �̿ܿ� ���� ���� ���� balance_temp.txt�� �ۼ�.
		}

		if (i == client)
		{
			fgets(bal, sizeof(bal), rfp);
			// ���⼭ ���� ������ ���Ͽ� s[client].balance�� balance.txt����
			// �ŷ� ����� �����Ǳ� �� ���ڿ��� ���� ���δ�.
			fprintf(wfp, "%s\n", s[client].balance);
			// client�� ����ü���� �ܰ� ���ڿ��� �״�� ���Ͽ� ����.
		}
	}

	fclose(rfp);
	fclose(wfp);

	balance_modify(); // client�� ���¿��� ����� ����� ���� �ܰ� ���Ͽ� ����.
	
	fopen_s(&rfp, "balance.txt", "r");
	fopen_s(&wfp, "balance_temp.txt", "w");

	// ���� ������ rfp�� wfp�� �ݰ� balance.txt, balance_temp.txt�� ����
	// �б� ���, ���� ���� ���� ����.

	// 146����� 189������� receiver�� ���¿� �Ա��ϴ� �ڵ��̴�.

	for (i = 0; i < 16; i++)
	{
		c_money[i] = s[receiver].balance[i + 5];
	}

	result = atoi(c_money);

	result += atoi(d_money); // ��ü���� �ݾ��� ���� �ܰ� �Ա��Ѵ�.

	_itoa_s(result, b_money, sizeof(b_money), 10);

	for (i = 0; i < 16; i++)
		s[receiver].balance[i + 5] = b_money[i];

	for (i = 0; ; i++)
	{
		if (i != receiver)
		{
			fgets(bal, sizeof(bal), rfp); // balance.txt���� �о� bal�� ����.

			if (feof(rfp))
				break;

			bal[strlen(bal)] = '\0';

			fprintf(wfp, "%s", bal); // client �̿ܿ� ���� ���� ���� balance_temp.txt�� �ۼ�.
		}

		if (i == receiver)
		{
			fgets(bal, sizeof(bal), rfp);
			// ���⼭ ���� ������ ���Ͽ� s[client].balance�� balance.txt����
			// �ŷ� ����� �����Ǳ� �� ���ڿ��� ���� ���δ�.
			fprintf(wfp, "%s\n", s[receiver].balance);
			// receiver�� ����ü���� �ܰ� ���ڿ��� �״�� ���Ͽ� ����.
		}
	}

	fclose(rfp);
	fclose(wfp);

	balance_modify(); // receiver�� ���¿� �Ա��� ����� ���� �ܰ� ���Ͽ� ����.

	while (1)
	{
		printf("�ʱ� ȭ������ ���÷��� 0�� �Է����ּ��� : ");
		scanf_s("%d", &end);
		if (end == 0) // end�� 0�� �Է¹����� transfer() �Լ��� �����Ѵ�.
			return 0;
		else
			printf("\n�߸� �Է��ϼ̽��ϴ�.\n\n");
	}
}