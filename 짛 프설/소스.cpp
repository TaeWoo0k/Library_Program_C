#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#pragma warning (disable : 4996)
struct MEMBER             //ȸ��
{
	char member_name[30];
	char member_age[20];
	char member_sex[20];
	char member_phone[30];
	int  borrow;
};
struct BOOK              //����
{
	char book_name[30];
	char auth_name[30];
	char publ_name[30];
	int borrowed;
};

typedef struct MEMBER MEMBER;      //����ü ��� ����         
typedef struct BOOK BOOK;         //����ü å ����

/* �����ƾ���� */
int mem_member(MEMBER *member_list, int *ntn);   //ȸ�� �߰�
//int membership_member();
int retrieve_member_info(MEMBER **member_list, int *total_num_member); //
int print_member_list(MEMBER *member_list, int total_num_member);
int register_book(BOOK *book_list, int *nth);
int search_book(BOOK *book_list, int total_num_book);
int borrow_book(BOOK *book_list, MEMBER *member_list, int total_num_member, int total_num_book);
int return_book(BOOK *book_list, MEMBER *member_list, int total_num_member, int total_num_book);
int print_book_list(BOOK *book_list, int total_num_book);
int retrieve_book_info(BOOK **book_list, int *total_num_book);
int compare(char *str1, char *str2);
int member_cnt(void);
int book_main(void);
int seat_main(void);

void SYSTEM();
void VIEW_SEAT(int chain[7][9]);
void SEAT(int chain[7][9], int width, int height);
void EXIT(int chain[7][9], int width, int height);
void END();



int num_total_member = 0; /* ���� ȸ���� �� */
int num_total_book = 0; /* ���� å�� �� */
BOOK *book_list;      //����ü�� txt ���Ͽ� �ҷ��´�
MEMBER *member_list;   //����ü�� txt ���Ͽ� �ҷ��´�

int main()
{
	member_list = (MEMBER *)malloc(sizeof(MEMBER)* 1000);   //���� �޸��Ҵ�
	retrieve_member_info(&member_list, &num_total_member); //��� �ҷ�����
	int user_choice;
	int i;
	printf("\n");
	printf("********************************************************************************");
	printf("********************************************************************************");
	printf("***************************���� & �¼� ���� ���α׷�****************************");
	printf("\n");
	printf("********************************************************************************");
	printf("********************************************************************************");

	_getch();
	system("cls");
	while (1)
	{
		printf("********************************************************************************");
		printf("*******************************************************************************");
		printf("\n\n");
		printf("                  ��------�ڿ��Ͻô� �޴��� �����ϼ����------��\n");
		printf("                  ��        [1]ȸ�����                       ��\n");
		printf("                  ��        [2]ȸ�����                       ��\n");
		printf("                  ��        [3]��������                       ��\n");
		printf("                  ��        [4]�¼�����                       ��\n");
		printf("                  ��        [5]���α׷�����                   ��\n");
		printf("                  ����������������������������������������������");
		printf("\n");
		printf("[6]������ ��й�ȣ");
		printf("\n\n");
		printf("********************************************************************************");
		printf("********************************************************************************");


		printf("����� ������ : ");
		scanf_s("%d", &user_choice);

		if (user_choice == 1)
		{
			/*ȸ�� ��� �ϴ� �Լ� ȣ��*/
			mem_member(member_list, &num_total_member);
			print_member_list(member_list, num_total_member);

		}
		else if (user_choice == 2)
		{
			/*ȸ�� ��� Ȯ�� �ϴ� �Լ� ȣ��*/
			for (i = 0; i < num_total_member; i++)
			{
				printf("%s // %s // %s // %s //\n ", member_list[i].member_name, member_list[i].member_age, member_list[i].member_sex, member_list[i].member_phone);
			}

		}

		if (user_choice == 3)
		{
			book_main();

		}
		else if (user_choice == 4)
		{
			seat_main();
		}


		else if (user_choice == 5)
		{
			system("cls");
			printf("\n\n\n\n\n    ---------- ���� �̿� ��Ź�帳�ϴ� ---------\n");

			printf("������ : 4��(����) \n");

			printf("������б� ���α׷��� ���� (������ ������) �����ϼ��� ! \n");

			exit(0);
			break;
		}
		else if (user_choice == 6)
		{

		}
	}
	free(member_list);   //�޸� �Ҵ� ����
	return 0;
}
int print_member_list(MEMBER *member_list, int total_num_member)   //txt ���� �ҷ�����
{

	FILE *fp = fopen("member_list.txt", "w");      //���� ����
	int i;

	if (fp == NULL)                           //������ �ƹ��ŵ� ������ ��¿���
	{
		printf("��� ���� ! \n");
		return -1;      //-1�� �����߻��� �ǹ�
	}

	fprintf(fp, "%d\n", total_num_member);

	for (i = 0; i < total_num_member; i++)   //���Ͽ� �� �ɹ��� ���ڰ� ����������
	{

		fprintf(fp, "%s\n%s\n%s\n%s\n", member_list[i].member_name, member_list[i].member_age, member_list[i].member_sex, member_list[i].member_phone);
	}

	printf("��� �Ϸ�! \n");
	fclose(fp);

	return 0;

}
/* ȸ�� �߰� �Լ� */
int mem_member(MEMBER *member_list, int *ntn)
{

	printf("�̸� : ");
	scanf_s("%s", member_list[*ntn].member_name);
	printf("���� : ");
	scanf_s("%s", member_list[*ntn].member_age);

	printf("���� : ");
	scanf_s("%s", member_list[*ntn].member_sex);

	printf("�ڵ��� ��ȣ : ");
	scanf_s("%s", member_list[*ntn].member_phone);

	member_list[*ntn].borrow = 0;    //������� ���̰�
	(*ntn)++;


	return 0;
}
//int membership_member()



int book_main(void)
{
	system("cls");
	int user_choice; /* ������ ������ �޴� */
	int i;

	//    printf("�������� �ִ� ���� �弭 ���� �������ּ��� : "); 
	//    scanf_s("%d", &user_choice); 

	book_list = (BOOK *)malloc(sizeof(BOOK)* 1000);      //���� �޸��Ҵ�
	retrieve_book_info(&book_list, &num_total_book);   //ȸ�� �ҷ�����


	num_total_member = member_cnt();
	//   printf("%d", num_total_member);

	while (1)
	{
		printf("********************************************************************************");
		printf("***************************���� & �¼� ���� ���α׷�****************************");
		printf("\n");
		printf("                  ��------�ڿ��Ͻô� �޴��� �����ϼ����------��\n");
		printf("                  ��        [1]å�߰�                         ��\n");
		printf("                  ��        [2]å�˻�                         ��\n");
		printf("                  ��        [3]å�뿩                         ��\n");
		printf("                  ��        [4]å�ݳ�                         ��\n");
		printf("                  ��        [5]å���                         ��\n");
		printf("                  ��        [6]���α׷�����                   ��\n");
		printf("                  ����������������������������������������������");
		printf("\n");
		printf("\n");
		printf("********************************************************************************");
		printf("********************************************************************************");



		printf("����� ������ : ");
		scanf_s("%d", &user_choice);

		if (user_choice == 1)
		{
			/* å�� ���� �߰��ϴ� �Լ� ȣ�� */
			register_book(book_list, &num_total_book);
			print_book_list(book_list, num_total_book);
		}
		else if (user_choice == 2)
		{
			/* å�� �˻��ϴ� �Լ� ȣ�� */
			search_book(book_list, num_total_book);
		}
		else if (user_choice == 3)
		{
			/* å�� ������ �Լ� ȣ�� */
			borrow_book(book_list, member_list, num_total_member, num_total_book);
		}
		else if (user_choice == 4)
		{
			/* å�� �ݳ��ϴ� �Լ� ȣ�� */
			return_book(book_list, member_list, num_total_member, num_total_book);
		}

		else if (user_choice == 5)
		{
			/* å���� ����� ȭ�鿡 ����Ѵ�. */
			for (i = 0; i < num_total_book; i++)
			{
				printf("%s // %s // %s // ", book_list[i].book_name, book_list[i].auth_name, book_list[i].publ_name);
				if (book_list[i].borrowed == 0)
					printf("NO\n");
				else
					printf("YES\n");
			}
		}
		else if (user_choice == 6)
		{
			system("cls");
			break;
		}
	}
	free(book_list);   //�޸� �Ҵ� ����
	return 0;
}






int print_book_list(BOOK *book_list, int total_num_book)
{
	FILE *fp = fopen("book_list.txt", "w"); //���Ͼ���
	int i;

	if (fp == NULL)                     //������ ������
	{
		printf("��� ���� ! \n");         //��¿���
		return -1;                     //�����߻�
	}

	fprintf(fp, "%d\n", total_num_book);

	for (i = 0; i < total_num_book; i++)      //������ ��å�� ���ڰ� ���������� �ҷ��´�
	{
		fprintf(fp, "%s\n%s\n%s\n", book_list[i].book_name, book_list[i].auth_name, book_list[i].publ_name);
		if (book_list[i].borrowed == 0)
			fprintf(fp, "NO\n");
		else
			fprintf(fp, "YES\n");
	}

	printf("��� �Ϸ�! \n");
	fclose(fp);            //���� �ݱ�

	return 0;
}
int compare(char *str1, char *str2) //���Լ�
{
	while (*str1)
	{
		if (*str1 != *str2)
		{
			return 0;
		}

		str1++;
		str2++;
	}
	if (*str2 == '\0')
		return 1;

	return 0;
}
/* �������� member_list �� ���� �ٲ�� �ϹǷ� ���� ������ ���� */
int retrieve_member_info(MEMBER **member_list, int *total_num_member)
{
	FILE *fp = fopen("member_list.txt", "r");      //���� �ҷ����� 
	int total_member;
	int i;
	char str[20];

	if (fp == NULL)
	{
		printf("������ ������ ã�� �� �����ϴ�! \n");
		return -1;
	}

	/* ã�Ҵٸ� ��ü ȸ���� ������ �о�´�. */
	fscanf_s(fp, "%d", &total_member);
	(*total_num_member) = total_member;

	/* ������ member_list �����͸� ���� */
	free(*member_list);
	/* �׸��� �ٽ� malloc ���� ���Ҵ� �Ѵ�. */
	(*member_list) = (MEMBER *)malloc(sizeof(MEMBER)*total_member); //���Ͽ��� �Է¹��� å�� �� ��ŭ malloc ���� member_list�� �Ҵ�

	if (*member_list == NULL)
	{
		printf("\n ERROR \n");
		return -1;
	}
	for (i = 0; i<total_member; i++)
	{
		/* member_list[i]->member_name �� �ƴԿ� ����!! */
		fscanf_s(fp, "%s", (*member_list)[i].member_name);
		fscanf_s(fp, "%s", (*member_list)[i].member_age);
		fscanf_s(fp, "%s", (*member_list)[i].member_sex);
		fscanf_s(fp, "%s", (*member_list)[i].member_phone);
		fscanf_s(fp, "%s", str);
	}
	if (compare(str, "YES"))               //�뿩������ YES
	{
		(*member_list)[i].borrow = 1;
	}
	else if (compare(str, "NO"))            //�뿩������ ������ NO
	{
		(*member_list)[i].borrow = 0;
	}

	fclose(fp);
	return 0;

}
/* �������� book_list �� ���� �ٲ�� �ϹǷ� ���� ������ ���� */
int retrieve_book_info(BOOK **book_list, int *total_num_book)
{
	FILE *fp = fopen("book_list.txt", "r");
	int total_book;
	int i;
	char str[20];

	if (fp == NULL)
	{
		printf("������ ������ ã�� �� �����ϴ�! \n");
		return -1;
	}

	/* ã�Ҵٸ� ��ü å�� ������ �о�´�. */
	fscanf_s(fp, "%d", &total_book);
	(*total_num_book) = total_book;

	/* ������ book_list �����͸� ���� */
	free(*book_list);
	/* �׸��� �ٽ� malloc ���� ���Ҵ� �Ѵ�. */
	(*book_list) = (BOOK *)malloc(sizeof(BOOK)*total_book);

	if (*book_list == NULL)
	{
		printf("\n ERROR \n");
		return -1;
	}
	for (i = 0; i<total_book; i++)
	{
		/* book_list[i]->book_name �� �ƴԿ� ����!! */
		fscanf_s(fp, "%s", (*book_list)[i].book_name);
		fscanf_s(fp, "%s", (*book_list)[i].auth_name);
		fscanf_s(fp, "%s", (*book_list)[i].publ_name);
		fscanf_s(fp, "%s", str);

		if (compare(str, "YES"))               //�뿩������ YES
		{
			(*book_list)[i].borrowed = 1;
		}
		else if (compare(str, "NO"))            //�뿩������ ������ NO
		{
			(*book_list)[i].borrowed = 0;
		}
	}

	fclose(fp);
	return 0;

}
/* å�� �߰� �ϴ� �Լ�*/
int register_book(BOOK *book_list, int *nth)
{


	printf("å�� �̸� : ");
	scanf_s("%s", book_list[*nth].book_name);

	printf("å�� ���� : ");
	scanf_s("%s", book_list[*nth].auth_name);

	printf("å�� ���ǻ� : ");
	scanf_s("%s", book_list[*nth].publ_name);

	book_list[*nth].borrowed = 0;      // ������� ����
	(*nth)++;



	return 0;

}
/* å�� �˻��ϴ� �Լ� */
int search_book(BOOK *book_list, int total_num_book)
{


	system("cls");
	int user_input; /* ������� �Է��� �޴´�. */
	int i;
	char user_search[30]; //����ڰ� �Է��� �˻��� 

	printf("��� ������ �˻� �� ���ΰ���? \n");
	printf("1. å ���� �˻� \n");
	printf("2. ������ �˻� \n");
	printf("3. ���ǻ� �˻� \n");
	scanf_s("%d", &user_input);

	printf("�˻��� �ܾ �Է����ּ��� : ");
	scanf_s("%s", user_search);

	printf("�˻� ��� \n");

	if (user_input == 1)
	{
		/*

		i �� 0 ���� num_total_book ���� ���鼭 ������ å ������
		����ڰ� �Է��� �˻���� ��

		*/
		for (i = 0; i < total_num_book; i++)
		{
			if (compare(book_list[i].book_name, user_search))  //����ڰ� �Է��ѰŶ� �ϸ���Ʈ�� �ִ� å�� �̸��� ���ϴ�
			{
				printf("��ȣ : %d // å �̸� : %s // ������ : %s // ���ǻ� : %s \n",
					i, book_list[i].book_name, book_list[i].auth_name, book_list[i].publ_name);
			}
		}

	}
	else if (user_input == 2)
	{
		/*

		i �� 0 ���� num_total_book ���� ���鼭 ������ ������ �̸���
		����ڰ� �Է��� �˻���� ��

		*/
		for (i = 0; i < total_num_book; i++)
		{
			if (compare(book_list[i].auth_name, user_search))
			{
				printf("��ȣ : %d // å �̸� : %s // ������ : %s // ���ǻ� : %s \n",
					i, book_list[i].book_name, book_list[i].auth_name, book_list[i].publ_name);
			}
		}

	}
	else if (user_input == 3)
	{
		/*

		i �� 0 ���� num_total_book ���� ���鼭 ������ ���ǻ縦
		����ڰ� �Է��� �˻���� ��.

		*/
		for (i = 0; i < total_num_book; i++)
		{
			if (compare(book_list[i].publ_name, user_search))
			{
				printf("��ȣ : %d // å �̸� : %s // ������ : %s // ���ǻ� : %s \n",
					i, book_list[i].book_name, book_list[i].auth_name, book_list[i].publ_name);
			}
		}
	}

	return 0;
}
int borrow_book(BOOK *book_list, MEMBER *member_list, int total_num_member, int total_num_borrow)
{
	system("cls");
	int user_input; /* ������� �Է��� �޴´�. */
	int i;
	char user_search[30]; //����ڰ� �Է��� �˻��� 



	printf("��ȭ��ȣ�� �Է����ּ���\n");
	printf("��ȭ��ȣ:");
	scanf_s("%s", &user_search);

	printf("�˻� ��� \n");

	for (i = 0; i < total_num_member; i++)
	{
		if (compare(member_list[i].member_phone, user_search))  //����ڰ� �Է��ѰŶ� �ϸ���Ʈ�� �ִ� å�� �̸��� ���ϴ�
		{
			printf("�̸� : %s\n���� : %s\n���� : %s\n��ȭ��ȣ: %s\n",
				member_list[i].member_name, member_list[i].member_age, member_list[i].member_sex, member_list[i].member_phone);
		}
	}
	printf("ȸ�� ������ �����Ű���?\n");
	printf("1.��");
	printf("2.�ƴϿ�");
	scanf_s("%d", &user_input);

	if (user_input == 1)
	{
		/* ����ڷ� ���� å��ȣ�� ���� ����*/

		int book_num;

		printf("���� å�� ��ȣ�� �����ּ��� \n");
		printf("å ��ȣ : ");

		scanf_s("%d", &book_num);



		if (book_list[book_num].borrowed == 0)
		{
			printf("å�� ���������� ����Ǿ����ϴ�.\n");
			book_list[book_num].borrowed = 1;
		}
		else
		{
			printf("�̹� ������ �Դϴ�");
		}
	}
	else if (user_input == 2)
	{
		printf("�ٽ� �����ϼ���\n");


	}
	/*   FILE *fp = fopen("borrow_list.txt", "w");

	int j;

	if(fp == NULL)                     //������ ������
	{
	printf("��� ���� ! \n");         //��¿���
	return -1;                     //�����߻�
	}

	fprintf(fp, "%d\n", total_num_borrow);

	for(j = 0; j < total_num_borrow; i++)      //������ �뿩 ��Ȳ�� �ҷ��´�.
	{
	fprintf(fp, "%d\n%s\n", member_list[i].member_phone, book_list[i].book_name);
	}

	printf("��� �Ϸ�! \n");
	fclose(fp);            //���� �ݱ� */



	return 0;
}


int return_book(BOOK *book_list, MEMBER *member_list, int total_num_member, int total_num_book)
{
	system("cls");
	int user_input; /* ������� �Է��� �޴´�. */
	int i;
	char user_search[30]; //����ڰ� �Է��� �˻��� 
	char search[30];

	printf("��ȭ��ȣ�� �Է����ּ���\n");
	printf("��ȭ��ȣ:");
	scanf_s("%s", user_search);

	printf("�˻� ��� \n");

	for (i = 0; i < total_num_member; i++)
	{
		if (compare(member_list[i].member_phone, user_search))  //����ڰ� �Է��ѰŶ� �ϸ���Ʈ�� �ִ� å�� �̸��� ���ϴ�
		{
			printf("�̸� : %s\n���� : %s\n���� : %s\n��ȭ��ȣ: %s\n",
				member_list[i].member_name, member_list[i].member_age, member_list[i].member_sex, member_list[i].member_phone);
		}
	}

	/*
	printf("�ݳ��� å�� �����Դϴ�\n");
	scanf_s("%s",search);
	if(member_list[i].member_phone == book_list[i].book_name)
	{
	for(i = 0;i < total_num_book; i++)
	{
	if(compare(book_list[i].book_name, search))  //����ڰ� �Է��ѰŶ� �ϸ���Ʈ�� �ִ� å�� �̸��� ���ϴ�
	{
	printf("��ȣ : %d // å �̸� : %s // ������ : %s // ���ǻ� : %s \n",
	i, book_list[i].book_name, book_list[i].auth_name, book_list[i].publ_name);
	}
	}
	} */
	/* �ݳ��� å�� ��ȣ */
	int num_book;

	printf("�ݳ��� å�� ��ȣ�� ���ּ��� \n");
	printf("å ��ȣ : ");

	scanf_s("%d", &num_book);

	if (book_list[num_book].borrowed == 0)
	{
		printf("�̹� �ݳ��Ǿ� �ִ� �����Դϴ�\n");
	}
	else
	{
		book_list[num_book].borrowed = 0;
		printf("���������� �ݳ��Ǿ����ϴ�\n");
	}

	return 0;
}

int member_cnt(void)
{
	FILE *fp = fopen("member_list.txt", "r");      //���� �б�
	int total_num = 022;
	char s[2];

	if (fp == NULL)                           //������ �ƹ��ŵ� ������ ��¿���
	{
		printf("��� ���� ! \n");
		return -1;      //-1�� �����߻��� �ǹ�
	}

	fgets(s, 2, fp);
	total_num = atoi(s);

	return total_num;
}



int seat_main(void)
{

//	srand(time(NULL));
	/* printf("********************************************************************************");
	printf("***************************���� & �¼� ���� ���α׷�****************************");
	printf("\n");
	printf("********************************************************************************");
	printf("********************************************************************************");

	_getch();
	system("cls");*/
	SYSTEM();

	return 0;
}

void SYSTEM()
{
	system("cls");
	int i, j, select, width = 0, height = 0;
	int chain[7][9] = { 0 };

	for (i = 1; i <= 6; i++)
	for (j = 1; j <= 8; j++)
	{
		//chain[i][j]=rand()%2;

		for (i = 0; i <= 6; i++)
		{
			chain[i][3] = 2;
			chain[i][6] = 2;
		}
		while (1)
		{
			VIEW_SEAT(chain);
			printf("\n");
			printf("                  ��------�ڿ��Ͻô� �޴��� �����ϼ����------��\n");
			printf("                  ��        [1]�¼� ����                      ��\n");
			printf("                  ��        [2]�¼� ���� ���                 ��\n");
			printf("                  ��        [3]���α׷� ����                  ��\n");
			printf("                  ����������������������������������������������");
			printf("\n");
			scanf_s("%d", &select);
			if (select == 1)
			{
				SEAT(chain, width, height);
			}
			else if (select == 2)
			{
				EXIT(chain, width, height);
			}
			else if (select == 3)
			{
				END();
			}

		}
	}return;
}

void VIEW_SEAT(int chain[7][9])
{
	int width, height;
	printf("���¼� : �� \n�ڸ� ���� : �� \n\n");
	printf("1 2  3 4  5 6 \n");
	for (height = 1; height <= 6; height++)
	{
		for (width = 1; width <= 8; width++)
		{
			if (chain[height][width] == 0)
				printf("��");
			else if (chain[height][width] == 1)
				printf("��");
			else if (chain[height][width] == 2)
				printf(" ");
		}
		printf("\n");
	}
}

void SEAT(int chain[7][9], int width, int height)
{
	int cnt;
	while (1)
	{

		VIEW_SEAT(chain);

		printf("\n������ �ڸ��� �ٰ� ��ȣ�� �Է��ϰ� ���͸� ��������\n  ��)1��° �� 3��° �ڸ� : 1 3 ��, �߰��� �����̽��� �ѹ� ��켼��\n");
		scanf_s("%d %d", &height, &width);

		if (height>6 || width>6)
		{
			printf("\n�Է¿����Դϴ�. �ƹ�Ű�� ������ �ٽ� �Է��ϼ���\n\n");
			_getch();
		}
		else if (height <= 6 || width <= 6){
			break;
		}
	}


	for (cnt = 1; cnt<2; cnt++)
	{
		if (width == cnt)
		{
			if (chain[height][width] == 1)
			{
				system("cls");
				VIEW_SEAT(chain);
				printf("\n�̹� ����� �¼� �Դϴ�. �ƹ�Ű�� ���� �ٽ� �ϼ���\n\n");
				_getch();
			}
		}
	}

	if (width == 3){
		width += 1;
		if (chain[height][width] == 1)
		{
			system("cls");
			VIEW_SEAT(chain);
			printf("\n�̹� ����� �¼� �Դϴ�. �ƹ�Ű�� ���� �ٽ� �ϼ���\n\n");
			_getch();
		}
		else{
			chain[height][width] = 1;
			width -= 1;
		}
	}
	else if (width == 4){
		width += 1;
		if (chain[height][width] == 1){
			system("cls");
			VIEW_SEAT(chain);
			printf("\n�̹� ����� �¼� �Դϴ�. �ƹ�Ű�� ���� �ٽ� �ϼ���\n\n");
			_getch();
		}
		else
			chain[height][width] = 1;
	}
	else if (width == 5){
		width += 2;
		if (chain[height][width] == 1){
			system("cls");
			VIEW_SEAT(chain);
			printf("\n�̹� ����� �¼� �Դϴ�. �ƹ�Ű�� ���� �ٽ� �ϼ���\n\n");
			_getch();
		}
		else
			chain[height][width] = 1;
	}
	else if (width == 6){
		width += 2;
		if (chain[height][width] == 1){
			system("cls");
			VIEW_SEAT(chain);
			printf("\n�̹� ����� �¼� �Դϴ�. �ƹ�Ű�� ���� �ٽ� �ϼ���\n\n");
			_getch();
		}
		else
			chain[height][width] = 1;
	}
	else
		chain[height][width] = 1;
	system("cls");
}

void EXIT(int chain[7][9], int width, int height){
	int cnt;
	while (1){
		system("cls");
		VIEW_SEAT(chain);
		printf("\n������ ����� �ڸ��� �ٰ� ��ȣ�� �Է��Ͻð� ���͸� �����ÿ�.\n");
		scanf_s("%d %d", &height, &width);

		if (height>6 || width>6)
		{
			printf("\n�Է¿����Դϴ�. �ƹ�Ű�� ������ �ٽ� �Է��ϼ���\n\n");
			_getch();
		}
		else if (height <= 6 || width <= 6){
			break;
		}
	}


	for (cnt = 1; cnt <= 2; cnt++)
	{
		if (width == cnt)
		{
			if (chain[height][width] == 1)
			{
				system("cls");
				chain[height][width] = 0;
				VIEW_SEAT(chain);
				printf("\n������ ��� �Ϸ�Ǿ����ϴ�. �ƹ�Ű�� ������ �����޴��� �Ѿ�ϴ�\n\n");
				_getch();
			}
			else if (chain[height][width] == 0){
				printf("\n�ڸ��� ���� ���Դϴ� �ƹ�Ű�� ������ �����޴��� �Ѿ�ϴ�.\n\n");
				_getch();
			}
		}
	}

	if (width == 3){
		width += 1;
		if (chain[height][width] == 1){
			system("cls");
			chain[height][width] = 0;
			VIEW_SEAT(chain);
			printf("\n������ ��� �Ϸ�Ǿ����ϴ�. �ƹ�Ű�� ������ �����޴��� �Ѿ�ϴ�\n\n");
			_getch();
		}
		else if (chain[height][width] == 0){
			printf("\n�ڸ��� ���� ���Դϴ�. �ƹ�Ű�� ������ �����޴��� �Ѿ�ϴ�.\n\n");
			_getch();
		}
		width -= 1;
	}

	if (width == 4){
		width += 1;
		if (chain[height][width] == 1){
			system("cls");
			chain[height][width] = 0;
			VIEW_SEAT(chain);
			printf("\n������ ��� �Ϸ�Ǿ����ϴ�. �ƹ�Ű�� ������ �����޴��� �Ѿ�ϴ�\n\n");
			_getch();
		}
		else if (chain[height][width] == 0){
			printf("\n�ڸ��� ���� ���Դϴ�. �ƹ�Ű�� ������ �����޴��� �Ѿ�ϴ�.\n\n");
			_getch();
		}
		width = 4;
	}

	if (width == 5){
		width += 2;
		if (chain[height][width] == 1){
			system("cls");
			chain[height][width] = 0;
			VIEW_SEAT(chain);
			printf("\n������ ��� �Ϸ�Ǿ����ϴ�. �ƹ�Ű�� ������ �����޴��� �Ѿ�ϴ�\n\n");
			_getch();
		}
		else if (chain[height][width] == 0){
			printf("\n�ڸ��� ���� ���Դϴ�. �ƹ�Ű�� ������ �����޴��� �Ѿ�ϴ�.\n\n");
			_getch();
		}
		width -= 2;
	}

	if (width == 6){
		width += 2;
		if (chain[height][width] == 1){
			system("cls");
			chain[height][width] = 0;
			VIEW_SEAT(chain);
			printf("\n������ ��� �Ϸ�Ǿ����ϴ�. �ƹ�Ű�� ������ �����޴��� �Ѿ�ϴ�\n\n");
			_getch();
		}
		else if (chain[height][width] == 0){
			printf("\n�ڸ��� ���� ���Դϴ�. �ƹ�Ű�� ������ �����޴��� �Ѿ�ϴ�.\n\n");
			_getch();
		}
	}
	system("cls");
}

void END()
{
	exit(1);
}