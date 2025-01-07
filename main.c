#include "datatype.h"
#include "function.h"

int main(int argc, char *argv[]) { 
	int size = 0;
	int *sizePtr = &size;
	a = (struct Accounts *)calloc(1, sizeof(struct Accounts));
	int choice;
	loadFromFile(sizePtr);
	char *emailSignIn;
	char *passSignIn;	
	printf("***Bank Managemant System Using C***\n\n");
	do{
		printf("\t   CHOOSE YOUR ROLE");
		printf("\n========================================\n");
		printf("[1] Admin.\n");
		printf("[2] User.\n");
		printf("[3] Exit the Program.");
		printf("\n========================================\n");
		printf("Enter the choice: ");
		scanf("%d", &choice);
		emailSignIn = (char *)calloc(50, sizeof(char));
		passSignIn = (char *)calloc(50, sizeof(char));
		switch(choice){	
			case 1:
				signInAdmin(emailSignIn, passSignIn, sizePtr);
				break;
			case 2:
				signInUser(emailSignIn, passSignIn, sizePtr);
				break;
			case 3:
				printf("\nThoat thanh cong\n");
				break;
			default:
				printf("\nChuc nang nhap khong hop le\n\n");
				break;
		}
	}
	while(choice != 3);
	free(emailSignIn);
	free(passSignIn);
	free(a);
	return 0;
}
