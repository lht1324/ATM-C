#include <stdio.h>
#include <stdlib.h>
#include <string.h.>
#include <malloc.h>
#include <time.h>
#include "function.h"
#include "client_info.h"
// acc.txt : ���¹�ȣ�� �����ϴ� �ؽ�Ʈ ����.
// name.txt : �̸��� �����ϴ� �ؽ�Ʈ ����.
// balance.txt : ���� �ܰ� �����ϴ� �ؽ�Ʈ ����.
// acc_temp.txt : acc.txt�� ����� ���¹�ȣ�� ��� �� ���Ǵ� �ؽ�Ʈ ����.
// name_temp.txt : name.txt�� ����� �̸��� ��� �� ���Ǵ� �ؽ�Ʈ ����.
// balance_temp.txt : balance.txt�� ����� ���� �ܰ� ��� �� ���Ǵ� �ؽ�Ʈ ����.
int main()
{
	int count, choice, client = 0, finish = 0, start = 1;
	// admin_finish = ������ ��忡�� �޴� ���� ����

	printf("GC OS ver.1.0.0 ����.\n\n");

	printf("GC���� ATM ���� �����մϴ�.\n\n");

	count = account_load(); 
	// admin()�� ������ ���� account_load()�� ������ �� ������ ��� count�� �����Ѵ�.
	finish = admin(count, start);
	// ���α׷��� ó�� ������ ���� ������ ��忡�� �����Ѵ�. 
	if (finish == 1) // ó�� ������ ������ ��忡�� ��й�ȣ�� Ʋ�ȴٸ� ���α׷��� ����ȴ�.
		return 0;

	start = 0;
	// admin() ���ο��� ��й�ȣ�� Ʋ���� �� �ٷ� �����ϴ� ���� �� 20����
	// admin() �Լ��������̴�. ���� �ݺ������� admin()�� ����� �� �Ű� ���� 
	// start�� 0���� ����. 20���� admin() �Լ� ���� ���� ����Ǵ� admin()������
	// ��й�ȣ�� Ʋ���� ���α׷��� ����Ǵ� �� �ƴ϶� ����� ���� ���ƿ´�.

	while(finish == 0)
	{
		count = account_load(); 
		// �Ա�, ���, ��ü, ���� ����, ���� �� �� ������ �ٲ�ų� ������ ������ �ٲ��
		// �Լ��� �����Ƿ� while���� �ݺ��� ������ ������ ������ �ٽ� �о� ����ü��
		// �����ϰ� �� ������ ���� ���Ѵ�.
		choice = kiosk(); // �Լ� kiosk()�� ������ ���� ������ ���� choice�� �����Ѵ�.

		switch (choice) // choice�� �Ű� ������ �� �۵��ϴ� switch~case()���̴�.
		{
		case 0: // ������ ���.
			finish = admin(count, start); // admin()�� ������ finish�� �Է¹޴´�.

			while (1)
			{
				if (finish == 1) // admin()�� 1�� ����ϸ� ���α׷��� �����Ѵ�.
					return 0;
				else // 0�� ����ϸ� ����� ��� �ʱ� ȭ������ ���ƿ´�.
					break;
			}
			break;
		case 1: // �Ա�.
			client = account_judge(count);
			// account_judge�� �� ������ �Ű������� �־� ������ ���� �� ����Ʈ����
			// �� ��°���� ���� ��, ���� ������ client�� �����Ѵ�. �� �� ������ �ϻ����� 
			// ���ڰ� �ƴ�, ���α׷��ֿ��� ���Ǵ� 0���� �����ϴ� ���̴�.
			if (client != -1)
			{	// client�� -1�� �ƴ϶�� deposit�� client�� �Ű������� �־� �����Ѵ�.
				deposit(client); 
				break;
			}
			else // client�� -1�̶�� �ʱ� ȭ������ ���ư���.
				break;
			// ������ return ���� 0���� ������, ���� ����Ʈ���� ù ��° ���̸� 0��
			// ��µǹǷ�, ���¹�ȣ�� ��й�ȣ�� �߸� �Է¹����� -1�� ����ϵ��� �ߴ�.
		case 2: // ���.
			client = account_judge(count);
			// account_judge()�� count�� �Ű������� �־� ������ ��°��� client�� �����Ѵ�.
			if (client != -1) 
			{	// client�� -1�� �ƴ϶�� withdraw()�� client�� �Ű������� �־� �����Ѵ�.
				withdraw(client);
				break;
			}	
			else	// client�� -1�̶�� �ʱ� ȭ������ ���ư���.
				break;
		case 3: // ���� ��ü
			client = account_judge(count);
			if (client != -1)
			{
				transfer(client, count);
				break;
			}	
			// ���¹�ȣ�� ��й�ȣ�� ��ġ�ϸ� transfer()�� ���� ������
			// �� ������ �Ű������� �־� �����Ѵ�.
			else
				break;
			
		case 4: // ���� ��ȸ
			client = account_judge(count);
			if (client != -1)
			{
				account_view(client); // account_view()�� client�� �Ű� ������ �־� �����Ѵ�.
				break;
			}
			else
				break;
		default: // �޴��� �߸� �����ϸ� �ٽ� �ʱ� ȭ������ ���ư���.
			printf("�޴� ������ �߸� �ϼ̽��ϴ�. �ٽ� �������ֽʽÿ�.\n");
			break;
		}
	}
}