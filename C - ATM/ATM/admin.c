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
	// i : 반복문에서 사용되는 변수. finish : 종료 여부를 물을 때 사용되는 변수.
	// client : 고객이 고객 리스트에서 몇 번째인지 저장할 변수.
	// choice : switch~case문에서 매개 변수로 사용된다.
	char password[5], test[5];
	// password : 기존 관리자 비밀번호를 읽어 저장한다.
	// test : 
	enum menu {
		user = 0, create, delete, end
	}; // 열거형을 이용해 switch~case문에서 사용되는 변수들을 선언한다.

	FILE *rfp; // 파일 포인터를 선언한다.

	fopen_s(&rfp, "admin_password.txt", "r");
	// 관리자 비밀번호가 저장된 텍스트 파일을 읽기 모드로 연다.
	fgets(password, 5, rfp); // 관리자 비밀번호를 읽어온다.

	password[4] = '\0'; // password의 마지막 원소에 NULL 값을 대입한다.

	printf("비밀번호를 입력해주세요 : ");
	scanf_s("%s", test, 5); // 관리자 모드를 연 인물에게 비밀번호를 입력받는다.
	test[4] = '\0'; // test의 마지막 원소에 NULL 값을 대입한다.

	for (i = 0; i < 5; i++)
	{
		if (test[i] != password[i]) // 비밀번호가 잘못 입력되었을 때를 찾는 if문이다.
		{
			printf("\n비밀번호를 잘못 입력하셨습니다.\n\n");
			if (start == 1)
			{	// main()함수 내부의 반복문 실행 전 실행된 admin() 함수에서
				// 비밀번호를 틀렸다면 초기 메뉴로 돌아가는 것이 아니라 프로그램을 종료한다.
				printf("기기를 종료합니다.\n\n");
				return 1;
			}
			else 
			{	// main() 함수 내부의 반복문에서 실행된 admin() 함수에서 비밀번호를 틀린다면
				// 사용자 모드로 다시 돌아간다.
				printf("접근 권한을 획득할 수 없습니다.\n\n");
				printf("초기 메뉴로 돌아갑니다.\n");
				return 0;
			}
		}
	}

	while (1) // 무한 반복 while문이다.
	{
		count = account_load(); // 계좌를 생성, 제거한 뒤 변경된 총 고객수를 다시 읽는다.

		printf("\n-------------------------------------\n\n");
		printf("--- 관리자 모드에 진입하셨습니다. ---\n\n");
		printf("<1> 계좌 생성\n\n");
		printf("<2> 계좌 제거\n\n");
		printf("<3> 기기 종료\n\n");
		printf("<0> 사용자 모드\n\n");
		printf("무엇을 할 지 선택해 주십시오 : ");
		scanf_s("%d", &choice); // choice를 입력받는다.
		printf("\n-------------------------------------\n\n");
		switch (choice) // chioce를 매개 변수로 해 switch~case 문을 실행한다.
		{
		case user: // user = 0, admin()을 종료, 즉 사용자 모드로 돌아간다.
			printf("사용자 모드로 전환합니다.\n");
			return 0;
			break;
		case create: // create = 1, 계좌 생성 함수인 create_account()를 실행한다.
			create_account(count);
			break;
		case delete: // delete = 2, 계좌 제거 함수인 delete_account()를 실행한다.
			client = account_judge(count);
			delete_account(client); 
			// delete_account()엔 고객이 몇 번째인지 알려주는 변수
			// client를 매개변수로 넣는다.
			break;
		case end: // end = 3, 프로그램을 종료한다.
			printf("기기를 종료하시겠습니까? <Yes : 1, No : 0> : ");
			scanf_s("%d", &finish); // finish를 입력받는다.
			printf("\n");

			if (finish == 1) // finish가 1이면 1을 출력한다.
			{
				printf("기기를 종료합니다.\n\n");
				return 1;
			}
			else // finish가 1이 아니라면 관리자 모드 초기 화면으로 돌아간다.
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