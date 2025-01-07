#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>

struct Balance{
	float money;
};

struct Birthday{
	int day;
	int month;
	int year;
};

struct Users{
	char id[12];
	char username[20];
	char fullName[100];
	char phoneNumber[20];
	
};

struct Accounts{
	char email[50];
	char pass[50];
	int status;
	int amount;
	struct Users user;
	struct Balance balance;
	struct Birthday birthday;
};

struct Accounts *a;
