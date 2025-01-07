#include"datatype.h"

void loadFromFile(int *size){
	FILE *file = fopen("bank.bin", "rb");
	if(file == NULL){
		printf("Da xay ra loi vui long thu lai\n\n");
		return;
	}
	while(1){
		a = realloc(a, ((*size)+1)*sizeof(struct Accounts));
		if(a == NULL){
			printf("Da xay ra loi vui long thu lai\n\n");
			break;
		}
		if(fread(&a[*size], sizeof(struct Accounts), 1, file) != 1){
			break;
		}
		(*size)++;
	}
	fclose(file);
}

void saveToFile(int *size){
	FILE *file = fopen("bank.bin", "wb");
	if(file == NULL){
		printf("\nDa xay ra loi vui long thu lai\n\n");
		return;
	}
	fwrite(a, sizeof(struct Accounts), *size, file);
	fclose(file);
}

int checkAddUser(char check[], int *size, int flag){
	switch(flag){
		case 1:
			if(strlen(check) != 10){
				printf("\nID phai co it nhat 10 ki tu\n");
				return 0;
			}
			for(int i = 0; i < strlen(check); i++){
				if(!isalnum(check[i])){
					printf("\nID khong duoc chua ki tu dac biet\n");
					return 0;
				}	
			}
			for(int i = 0; i < *size; i++){
				if(strcmp(check, a[i].user.id) == 0){
					printf("\nID da ton tai\n");
					return 0;
				}
			}
			break;
		case 2:
			if(strlen(check) == 0){
				printf("\nVui long nhap email\n");
				return 0;
			}
			char *position = strstr(check, "@gmail.com");
			if(position == NULL && position != check + strlen(check) - strlen("@gmail.com")){
				printf("\nEmail phai co @gmail.com\n");
				return 0;
			}
			for(int i = 0; i < strlen(check); i++){
				if(!isalnum(check[i]) && check[i] != '@' && check[i] != '.'){
					printf("\nEmail khong duoc chua ki tu dac biet\n");
					return 0;
				}
			}
			for(int i = 0; i < *size; i++){
				if(strcmp(check, a[i].email) == 0){
					printf("\nEmail da ton tai\n");
					return 0;
				}
			}
			break;
		case 3:
			if(strlen(check) != 10){
				printf("\nSo dien thoai phai co 10 so\n");
				return 0;
			}
			for(int i = 0; i < strlen(check); i++){
				if(!isdigit(check[i])){
					printf("\nSo dien thoai phai la chu so\n");
					return 0;
				}
			}
			for(int i = 0; i < *size; i++){
				if(strcmp(check, a[i].user.phoneNumber) == 0){
					printf("\nSo dien thoai da ton tai\n");
					return 0;
				}
			}
			break;
		case 4:
			if(strlen(check) < 6){
				printf("\nUsername toi thieu 6 ki tu\n");
				return 0;
			}
			for(int i = 0; i < strlen(check); i++){
				if(!isalnum(check[i])){
					printf("\nUsername khong duoc chua ki tu dac biet\n");
					return 0;
				}
			}
			for(int i = 0; i < *size; i++){
				if(strcmp(check, a[i].user.username) == 0){
					printf("\nUsername da ton tai\n");
					return 0;
				}
			}
			break;
	}
	return 1;
}

void displayUserDetail(int *size) {
    printf("\n+------------+----------------------+------------+-----------------+----------------------+------------------------+-----------------+------------+-----------------+\n");
    printf("| %-10s | %-20s | %-10s | %-15s | %-20s | %-22s | %-15s | %-10s | %-15s |\n",
           "ID", "Ho ten", "Sinh nhat", "So dien thoai", "Username", "Email", "Mat khau", "Trang thai", "So du");
    printf("+------------+----------------------+------------+-----------------+----------------------+------------------------+-----------------+------------+-----------------+\n");
    for (int i = 0; i < *size; i++) {
        printf("| %-10s | %-20s | %02d/%02d/%-4d | %-15s | %-20s | %-22s | %-15s | %-10s | %-15.2f |\n",
               a[i].user.id,
               a[i].user.fullName,
               a[i].birthday.day, a[i].birthday.month, a[i].birthday.year,
               a[i].user.phoneNumber,
               a[i].user.username,
               a[i].email,
               a[i].pass,
               a[i].status == 0 ? "Khoa" : "Mo khoa",
               a[i].balance.money);
        printf("+------------+----------------------+------------+-----------------+----------------------+------------------------+-----------------+------------+-----------------+\n");
    }
}

int checkFullName(char fullName[], int length){
	if(length == 0 || fullName[0] == '\0'){
		printf("\nVui long nhap ten nguoi dung\n");
		return 0;
	}
	
	if(fullName[0] == ' '){
		printf("\nTen nguoi dung khong the bat dau bang dau cach\n");
		return 0;
	}
	
	if(fullName[strlen(fullName) - 1] == ' '){
		printf("\nTen nguoi dung khong the ket thuc bang dau cach\n");
		return 0;
	}
	
	for(int i = 0 ; i < length; i++){
		if(!isalpha(fullName[i]) && fullName[i] != ' '){
			printf("\nTen nguoi dung khong duoc chua ki tu dac biet hoac so\n");
			return 0;
		}
		else if(fullName[i] ==' ' && fullName[i+1] == ' '){
			printf("\nTen nguoi dung co qua nhieu dau cach\n");
			return 0;
		}
	}
	return 1;
}

int checkBirthday(int day, int month, int year) {
    if (year <= 0) {
        printf("\nNam nhap khong hop le\n");
        return 0;
    }

    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if (day < 1 || day > 31) {
                printf("\nNgay nhap khong hop le\n");
                return 0;
            }
            break;

        case 4: case 6: case 9: case 11:
            if (day < 1 || day > 30) {
                printf("\nNgay nhap khong hop le\n");
                return 0;
            }
            break;

        case 2:
            if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
                if (day < 1 || day > 29) {
                    printf("\nNgay nhap khong hop le\n");
                    return 0;
                }
            } 
			else {
                if (day < 1 || day > 28) {
                    printf("\nNgay nhap khong hop le\n");
                    return 0;
                }
            }
            break;

        default:
            printf("\nThang nhap khong hop le\n");
            return 0;
    }

    return 1;
}

void addUser(int *size){
	a = realloc(a, ((*size)+1)*sizeof(struct Accounts));
	if(a == NULL){
		printf("\nDa xay ra loi\n");
		return;
	}

	do{
		fflush(stdin);
		printf("\nNhap ID: ");
		fgets(a[*size].user.id, 12, stdin);
		a[*size].user.id[strcspn(a[*size].user.id, "\n")] = '\0';
	}
	while(checkAddUser(a[*size].user.id, size, 1) == 0);
	
	do{
		printf("\nNhap ho ten: ");
		fgets(a[*size].user.fullName, 100, stdin);
		a[*size].user.fullName[strcspn(a[*size].user.fullName, "\n")] = '\0';
	}
	while(checkFullName(a[*size].user.fullName, strlen(a[*size].user.fullName)) == 0);
	
	printf("\nNhap ngay thang nam sinh");
	do{
		printf("\n\tNam sinh: ");
		scanf("%d", &a[*size].birthday.year);
		if(a[*size].birthday.year <= 0){
			printf("\nNam sinh nhap khong hop le\n");
		}
	}
	while(a[*size].birthday.year <= 0);
	
	
	do{
		printf("\n\tThang sinh: ");
		scanf("%d", &a[*size].birthday.month);
		if(a[*size].birthday.month < 1 || a[*size].birthday.month > 12){
			printf("\nThang sinh nhap khong hop le\n");
		}
	}
	while(a[*size].birthday.month < 1 || a[*size].birthday.month > 12);
	
	do{
		printf("\n\tNgay sinh: ");
		scanf("%d", &a[*size].birthday.day);
	}
	while(checkBirthday(a[*size].birthday.day, a[*size].birthday.month, a[*size].birthday.year) == 0);
	
	fflush(stdin);
	
	do{
		printf("\nNhap email: ");
		fgets(a[*size].email, 50, stdin);
		a[*size].email[strcspn(a[*size].email, "\n")] = '\0';
	}
	while(checkAddUser(a[*size].email, size, 2) == 0);
	
	do{
		printf("\nNhap mat khau: ");
		fgets(a[*size].pass, 50, stdin);
		a[*size].pass[strcspn(a[*size].pass, "\n")] = '\0';
		if(strlen(a[*size].pass) < 6){
			printf("\nMat khau phai co it nhat 6 ki tu\n");
		}
	}
	while(strlen(a[*size].pass) < 6);
	
	
	do{
		printf("\nNhap so dien thoai: ");
		fgets(a[*size].user.phoneNumber, 15, stdin);
		a[*size].user.phoneNumber[strcspn(a[*size].user.phoneNumber, "\n")] = '\0';
	}
	while(checkAddUser(a[*size].user.phoneNumber, size, 3) == 0);
	
	do{
		printf("\nNhap username: ");
		fgets(a[*size].user.username, 20, stdin);
		a[*size].user.username[strcspn(a[*size].user.username, "\n")] = '\0';
	}
	while(checkAddUser(a[*size].user.username, size, 4) == 0);
	
	do{
		printf("\nNhap trang thai tai khoan (0. khoa, 1. mo khoa): ");
		scanf("%d", &a[*size].status);
		if(a[*size].status != 0 && a[*size].status != 1){
			printf("\nNhap khong hop le\n");
		}
	}
	while(a[*size].status != 0 && a[*size].status != 1);
	
	a[*size].balance.money = 0;
	
	printf("\nThem nguoi dung thanh cong\n");
	
	(*size)++;
}

void lockUnlockAccounts(int *size){
	char *id, choice;
	int found = 0;
	id = (char *)calloc(20, sizeof(char));
	fflush(stdin);
	printf("\nNhap ID nguoi dung: ");
	fgets(id, 20, stdin);
	id[strcspn(id, "\n")] = '\0';
	for(int i = 0; i < *size; i++){
		if(strcmp(a[i].user.id, id) == 0){
			found = 1;
			printf("\nTrang thai tai khoan: %s", a[i].status == 0 ? "Khoa" : "Mo khoa");
			switch(a[i].status){
				case 0:
					do{
						printf("\n\nBan co muon mo khoa tai khoan khong (y/n): ");
						scanf("%c", &choice);
						fflush(stdin);
						switch(choice){
							case 'y':
								a[i].status = 1;
								printf("\nCap nhat trang thai thanh cong\n");
								break;
							case 'n':
								printf("\nCap nhat trang thai thanh cong\n");
								break;
							default:
								printf("\nNhap khong hop le");
								break;
						}
					}
					while(choice != 'y' && choice != 'n');
					break;
				case 1:
					do{
						printf("\n\nBan co muon khoa khong (y/n): ");
						scanf("%c", &choice);
						switch(choice){
							case 'y':
								a[i].status = 0;
								printf("\nCap nhat trang thai thanh cong\n");
								break;
							case 'n':
								printf("\nCap nhat trang thai thanh cong\n");
							break;
							default:
								printf("\nChuc nang khong hop le");
								break;
						}
					}
					while(choice != 'y' && choice != 'n');
					break;
			}
			break;
		}
	}
	if(found == 0){
		printf("\nID khong ton tai\n");
	}
	free(id);
}

void deleteAccounts(int *size){
	fflush(stdin);
	char *id;
	int found = 0;
	id = (char *)calloc(50, sizeof(char));
	printf("\nNhap ID ban muon xoa: ");
	fgets(id, 50, stdin);
	id[strcspn(id, "\n")] = '\0';
	for(int i = 0; i < *size; i++){
		if(strcmp(id, a[i].user.id) == 0){
			found = 1;
			for(int j = i; j < *size; j++){
				a[j] = a[j+1];
			}
			printf("\nXoa thanh cong\n");
			(*size)--;
			a = realloc(a, (*size)*sizeof(struct Accounts));
			break;
		}
	}
	if(found == 0){
		printf("\nID khong ton tai\n\n");
	}
	free(id);
}

void searchByName(int *size){
	fflush(stdin);
	int found = 0;
	char *name;
	char *fullName;
	fullName = (char *)calloc(100, sizeof(char));
	name = (char *)calloc(100, sizeof(char));
	printf("\nNhap nguoi dung muon tim kiem: ");
	fgets(name, 100, stdin);
	if(strlen(name) == 0 || name[0] == '\n'){
		printf("\nVui long nhap ten nguoi dung\n");
		return;
	}
	name[strcspn(name, "\n")] = '\0';
	printf("\n+------------+----------------------+------------+-----------------+----------------------+------------------------+-----------------+------------+-----------------+\n");
    printf("| %-10s | %-20s | %-10s | %-15s | %-20s | %-22s | %-15s | %-10s | %-15s |\n",
           "ID", "Ho ten", "Sinh nhat", "So dien thoai", "Username", "Email", "Mat khau", "Trang thai", "So du");
    printf("+------------+----------------------+------------+-----------------+----------------------+------------------------+-----------------+------------+-----------------+\n");
	for(int i = 0; i < *size; i++){
		strcpy(fullName, a[i].user.fullName);
		if(strstr(strlwr(fullName), strlwr(name)) != NULL){
			found = 1;
    		printf("| %-10s | %-20s | %02d/%02d/%-4d | %-15s | %-20s | %-22s | %-15s | %-10s | %-15.2f |\n",
               a[i].user.id,
               a[i].user.fullName,
               a[i].birthday.day, a[i].birthday.month, a[i].birthday.year,
               a[i].user.phoneNumber,
               a[i].user.username,
               a[i].email,
               a[i].pass,
               a[i].status == 0 ? "Khoa" : "Mo",
               a[i].balance.money);
       		 printf("+------------+----------------------+------------+-----------------+----------------------+------------------------+-----------------+------------+-----------------+\n");
		}
	}
	if(found == 0){
		printf("\nTen nguoi dung khong ton tai\n\n");
	}
	free(fullName);
	free(name);
}

void arrangeAccounts(int *size){
	fflush(stdin);
	int choice;
	printf("\n[1]. A -> Z");
	printf("\n[2]. Z -> A\n");
	printf("Nhap chuc nang: ");
	scanf("%d", &choice);
	switch(choice){
		case 1:
			for(int i = 0; i < (*size) - 1; i++){
				int minIndex = i;
				for(int j = i + 1; j < *size; j++){
					if (strcmp(a[minIndex].user.fullName, a[j].user.fullName) > 0){
						minIndex = j;
					}
				}
				if(minIndex != i){
					struct Accounts temp = a[i];
					a[i] = a[minIndex];
					a[minIndex] = temp;
				}
			}
			printf("\nSap xep hoan tat\n");
			
			printf("\n+------------+----------------------+------------+-----------------+----------------------+------------------------+-----------------+------------+-----------------+\n");
    		printf("| %-10s | %-20s | %-10s | %-15s | %-20s | %-22s | %-15s | %-10s | %-15s |\n",
           			"ID", "Ho ten", "Sinh nhat", "So dien thoai", "Username", "Email", "Mat khau", "Trang thai", "So du");
   			printf("+------------+----------------------+------------+-----------------+----------------------+------------------------+-----------------+------------+-----------------+\n");
    		for (int i = 0; i < *size; i++) {
       			printf("| %-10s | %-20s | %02d/%02d/%-4d | %-15s | %-20s | %-22s | %-15s | %-10s | %-15.2f |\n",
              		a[i].user.id,
               		a[i].user.fullName,
              		a[i].birthday.day, a[i].birthday.month, a[i].birthday.year,
              		a[i].user.phoneNumber,
            		a[i].user.username,
              		a[i].email,
              		a[i].pass,
              		a[i].status == 0 ? "Khoa" : "Mo",
               		a[i].balance.money);
        		printf("+------------+----------------------+------------+-----------------+----------------------+------------------------+-----------------+------------+-----------------+\n");
    		}
			break;
		case 2:
			for(int i = 0; i < (*size) - 1; i++){
				int minIndex = i;
				for(int j = i + 1; j < *size; j++){
					if (strcmp(a[minIndex].user.fullName, a[j].user.fullName) < 0){
						minIndex = j;
					}
				}
				if(minIndex != i){
					struct Accounts temp = a[i];
					a[i] = a[minIndex];
					a[minIndex] = temp;
				}
			}
			printf("\nSap xep hoan tat\n");
			
			printf("\n+------------+----------------------+------------+-----------------+----------------------+------------------------+-----------------+------------+-----------------+\n");
    		printf("| %-10s | %-20s | %-10s | %-15s | %-20s | %-22s | %-15s | %-10s | %-15s |\n",
           			"ID", "Ho ten", "Sinh nhat", "So dien thoai", "Username", "Email", "Mat khau", "Trang thai", "So du");
   			printf("+------------+----------------------+------------+-----------------+----------------------+------------------------+-----------------+------------+-----------------+\n");
    		for (int i = 0; i < *size; i++) {
       			printf("| %-10s | %-20s | %02d/%02d/%-4d | %-15s | %-20s | %-22s | %-15s | %-10s | %-15.2f |\n",
              		a[i].user.id,
               		a[i].user.fullName,
              		a[i].birthday.day, a[i].birthday.month, a[i].birthday.year,
              		a[i].user.phoneNumber,
            		a[i].user.username,
              		a[i].email,
              		a[i].pass,
              		a[i].status == 0 ? "Khoa" : "Mo",
               		a[i].balance.money);
        		printf("+------------+----------------------+------------+-----------------+----------------------+------------------------+-----------------+------------+-----------------+\n");
    		}
			break;
		default:
			printf("\nChuc nang nhap khong hop le\n");
			break;
	}
}

void searchByID(int *size){
	char *id;
	id = (char *)calloc(20, sizeof(char));
	int found = 0;
	fflush(stdin);
	printf("\nNhap ID nguoi muon tim kiem: ");
	fgets(id, 20, stdin);
	if(strlen(id) == 0 || id[0] == '\n'){
		printf("\nVui long nhap ID\n");
		return;
	}
	id[strcspn(id, "\n")] = '\0';
	for(int i = 0; i < *size; i++){
		if(strcmp(a[i].user.id, id) == 0){
			found = 1;
			printf("\n+------------+--------------------+------------------+-------------------+-------------+---------------+----------+--------+\n");
    		printf("| %-10s | %-18s | %-16s | %-17s | %-11s | %-13s | %-8s | %-6s |\n",
           			"ID", "Name", "Username", "Email", "Password", "Phone", "Balance", "Status");
    		printf("+============+====================+==================+===================+=============+===============+==========+========+\n");
    		printf("| %-10s | %-18s | %-16s | %-17s | %-11s | %-13s | %-8.2f | %-6s |\n",
               a[i].user.id,
               a[i].user.fullName,
               a[i].user.username,
               a[i].email,
               a[i].pass,
               a[i].user.phoneNumber,
               a[i].balance.money,
               a[i].status == 0 ? "Lock" : "Open");
        	printf("+------------+--------------------+------------------+-------------------+-------------+---------------+----------+--------+\n");
		}
	}
	free(id);
	if(found == 0){
		printf("\nID khong ton tai\n");
	}
}

void editAccounts(int *size, int index){
	char *change;
	int year, month, day;
	change = (char *)calloc(100, sizeof(char));
	fflush(stdin);
	
	do{
		printf("\nNhap ho ten (Nhan 0 de bo qua): ");
		fgets(change, 100, stdin);
		change[strcspn(change, "\n")] = '\0';
		if(strcmp(change, "0") == 0){
			break;
		}
	}
	while(checkFullName(change, strlen(change)) == 0);
	if(strcmp(change, "0") != 0){
		strcpy(a[index].user.fullName, change);
	}
	
	printf("\nNhap ngay thang nam sinh: ");
	do{
		printf("\n\tNhap nam sinh (nhan 0 de qua bo): ");
		scanf("%d", &year);
		if(year < 0){
			printf("\n\tNam nam sinh khong hop le\n");
		}
		if(year == 0){
			break;
		}
	}
	while(year < 0);
	if(year != 0){
		a[index].birthday.year = year;
	}
	
	do{
		printf("\tNhap thang sinh (bam 0 de bo qua): ");
		scanf("%d", &month);
		if(month == 0){
			break;
		}
		if(month < 1 || month > 12){
			printf("\n\tThang sinh khong hop le\n\n");
		}
	}
	while(month < 1 || month > 12);
	if(month != 0){
		a[index].birthday.month = month;
	}
	
	do{
		printf("\tNhap ngay sinh (bam 0 de bo qua): ");
		scanf("%d", &day);
		if(day == 0){
			break;
		}
	}
	while(checkBirthday(day, month, year) == 0);
	if(day != 0){
		a[index].birthday.day = day;
	}
	
	fflush(stdin);
	do{
		printf("\nNhap email (bam 0 de bo qua): ");
		fgets(change, 100, stdin);
		change[strcspn(change, "\n")] = '\0';
		if(strcmp(change, "0") == 0){
			break;
		}
	}
	while(checkAddUser(change, size, 2) == 0);
	if(strcmp(change, "0") != 0){
		strcpy(a[index].email, change);
	}
	
	do{
		printf("\nNhap so dien thoai (bam 0 de bo qua): ");
		fgets(change, 100, stdin);
		change[strcspn(change, "\n")] = '\0';
		if(strcmp(change, "0") == 0){
			break;
		}
	}
	while(checkAddUser(change, size, 3) == 0);
	if(strcmp(change, "0") != 0){
		strcpy(a[index].user.phoneNumber, change);
	}
	
	do{
		printf("\nNhap username (bam 0 de bo qua): ");
		fgets(change, 100, stdin);
		change[strcspn(change, "\n")] = '\0';
		if(strcmp(change, "0") == 0){
			break;
		}
	}
	while(checkAddUser(change, size, 4) == 0);
	if(strcmp(change, "0") != 0){
		strcpy(a[index].user.username, change);
	}
	
	printf("\nCap nhat thong tin nguoi dung thanh cong\n");
}

void IDeditAccounts(int *size){
	char *id;
	id = (char *)calloc(20, sizeof(char));
	if(id == NULL){
		printf("\nDa xay ra loi vui long thu lai\n");
		return;
	}
	fflush(stdin);
	printf("\nNhap ID nguoi dung: ");
	fgets(id, 20, stdin);
	id[strcspn(id, "\n")] = '\0';
	if(strlen(id) == 0){
		printf("\nVui long nhap ID\n");
		return;
	}
	int found = 0;
	for(int i = 0; i < *size; i++){
		if(strcmp(id, a[i].user.id) == 0){
			found = 1;
			editAccounts(size, i);
			break;
		}
	}
	if(found == 0){
		printf("\nID nguoi dung khong ton tai\n");
	}
	free(id);
}

void backOrExit(){
	char choice;
	fflush(stdin);
	do{
		printf("\nGo back (b)? or Exit (0)? :");
		scanf("%c", &choice);
		fflush(stdin);
		switch(choice){
			case 'b':
				break;
			case '0':
				exit(0);
			default:
				printf("\nERORR\n");
				break;
		}
	}
	while(choice != 'b');
}

void menuAdmin(int *size){
	int choice;
	printf("\n\t   MENU\n");
	printf("========================================");
	do{
		system("cls");
		printf("\n[1]. Them nguoi dung moi\n");
		printf("[2]. Hien thi chi tiet nguoi dung\n");
		printf("[3]. Khoa (mo) tai khoan\n");
		printf("[4]. Xoa tai khoan\n");
		printf("[5]. Tim kiem tai khoan theo ten\n");
		printf("[6]. Tim kiem tai khoan theo ID\n");
		printf("[7]. Sap xep tai khoan\n");
		printf("[8]. Sua thong tin nguoi dung\n");
		printf("[9]. Thoat\n");
		printf("========================================\n");
		printf("Nhap chuc nang: ");
		scanf("%d", &choice);
		system("cls");
		if(choice == 1){
			addUser(size);
			backOrExit();
			saveToFile(size);
		}
		else if(*size == 0){
			printf("\nDanh sach nguoi dung trong\n");
			backOrExit();
		}
		else{
			switch(choice){
				case 2:
					displayUserDetail(size);
					backOrExit();
					break;
				case 3:
					lockUnlockAccounts(size);
					backOrExit();
					saveToFile(size);
					break;
				case 4:
					deleteAccounts(size);
					backOrExit();
					saveToFile(size);
					break;
				case 5:
					searchByName(size);
					backOrExit();
					break;
				case 6:
					searchByID(size);
					backOrExit();
					break;
				case 7:
					arrangeAccounts(size);
					backOrExit();
					saveToFile(size);
					break;
				case 8:
					IDeditAccounts(size);
					backOrExit();
					saveToFile(size);
					break;
				case 9:
					printf("\nThoat thanh cong\n\n");
					break;
				default:
					printf("\nChuc nang khong hop le\n");
					break;
			}
		}
	}
	while(choice != 9);
}

void depositMoney(int myIndex){
	float money;
	printf("\nNhap so tien muon nap: ");
	scanf("%f", &money);
	if(money <= 0){
		printf("\nSo tien nap khong hop le\n");
		return;
	}
	a[myIndex].balance.money += money;
	printf("\nNap tien thanh cong\n");
}

int checkWithdrawMoney(int myIndex){
	char *pass, ch;
	int indexPass = 0;
	pass = (char *)calloc(50, sizeof(char));
	printf("\nVui long nhap lai mat khau: ");
	while((ch = getch()) != '\r'){
		if(ch == '\b'){
			if(indexPass > 0){
				indexPass--;
				printf("\b \b");
			}
		}
		else{
			printf("*");
			pass[indexPass++] = ch;
		}
	}
	pass[indexPass] = '\0';
	
	if(strcmp(pass, a[myIndex].pass) == 0){
		free(pass);
		return 1;
	}
	
	free(pass);
	return 0;
}

void withdrawMoney(int myIndex){
	float money;
	printf("\nNhap so tien ban muon rut: ");
	scanf("%f", &money);
	
	if(money <= 0 ){
		printf("\n\nSo tien muon rut nhap khong hop le\n\n");
		return;
	}
	
	if(money > a[myIndex].balance.money){
		printf("\n\nSo du hien khong du khong the thuc hien dao dich\n\n");
		return;
	}
	
	if(checkWithdrawMoney(myIndex) == 1){
		a[myIndex].balance.money -= money;
		printf("\n\nRut tien thanh cong\n");
	}
	else{
		printf("\n\nRut tien that bai\n");
	}
}

void checkTransferMoney(int *size, int myIndex, int indexTransfer){
	char *pass, ch;
	float money;
	pass = (char *)calloc(20, sizeof(char));
	int indexPass = 0, found = 0;
	printf("\nNhap so tien muon gui: ");
	scanf("%f", &money);
	
	if(money <= 0){
		printf("\nSo tien nhap khong hop le\n\n");
		return;
	}
	
	if(money > a[myIndex].balance.money){
		printf("\nSo du tai khoan khong du\n\n");
		return;
	}
	
	printf("\nNhap lai mat khau: ");
	while((ch = getch()) != '\r'){
		if(ch == '\b'){
			if(indexPass > 0){
				indexPass--;
				printf("\b \b");
			}
		}
		else{
			printf("*");
			pass[indexPass++] = ch;
		}
	}
	pass[indexPass] = '\0';
	
	if(strcmp(pass, a[myIndex].pass) == 0){
		a[myIndex].balance.money -= money;
		a[indexTransfer].balance.money += money;
		printf("\n\nChuyen tien thanh cong\n\n");
	}
	else{
		printf("\nMat khau nhap khong chinh xac\n\n");
	}
	free(pass);
}

void transferMoney(int *size, int myIndex){
	int found = 0;
	char *id;
	id = (char *)calloc(15, sizeof(char));
	fflush(stdin);
	printf("\nNhap ID muon gui tien: ");
	fgets(id, 20, stdin);
	
	if(id[0] == '\n'){
		printf("\nNhap khong hop le\n\n");
		return;
	}
	
	id[strcspn(id, "\n")] = '\0';
	
	if(strcmp(id, a[myIndex].user.id) == 0){
		printf("\nKhong the chuyen tien cho chinh minh\n\n");
		return;
	}
	
	for(int i = 0; i < *size; i++){
		if(strcmp(id, a[i].user.id) == 0){
			found = 1;
			if(a[i].status == 1){
				checkTransferMoney(size, myIndex, i);
				break;
			}
			else{
				printf("\nTai khoan nay hien dang bi khoa khong the thuc hien giao dich\n\n");
				break;
			}
		}
	}

	if(found == 0){
		printf("\nID nguoi dung nhap khong ton tai\n\n");
	}
}

void editPass(int myIndex){
	fflush(stdin);
	char *pass, *pass2;
	pass = (char *)calloc(50, sizeof(char));
	pass2 = (char *)calloc(50, sizeof(char));
	do{
		printf("\nNhap mat khau hien tai: ");
		fgets(pass, 50,stdin);
		pass[strcspn(pass, "\n")] = '\0';
		if(strcmp(pass, a[myIndex].pass) != 0){
			printf("\nMat khau khong chinh xac\n");
		}
	}
	while(strcmp(pass, a[myIndex].pass) != 0);
	
	do{
		printf("\nNhap mat khau moi: ");
		fgets(pass, 50, stdin);
		pass[strcspn(pass, "\n")] = '\0';
		if(strlen(pass) < 6){
			printf("\nMat khau phai co it nhat 6 ki tu\n");
		}
	}
	while(strlen(pass) < 6);
	
	do{
		printf("\nNhap lai mat khau: ");
		fgets(pass2, 50, stdin);
		pass2[strcspn(pass2, "\n")] = '\0';
		if(strcmp(pass, pass2) != 0){
			printf("\nMat khau khong trung nhau\n");
		}
	}
	while(strcmp(pass, pass2) != 0);
	strcpy(a[myIndex].pass, pass);
	printf("\nDoi mat khau thanh cong\n");
	free(pass);
	free(pass2);
}

void menuUser(int *size, int myIndex){
	int choice;
	printf("\n\n\t     WELCOME\n");
	printf("========================================\n");
	do{
		system("cls");
		printf("Xin chao %s\n", a[myIndex].user.fullName);
		printf("\nSo du hien tai: %.2f\n", a[myIndex].balance.money);
		printf("========================================\n");
		printf("[1]. Nap tien vao tai khoan\n");
		printf("[2]. Rut tien khoi tai khoan\n");
		printf("[3]. Chuyen tien\n");
		printf("[4]. Doi mat khau\n");
		printf("[5]. Sua thong tin ca nhan\n");
		printf("[6]. Thoat\n");
		printf("========================================\n");
		printf("Nhap chuc nang: ");
		scanf("%d", &choice);
		system("cls");
		switch(choice){
			case 1:
				depositMoney(myIndex);
				saveToFile(size);
				backOrExit();
				break;
			case 2:
				withdrawMoney(myIndex);
				saveToFile(size);
				backOrExit();
				break;
			case 3:
				transferMoney(size, myIndex);
				saveToFile(size);
				backOrExit();
				break;
			case 4:
				editPass(myIndex);
				saveToFile(size);
				backOrExit();
				break;
			case 5:
				editAccounts(size, myIndex);
				saveToFile(size);
				backOrExit();
				break;
			case 6:
				printf("\nCam on quy khach da su dung dich vu\n\n");
				break;
		}
	}
	while(choice != 6);
	return;
}

void checkSignInUser(char *email, char *pass, int *size){
	int found = 0;
	if(strlen(email) == 0 || strlen(email) == '\n' && strlen(pass) == 0 && strlen(pass) == '\n'){
		printf("\n\nNhap khong hop le\n\n");
		return;
	}
	for(int i = 0; i < *size; i++){
		if(strcmp(a[i].email, email) == 0 && strcmp(a[i].pass, pass) == 0){
			found = 1;
			if(a[i].status == 1){
				menuUser(size, i);
				break;
			}
			else{
				printf("\n\nTai khoan hien dang bi khoa vui long thu lai\n\n");
				break;
			}
		}
	}
	if(found == 0){
		printf("\n\nTai khoan hoac mat khau khong chinh xac\n\n");
	}
}

void signInAdmin(char *email, char *pass, int *size){
	char ch;
	int indexPass = 0;
	fflush(stdin);
	
	printf("\nNhap tai khoan: ");
	fgets(email, 50, stdin);
	email[strcspn(email, "\n")] = '\0';
	printf("\nNhap mat khau: ");
	while((ch = getch()) != '\r'){
		if(ch == '\b'){
			if(indexPass > 0){
				indexPass--;
				printf("\b \b");
			}
		}
		else{
			printf("*");
			pass[indexPass++] = ch;
		}
	}
	pass[indexPass] = '\0';
	
	if(strcmp(email, "admin") == 0 && strcmp(pass, "admin") == 0){
		printf("\n\nDang nhap thanh cong voi quyen quan tri vien\n");
		menuAdmin(size);
	}
	else{
		printf("\n\nDang nhap that bai vui long thu lai\n\n");
	}
}

void signInUser(char *email, char *pass, int *size){
	char ch;
	int indexPass = 0;
	fflush(stdin);
	
	printf("\nNhap tai khoan: ");
	fgets(email, 50, stdin);
	email[strcspn(email, "\n")] = '\0';
	printf("\nNhap mat khau: ");
	while((ch = getch()) != '\r'){
		if(ch == '\b'){
			if(indexPass > 0){
				indexPass--;
				printf("\b \b");
			}
		}
		else{
			printf("*");
			pass[indexPass++] = ch;
		}
	}
	pass[indexPass] = '\0';
	
	checkSignInUser(email, pass, size);
}
	

