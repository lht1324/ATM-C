#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client_info.h"

int account_load()
{	// 계좌번호, 이름, 잔고를 기록한 텍스트 파일에서 고객 정보를 읽어 구조체 배열에 저장한다.
	// 구조체 배열은 동적할당으로 선언한다.
	int count = 1;
	char str_a[30], str_n[30], str_b[30];
	// count : 총 고객 수. 파일의 끝까지 읽는 반복문이 실행되어야 하니 읽을 때마다
	// 1씩 추가되고, 파일의 끝까지 읽으면 1을 뺀 count를 출력한다. 반복문에서 
	// feof가 count++보다 앞에 있기 때문에 count가 고객수보다 1이 더 더해지기 때문이다.
	
	s = (struct info*) calloc(sizeof(struct info), count);
	// client_info.h에서 선언된 구조체 포인터 변수 s를 count만큼 동적할당한다.
	
	FILE *rfp1;
	FILE *rfp2;
	FILE *rfp3;
	
	fopen_s(&rfp1, "acc.txt", "r");
	fopen_s(&rfp2, "name.txt", "r");
	fopen_s(&rfp3, "balance.txt", "r");
	// 계좌번호, 이름, 잔고 텍스트 파일을 읽는다.
	
	while (1) // 무한 반복하는 while문이다.
	{
		fgets(str_a, sizeof(str_a), rfp1);
		fgets(str_n, sizeof(str_n), rfp2);
		fgets(str_b, sizeof(str_b), rfp3);
		// 계좌번호, 이름, 잔고 텍스트 파일을 한 줄씩 읽는다.
		
		if (feof(rfp1) && feof(rfp2) && feof(rfp3))
		{
			count--;
			break;
		} // 텍스트 파일들의 끝이라면 count에서 1을 뺀 뒤 무한반복을 종료한다.
		
		str_a[strlen(str_a)] = '\0';
		str_n[strlen(str_n)] = '\0';
		str_b[strlen(str_b)] = '\0';
		// str_a, str_n, str_b의 마지막 원소에 NULL 값을 대입한다.
		
		strcpy_s(s[count - 1].acc, sizeof(str_a), str_a);
		strcpy_s(s[count - 1].name, sizeof(str_n), str_n);
		strcpy_s(s[count - 1].balance, sizeof(str_b), str_b);
		// 구조체에 읽어들인 고객 정보를 저장한다. count는 0이 아닌 1부터 시작하는 수이니
		// 1을 빼고 구조체에 인덱스로 사용한다.
		
		count++; // 전부 읽으면 count에 1을 더한다.

		s = (struct info*) realloc(s, sizeof(struct info) * count);
		// 1이 더해진 count만큼 동적 메모리를 재할당한다.
	}

	fclose(rfp1);
	fclose(rfp2);
	fclose(rfp3);
	
	return count; // 총 고객이 몇 명인지 나타내는 변수 count를 출력한다.
}
