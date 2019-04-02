#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client_info.h"
#include "function.h"

int deposit(int client) // 입금을 담당하는 함수이다.
{
	int i, len, result, end;
	// i : 반복문에 사용되는 변수이다. len : 고객의 잔고의 길이를 저장할 변수이다.
	// result : 입금한 결과를 저장할 변수이다.
	// end : 입금 후 고객에게 초기 화면으로 갈 지 물어볼 때 사용되는 변수이다.
	char c_money[16], d_money[16], b_money[16], bal[21];
	// client_money(기존 잔고), deposit_money(입금할 돈), balance_money(기존 잔고 + 입금할 돈)
	FILE *rfp;
	FILE *wfp;
	// 파일 포인터 2개를 선언한다.
	fopen_s(&rfp, "balance.txt", "r");
	fopen_s(&wfp, "balance_temp.txt", "w");
	// balance.txt를 읽기 모드로, balance_temp.txt를 쓰기 모드로 연다.
	for (i = 0; i < 16; i++)
	{
		c_money[i] = s[client].balance[i + 5];
	}	// 기존 잔고가 얼마인지 c_money에 저장한다.

	result = atoi(c_money); // result에 c_money를 정수로 변환한 값을 대입한다.

	printf("입금하실 금액을 입력해주세요 : ");
	scanf_s("%s", d_money, 16); // 입금할 금액을 입력받는다.

	result += atoi(d_money); // 입금할 금액인 d_money를 정수로 바꿔 result에 더한다.

	_itoa_s(result, b_money, sizeof(b_money), 10);
	// 입금 후 잔고 result를 문자열로 바꿔 b_money에 저장한다.
	for (i = 0; i < 16; i++)
		s[client].balance[i + 5] = b_money[i];
	// 고객의 기존 잔고에 b_money를 대입한다.
	len = strlen(s[client].balance);

	printf("\n입금이 완료되었습니다.\n\n");

	for (i = 5; i < 20; i++) // 계좌의 잔고를 출력하는 for문이다.
	{
		if (i == 5)
			printf("고객님의 계좌 잔고는 ");

		if (s[client].balance[i] != '\0') 
			printf("%c", s[client].balance[i]);
		// s[client].balance[i]가 NULL값이 아닐 때까지 s[client].balance[i]를 출력한다.
		if ((len - i + 2) % 3 == 0 && i != (len - 1)) // 3자리마다 ','로 끊어준다.
			printf(",");

		if (i == (len - 1)) // 잔고를 모두 출력하면 맨 뒤에 붙여준다.
		{
			printf("원입니다.\n\n");
			break;
		}
	}

	for (i = 0; ; i++) // 수정된 잔고를 파일에 입력하는 for문이다.
	{
		if (i != client)
		{
			fgets(bal, sizeof(bal), rfp); // balance.txt에서 한 줄 읽어 bal에 저장한다.

			if (feof(rfp)) // 파일의 끝이라면 반복을 종료한다.
				break;

			bal[strlen(bal)] = '\0'; // bal의 마지막 원소에 NULL 값을 대입한다.

			fprintf(wfp, "%s", bal); // client가 아닌 것을 전부 balance_temp.txt에 작성.
		}

		if (i == client)
		{
			fgets(bal, sizeof(bal), rfp); 
			// 여기서 읽지 않으면 파일엔 s[client].balance와 balance.txt에
			// 읽히기 전의 문자열이 같이 쓰인다.
			fprintf(wfp, "%s\n", s[client].balance);
			// balance_temp.txt에 고객의 수정된 잔고를 입력한다.
		}
	}

	fclose(rfp);
	fclose(wfp);
	// 파일 포인터 2개를 닫는다.
	balance_modify();
	// 함수 balance_modify(balance_temp.txt에서 읽어 balance.txt에 쓰는 함수)
	// 를 실행한다.
	while (1)
	{
		printf("초기 화면으로 가시려면 0을 입력해주세요 : ");
		scanf_s("%d", &end);
		if (end == 0) // end에 0을 입력받으면 deposit() 함수를 종료한다.
			return 0;
		else
			printf("\n잘못 입력하셨습니다.\n\n");
	}
}