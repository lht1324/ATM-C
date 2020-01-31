#include <stdio.h>
#include <string.h>
#include "client_info.h"
#include "function.h"

int admin(int count, int start) // 관리자 모드를 다루는 함수.
{	// count는 총 고객 수, start는 처음 시작하는지 아닌지의 여부를 다룬다.
	// 프로그램을 실행했을 때 가장 먼저 실행된다. 
	// 고객이 ATM 전원에 손 댈 이유도 없고 권한도 없다.
	// 관리자가 전원을 켜는 것을 전제로 한다.

	int i, finish, client, choice = 0;
	// finish : 종료 여부를 물을 때 사용되는 변수.
	// client : 고객이 고객 리스트에서 몇 번째인지 저장할 변수.
	
	char password[5], input[5];
	// password : 기존 관리자 비밀번호를 읽어 저장한다.
	// input : 입력받을 비밀번호가 저장된다.
	enum menu {
		user = 0, create, delete, end
	}; // switch~case문에서 사용되는 변수들을 선언한다.

	FILE *rfp;

	fopen_s(&rfp, "admin_password.txt", "r");
	fgets(password, 5, rfp);
	// 관리자 비밀번호를 읽어 password에 저장한다.
	
	password[4] = '\0';

	printf("비밀번호를 입력해주세요 : ");
	scanf_s("%s", input, 5); // 관리자 모드를 연 인물에게 비밀번호를 입력받는다.
	input[4] = '\0';

	for (i = 0; i < 5; i++)
	{
		if (input[i] != password[i])
		{
			printf("\n비밀번호를 잘못 입력하셨습니다.\n\n");
			if (start == 1)
			{	
				printf("기기를 종료합니다.\n\n");
				return 1;
			}
			// main()함수 내부의 반복문 실행 전 실행된 admin() 함수에서
			// 비밀번호를 틀렸다면 초기 메뉴로 돌아가는 것이 아니라 프로그램을 종료한다.
			else 
			{	
				printf("접근 권한을 획득할 수 없습니다.\n\n");
				printf("초기 메뉴로 돌아갑니다.\n");
				return 0;
			}
			// main() 함수 내부의 반복문에서 실행된 admin() 함수에서 
			// 비밀번호를 틀린다면 사용자 모드로 다시 돌아간다.
		}
	}

	while (1)
	{
		count = account_load(); // 계좌를 생성, 제거한 뒤 변경된 총 고객수를 다시 읽는다.

		printf("\n-------------------------------------\n\n");
		printf("--- 관리자 모드에 진입하셨습니다. ---\n\n");
		printf("<1> 계좌 생성\n\n");
		printf("<2> 계좌 제거\n\n");
		printf("<3> 기기 종료\n\n");
		printf("<0> 사용자 모드\n\n");
		printf("무엇을 할 지 선택해 주십시오 : ");
		scanf_s("%d", &choice);
		printf("\n-------------------------------------\n\n");
		
		switch (choice)
		{
		case user: // user = 0, admin()을 종료, 즉 사용자 모드로 돌아간다.
			printf("사용자 모드로 전환합니다.\n");
			return 0;
			break;
		case create: // 계좌 생성 함수인 create_account()를 실행한다.
			create_account(count);
			break;
		case delete: // 계좌 제거 함수인 delete_account()를 실행한다.
			client = account_judge(count);
			delete_account(client); 
			break;
		case end: // 프로그램을 종료한다.
			printf("기기를 종료하시겠습니까? <Yes : 1, No : 0> : ");
			scanf_s("%d", &finish);
			printf("\n");

			if (finish == 1) // 기기를 종료한다.
			{
				printf("기기를 종료합니다.\n\n");
				return 1;
			}
			else // 관리자 모드 초기 화면으로 돌아간다.
			{
				printf("초기 화면으로 돌아갑니다.\n");
				break;
			}
		default: // 잘못된 값을 입력받았다면 switch~case문을 종료한 뒤 다시 실행한다.
			printf("메뉴 선택을 잘못 하셨습니다. 다시 선택해주십시오.\n");
			break;
		}
	}
}
