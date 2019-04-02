#include <stdio.h>

struct info {
	char acc[30];
	char name[30];
	char balance[30];
};
// 고객 정보를 담을 구조체 info를 선언한다. 내용은 계좌번호, 이름, 잔고를 입력할 문자열
// 3개이다.
struct info *s;
// 문자열 포인터 변수 s를 선언한다. s를 account_load()에서 동적할당하는 것으로
// 고객의 수에 맞춰 고객 정보를 입력받을 수 있다.