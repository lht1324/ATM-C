#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client_info.h"
#include "function.h"

void delete_account(int client) // ���� ���Ÿ� �ϴ� �Լ��̴�.
{	// �� �Լ��� �⺻������ ���Ͽ��� ���� �� ���� ����� �ϴµ�, ���� �κ���
	// �б⸸ �ϰ� ���� �ʴ� ������� ���Ͽ��� ���� ���� ������ �����Ѵ�. 
	int i, end; // i : �ݺ��� ����� ���� �����̴�. 
						// end : ������ �ʱ� ȭ������ �� �� ���� �� ���Ǵ� �����̴�.
	char acc[30], name[30], bal[30];
	// acc.txt, name.txt, bal.txt���� ���� ������ �ӽ÷� ������ ���ڿ����̴�.

	FILE *rfp1;
	FILE *rfp2;
	FILE *rfp3;
	FILE *wfp1;
	FILE *wfp2;
	FILE *wfp3;
	// �б�, ���⿡ �� ���� ������ 6���� �����Ѵ�.
	fopen_s(&rfp1, "acc.txt", "r");
	fopen_s(&rfp2, "name.txt", "r");
	fopen_s(&rfp3, "balance.txt", "r");
	fopen_s(&wfp1, "acc_temp.txt", "w");
	fopen_s(&wfp2, "name_temp.txt", "w");
	fopen_s(&wfp3, "balance_temp.txt", "w");
	// ���� acc.txt, name.txt, balance.txt�� �б� ����, �ӽ÷� ������ ������ ���ϵ���
	// ���� ���� ����.
	for (i = 0; ; i++) // �ʱ갪, �����ĸ� �ְ� ���ǽ��� �� ���� �ݺ� for���̴�.
	{
		if (i != client) // i�� client�� �ƴ� �� ���� ���Ͽ��� ���� �� �ӽ� ���Ͽ� �Է��Ѵ�.
		{	
			fgets(acc, sizeof(acc), rfp1);
			fgets(name, sizeof(name), rfp2);
			fgets(bal, sizeof(bal), rfp3);
			// ���� ���Ͽ��� ������ �о�´�.
			if (feof(rfp1) && feof(rfp2) && feof(rfp3)) // ������ ���̶�� �ݺ��� �����Ѵ�.
				break;

			acc[strlen(acc)] = '\0';
			name[strlen(name)] = '\0';
			bal[strlen(bal)] = '\0';
			// acc, name, bal�� ������ ���ҿ� NULL ���� �����Ѵ�.
			fprintf(wfp1, "%s", acc);
			fprintf(wfp2, "%s", name);
			fprintf(wfp3, "%s", bal);
			// �ӽ� ���Ͽ� ���� ���Ͽ��� �о�� �� ������ �Է��Ѵ�.
		}

		if (i == client) // i�� ������ �� ��ȣ�� ���ٸ�
		{
			fgets(acc, sizeof(acc), rfp1);
			fgets(name, sizeof(name), rfp2);
			fgets(bal, sizeof(bal), rfp3);
			// �б⸸ �Ѵ�. ���� ���� �ʰ� �Ѿ�ٸ� ��ǻ�ʹ� �������� ���ϰ�, i + 1�� �Ǿ��� ��
			// client ���� ������ �о������. ���� �� ���� �ʴ� ������ ��ü ����Ʈ���� Ư��
			// ���� ������ �����Ѵ�.
		}	
	}

	fclose(rfp1);
	fclose(rfp2);
	fclose(rfp3);
	fclose(wfp1);
	fclose(wfp2);
	fclose(wfp3);
	// ���� ������ 6���� �ݴ´�.
	fopen_s(&rfp1, "acc_temp.txt", "r");
	fopen_s(&rfp2, "name_temp.txt", "r");
	fopen_s(&rfp3, "balance_temp.txt", "r");
	fopen_s(&wfp1, "acc.txt", "w");
	fopen_s(&wfp2, "name.txt", "w");
	fopen_s(&wfp3, "balance.txt", "w");
	// �ӽ� ���ϵ��� �б� ����, ���� ���ϵ��� ���� ���� ����.
	while (1)
	{
		fgets(acc, sizeof(acc), rfp1);
		fgets(name, sizeof(name), rfp2);
		fgets(bal, sizeof(bal), rfp3);

		if (feof(rfp1) && feof(rfp2) && feof(rfp3))
			break;

		fprintf(wfp1, "%s", acc);
		fprintf(wfp2, "%s", name);
		fprintf(wfp3, "%s", bal);
	}	// Ư�� �� ������ ���ŵ� �ӽ� ���ϵ��� ������ ���� ���Ͽ� �����.

	fclose(rfp1);
	fclose(rfp2);
	fclose(rfp3);
	fclose(wfp1);
	fclose(wfp2);
	fclose(wfp3);

	// ���� ������ 6���� �ݴ´�.

	printf("���°� ���ŵǾ����ϴ�. �̿� �����մϴ�.\n\n");

	while (1)
	{
		printf("�ʱ� ȭ������ ���÷��� 0�� �Է����ּ��� : ");
		scanf_s("%d", &end);
		if (end == 0) // end�� 0�� �Է¹����� delete_account() �Լ��� �����Ѵ�.
			return 0;
		else
			printf("\n�߸� �Է��ϼ̽��ϴ�.\n\n");
	}
}