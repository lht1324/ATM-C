int account_load(); // 계좌번호, 이름, 잔고 파일을 읽어 구조체에 저장하는 함수.
int kiosk(); // 사용자 모드의 초기 화면을 띄워주는 함수.
int account_judge(int count);
// 계좌번호와 비밀번호 참 거짓 여부를 판단하고 고객이 고객 리스트에서
// 몇 번째인지 알아내 출력하는 함수.
int deposit(int client); // 입금 기능을 담당하는 함수.
int withdraw(int client); // 출금 기능을 담당하는 함수.
int transfer(int client, int count); // 이체 기능을 담당하는 함수.
void balance_modify(); // 입금, 출금, 이체 시 수정된 내용을 파일에 기록하는 함수.
int account_view(int client); // 계좌 조회 기능을 담당하는 함수.
int admin(int count, int start); // 관리자 모드 기능을 담당하는 함수.
int create_account(int count); // 계좌 생성 기능을 담당하는 함수.
void delete_account(int client); // 계좌 제거 기능을 담당하는 함수.