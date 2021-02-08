#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#pragma warning (disable : 4996)
struct MEMBER             //회원
{
	char member_name[30];
	char member_age[20];
	char member_sex[20];
	char member_phone[30];
	int  borrow;
};
struct BOOK              //도서
{
	char book_name[30];
	char auth_name[30];
	char publ_name[30];
	int borrowed;
};

typedef struct MEMBER MEMBER;      //구조체 멤버 선언         
typedef struct BOOK BOOK;         //구조체 책 선언

/* 서브루틴값들 */
int mem_member(MEMBER *member_list, int *ntn);   //회원 추가
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



int num_total_member = 0; /* 현재 회원의 수 */
int num_total_book = 0; /* 현재 책의 수 */
BOOK *book_list;      //구조체를 txt 파일에 불러온다
MEMBER *member_list;   //구조체를 txt 파일에 불러온다

int main()
{
	member_list = (MEMBER *)malloc(sizeof(MEMBER)* 1000);   //동적 메모리할당
	retrieve_member_info(&member_list, &num_total_member); //멤버 불러오기
	int user_choice;
	int i;
	printf("\n");
	printf("********************************************************************************");
	printf("********************************************************************************");
	printf("***************************도서 & 좌석 관리 프로그램****************************");
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
		printf("                  ┌------★원하시는 메뉴를 선택하세요★------┐\n");
		printf("                  │        [1]회원등록                       │\n");
		printf("                  │        [2]회원목록                       │\n");
		printf("                  │        [3]도서관리                       │\n");
		printf("                  │        [4]좌석관리                       │\n");
		printf("                  │        [5]프로그램종료                   │\n");
		printf("                  └─────────────────────┘");
		printf("\n");
		printf("[6]관리자 비밀번호");
		printf("\n\n");
		printf("********************************************************************************");
		printf("********************************************************************************");


		printf("당신의 선택은 : ");
		scanf_s("%d", &user_choice);

		if (user_choice == 1)
		{
			/*회원 등록 하는 함수 호출*/
			mem_member(member_list, &num_total_member);
			print_member_list(member_list, num_total_member);

		}
		else if (user_choice == 2)
		{
			/*회원 목록 확인 하는 함수 호출*/
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
			printf("\n\n\n\n\n    ---------- 많은 이용 부탁드립니다 ---------\n");

			printf("만든팀 : 4조(사죠) \n");

			printf("성결대학교 프로그래밍 설계 (정복래 교수님) 월요일수업 ! \n");

			exit(0);
			break;
		}
		else if (user_choice == 6)
		{

		}
	}
	free(member_list);   //메모리 할당 해제
	return 0;
}
int print_member_list(MEMBER *member_list, int total_num_member)   //txt 파일 불러오기
{

	FILE *fp = fopen("member_list.txt", "w");      //파일 쓰기
	int i;

	if (fp == NULL)                           //파일이 아무거도 없으면 출력오류
	{
		printf("출력 오류 ! \n");
		return -1;      //-1은 에러발생을 의미
	}

	fprintf(fp, "%d\n", total_num_member);

	for (i = 0; i < total_num_member; i++)   //파일에 총 맴버의 숫자가 끝날때까지
	{

		fprintf(fp, "%s\n%s\n%s\n%s\n", member_list[i].member_name, member_list[i].member_age, member_list[i].member_sex, member_list[i].member_phone);
	}

	printf("출력 완료! \n");
	fclose(fp);

	return 0;

}
/* 회원 추가 함수 */
int mem_member(MEMBER *member_list, int *ntn)
{

	printf("이름 : ");
	scanf_s("%s", member_list[*ntn].member_name);
	printf("나이 : ");
	scanf_s("%s", member_list[*ntn].member_age);

	printf("성별 : ");
	scanf_s("%s", member_list[*ntn].member_sex);

	printf("핸드폰 번호 : ");
	scanf_s("%s", member_list[*ntn].member_phone);

	member_list[*ntn].borrow = 0;    //순서대로 쌓이게
	(*ntn)++;


	return 0;
}
//int membership_member()



int book_main(void)
{
	system("cls");
	int user_choice; /* 유저가 선택한 메뉴 */
	int i;

	//    printf("도서관의 최대 보관 장서 수를 설정해주세요 : "); 
	//    scanf_s("%d", &user_choice); 

	book_list = (BOOK *)malloc(sizeof(BOOK)* 1000);      //동적 메모리할당
	retrieve_book_info(&book_list, &num_total_book);   //회원 불러오기


	num_total_member = member_cnt();
	//   printf("%d", num_total_member);

	while (1)
	{
		printf("********************************************************************************");
		printf("***************************도서 & 좌석 관리 프로그램****************************");
		printf("\n");
		printf("                  ┌------★원하시는 메뉴를 선택하세요★------┐\n");
		printf("                  │        [1]책추가                         │\n");
		printf("                  │        [2]책검색                         │\n");
		printf("                  │        [3]책대여                         │\n");
		printf("                  │        [4]책반납                         │\n");
		printf("                  │        [5]책목록                         │\n");
		printf("                  │        [6]프로그램종료                   │\n");
		printf("                  └─────────────────────┘");
		printf("\n");
		printf("\n");
		printf("********************************************************************************");
		printf("********************************************************************************");



		printf("당신의 선택은 : ");
		scanf_s("%d", &user_choice);

		if (user_choice == 1)
		{
			/* 책을 새로 추가하는 함수 호출 */
			register_book(book_list, &num_total_book);
			print_book_list(book_list, num_total_book);
		}
		else if (user_choice == 2)
		{
			/* 책을 검색하는 함수 호출 */
			search_book(book_list, num_total_book);
		}
		else if (user_choice == 3)
		{
			/* 책을 빌리는 함수 호출 */
			borrow_book(book_list, member_list, num_total_member, num_total_book);
		}
		else if (user_choice == 4)
		{
			/* 책을 반납하는 함수 호출 */
			return_book(book_list, member_list, num_total_member, num_total_book);
		}

		else if (user_choice == 5)
		{
			/* 책들의 목록을 화면에 출력한다. */
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
	free(book_list);   //메모리 할당 해제
	return 0;
}






int print_book_list(BOOK *book_list, int total_num_book)
{
	FILE *fp = fopen("book_list.txt", "w"); //파일쓰기
	int i;

	if (fp == NULL)                     //파일이 없으면
	{
		printf("출력 오류 ! \n");         //출력오류
		return -1;                     //에러발생
	}

	fprintf(fp, "%d\n", total_num_book);

	for (i = 0; i < total_num_book; i++)      //파일의 총책의 숫자가 끝날떄까지 불러온다
	{
		fprintf(fp, "%s\n%s\n%s\n", book_list[i].book_name, book_list[i].auth_name, book_list[i].publ_name);
		if (book_list[i].borrowed == 0)
			fprintf(fp, "NO\n");
		else
			fprintf(fp, "YES\n");
	}

	printf("출력 완료! \n");
	fclose(fp);            //파일 닫기

	return 0;
}
int compare(char *str1, char *str2) //비교함수
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
/* 포인터인 member_list 의 값을 바꿔야 하므로 더블 포인터 형태 */
int retrieve_member_info(MEMBER **member_list, int *total_num_member)
{
	FILE *fp = fopen("member_list.txt", "r");      //파일 불러오기 
	int total_member;
	int i;
	char str[20];

	if (fp == NULL)
	{
		printf("지정한 파일을 찾을 수 없습니다! \n");
		return -1;
	}

	/* 찾았다면 전체 회원의 개수를 읽어온다. */
	fscanf_s(fp, "%d", &total_member);
	(*total_num_member) = total_member;

	/* 기존의 member_list 데이터를 삭제 */
	free(*member_list);
	/* 그리고 다시 malloc 으로 재할당 한다. */
	(*member_list) = (MEMBER *)malloc(sizeof(MEMBER)*total_member); //파일에서 입력받은 책의 수 만큼 malloc 으로 member_list에 할당

	if (*member_list == NULL)
	{
		printf("\n ERROR \n");
		return -1;
	}
	for (i = 0; i<total_member; i++)
	{
		/* member_list[i]->member_name 이 아님에 유의!! */
		fscanf_s(fp, "%s", (*member_list)[i].member_name);
		fscanf_s(fp, "%s", (*member_list)[i].member_age);
		fscanf_s(fp, "%s", (*member_list)[i].member_sex);
		fscanf_s(fp, "%s", (*member_list)[i].member_phone);
		fscanf_s(fp, "%s", str);
	}
	if (compare(str, "YES"))               //대여했으면 YES
	{
		(*member_list)[i].borrow = 1;
	}
	else if (compare(str, "NO"))            //대여정보가 없으면 NO
	{
		(*member_list)[i].borrow = 0;
	}

	fclose(fp);
	return 0;

}
/* 포인터인 book_list 의 값을 바꿔야 하므로 더블 포인터 형태 */
int retrieve_book_info(BOOK **book_list, int *total_num_book)
{
	FILE *fp = fopen("book_list.txt", "r");
	int total_book;
	int i;
	char str[20];

	if (fp == NULL)
	{
		printf("지정한 파일을 찾을 수 없습니다! \n");
		return -1;
	}

	/* 찾았다면 전체 책의 개수를 읽어온다. */
	fscanf_s(fp, "%d", &total_book);
	(*total_num_book) = total_book;

	/* 기존의 book_list 데이터를 삭제 */
	free(*book_list);
	/* 그리고 다시 malloc 으로 재할당 한다. */
	(*book_list) = (BOOK *)malloc(sizeof(BOOK)*total_book);

	if (*book_list == NULL)
	{
		printf("\n ERROR \n");
		return -1;
	}
	for (i = 0; i<total_book; i++)
	{
		/* book_list[i]->book_name 이 아님에 유의!! */
		fscanf_s(fp, "%s", (*book_list)[i].book_name);
		fscanf_s(fp, "%s", (*book_list)[i].auth_name);
		fscanf_s(fp, "%s", (*book_list)[i].publ_name);
		fscanf_s(fp, "%s", str);

		if (compare(str, "YES"))               //대여했으면 YES
		{
			(*book_list)[i].borrowed = 1;
		}
		else if (compare(str, "NO"))            //대여정보가 없으면 NO
		{
			(*book_list)[i].borrowed = 0;
		}
	}

	fclose(fp);
	return 0;

}
/* 책을 추가 하는 함수*/
int register_book(BOOK *book_list, int *nth)
{


	printf("책의 이름 : ");
	scanf_s("%s", book_list[*nth].book_name);

	printf("책의 저자 : ");
	scanf_s("%s", book_list[*nth].auth_name);

	printf("책의 출판사 : ");
	scanf_s("%s", book_list[*nth].publ_name);

	book_list[*nth].borrowed = 0;      // 순서대로 정렬
	(*nth)++;



	return 0;

}
/* 책을 검색하는 함수 */
int search_book(BOOK *book_list, int total_num_book)
{


	system("cls");
	int user_input; /* 사용자의 입력을 받는다. */
	int i;
	char user_search[30]; //사용자가 입력한 검색어 

	printf("어느 것으로 검색 할 것인가요? \n");
	printf("1. 책 제목 검색 \n");
	printf("2. 지은이 검색 \n");
	printf("3. 출판사 검색 \n");
	scanf_s("%d", &user_input);

	printf("검색할 단어를 입력해주세요 : ");
	scanf_s("%s", user_search);

	printf("검색 결과 \n");

	if (user_input == 1)
	{
		/*

		i 가 0 부터 num_total_book 까지 가면서 각각의 책 제목을
		사용자가 입력한 검색어와 비교

		*/
		for (i = 0; i < total_num_book; i++)
		{
			if (compare(book_list[i].book_name, user_search))  //사용자가 입력한거랑 북리스트에 있는 책의 이름과 비교하는
			{
				printf("번호 : %d // 책 이름 : %s // 지은이 : %s // 출판사 : %s \n",
					i, book_list[i].book_name, book_list[i].auth_name, book_list[i].publ_name);
			}
		}

	}
	else if (user_input == 2)
	{
		/*

		i 가 0 부터 num_total_book 까지 가면서 각각의 지은이 이름을
		사용자가 입력한 검색어와 비교

		*/
		for (i = 0; i < total_num_book; i++)
		{
			if (compare(book_list[i].auth_name, user_search))
			{
				printf("번호 : %d // 책 이름 : %s // 지은이 : %s // 출판사 : %s \n",
					i, book_list[i].book_name, book_list[i].auth_name, book_list[i].publ_name);
			}
		}

	}
	else if (user_input == 3)
	{
		/*

		i 가 0 부터 num_total_book 까지 가면서 각각의 출판사를
		사용자가 입력한 검색어와 비교.

		*/
		for (i = 0; i < total_num_book; i++)
		{
			if (compare(book_list[i].publ_name, user_search))
			{
				printf("번호 : %d // 책 이름 : %s // 지은이 : %s // 출판사 : %s \n",
					i, book_list[i].book_name, book_list[i].auth_name, book_list[i].publ_name);
			}
		}
	}

	return 0;
}
int borrow_book(BOOK *book_list, MEMBER *member_list, int total_num_member, int total_num_borrow)
{
	system("cls");
	int user_input; /* 사용자의 입력을 받는다. */
	int i;
	char user_search[30]; //사용자가 입력한 검색어 



	printf("전화번호를 입력해주세요\n");
	printf("전화번호:");
	scanf_s("%s", &user_search);

	printf("검색 결과 \n");

	for (i = 0; i < total_num_member; i++)
	{
		if (compare(member_list[i].member_phone, user_search))  //사용자가 입력한거랑 북리스트에 있는 책의 이름과 비교하는
		{
			printf("이름 : %s\n나이 : %s\n성별 : %s\n전화번호: %s\n",
				member_list[i].member_name, member_list[i].member_age, member_list[i].member_sex, member_list[i].member_phone);
		}
	}
	printf("회원 정보가 맞으신가요?\n");
	printf("1.네");
	printf("2.아니오");
	scanf_s("%d", &user_input);

	if (user_input == 1)
	{
		/* 사용자로 부터 책번호를 받을 변수*/

		int book_num;

		printf("빌릴 책의 번호를 말해주세요 \n");
		printf("책 번호 : ");

		scanf_s("%d", &book_num);



		if (book_list[book_num].borrowed == 0)
		{
			printf("책이 성공적으로 대출되었습니다.\n");
			book_list[book_num].borrowed = 1;
		}
		else
		{
			printf("이미 대출중 입니다");
		}
	}
	else if (user_input == 2)
	{
		printf("다시 선택하세요\n");


	}
	/*   FILE *fp = fopen("borrow_list.txt", "w");

	int j;

	if(fp == NULL)                     //파일이 없으면
	{
	printf("출력 오류 ! \n");         //출력오류
	return -1;                     //에러발생
	}

	fprintf(fp, "%d\n", total_num_borrow);

	for(j = 0; j < total_num_borrow; i++)      //파일의 대여 현황을 불러온다.
	{
	fprintf(fp, "%d\n%s\n", member_list[i].member_phone, book_list[i].book_name);
	}

	printf("출력 완료! \n");
	fclose(fp);            //파일 닫기 */



	return 0;
}


int return_book(BOOK *book_list, MEMBER *member_list, int total_num_member, int total_num_book)
{
	system("cls");
	int user_input; /* 사용자의 입력을 받는다. */
	int i;
	char user_search[30]; //사용자가 입력한 검색어 
	char search[30];

	printf("전화번호를 입력해주세요\n");
	printf("전화번호:");
	scanf_s("%s", user_search);

	printf("검색 결과 \n");

	for (i = 0; i < total_num_member; i++)
	{
		if (compare(member_list[i].member_phone, user_search))  //사용자가 입력한거랑 북리스트에 있는 책의 이름과 비교하는
		{
			printf("이름 : %s\n나이 : %s\n성별 : %s\n전화번호: %s\n",
				member_list[i].member_name, member_list[i].member_age, member_list[i].member_sex, member_list[i].member_phone);
		}
	}

	/*
	printf("반납할 책의 내역입니다\n");
	scanf_s("%s",search);
	if(member_list[i].member_phone == book_list[i].book_name)
	{
	for(i = 0;i < total_num_book; i++)
	{
	if(compare(book_list[i].book_name, search))  //사용자가 입력한거랑 북리스트에 있는 책의 이름과 비교하는
	{
	printf("번호 : %d // 책 이름 : %s // 지은이 : %s // 출판사 : %s \n",
	i, book_list[i].book_name, book_list[i].auth_name, book_list[i].publ_name);
	}
	}
	} */
	/* 반납할 책의 번호 */
	int num_book;

	printf("반납할 책의 번호를 써주세요 \n");
	printf("책 번호 : ");

	scanf_s("%d", &num_book);

	if (book_list[num_book].borrowed == 0)
	{
		printf("이미 반납되어 있는 상태입니다\n");
	}
	else
	{
		book_list[num_book].borrowed = 0;
		printf("성공적으로 반납되었습니다\n");
	}

	return 0;
}

int member_cnt(void)
{
	FILE *fp = fopen("member_list.txt", "r");      //파일 읽기
	int total_num = 022;
	char s[2];

	if (fp == NULL)                           //파일이 아무거도 없으면 출력오류
	{
		printf("출력 오류 ! \n");
		return -1;      //-1은 에러발생을 의미
	}

	fgets(s, 2, fp);
	total_num = atoi(s);

	return total_num;
}



int seat_main(void)
{

//	srand(time(NULL));
	/* printf("********************************************************************************");
	printf("***************************도서 & 좌석 관리 프로그램****************************");
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
			printf("                  ┌------★원하시는 메뉴를 선택하세요★------┐\n");
			printf("                  │        [1]좌석 예약                      │\n");
			printf("                  │        [2]좌석 예약 취소                 │\n");
			printf("                  │        [3]프로그램 종료                  │\n");
			printf("                  └─────────────────────┘");
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
	printf("빈좌석 : □ \n자리 있음 : ■ \n\n");
	printf("1 2  3 4  5 6 \n");
	for (height = 1; height <= 6; height++)
	{
		for (width = 1; width <= 8; width++)
		{
			if (chain[height][width] == 0)
				printf("□");
			else if (chain[height][width] == 1)
				printf("■");
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

		printf("\n예약할 자리의 줄과 번호를 입력하고 엔터를 누르세요\n  예)1번째 줄 3번째 자리 : 1 3 단, 중간은 스페이스로 한번 띄우세요\n");
		scanf_s("%d %d", &height, &width);

		if (height>6 || width>6)
		{
			printf("\n입력오류입니다. 아무키나 눌러서 다시 입력하세요\n\n");
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
				printf("\n이미 예약된 좌석 입니다. 아무키나 눌러 다시 하세요\n\n");
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
			printf("\n이미 예약된 좌석 입니다. 아무키나 눌러 다시 하세요\n\n");
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
			printf("\n이미 예약된 좌석 입니다. 아무키나 눌러 다시 하세요\n\n");
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
			printf("\n이미 예약된 좌석 입니다. 아무키나 눌러 다시 하세요\n\n");
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
			printf("\n이미 예약된 좌석 입니다. 아무키나 눌러 다시 하세요\n\n");
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
		printf("\n예약을 취소할 자리의 줄과 번호를 입력하시고 엔터를 누르시오.\n");
		scanf_s("%d %d", &height, &width);

		if (height>6 || width>6)
		{
			printf("\n입력오류입니다. 아무키나 눌러서 다시 입력하세요\n\n");
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
				printf("\n예약이 취소 완료되었습니다. 아무키나 누르면 하위메뉴로 넘어갑니다\n\n");
				_getch();
			}
			else if (chain[height][width] == 0){
				printf("\n자리가 없는 곳입니다 아무키나 누르면 하위메뉴로 넘어갑니다.\n\n");
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
			printf("\n예약이 취소 완료되었습니다. 아무키나 누르면 하위메뉴로 넘어갑니다\n\n");
			_getch();
		}
		else if (chain[height][width] == 0){
			printf("\n자리가 없는 곳입니다. 아무키나 누르면 하위메뉴로 넘어갑니다.\n\n");
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
			printf("\n예약이 취소 완료되었습니다. 아무키나 누르면 하위메뉴로 넘어갑니다\n\n");
			_getch();
		}
		else if (chain[height][width] == 0){
			printf("\n자리가 없는 곳입니다. 아무키나 누르면 하위메뉴로 넘어갑니다.\n\n");
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
			printf("\n예약이 취소 완료되었습니다. 아무키나 누르면 하위메뉴로 넘어갑니다\n\n");
			_getch();
		}
		else if (chain[height][width] == 0){
			printf("\n자리가 없는 곳입니다. 아무키나 누르면 하위메뉴로 넘어갑니다.\n\n");
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
			printf("\n예약이 취소 완료되었습니다. 아무키나 누르면 하위메뉴로 넘어갑니다\n\n");
			_getch();
		}
		else if (chain[height][width] == 0){
			printf("\n자리가 없는 곳입니다. 아무키나 누르면 하위메뉴로 넘어갑니다.\n\n");
			_getch();
		}
	}
	system("cls");
}

void END()
{
	exit(1);
}