#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client_info.h"
#include "function.h"

void delete_account(int client) // 계좌 제거를 하는 함수이다.
{	// 이 함수는 기본적으로 파일에서 읽은 뒤 쓰는 기능을 하는데, 지울 부분을
	// 읽기만 하고 쓰지 않는 방식으로 파일에서 고객의 계좌 정보를 삭제한다. 
	int i, end; // i : 반복문 사용을 위한 변수이다. 
						// end : 고객에게 초기 화면으로 갈 지 물을 때 사용되는 변수이다.
	char acc[30], name[30], bal[30];
	// acc.txt, name.txt, bal.txt에서 읽은 내용을 임시로 저장할 문자열들이다.

	FILE *rfp1;
	FILE *rfp2;
	FILE *rfp3;
	FILE *wfp1;
	FILE *wfp2;
	FILE *wfp3;
	// 읽기, 쓰기에 쓸 파일 포인터 6개를 선언한다.
	fopen_s(&rfp1, "acc.txt", "r");
	fopen_s(&rfp2, "name.txt", "r");
	fopen_s(&rfp3, "balance.txt", "r");
	fopen_s(&wfp1, "acc_temp.txt", "w");
	fopen_s(&wfp2, "name_temp.txt", "w");
	fopen_s(&wfp3, "balance_temp.txt", "w");
	// 기존 acc.txt, name.txt, balance.txt는 읽기 모드로, 임시로 내용을 저장할 파일들은
	// 쓰기 모드로 연다.
	for (i = 0; ; i++) // 초깃값, 증감식만 넣고 조건식은 뺀 무한 반복 for문이다.
	{
		if (i != client) // i가 client가 아닐 때 기존 파일에서 읽은 뒤 임시 파일에 입력한다.
		{	
			fgets(acc, sizeof(acc), rfp1);
			fgets(name, sizeof(name), rfp2);
			fgets(bal, sizeof(bal), rfp3);
			// 기존 파일에서 내용을 읽어온다.
			if (feof(rfp1) && feof(rfp2) && feof(rfp3)) // 파일의 끝이라면 반복을 종료한다.
				break;

			acc[strlen(acc)] = '\0';
			name[strlen(name)] = '\0';
			bal[strlen(bal)] = '\0';
			// acc, name, bal의 마지막 원소에 NULL 값을 대입한다.
			fprintf(wfp1, "%s", acc);
			fprintf(wfp2, "%s", name);
			fprintf(wfp3, "%s", bal);
			// 임시 파일에 기존 파일에서 읽어온 고객 정보를 입력한다.
		}

		if (i == client) // i가 제거할 고객 번호와 같다면
		{
			fgets(acc, sizeof(acc), rfp1);
			fgets(name, sizeof(name), rfp2);
			fgets(bal, sizeof(bal), rfp3);
			// 읽기만 한다. 만일 읽지 않고 넘어간다면 컴퓨터는 구분하지 못하고, i + 1이 되었을 때
			// client 고객의 정보를 읽어버린다. 읽은 뒤 쓰지 않는 것으로 전체 리스트에서 특정
			// 고객의 정보를 제거한다.
		}	
	}

	fclose(rfp1);
	fclose(rfp2);
	fclose(rfp3);
	fclose(wfp1);
	fclose(wfp2);
	fclose(wfp3);
	// 파일 포인터 6개를 닫는다.
	fopen_s(&rfp1, "acc_temp.txt", "r");
	fopen_s(&rfp2, "name_temp.txt", "r");
	fopen_s(&rfp3, "balance_temp.txt", "r");
	fopen_s(&wfp1, "acc.txt", "w");
	fopen_s(&wfp2, "name.txt", "w");
	fopen_s(&wfp3, "balance.txt", "w");
	// 임시 파일들을 읽기 모드로, 기존 파일들을 쓰기 모드로 연다.
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
	}	// 특정 고객 정보가 제거된 임시 파일들의 내용을 기존 파일에 덮어쓴다.

	fclose(rfp1);
	fclose(rfp2);
	fclose(rfp3);
	fclose(wfp1);
	fclose(wfp2);
	fclose(wfp3);

	// 파일 포인터 6개를 닫는다.

	printf("계좌가 제거되었습니다. 이용 감사합니다.\n\n");

	while (1)
	{
		printf("초기 화면으로 가시려면 0을 입력해주세요 : ");
		scanf_s("%d", &end);
		if (end == 0) // end에 0을 입력받으면 delete_account() 함수를 종료한다.
			return 0;
		else
			printf("\n잘못 입력하셨습니다.\n\n");
	}
}