#include <stdio.h>
#include "client_info.h"
#include "function.h"

void balance_modify() // �ܰ� �κ� ������ ���� ���� �ڵ�.
{	 // ���Ǵ� ���� ���� �Ա�, ���, ��ü ���� �ڵ���� ����� C ���Ϸ� ������.
	char str[21];
	// ���� �ݺ������� ���Ǵ� ���� 21�� ���ڿ� str�� �����Ѵ�.
	FILE *rfp;
	FILE *wfp;
	// ���� ������ rfp, wfp�� �����Ѵ�.
	fopen_s(&rfp, "balance_temp.txt", "r");
	fopen_s(&wfp, "balance.txt", "w");
	// balance_temp.txt�� �б� ����, balance.txt�� ���� ���� ����.
	// �Ա�, ���, ���� ��ü �Լ����� balance_temp.txt�� ������ balance.txt�� ������
	// �ۼ��ߴ�. �� �Լ��� �̿��� balance_temp.txt�� �Էµ� ���ο� �ܰ� ������ �ٽ�
	// balance.txt�� �����.
	while(1) // ���� �ݺ����̴�.
	{
		fgets(str, sizeof(str), rfp); // balance_temp.txt�� �� �پ� �д´�.

		if (feof(rfp)) // ������ ���̶�� �����Ѵ�.
			break;

		fprintf(wfp, "%s", str); // �о���� ������ balance.txt�� �����.
	}

	fclose(rfp);
	fclose(wfp);
	// rfp, wfp�� �ݴ´�.
}