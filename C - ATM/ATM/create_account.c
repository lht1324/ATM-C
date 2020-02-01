#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "client_info.h"
#include "function.h"

int create_account(int count) // 계좌를 새로 생성하는 함수이다.
{	
	int i, account_check = 0, end;
	// account_check : 계좌번호 생성 시 기존 계좌번호 중 같은 번호가 있는지 없는지 확인할 때 사용되는 변수이다.
	// end : end == 0이면 함수가 종료된다.
	
	char str_a[22], str_n[18], str_b[21], password[5], name[13], fp[17];
	// str_a : str_account, 계좌를 생성해 임시로 저장하기 위한 문자열이다.
	// str_n : str_name, 이름을 입력받은 뒤 임시로 저장하기 위한 문자열이다.
	// str_b : str_balance, 잔고를 임시로 저장하기 위한 문자열이다.
	// fp : 화면에 계좌번호를 출력하기 위해 임시로 계좌번호가 저장되는 문자열이다.
	
	// 이름, 계좌번호, 잔고가 파일에 쓰여질 때 앞의 5자리엔 비밀번호 4자리와 공백 1자리가
	// 쓰인다. 3개의 파일에 쓰인 비밀번호가 모두 맞다면 파일은 변조되지 않은 것이다.
	FILE *afp1;
	FILE *afp2;
	FILE *afp3;
	
	fopen_s(&afp1, "acc.txt", "a");
	fopen_s(&afp2, "name.txt", "a");
	fopen_s(&afp3, "balance.txt", "a");
	// acc.txt, name.txt, balance.txt를 추가 모드로 연다.
	
	printf("성함을 입력해주세요 : ");
	scanf_s("%s", name, 13); // 이름을 입력받는다.
	name[strlen(name)] = '\0';

	printf("\n4자리의 비밀번호를 정해주세요 : ");
	scanf_s("%s", password, 5); // 비밀번호를 입력받는다.
	password[4] = '\0';
	
	printf("\n");

	
	for (i = 0; i < 5; i++)
	{
		str_a[i] = password[i];
		str_n[i] = password[i];
		str_b[i] = password[i];
		
		if (i == 4)
		{
			str_a[4] = ' ';
			str_n[4] = ' ';
			str_b[4] = ' ';
		}
	}	// 계좌번호, 이름, 잔고의 앞 5자리에 비밀번호와 공백 1자리를 넣는다.

	for (i = 0; i < 17; i++)
	{
		str_n[i + 5] = name[i];
	}	
	// 비밀번호가 쓰여진 str_n[i + 5]에 name[i]를 대입한다.
	// <비밀번호 5자리 + 이름> 의 형식이 된다.

	srand((unsigned)time(NULL));
	
	while (account_check == 0)
	{
		for (i = 5; i < 21; i++)
		{
			str_a[i] = (char)((rand() % 10) + 48);
			fp[i - 5] = str_a[i];

			if (i == 11 || i == 14)
			{
				str_a[i] = '-';
				fp[i - 5] = '-';
			}
		}	// 계좌를 랜덤으로 생성하는 for문이다.
		
		str_a[21] = '\0';
		fp[16] = '\0';
		
		for (i = 0; i < count; i++)
		{
			if (strncmp(fp, s[i].acc, 17) == 0)
				account_check = 0;
			else
				account_check = 1;
		}	
		// 구조체 계좌번호 항목을 훑어 새로 생성된 계좌번호와 같은 번호가 있다면 
		// 계좌번호를 다시 생성한다.
	}
	str_b[5] = '0'; // 처음 만들어지는 계좌이니 잔고는 0으로 한다.
	str_b[6] = '\0';

	fprintf(afp1, "%s\n", str_a);
	fprintf(afp2, "%s\n", str_n);
	fprintf(afp3, "%s\n", str_b);
	// str_a, str_n, str_b를 각각 acc.txt, name.txt, balance.txt에 추가로 쓴다.
	
	fclose(afp1);
	fclose(afp2);
	fclose(afp3);
	
	printf("계좌가 생성되었습니다. %s 고객님의 계좌번호는 %s입니다.\n\n", name, fp);
	
	while (1)
	{
		printf("초기 화면으로 가시려면 0을 입력해주세요 : ");
		scanf_s("%d", &end);
		if (end == 0) // end에 0을 입력받으면 create_account() 함수를 종료한다.
			return 0;
		else
			printf("\n잘못 입력하셨습니다.\n\n");
	}
}
