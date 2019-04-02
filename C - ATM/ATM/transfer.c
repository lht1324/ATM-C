#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client_info.h"
#include "function.h"

int transfer(int client, int count) // 출금 기능을 담당하는 함수이다.
{	// 이체라는 것의 본질은, 내 계좌에서 돈을 출금해 다른 사람의 계좌에 입금하는 것이다.
	// 출금 함수의 일부분과 입금 함수의 일부분, 그리고 
	// 계좌번호와 비밀번호의 참 거짓 여부 판정 함수의 일부분을 합친 코드이다.
	char account[17], temp[17];
	// account : 이체할 고객의 계좌를 입력받을 문자열이다.
	// temp : 계좌번호 판정을 위해 고객의 계좌번호 정보를 임시로 입력받을 문자열이다.
	char c_money[16], d_money[16], b_money[16], bal[21];
	// c_money : client_money(기존 잔고)
	// d_money : deposit_money(입금할 돈)
	// b_money : balance_money(기존 잔고 + 입금할 돈)
	// bal : 수정된 잔고에 패스워드를 합친 것을 파일에 입력하기 위해 사용되는 문자열.
	int i, j, len, result, end, receiver = 0, judge = 0;
	// i, j : 반복문에 사용되는 변수. len : 고객의 잔고를 나타낸 문자열의 길이를 대입할 변수.
	// result : 이체 후 결과를 대입할 변수. 
	// end : 초기 화면으로 갈 지 안 갈 지 물을 때 사용되는 변수.
	// receiver : 구조체 배열 s에서 이체받을 사람의 인덱스.
	// judge : 송금할 사람이 입력한 계좌번호와 비밀번호를 판단하는데 사용되는 변수.
	FILE *rfp;
	FILE *wfp;
	// 파일 포인터를 선언한다.
	fopen_s(&rfp, "balance.txt", "r");
	fopen_s(&wfp, "balance_temp.txt", "w");
	// balance.txt를 읽기 모드로, balance_temp.txt를 쓰기 모드로 연다.
	printf("이체하실 계좌번호를 입력해주세요 : ");
	scanf_s("%s", account, 17); // 이체할 고객의 계좌번호를 입력받는다.

	for (i = 0; i < count; i++)
	{
		for (j = 0; j < 16; j++)
		{
			temp[j] = s[i].acc[j + 5];
		}
		temp[16] = '\0';

		if (strncmp(account, temp, 17) == 0)
			judge = 1;
		// 입력받은 계좌 번호가 기존 계좌와 같다면 judge는 1이다.
		else
			judge = 0;
		// 입력받은 게 기존 계좌와 다르다면 judge는 0이다.
		if (judge == 1)
		{
			receiver = i; // 계좌번호가 맞다면 이체받을 사람의 인덱스 receiver를 i라 한다.
			break;
		}

		if (i == count - 1 && judge == 0) 
		{
			printf("\n");
			printf("계좌번호를 잘못 입력하셨습니다.\n");
			return -1;
		}	
		// 반복문이 끝나기 직전 judge가 0이라면 계좌번호를 잘못 입력한 것이라 판단 후
		// 함수를 종료한다.
	}

	// 64행부터 137행까지는 client의 계좌에서 출금하는 코드이다.

	for (i = 0; i < 16; i++)
	{
		c_money[i] = s[client].balance[i + 5];
	}

	result = atoi(c_money);

	printf("\n이체하실 금액을 입력해주세요 : ");
	scanf_s("%s", d_money, 16);

	if (result < atoi(d_money))
	{
		printf("\n잔고가 부족합니다.\n");
		return 0;
	}
	else
		result -= atoi(d_money); 
	// 이체할 금액을 기존 잔고에서 출금한다.

	_itoa_s(result, b_money, sizeof(b_money), 10);

	for (i = 0; i < 16; i++)
		s[client].balance[i + 5] = b_money[i];

	len = strlen(s[client].balance);

	printf("\n이체가 완료되었습니다.\n\n");

	for (i = 5; i < 20; i++)
	{
		if (i == 5)
			printf("고객님의 계좌 잔고는 ");

		if (s[client].balance[i] != '\0')
			printf("%c", s[client].balance[i]);

		if ((len - i + 2) % 3 == 0 && i != (len - 1))
			printf(",");

		if (i == (len - 1))
		{
			printf("원입니다.\n\n");
			break;
		}
	}

	for (i = 0; ; i++)
	{
		if (i != client)
		{
			fgets(bal, sizeof(bal), rfp); // balance.txt에서 읽어 bal에 저장.

			if (feof(rfp))
				break;

			bal[strlen(bal)] = '\0';

			fprintf(wfp, "%s", bal); // client 이외에 읽은 것을 전부 balance_temp.txt에 작성.
		}

		if (i == client)
		{
			fgets(bal, sizeof(bal), rfp);
			// 여기서 읽지 않으면 파일에 s[client].balance와 balance.txt에서
			// 거래 결과로 수정되기 전 문자열이 같이 쓰인다.
			fprintf(wfp, "%s\n", s[client].balance);
			// client의 구조체에서 잔고 문자열을 그대로 파일에 쓴다.
		}
	}

	fclose(rfp);
	fclose(wfp);

	balance_modify(); // client의 계좌에서 출금한 결과를 기존 잔고 파일에 쓴다.
	
	fopen_s(&rfp, "balance.txt", "r");
	fopen_s(&wfp, "balance_temp.txt", "w");

	// 파일 포인터 rfp와 wfp를 닫고 balance.txt, balance_temp.txt를 각각
	// 읽기 모드, 쓰기 모드로 새로 연다.

	// 146행부터 189행까지는 receiver의 계좌에 입금하는 코드이다.

	for (i = 0; i < 16; i++)
	{
		c_money[i] = s[receiver].balance[i + 5];
	}

	result = atoi(c_money);

	result += atoi(d_money); // 이체받은 금액을 기존 잔고에 입금한다.

	_itoa_s(result, b_money, sizeof(b_money), 10);

	for (i = 0; i < 16; i++)
		s[receiver].balance[i + 5] = b_money[i];

	for (i = 0; ; i++)
	{
		if (i != receiver)
		{
			fgets(bal, sizeof(bal), rfp); // balance.txt에서 읽어 bal에 저장.

			if (feof(rfp))
				break;

			bal[strlen(bal)] = '\0';

			fprintf(wfp, "%s", bal); // client 이외에 읽은 것을 전부 balance_temp.txt에 작성.
		}

		if (i == receiver)
		{
			fgets(bal, sizeof(bal), rfp);
			// 여기서 읽지 않으면 파일에 s[client].balance와 balance.txt에서
			// 거래 결과로 수정되기 전 문자열이 같이 쓰인다.
			fprintf(wfp, "%s\n", s[receiver].balance);
			// receiver의 구조체에서 잔고 문자열을 그대로 파일에 쓴다.
		}
	}

	fclose(rfp);
	fclose(wfp);

	balance_modify(); // receiver의 계좌에 입금한 결과를 기존 잔고 파일에 쓴다.

	while (1)
	{
		printf("초기 화면으로 가시려면 0을 입력해주세요 : ");
		scanf_s("%d", &end);
		if (end == 0) // end에 0을 입력받으면 transfer() 함수를 종료한다.
			return 0;
		else
			printf("\n잘못 입력하셨습니다.\n\n");
	}
}