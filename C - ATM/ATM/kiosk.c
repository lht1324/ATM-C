#include <stdio.h>
#include "function.h"

int kiosk() // ������ �� �޴��� ����ϴ� �Լ��̴�.
{
	int choice = 0;
	enum menu {
		deposit = 1, withdraw, transfer, account_view, admin = 0, error = -1
	}; // switch~case()������ ���Ǵ� ������ ���������� �����Ѵ�.
	printf("\n----------------------------------------------------\n\n");
	printf("--- � ���ʽÿ�, ����! GC���� ATM����Դϴ�. ---\n\n");
	printf("<1> �Ա�\n\n");
	printf("<2> ���\n\n");
	printf("<3> ���� ��ü\n\n");
	printf("<4> ���� ��ȸ\n\n");
	printf("<0> ������ ���\n\n");
	printf("���Ͻô� �ŷ��� �������ֽʽÿ� : ");
	scanf_s("%d", &choice);
	printf("\n----------------------------------------------------\n\n");
	switch (choice)
	{
	case admin: // admin = 0, 0�� ����Ѵ�.
		return admin;
	case deposit: // deposit = 1, 1�� ����Ѵ�.
		return deposit;
	case withdraw: // withdraw = 2, 2�� ����Ѵ�.
		return withdraw;
	case transfer: // transfer = 3, 3�� ����Ѵ�.
		return transfer;
	case account_view: // account_view = 4, 4�� ����Ѵ�.
		return account_view;
	default:
		return error; 
		// error = -1, -1�� ����ϸ�, main() �Լ��� switch~case()������ 
		// case -1: �� �����Ƿ� default�� ó���ȴ�.
	}
}