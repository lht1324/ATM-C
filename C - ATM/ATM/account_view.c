#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#include "client_info.h"

int account_view(int client) // 계좌를 조회하는 함수이다.
{
	int i, len1, len2, len3, end;
	// i : 반복문에 사용되는 변수이다. 
	// len1부터 len3 : 구조체 내부에서 이름, 계좌번호, 잔고를 저장하는 문자열의 길이.
	// end : 변수가 0이라면 함수가 끝난다.
	len1 = strlen(s[client].name);
	len2 = strlen(s[client].acc);
	len3 = strlen(s[client].balance);

	printf("성함 : ");

	for (i = 5; i < len1; i++)
	{
		if (s[client].name[i] != '\0') 
			printf("%c", s[client].name[i]);

		else if (s[client].name[i] == '\0') 
			break;
	}// 고객의 이름을 저장한 문자열의 내용을 출력한다.
	// 문자열의 원소가 NULL값이라면 for문을 종료한다.
	printf("\n");

	printf("계좌 번호 : ");

	for (i = 5; i < len2; i++)
	{
		if (s[client].acc[i] != '\0')
			printf("%c", s[client].acc[i]);
			
		else if (s[client].acc[i] == '\0')
				break;
	} // 고객의 계좌를 저장한 문자열의 내용을 출력한다. 
	// 문자열의 원소가 NULL값이라면 for문을 종료한다.
	printf("\n");
	
	printf("잔고 : ");

	for (i = 5; i < len3; i++)
	{
		if (s[client].balance[i] != '\0')
			printf("%c", s[client].balance[i]);

		if ((len3 - i + 1) % 3 == 0 && i != (len3 - 2)) // 수를 세 자리마다 쉼표로 끊어준다.
			printf(",");

		if (i == (len3 - 2) || s[client].balance[5] == '0')
		{
			printf("원\n\n");
			break;
		} // 반복문의 마지막이거나, 잔고가 0원일 때
		// (비밀번호 4자리 + 공백 ' ' 1자리 + 잔고 '0' 1자리) 숫자의 뒤에 "원\n\n"을 출력한다.
	}

	while (1)
	{
		printf("초기 화면으로 가시려면 0을 입력해주세요 : ");
		scanf_s("%d", &end);
		if (end == 0) // end에 0을 입력받으면 account_view() 함수를 종료한다.
			return 0;
		else
			printf("\n잘못 입력하셨습니다.\n\n");
	}
}