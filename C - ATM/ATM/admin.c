#include <stdio.h>
#include <string.h>
#include "client_info.h"
#include "function.h"

int admin(int count, int start) // ������ ��带 �ٷ�� �Լ�.
{	// count�� �� �� ��, start�� ó�� �����ϴ��� �ƴ����� ���θ� �ٷ��.
	// ���α׷��� �������� �� ���� ���� ����ȴ�. 
	// ���� ATM ������ �� �� ������ ���� ���ѵ� ����.
	// �����ڰ� ������ �Ѵ� ���� ������ �Ѵ�.

	int i, finish, client, choice = 0;
	// i : �ݺ������� ���Ǵ� ����. finish : ���� ���θ� ���� �� ���Ǵ� ����.
	// client : ���� �� ����Ʈ���� �� ��°���� ������ ����.
	// choice : switch~case������ �Ű� ������ ���ȴ�.
	char password[5], test[5];
	// password : ���� ������ ��й�ȣ�� �о� �����Ѵ�.
	// test : 
	enum menu {
		user = 0, create, delete, end
	}; // �������� �̿��� switch~case������ ���Ǵ� �������� �����Ѵ�.

	FILE *rfp; // ���� �����͸� �����Ѵ�.

	fopen_s(&rfp, "admin_password.txt", "r");
	// ������ ��й�ȣ�� ����� �ؽ�Ʈ ������ �б� ���� ����.
	fgets(password, 5, rfp); // ������ ��й�ȣ�� �о�´�.

	password[4] = '\0'; // password�� ������ ���ҿ� NULL ���� �����Ѵ�.

	printf("��й�ȣ�� �Է����ּ��� : ");
	scanf_s("%s", test, 5); // ������ ��带 �� �ι����� ��й�ȣ�� �Է¹޴´�.
	test[4] = '\0'; // test�� ������ ���ҿ� NULL ���� �����Ѵ�.

	for (i = 0; i < 5; i++)
	{
		if (test[i] != password[i]) // ��й�ȣ�� �߸� �ԷµǾ��� ���� ã�� if���̴�.
		{
			printf("\n��й�ȣ�� �߸� �Է��ϼ̽��ϴ�.\n\n");
			if (start == 1)
			{	// main()�Լ� ������ �ݺ��� ���� �� ����� admin() �Լ�����
				// ��й�ȣ�� Ʋ�ȴٸ� �ʱ� �޴��� ���ư��� ���� �ƴ϶� ���α׷��� �����Ѵ�.
				printf("��⸦ �����մϴ�.\n\n");
				return 1;
			}
			else 
			{	// main() �Լ� ������ �ݺ������� ����� admin() �Լ����� ��й�ȣ�� Ʋ���ٸ�
				// ����� ���� �ٽ� ���ư���.
				printf("���� ������ ȹ���� �� �����ϴ�.\n\n");
				printf("�ʱ� �޴��� ���ư��ϴ�.\n");
				return 0;
			}
		}
	}

	while (1) // ���� �ݺ� while���̴�.
	{
		count = account_load(); // ���¸� ����, ������ �� ����� �� ������ �ٽ� �д´�.

		printf("\n-------------------------------------\n\n");
		printf("--- ������ ��忡 �����ϼ̽��ϴ�. ---\n\n");
		printf("<1> ���� ����\n\n");
		printf("<2> ���� ����\n\n");
		printf("<3> ��� ����\n\n");
		printf("<0> ����� ���\n\n");
		printf("������ �� �� ������ �ֽʽÿ� : ");
		scanf_s("%d", &choice); // choice�� �Է¹޴´�.
		printf("\n-------------------------------------\n\n");
		switch (choice) // chioce�� �Ű� ������ �� switch~case ���� �����Ѵ�.
		{
		case user: // user = 0, admin()�� ����, �� ����� ���� ���ư���.
			printf("����� ���� ��ȯ�մϴ�.\n");
			return 0;
			break;
		case create: // create = 1, ���� ���� �Լ��� create_account()�� �����Ѵ�.
			create_account(count);
			break;
		case delete: // delete = 2, ���� ���� �Լ��� delete_account()�� �����Ѵ�.
			client = account_judge(count);
			delete_account(client); 
			// delete_account()�� ���� �� ��°���� �˷��ִ� ����
			// client�� �Ű������� �ִ´�.
			break;
		case end: // end = 3, ���α׷��� �����Ѵ�.
			printf("��⸦ �����Ͻðڽ��ϱ�? <Yes : 1, No : 0> : ");
			scanf_s("%d", &finish); // finish�� �Է¹޴´�.
			printf("\n");

			if (finish == 1) // finish�� 1�̸� 1�� ����Ѵ�.
			{
				printf("��⸦ �����մϴ�.\n\n");
				return 1;
			}
			else // finish�� 1�� �ƴ϶�� ������ ��� �ʱ� ȭ������ ���ư���.
			{
				printf("�ʱ� ȭ������ ���ư��ϴ�.\n");
				break;
			}
		default: // �߸��� ���� �Է¹޾Ҵٸ� switch~case���� ������ �� �ٽ� �����Ѵ�.
			printf("�޴� ������ �߸� �ϼ̽��ϴ�. �ٽ� �������ֽʽÿ�.\n");
			break;
		}
	}
}