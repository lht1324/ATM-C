#include <stdio.h>
#include "function.h"

int kiosk() // 고객들이 볼 메뉴를 출력하는 함수이다.
{
	int choice = 0;
	enum menu {
		deposit = 1, withdraw, transfer, account_view, admin = 0, error = -1
	}; // switch~case()문에서 사용되는 변수를 열거형으로 선언한다.
	printf("\n----------------------------------------------------\n\n");
	printf("--- 어서 오십시오, 고객님! GC은행 ATM기기입니다. ---\n\n");
	printf("<1> 입금\n\n");
	printf("<2> 출금\n\n");
	printf("<3> 계좌 이체\n\n");
	printf("<4> 계좌 조회\n\n");
	printf("<0> 관리자 모드\n\n");
	printf("원하시는 거래를 선택해주십시오 : ");
	scanf_s("%d", &choice);
	printf("\n----------------------------------------------------\n\n");
	switch (choice)
	{
	case admin: // admin = 0, 0을 출력한다.
		return admin;
	case deposit: // deposit = 1, 1을 출력한다.
		return deposit;
	case withdraw: // withdraw = 2, 2를 출력한다.
		return withdraw;
	case transfer: // transfer = 3, 3을 출력한다.
		return transfer;
	case account_view: // account_view = 4, 4를 출력한다.
		return account_view;
	default:
		return error; 
		// error = -1, -1을 출력하며, main() 함수의 switch~case()문에는 
		// case -1: 이 없으므로 default로 처리된다.
	}
}