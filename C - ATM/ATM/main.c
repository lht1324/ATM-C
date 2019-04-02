#include <stdio.h>
#include <stdlib.h>
#include <string.h.>
#include <malloc.h>
#include <time.h>
#include "function.h"
#include "client_info.h"
// acc.txt : 계좌번호를 저장하는 텍스트 파일.
// name.txt : 이름을 저장하는 텍스트 파일.
// balance.txt : 계좌 잔고를 저장하는 텍스트 파일.
// acc_temp.txt : acc.txt에 저장된 계좌번호를 덮어쓸 때 사용되는 텍스트 파일.
// name_temp.txt : name.txt에 저장된 이름을 덮어쓸 때 사용되는 텍스트 파일.
// balance_temp.txt : balance.txt에 저장된 계좌 잔고를 덮어쓸 때 사용되는 텍스트 파일.
int main()
{
	int count, choice, client = 0, finish = 0, start = 1;
	// admin_finish = 관리자 모드에서 받는 종료 변수

	printf("GC OS ver.1.0.0 가동.\n\n");

	printf("GC은행 ATM 가동 시작합니다.\n\n");

	count = account_load(); 
	// admin()의 실행을 위해 account_load()를 실행해 총 고객수를 얻어 count에 대입한다.
	finish = admin(count, start);
	// 프로그램을 처음 실행할 때는 관리자 모드에서 시작한다. 
	if (finish == 1) // 처음 실행한 관리자 모드에서 비밀번호를 틀렸다면 프로그램이 종료된다.
		return 0;

	start = 0;
	// admin() 내부에서 비밀번호를 틀렸을 때 바로 종료하는 것은 위 20행의
	// admin() 함수에서만이다. 이후 반복문에서 admin()이 실행될 때 매개 변수 
	// start는 0으로 들어간다. 20행의 admin() 함수 실행 이후 실행되는 admin()에서는
	// 비밀번호를 틀리면 프로그램이 종료되는 게 아니라 사용자 모드로 돌아온다.

	while(finish == 0)
	{
		count = account_load(); 
		// 입금, 출금, 이체, 계좌 생성, 제거 등 총 고객수가 바뀌거나 파일의 내용이 바뀌는
		// 함수가 많으므로 while문을 반복할 때마다 파일의 내용을 다시 읽어 구조체에
		// 저장하고 총 고객수를 새로 구한다.
		choice = kiosk(); // 함수 kiosk()를 실행해 고객이 선택한 수를 choice에 대입한다.

		switch (choice) // choice를 매개 변수로 해 작동하는 switch~case()문이다.
		{
		case 0: // 관리자 모드.
			finish = admin(count, start); // admin()을 실행해 finish를 입력받는다.

			while (1)
			{
				if (finish == 1) // admin()이 1을 출력하면 프로그램을 종료한다.
					return 0;
				else // 0을 출력하면 사용자 모드 초기 화면으로 돌아온다.
					break;
			}
			break;
		case 1: // 입금.
			client = account_judge(count);
			// account_judge에 총 고객수를 매개변수로 넣어 실행해 고객이 고객 리스트에서
			// 몇 번째인지 구한 뒤, 고객의 순서를 client에 대입한다. 이 때 순서는 일상적인 
			// 숫자가 아닌, 프로그래밍에서 사용되는 0부터 시작하는 수이다.
			if (client != -1)
			{	// client가 -1이 아니라면 deposit에 client를 매개변수로 넣어 실행한다.
				deposit(client); 
				break;
			}
			else // client가 -1이라면 초기 화면으로 돌아간다.
				break;
			// 보통은 return 값을 0으로 하지만, 고객이 리스트에서 첫 번째 고객이면 0이
			// 출력되므로, 계좌번호나 비밀번호를 잘못 입력받으면 -1을 출력하도록 했다.
		case 2: // 출금.
			client = account_judge(count);
			// account_judge()에 count를 매개변수로 넣어 실행해 출력값을 client에 대입한다.
			if (client != -1) 
			{	// client가 -1이 아니라면 withdraw()에 client를 매개변수로 넣어 실행한다.
				withdraw(client);
				break;
			}	
			else	// client가 -1이라면 초기 화면으로 돌아간다.
				break;
		case 3: // 계좌 이체
			client = account_judge(count);
			if (client != -1)
			{
				transfer(client, count);
				break;
			}	
			// 계좌번호와 비밀번호가 일치하면 transfer()에 고객의 순서와
			// 총 고객수를 매개변수로 넣어 실행한다.
			else
				break;
			
		case 4: // 계좌 조회
			client = account_judge(count);
			if (client != -1)
			{
				account_view(client); // account_view()에 client를 매개 변수로 넣어 실행한다.
				break;
			}
			else
				break;
		default: // 메뉴를 잘못 선택하면 다시 초기 화면으로 돌아간다.
			printf("메뉴 선택을 잘못 하셨습니다. 다시 선택해주십시오.\n");
			break;
		}
	}
}