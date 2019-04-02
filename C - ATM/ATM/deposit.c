#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client_info.h"
#include "function.h"

int deposit(int client) // �Ա��� ����ϴ� �Լ��̴�.
{
	int i, len, result, end;
	// i : �ݺ����� ���Ǵ� �����̴�. len : ���� �ܰ��� ���̸� ������ �����̴�.
	// result : �Ա��� ����� ������ �����̴�.
	// end : �Ա� �� ������ �ʱ� ȭ������ �� �� ��� �� ���Ǵ� �����̴�.
	char c_money[16], d_money[16], b_money[16], bal[21];
	// client_money(���� �ܰ�), deposit_money(�Ա��� ��), balance_money(���� �ܰ� + �Ա��� ��)
	FILE *rfp;
	FILE *wfp;
	// ���� ������ 2���� �����Ѵ�.
	fopen_s(&rfp, "balance.txt", "r");
	fopen_s(&wfp, "balance_temp.txt", "w");
	// balance.txt�� �б� ����, balance_temp.txt�� ���� ���� ����.
	for (i = 0; i < 16; i++)
	{
		c_money[i] = s[client].balance[i + 5];
	}	// ���� �ܰ� ������ c_money�� �����Ѵ�.

	result = atoi(c_money); // result�� c_money�� ������ ��ȯ�� ���� �����Ѵ�.

	printf("�Ա��Ͻ� �ݾ��� �Է����ּ��� : ");
	scanf_s("%s", d_money, 16); // �Ա��� �ݾ��� �Է¹޴´�.

	result += atoi(d_money); // �Ա��� �ݾ��� d_money�� ������ �ٲ� result�� ���Ѵ�.

	_itoa_s(result, b_money, sizeof(b_money), 10);
	// �Ա� �� �ܰ� result�� ���ڿ��� �ٲ� b_money�� �����Ѵ�.
	for (i = 0; i < 16; i++)
		s[client].balance[i + 5] = b_money[i];
	// ���� ���� �ܰ� b_money�� �����Ѵ�.
	len = strlen(s[client].balance);

	printf("\n�Ա��� �Ϸ�Ǿ����ϴ�.\n\n");

	for (i = 5; i < 20; i++) // ������ �ܰ� ����ϴ� for���̴�.
	{
		if (i == 5)
			printf("������ ���� �ܰ�� ");

		if (s[client].balance[i] != '\0') 
			printf("%c", s[client].balance[i]);
		// s[client].balance[i]�� NULL���� �ƴ� ������ s[client].balance[i]�� ����Ѵ�.
		if ((len - i + 2) % 3 == 0 && i != (len - 1)) // 3�ڸ����� ','�� �����ش�.
			printf(",");

		if (i == (len - 1)) // �ܰ� ��� ����ϸ� �� �ڿ� �ٿ��ش�.
		{
			printf("���Դϴ�.\n\n");
			break;
		}
	}

	for (i = 0; ; i++) // ������ �ܰ� ���Ͽ� �Է��ϴ� for���̴�.
	{
		if (i != client)
		{
			fgets(bal, sizeof(bal), rfp); // balance.txt���� �� �� �о� bal�� �����Ѵ�.

			if (feof(rfp)) // ������ ���̶�� �ݺ��� �����Ѵ�.
				break;

			bal[strlen(bal)] = '\0'; // bal�� ������ ���ҿ� NULL ���� �����Ѵ�.

			fprintf(wfp, "%s", bal); // client�� �ƴ� ���� ���� balance_temp.txt�� �ۼ�.
		}

		if (i == client)
		{
			fgets(bal, sizeof(bal), rfp); 
			// ���⼭ ���� ������ ���Ͽ� s[client].balance�� balance.txt��
			// ������ ���� ���ڿ��� ���� ���δ�.
			fprintf(wfp, "%s\n", s[client].balance);
			// balance_temp.txt�� ���� ������ �ܰ� �Է��Ѵ�.
		}
	}

	fclose(rfp);
	fclose(wfp);
	// ���� ������ 2���� �ݴ´�.
	balance_modify();
	// �Լ� balance_modify(balance_temp.txt���� �о� balance.txt�� ���� �Լ�)
	// �� �����Ѵ�.
	while (1)
	{
		printf("�ʱ� ȭ������ ���÷��� 0�� �Է����ּ��� : ");
		scanf_s("%d", &end);
		if (end == 0) // end�� 0�� �Է¹����� deposit() �Լ��� �����Ѵ�.
			return 0;
		else
			printf("\n�߸� �Է��ϼ̽��ϴ�.\n\n");
	}
}