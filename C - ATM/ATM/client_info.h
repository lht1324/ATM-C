#include <stdio.h>

struct info {
	char acc[30];
	char name[30];
	char balance[30];
};
// �� ������ ���� ����ü info�� �����Ѵ�. ������ ���¹�ȣ, �̸�, �ܰ� �Է��� ���ڿ�
// 3���̴�.
struct info *s;
// ���ڿ� ������ ���� s�� �����Ѵ�. s�� account_load()���� �����Ҵ��ϴ� ������
// ���� ���� ���� �� ������ �Է¹��� �� �ִ�.