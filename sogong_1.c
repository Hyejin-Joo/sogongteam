#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<conio.h>

#define PASSWORD_SIZE 4
#define TRUE 1
#define FALSE 0

typedef struct contact  // �ּҷ� ����
{
  char lastName[5];  	//��
  char firstName[15];	//(�� ����)�̸�
  char position[20];	//��å
  char department[20];	//�μ�
  char company[20];		//ȸ���
  char address[60];		//�ּ�
  char homePhone[11];	//��ȭ��ȣ
  char faxNumber[11];	//�ѽ���ȣ
  char mobilePhone[12];	//�޴���ȭ��ȣ
  char email[40];		//E-mail
  char homepage[50];	//Ȩ������
  char CheckedNum;		//������ ��ȣ
} Contact;

int loginState = FALSE;

typedef struct node
{
  Contact sContact;
  struct node *next;
} Node;

Node *head;
Node *tail;

FILE* fp = NULL;
char buff[PASSWORD_SIZE+1];
char inputPassword[PASSWORD_SIZE+1];

int isEmpty();
Node *isFull();
int login();
int isValidPassword();
void linkedListInit();
void viewAllContacts();
void printContactList();
void addContact();
void modifyAddress();
void deleteAddress();
void findAddress();
void changePassword();
void logout();
int printMainMenu();
void changePassword();

int isEmpty()
{
	if( head->next == tail ) 
		return TRUE;
	else return FALSE;
}

Node *isFull()
{
	Node *p = (Node *)malloc(sizeof(Node));
	if(p == NULL)
		return NULL;
	else return p;
}

int login()
{	
	printf("������� ��й�ȣ�� �Է��ϼ���: ");
	gets(inputPassword);

	while( isValidPassword() == FALSE ) {
		printf("��й�ȣ�� �� �ڸ��� �Է����ּ���\n\n");
		printf("������� ��й�ȣ�� �Է��ϼ���: ");
		gets(inputPassword); }

	if( strcmp(buff,inputPassword) != 0 ) {
		printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�.\n\n");
		return FALSE; }
	else return TRUE;

}

int isValidPassword()
{
	int isValid;
	
	if(strlen(inputPassword) != PASSWORD_SIZE)
		isValid = FALSE;
	else isValid = TRUE;

	return isValid;
}

void linkedListInit()
{
	head = (Node *)malloc(sizeof(Node));
	tail = (Node *)malloc(sizeof(Node));

	head->next = tail;
	tail->next = tail;
}

void viewAllContacts()
{
	Node *p;
	int k=1;

	p = head -> next;
	
	system("cls");
	if( isEmpty() == TRUE )
	{
		printf("�� ������ �������� �ʽ��ϴ�. \n");
	}
	else
	{
		printf("----------------------------------\n");
		printf("��ȣ ��\t�̸�\t�޴���ȭ��ȣ\n");
		while( p!=tail )
		{
			printf(" %d %4s %4s %14s\n", k++, p->sContact.lastName, p->sContact.firstName, p->sContact.mobilePhone);
			p = p->next;
		}
		printf("----------------------------------\n");
	}
	
	getch();
}

void addContact()
{
	Node *t;
	Node *searchNode;
	Node *searchPreNode;
	Contact pContact;
	char temp;
	
	searchNode = searchPreNode = head->next;
	t = isFull();

	if( t == NULL ) {
		printf("�� �̻� ������ ������ �����ϴ�.\n");
		system("cls");
	}
	
	system("cls"); ///
	printf("�ּҷ� �߰�\n");
	printf("----------------------------------\n");
	printf("1. �� : "); gets(pContact.lastName);
	printf("2. (�� ����) �̸� : "); gets(pContact.firstName);
	printf("3. ��å : "); gets(pContact.position);
	printf("4. �μ� : "); gets(pContact.department);
	printf("5. ȸ��� : "); gets(pContact.company);
	printf("6. �ּ� : "); gets(pContact.address);
	printf("7. ��ȭ��ȣ : "); gets(pContact.homePhone);
	printf("8. �ѽ���ȣ : "); gets(pContact.faxNumber);
	printf("9. �޴���ȭ��ȣ : "); gets(pContact.mobilePhone);
	printf("10. E-mail : "); gets(pContact.email);
	printf("11. Ȩ������ : "); gets(pContact.homepage);
	printf("----------------------------------\n\n");
	
	t->sContact = pContact;
	
	printf("������ ����Ͻðڽ��ϱ�? (y/n) : ");
	temp = getch();
	
	if(temp == 'y' || temp == 'Y')
	{
		if( isEmpty() == TRUE )
		{
			head->next = t;
			t->next = tail; //�����Ͱ� ���� ���, head�� tail ���̿� ���� ����
		}
		else
		{
			while( searchNode != tail ) {
				if((strcmp(searchNode->sContact.lastName,t->sContact.lastName)<0) ||
					((strcmp(searchNode->sContact.lastName,t->sContact.lastName)==0) && (strcmp(searchNode->sContact.firstName,t->sContact.firstName)<0)))
				{	searchPreNode = searchNode;
					searchNode = searchNode->next;}
				else break;}
			if( searchNode == head->next ) {	// �Էµ� ������ ���� ó���� ���ԵǾ�� �� ���
				t->next = head->next;
				head->next = t;
			}
			else if( searchNode == tail ) {	// �Էµ� ������ ���� �������� ���ԵǾ�� �� ���
				searchPreNode->next = t;
				t->next = tail;
			}
			else {							// �Էµ� ������ �߰��� ���ԵǾ�� �� ���
				t->next = searchNode;
				searchPreNode->next = t;
			}
		}
	
		system("cls");
		printf("����� ���������� �Ϸ�Ǿ����ϴ�.\n");
	}
	else
	{
		free(t);
		system("cls");
		printf("����� ����Ͽ����ϴ�.\n");
	}
	Sleep(1000);	//1��(1000) ������	
}
/*
void modifyAddress(){
	Node *t;
	Contact *pContact;
	char temp;
	char lastName[5];	//��
	char firstName[15];	//(�� ����)�̸�
	char position[20];		//��å
	char department[20];	//�μ�
	char company[20];	//ȸ���
	char homeAddress[60];	//�ּ�
	char homePhone[11];	//��ȭ��ȣ
	char faxNumber[11];	//�ѽ���ȣ
	char mobilePhone[12];	//�޴���ȭ��ȣ
	char email[40];		//E-mail
	char homepage[50];	//Ȩ������
	char CheckedNum;
	
	t = isFull()
	if( t == NULL ) {
		printf("�� �̻� ������ ������ �����ϴ�.\n");
		system("cls");
	}
	
	pContact = (Contact *)malloc(sizeof(Contact));
	char SearchName;


	t = (node *)malloc(sizeof(node));
	pContact = (address *)malloc(sizeof(address));
	
	system("cls");
	
	searchpersonMenu();	//�ѱ����̸����

	printf("��µ� �׸� �� �����ϰ��� �ϴ� �̸��� �Է��ϼ���\n");
	scanf//�̸� �ޱ�
	//���� �̸��� ���Ͽ� 

	printf("� �׸��� �����ϰڽ��ϱ�\n");
	scanf("%s",CheckedNum);
	switch(CheckedNum) {
		case '1':
		printf("1. �� : "); gets("%s", pContact->lastName); break;
		case '2':
		printf("2. (�� ����) �̸� : "); gets("%s", pContact->firstName); break;
		case '3':
		printf("3. ��å : "); gets("%s", pContact->position); break;
		case '4':
		printf("4. �μ� : "); gets("%s", pContact->department); break;
		case '5':
		printf("5. ȸ��� : "); gets("%s", pContact->company); break;
		case '6':
		printf("6. �ּ� : "); gets("%s", pContact->homeAddress); break;
		case '7':
		printf("7. ��ȭ��ȣ : "); gets("%s", pContact->homePhone); break;
		case '8':
		printf("8. �ѽ���ȣ : "); gets("%s", pContact->faxNumber); break;
		case '9':
		printf("9. �޴���ȭ��ȣ : "); gets("%s", pContact->mobilePhone); break;
		case '10':
		printf("10. E-mail : "); gets("%s", pContact->email); break;
		case '11':
		printf("11. Ȩ������ : "); gets("%s", pContact->homepage); break;
	}

	printf("������ �����Ͻðڽ��ϱ�? (y/n) : "); //�����ؾ� �� 
	temp = getch();
	
	if(temp == 'y' || temp == 'Y')
	{
		if(head->next == tail)
		{
			t->next = tail; //�����Ͱ� ���� ���, head�� tail ���̿� ���� ����
		}
		else
		{
			t->next = head->next;
		}
		head->next = t;
		system("cls");
		printf("������ ���������� �Ϸ�Ǿ����ϴ�.\n");
	}
	else
	{
		free(t);
		free(pContact);
		system("cls");
		printf("������ ����Ͽ����ϴ�.\n");
	}
	Sleep(1000);	//1��(1000) ������	
}

void deleteAddress(){
	node *t;
	address *pContact;
	char temp;
	char lastName[5];	//��
	char firstName[15];	//(�� ����)�̸�
	char position[20];		//��å
	char department[20];	//�μ�
	char company[20];	//ȸ���
	char homeAddress[60];	//�ּ�
	char homePhone[11];	//��ȭ��ȣ
	char faxNumber[11];	//�ѽ���ȣ
	char mobilePhone[12];	//�޴���ȭ��ȣ
	char email[40];		//E-mail
	char homepage[50];	//Ȩ������
	char CheckedNum;

	t = (node *)malloc(sizeof(node));
	pContact = (address *)malloc(sizeof(address));
	
	system("cls");
	
	t->sAddress = pContact;
	
	printf("����ó �ϳ��� �����Ϸ��� 1��, ��ü �ּҷ��� �����Ϸ��� 2�� �����ּ���");
	scanf("%s",CheckedNum);
	switch(CheckedNum) {
		case '1':
			searchpersonMenu();//�ѱ����̸����
			break;
		case '2':
			//��� ����
			break;
	}
	printf("������ �����Ͻðڽ��ϱ�? (y/n) : ");
	temp = getch();
	
	if(temp == 'y' || temp == 'Y') //�����ؾ� �� 
	{
		if(head->next == tail)
		{
			t->next = tail; //�����Ͱ� ���� ���, head�� tail ���̿� ���� ����
		}
		else
		{
			t->next = head->next;
		}
		head->next = t;
		system("cls");
		printf("������ ���������� �Ϸ�Ǿ����ϴ�.\n");
	}
	else
	{
		free(t);
		free(pContact);
		system("cls");
		printf("������ ����Ͽ����ϴ�.\n");
	}
	Sleep(1000);	//1��(1000) ������	
}
void findAddress(){

	searchpersonMenu();
	
	scanf //ã�� �̸� �ޱ� 
	printContactList();	//����Ʈ ���
}

void changePassword(){;}
void Logout(){;}

void searchpersonMenu(){

char *SearchName;
SearchName = (char*)malloc(sizeof(char)*2);
1. �� ���� �Է¹���
2. �ּҷϿ� ����Ǿ� �ִ� ����� ����
3. �Է¹��� ���ڰ� ���Ե� ��� ��� ���
return ���;

	����ڰ� � ����� ���� ������ �ߴ��� ���θ� �˱� ���� ���� ��5���� ������ ��Enter���� �ƴ�. 
	ȭ�鿡 �˻��ϰ��� �ϴ� �̸��� �� ���ڸ� �Է��϶�� �ϱ淡 �������� ���� ��Enter���� �ƴ�. 
	ȭ�鿡�� �������� ������ �̸��� ���� ��ϵ��� ���´�.

printf("�����ϰ��� �ϴ� �̸� �� �� ���ڸ� �Է��ϼ���\n");
	scanf("%s",SearchName);
	if (SearchName==*lastName){}
	if (SearchName==*firstName){}
	//���


}*/

void changePassword()
{
	char input1[PASSWORD_SIZE+1], input2[PASSWORD_SIZE+1];

	printf("���� ��й�ȣ�� �Է��ϼ��� : ");
	gets(inputPassword);

	while( isValidPassword() == FALSE ) {
		printf("��й�ȣ�� �� �ڸ��� �Է����ּ���\n");
		printf("������� ��й�ȣ�� �Է��ϼ���: ");
		gets(inputPassword); }

	if( strcmp(buff,inputPassword) != 0 ) {
		printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�.\n");
		Sleep(1000);
		return ;}

	printf("1. ��й�ȣ �Է�(4�ڸ�) : ");
	gets(input1);
	printf("2. ��й�ȣ Ȯ��(4�ڸ�) : ");
	gets(input2);

	if(strcmp(input1,input2) != 0) {
		printf("�Է��Ͻ� �� ��й�ȣ�� ��ġ���� �ʽ��ϴ�.\n");
		Sleep(1000);
		return ;}
	else {
		printf("%s�� ��й�ȣ�� �����մϴ�.\n",input1);
		fseek(fp,0,SEEK_SET);
		fputs(input1, fp);
		Sleep(1000);
	}
}

void logout()
{
	system("cls");
	printf("\n�α׾ƿ� �Ǿ����ϴ�.\n����� �ּż� �����մϴ�.");
	Sleep(2000);
	system("cls");
}

int printMainMenu()
{
	int menuChoice;

	system("cls");
	printf("���� �޴�\n");
	printf("----------------------------------\n");
	printf("1. �ּҷ� ��ü����\n");
	printf("2. �ּҷ� �߰�\n");
	printf("3. �ּҷ� ����\n");
	printf("4. �ּҷ� ����\n");
	printf("5. �ּҷ� �˻�\n");
	printf("6. ��й�ȣ ����\n");
	printf("7. �α׾ƿ�\n");
	printf("8. ����\n");
	printf("----------------------------------\n\n");
	printf("��ȣ�� �Է��ϼ���(1~8) : ");
	scanf("%d", &menuChoice);
	fflush(stdin); //���� ����
	return menuChoice;
}

int main(void)
{
	int menuChoice = 0;

	fp = fopen("address_book.txt","r+");
	if(fp == NULL) {
		printf("��ġ�ϴ� �ּҷ��� �����ϴ�.\n");
		return ;}
			
label :
	fgets(buff, sizeof(int)*PASSWORD_SIZE, fp);

	printf("�ּҷ� �ý��ۿ� ���Ű� ȯ���մϴ�.\n\n");

	do { loginState = login(); }while( loginState == FALSE );

	printf("�α��ο� �����Ͽ����ϴ�!\n\n");
	Sleep(1000);

	linkedListInit();	//���Ḯ��Ʈ �ʱ�ȭ
		
	while( loginState == TRUE && menuChoice != 8 ) 
	{
		menuChoice = printMainMenu();
		if(!(menuChoice >=1 && menuChoice <=8))
		{
			continue;
		}
		
		switch(menuChoice) 
		{
		case 1: 
		  viewAllContacts(); //�ּҷ� ��ü����
		  break;
		case 2: 
		  addContact(); //�ּҷ� �߰�
		  break;
	/*	case 3: 
		  modifyAddress(); //�ּҷ� ����
		  break;
		case 4: 
		  deleteAddress(); //�ּҷ� ����
		  break;
		case 5: 
		  findAddress(); //�ּҷ� �˻�
		  break;*/
		case 6: 
		  changePassword(); //��й�ȣ ����
		  break;
		case 7: 
		  logout(); //�α׾ƿ�
		  goto label;
		  break;
		case 8: 
		  exit(1); //����
		  break;
		default: printf("�߸� �Է��ϼ̽��ϴ�.\n");
		}
	}

	fclose(fp);
	return 0;
}


