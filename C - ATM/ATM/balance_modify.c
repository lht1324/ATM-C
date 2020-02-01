#include <stdio.h>
#include "client_info.h"
#include "function.h"

void balance_modify() // 잔고 부분 수정을 위해 만든 코드.
{	
	char str[21];
	// 무한 반복문에서 사용되는 길이 21의 문자열 str을 선언한다.
	
	FILE *rfp;
	FILE *wfp;
	// 파일 포인터 rfp, wfp를 선언한다.
	fopen_s(&rfp, "balance_temp.txt", "r");
	fopen_s(&wfp, "balance.txt", "w");
	// 입금, 출금, 계좌 이체 함수에서 balance_temp.txt에 수정된 balance.txt의 내용을
	// 작성했다. 이 함수를 이용해 balance_temp.txt에 입력된 새로운 잔고 정보를 다시
	// balance.txt에 덮어쓴다.
	
	while(1)
	{
		fgets(str, sizeof(str), rfp); // balance_temp.txt를 한 줄씩 읽는다.

		if (feof(rfp)) // 파일의 끝이라면 종료한다.
			break;

		fprintf(wfp, "%s", str); // 읽어들인 내용을 balance.txt에 덮어쓴다.
	}

	fclose(rfp);
	fclose(wfp);
}
