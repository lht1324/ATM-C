int account_load(); // ���¹�ȣ, �̸�, �ܰ� ������ �о� ����ü�� �����ϴ� �Լ�.
int kiosk(); // ����� ����� �ʱ� ȭ���� ����ִ� �Լ�.
int account_judge(int count);
// ���¹�ȣ�� ��й�ȣ �� ���� ���θ� �Ǵ��ϰ� ���� �� ����Ʈ����
// �� ��°���� �˾Ƴ� ����ϴ� �Լ�.
int deposit(int client); // �Ա� ����� ����ϴ� �Լ�.
int withdraw(int client); // ��� ����� ����ϴ� �Լ�.
int transfer(int client, int count); // ��ü ����� ����ϴ� �Լ�.
void balance_modify(); // �Ա�, ���, ��ü �� ������ ������ ���Ͽ� ����ϴ� �Լ�.
int account_view(int client); // ���� ��ȸ ����� ����ϴ� �Լ�.
int admin(int count, int start); // ������ ��� ����� ����ϴ� �Լ�.
int create_account(int count); // ���� ���� ����� ����ϴ� �Լ�.
void delete_account(int client); // ���� ���� ����� ����ϴ� �Լ�.