#include <stdio.h>
#include <string.h>
#include "function.h"
#include "client_info.h"

int account_judge(int count) 
{	// 총 고객수를 입력 받아 고객이 입력한 계좌번호와 계좌의 비밀번호가 맞는지 판별하는 함수.
	char account[17], password[5], temp_a[17], temp_p[3][5];
	// account : 고객이 입력한 계좌번호. 
	// password : 고객이 입력한 비밀번호.
	// temp_a : 고객 정보에서 읽은 계좌번호가 저장된다.
	// temp_p : 고객정보를 키워드로 비밀번호를 읽어와 저장하는 이차원 문자열이다.
	
	int i, j, client = 0, judge = 0;
	// client : 고객이 고객 리스트에서 몇 번째인지 저장되어 함수가 끝날 때 출력되는 변수.
	// judge : 계좌번호와 비밀번호가 모두 맞다면 1이 되는 변수이다. 0으로 초기화.
	
	printf("계좌번호를 입력해주세요 : ");
	scanf_s("%s", account, 17); // 계좌번호를 입력받는다.
	
	for (i = 0; i < count; i++)
	{
		for (j = 0; j < 16; j++)
		{
			temp_a[j] = s[i].acc[j + 5]; // 판정을 위해 temp_a에 고객의 계좌번호를 저장한다.
		}
		temp_a[16] = '\0';

		if (strncmp(account, temp_a, 17) == 0) // 고객이 입력한 계좌번호와 temp_a가 일치하면
			judge = 1;
		else
			judge = 0;
		
		if (judge == 1)
		{
			client = i;
			break;
		} // judge가 1이면 client에 i를 대입하고 계좌번호를 판정하는 for문을 종료한다.

		if (i == count - 1 && judge == 0)
		{	
			printf("\n");
			printf("계좌번호를 잘못 입력하셨습니다.\n");
			return -1;
		}	// for문이 끝나기 전에 judge가 0이라면 계좌번호를 잘못 입력한 것이다.
	}

	printf("\n비밀번호를 입력해주세요 : ");
	scanf_s("%s", password, 5); // 비밀번호를 입력받는다.
	printf("\n");
	
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (i == 0) // 계좌번호와 함께 저장된 비밀번호를 temp_p[0]에 입력한다.
				temp_p[i][j] = s[client].acc[j]; 
			if (i == 1) // 이름과 함께 저장된 비밀번호를 temp_p[1]에 입력한다.
				temp_p[i][j] = s[client].name[j];
			if (i == 2) // 잔고와 함께 저장된 비밀번호를 temp_p[2]에 입력한다.
				temp_p[i][j] = s[client].balance[j];
		}
		temp_p[i][4] = '\0';
		
		if (strncmp(password, temp_p[i], 5) == 0) // temp_p[i]가 고객이 입력한 비밀번호와 같으면
			judge = 1;
		else
			judge = 0;
	}

	if (judge == 1) 
		return client;
	// 계좌번호와 비밀번호가 모두 맞다면 judge는 1이다.
	// 고객 리스트에서 고객이 몇 번째인지 알려주는 변수 client를 출력한다.
	else
	{
		printf("비밀번호를 잘못 입력하셨습니다.\n");
		return -1; 
	}	// judge가 1이 아니라면 계좌번호는 맞게 입력했지만 비밀번호가 틀린 것이다.
}
