#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define HEADER  "                             **ѧ���б�**\n"
#define HEADER0 "     -----------------------------------------------------------  \n"
#define HEADER1 "     |     ѧ ��     |    ��  ��    | �Ա� |    �� ϵ �� ��    |\n"
#define FORMAT1 "     |%-15s|    %-10s|  %-4s|    %-15s|\n"
#define HEADER2 "     |     ѧ ��     |   �� ��    |\n"
#define FORMAT2 "     |%-15s|%-10s  |\n"
#define HEADER3 "     |  �� ͥ ס ַ  |"
#define FORMAT3 "    %-35s |\n"
#define HEADER4 "     | ����|��ѧ|Ӣ��|ƽ����|����1|\n"
#define FORMAT4 "     | %-4d|%-4d|%-4d|%-6.2lf| %-4d|\n"
#define HEADER5 "     | ˼Ʒ|����|ʦ��|�ۺϷ�|����2|\n"
#define FORMAT5 "     | %-4d|%-4d|%-4d|%-6.2lf| %-4d|\n"


#define DATA1   p->num,p->name,p->sex,p->phone
#define DATA2   p->num,p->name
#define DATA3   p->address
#define DATA4   p->chinese,p->math,p->english,p->average,p->rank_main
#define DATA5   p->pinde,p->huping,p->teacher,p->score_all,p->rank_all

#define END     "     -----------------------------------------------------------  \n"
//------------------------------- ����ȫ�ֱ���------------------------------------
int check_result = 0;		//��¼������ı���
//------------------------------- ����ѧ�����ݽṹ��------------------------------------
typedef struct Stuinfo {
	char num[15];			//ѧ��
	char name[10];		//ѧ������
	char sex[4];		//�Ա�
	char address[35];	//��ͥסַ
	char phone[14];		//�绰
	int chinese, math, english, pinde;	//�����Ӣ��˼��Ʒ�³ɼ�
	int rank_main, rank_all;			//����Ӣ�������Σ��ۺϲ�������
	int huping, teacher;				//�����֣���ʦ����
	double average, score_all;			//����ƽ���֣��ۺ��ܷ�
	// ÿ��ѧ������ϢΪ��ѧ�š��������Ա𡢼�ͥסַ����ϵ�绰�����ġ���ѧ���������ŵ��Ƴɼ���
	// ����ƽ���ɼ����������Ρ�ͬѧ�����֡�Ʒ�³ɼ����ον�ʦ���֡��ۺϲ����ܷ֡��ۺϲ������Ρ�
	// ����ƽ���ɼ���ͬѧ�����֡�Ʒ�³ɼ����ον�ʦ���ֱַ�ռ�ۺϲ����ֵܷ�60% ��10% ��10% ��20% ��
	struct Stuinfo* next;
}Stu;
//------------------------------- ��������------------------------------------
void color(short x);
void toxy(int x, int y);
void Wrong(int a, int b);
void main_menu(Stu* l, Stu* p, Stu* r);
void teacher_account(Stu* l, Stu* p, Stu* r);
void stu_menu(Stu* l);
void about_us();
int pswd_check();
char mod_pswd();
void login_teacher(Stu* l, Stu* p, Stu* r);
void pswd_create();
void teacher_main_menu(Stu* l, Stu* p, Stu* r);
void Add_info(Stu* l);
void Add_score(Stu* l);
void Disp(Stu* l, int i);
void stringinput(char* t, int lens, char* notice);
void printinfo(Stu* pp);
void printscore(Stu* pp);
void Save(Stu* l);
void Modify_info(Stu* l);
void Modify_score(Stu* l);
void Sort(Stu* l, int sel);
void Del(Stu* l);
void Stu_score_feedback(Stu* p);
void look_feedback();
int main();

void color(short x)
{
	if (x >= 0 && x <= 15)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	}
}

void toxy(int x, int y)      //������ƶ���X,Y���괦
{
	COORD pos = { x , y };
	HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Out, pos);
}

void Wrong(int a, int b) /*�������������Ϣ*/
{
	system("cls");
	printf("=========================================\n");
	printf("\n\n\n��ѡ��%d-%d�е�ѡ��֮һ���벻Ҫ��������ѡ�\n\n\n", a, b);
	printf("\n=========================================\n\n\n\n");
}

void pswd_create()
{
	FILE* fp;
	if ((fp = fopen("pswd_teacher", "rb")) == NULL) //��д��ʽ�򿪽�ʦ�����ļ�               /*������ļ�������*/
	{
		fp = fopen("pswd_teacher", "wb+");			//���û���ҵ����½�һ��
		if (fp == NULL)
		{
			printf("�޷������ļ���\n");
			exit(0);
		}
		fputs("123456", fp);		//���ó�ʼ����123456
	}
	fclose(fp);
}

void Save(Stu* l)
{
	FILE* fp;
	Stu* p;
	int count = 0;
	fp = fopen("student_info.dat", "wb");/*��ֻд��ʽ�򿪶������ļ�*/
	if (fp == NULL) /*���ļ�ʧ��*/
	{
		printf("\n=====>�򿪴���\n");
		getchar();
		return;
	}
	p = l->next;

	while (p)
	{
		if (fwrite(p, sizeof(Stu), 1, fp) == 1)/*ÿ��дһ����¼��һ���ڵ���Ϣ���ļ�*/
		{
			p = p->next;
			count++;
		}
		else
		{
			break;
		}
	}
	if (count > 0)
	{

	}
	else
	{
		system("cls");
		printf("û����Ϣ�����棡\n");
		getchar();
	}
	fclose(fp); /*�رմ��ļ�*/
}
/*************************************************************
���ã����ڶ�λ�����з���Ҫ��Ľڵ㣬������ָ��ýڵ��ָ��
������find_data��ʾҪ���ҵ����ݣ�type_find��ʾ���ҷ�ʽ
	  �ڵ�����l�в���;
**************************************************************/
Stu* Locate(Stu* l, char find_data[], int type_find)
{
	Stu* r;
	if (type_find == 0) /*����Ų�ѯ*/
	{
		r = l->next;
		while (r)
		{
			if (strcmp(r->num, find_data) == 0) /*���ҵ�find_dataֵ�ı��*/
				return r;
			r = r->next;
		}
	}
	else if (type_find == 1)  /*��������ѯ*/
	{
		r = l->next;
		while (r)
		{
			if (strcmp(r->name, find_data) == 0)    /*���ҵ�find_dataֵ�Ľ�ʦ����*/
				return r;
			r = r->next;
		}
	}
	return 0; /*��δ�ҵ�������һ����ָ��*/
}

void Sort(Stu* l, int sel)
{
	Stu* temp1;
	temp1 = l->next; /*l�洢���ǵ�������ͷ����ָ�룬��ͷ���û�д洢��ʦ��Ϣ��ָ����ָ��ĺ�̽����н�ʦ��Ϣ*/
	if (!temp1)  /*p==NULL,NUll��stdlib�ж���Ϊ0*/
	{
		printf("\n\t\t\t\t\t\t=====>�ļ���û�����ݣ�\n");
		getchar();
		system("pause");
		system("cls");
		return;
	}
	Stu* p, * pre, * tail, * temp;
	tail = NULL;
	pre = l;
	int i = 1;
	p = (Stu*)malloc(sizeof(Stu));
	while ((l->next->next) != tail)
	{
		p = l->next;
		pre = l;
		while (p->next != tail)
		{
			if (sel == 0)
			{
				if (strcmp(p->next->num, p->num) < 0)
				{
					pre->next = p->next;
					temp = p->next->next;
					p->next->next = p;
					p->next = temp;
					p = pre->next;
				}
			}
			else if (sel == 1)
			{
				if ((p->average) < (p->next->average))
				{
					pre->next = p->next;
					temp = p->next->next;
					p->next->next = p;
					p->next = temp;
					p = pre->next;
				}
			}
			else if (sel == 2)
			{
				if ((p->score_all) < (p->next->score_all))
				{
					pre->next = p->next;
					temp = p->next->next;
					p->next->next = p;
					p->next = temp;
					p = pre->next;
				}
			}

			p = p->next;
			pre = pre->next;
		}
		tail = p;
	}
	p = l->next;           /*���ź����ͷָ�븳��p��׼����д����*/
	while (p != NULL)  /*��p��Ϊ��ʱ���������в���*/
	{
		if (sel == 1)
			p->rank_main = i;
		else if (sel == 2)
			p->rank_all = i;
		i++;       /*������*/
		p = p->next;   /*ָ�����*/

	}
	Save(l);
	system("cls");
	return;
}

//----------------------------------------��ҳ��----------------------------------------
void main_menu(Stu* l, Stu* p, Stu* r) {
	char option;
	while (1) {
		color(11);
		toxy(35, 12);
		printf("==================================================");
		toxy(52, 14);
		printf("ѧ���ۺϲ���ϵͳ");
		toxy(48, 18);
		printf("1.��ʦ�˻�");
		printf("\t2.ѧ���˻�");
		toxy(48, 20);
		printf("3.��������");
		printf("\t0.�˳�ϵͳ");
		toxy(52, 22);
		printf("�������Ӧ���: ");
		toxy(35, 24);
		printf("==================================================");
		p = r;
		toxy(60, 25);
		scanf("%c", &option);
		switch (option) {
		case '1':system("cls"); teacher_account(l, p, r); system("cls"); break;
		case '2':system("cls"); stu_menu(l); system("cls");  break;
		case '3':system("cls"); about_us(); system("pause"); getchar(); system("cls"); break;
		case '0':exit(0);
		default:Wrong(0, 3); system("pause"); getchar(); system("cls"); break;
		}
	}
}
//----------------------------------------��ʦ�����˵�----------------------------------------
void teacher_account(Stu* l, Stu* p, Stu* r) {
	pswd_create();			//ÿ�ν����ȷ��һ���Ƿ���������ļ�		
	int i;
	while (1) {
		color(11);
		toxy(35, 12);
		printf("==================================================");
		toxy(44, 14);
		printf("��ӭʹ��ѧ���ۺϲ���ϵͳ(��ʦ��)");
		toxy(48, 18);
		printf("1.��	¼");
		printf("\t2.�޸�����");
		toxy(48, 20);
		printf("3.�������˵�");
		printf("\t4.�˳�ϵͳ");
		toxy(52, 22);
		printf("�������Ӧ��ţ�");
		toxy(35, 24);
		printf("==================================================");
		toxy(60, 25);
		scanf("%d", &i);
		switch (i) {
		case 1:system("cls"); login_teacher(l, p, r); break;
		case 2:system("cls"); mod_pswd(); break;
		case 3:system("cls"); getchar(); return;
		case 4:exit(0);
		default:Wrong(1, 4); system("pause"); system("cls");
		}

	}
}
//----------------------------------------��ʦ�˵�¼----------------------------------------
void login_teacher(Stu* l, Stu* p, Stu* r) {
	char a[16];				//��ʱ�������������	
	char a1[16] = { "123456" }; //����Ĭ�����������
	FILE* fp;
	fp = fopen("pswd_teacher", "r"); //�򿪴���������ļ�
	fgets(a, 16, fp);	 //��ȡ���뵽����a��
	toxy(35, 12);
	printf("==================================================");
	toxy(57, 14);
	printf("��ʦ��¼����");
	if (strcmp(a, a1) == 0) {	 //�ж��Ƿ�Ϊ��ʼ����
		toxy(51, 15);
		printf("������ʹ�ó�ʼ���룬�뼰ʱ�������룡");
	}
	toxy(54, 16);
	printf("���������룺");
	pswd_check();
	if (check_result == 1) {
		toxy(48, 22);
		printf("��¼�ɹ������������ʦ��");
		toxy(35, 24);
		printf("==================================================");
		toxy(54, 26);
		system("pause");
		system("cls");
		teacher_main_menu(l, p, r);
	}
	else if (check_result == 0)
	{
		return;
	}
	fclose(fp);
}

int pswd_check() {		//���������ȷ��
	char a[16], b[16];
	FILE* fp;
	fp = fopen("pswd_teacher", "r"); //�򿪴���������ļ�
	fgets(b, 16, fp);	 //��ȡ���뵽����a��
	scanf("%s", &a);
	int i = 3;
	while (1) {
		if (strcmp(a, b) == 0) {
			check_result = 1;//���ͨ��
			fclose(fp);
			return (check_result);
		}
		else {
			toxy(41, 18);
			printf("���벻��ȷ�����������룬������%d�λ���!\n", i);
			toxy(54, 20);
			printf("���������룺");
			i--;
			scanf("%s", &a);
		}
		if (i == 0) {
			toxy(45, 22);
			printf("���������3�Σ���������������\n");
			toxy(35, 24);
			printf("==================================================");
			fclose(fp);
			toxy(54, 26);
			system("pause");
			system("cls");
			check_result = 0;
			return (check_result);
		}
	}
}

char mod_pswd() {	//�޸�����
	char b[16];		//��ʱ����������ı���
	FILE* fp;
	toxy(35, 12);
	printf("==================================================");
	toxy(53, 14);
	printf("��ʦ�������޸�");
	toxy(53, 16);
	printf("����������룺");
	pswd_check();
	if (check_result == 0)
		return;
	toxy(53, 22);
	printf("�����������룺");
	fp = fopen("pswd_teacher", "w");
	scanf("%s", &b);
	fputs(b, fp);
	fclose(fp);
	toxy(53, 24);
	printf("��ȷ�������룺");
	pswd_check();
	if (check_result == 1) {
		toxy(53, 26);
		printf("�޸�����ɹ���");
		toxy(35, 28);
		printf("==================================================");
		toxy(54, 30);
		system("pause");
		system("cls");
		return;
	}
}


void Disp(Stu* l, int i)  /*��ʾ������l�д洢�Ľ�ʦ��¼������Ϊteacher�ṹ�ж��������*/
{
	Stu* p;
	p = l->next; /*l�洢���ǵ�������ͷ����ָ�룬��ͷ���û�д洢��ʦ��Ϣ��ָ����ָ��ĺ�̽����н�ʦ��Ϣ*/

	if (!p)  /*p==NULL,NUll��stdlib�ж���Ϊ0*/
	{
		system("cls");
		toxy(49, 12);
		printf("=====>�ļ���û�����ݣ�\n");
		getchar();
		toxy(54, 14);
		system("pause");
		return;
	}

	printf("\n\n");
	toxy(27, 4);
	printf(HEADER);
	toxy(27, 5);
	printf(HEADER0);
	while (p)    /*������������д洢�Ľ�ʦ��Ϣ*/
	{
		if (i == 0)
			printinfo(p);
		else if (i == 1)
			printscore(p);
		else if (i == 2)
		{
			printf("\t\t\t   ");
			printf(HEADER2);
			printf("\t\t\t   ");
			printf(FORMAT2, DATA2);
			printf("\t\t\t   ");
			printf(HEADER4);
			printf("\t\t\t   ");
			printf(FORMAT4, DATA4);
		}
		else if (i == 3)
		{
			printf("\t\t\t   ");
			printf(HEADER2);
			printf("\t\t\t   ");
			printf(FORMAT2, DATA2);
			printf("\t\t\t   ");
			printf(HEADER5);
			printf("\t\t\t   ");
			printf(FORMAT5, DATA5);
		}
		else if (i == 4)
		{
			printf("\t\t\t   ");
			printf(HEADER1);
			printf("\t\t\t   ");
			printf(FORMAT1, DATA1);
			printf("\t\t\t   ");
			printf(HEADER3);
			printf("\t\t\t   ");
			printf(FORMAT3, DATA3);
			printf("\t\t\t   ");
			printf(HEADER4);
			printf("\t\t\t   ");
			printf(FORMAT4, DATA4);
			printf("\t\t\t   ");
			printf(HEADER5);
			printf("\t\t\t   ");
			printf(FORMAT5, DATA5);
		}
		p = p->next;  /*�ƶ�ֱ��һ�����*/
		printf("\t\t\t   ");
		printf(END);
	}
	getchar();
}

void printinfo(Stu* pp) /*��ʽ�������������*/
{
	Stu* p;
	p = pp;
	printf("\t\t\t   ");
	printf(HEADER1);
	printf("\t\t\t   ");
	printf(FORMAT1, DATA1);
	printf("\t\t\t   ");
	printf(HEADER3);
	printf(FORMAT3, DATA3);
}

void printscore(Stu* pp) /*��ʽ�������������*/
{
	Stu* p;
	p = pp;
	printf(HEADER2);
	printf(FORMAT2, DATA2);
	printf(HEADER4);
	printf(FORMAT4, DATA4);
	printf(HEADER5);
	printf(FORMAT5, DATA5);
}

void stringinput(char* t, int lens, char* notice)
{
	char n[255];
	do {
		printf(notice);  /*��ʾ��ʾ��Ϣ*/
		scanf("%s", n);  /*�����ַ���*/
		if (strlen(n) > lens)printf("\n exceed the required length! \n"); /*���г���У�飬����lensֵ��������*/
	} while (strlen(n) > lens);
	strcpy(t, n); /*��������ַ����������ַ���t��*/
}

void Add_info(Stu* l)
{
	Stu* p, * r, * s;  /*ʵ����Ӳ�������ʱ�Ľṹ��ָ�����*/
	char ch, flag = 0, num[15];
	r = l;
	s = l->next;
	system("cls");
	Disp(l, 0); /*�ȴ�ӡ�����еĽ�ʦ��Ϣ*/
	while (r->next != NULL)
		r = r->next; /*��ָ��������������ĩβ��׼����Ӽ�¼*/
	while (1) /*һ�ο����������¼��ֱ��������Ϊ0�ļ�¼�����Ӳ���*/
	{

		while (1) /*�����ţ���֤�ñ��û�б�ʹ�ã���������Ϊ0�����˳���Ӽ�¼����*/
		{
			stringinput(num, 15, "������\nѧ�ţ�"); /*��ʽ�������Ų�����*/
			flag = 0;
			if (strcmp(num, "0") == 0) /*����Ϊ0�����˳���Ӳ���������������*/
			{
				Save(l);
				return;
			}
			s = l->next;
			while (s) /*��ѯ�ñ���Ƿ��Ѿ����ڣ���������Ҫ����������һ��δ��ռ�õı��*/
			{
				if (strcmp(s->num, num) == 0)
				{
					flag = 1;
					break;
				}
				s = s->next;
			}

			if (flag == 1) /*��ʾ�û��Ƿ���������*/

			{
				getchar();
				printf("=====>ѧ�� %s ����Ϣ�ѱ�¼�룬Ҫ��Ҫ��һ���أ�(y/n):", num);
				scanf("%c", &ch);
				if (ch == 'y' || ch == 'Y')
					continue;
				else
					return;
			}
			else
			{
				break;
			}
		}

		p = (Stu*)malloc(sizeof(Stu)); /*�����ڴ�ռ�*/
		if (!p)
		{
			printf("\n �ڴ�����ʧ�ܣ��볢�Ի�ȡ����Ȩ�ޣ� "); /*��û�����뵽����ӡ��ʾ��Ϣ*/
			return;             /*����������*/
		}
		strcpy(p->num, num); /*���ַ���num������p->data.num��*/
		stringinput(p->name, 10, "������");
		printf("�Ա�");
		scanf("%s", p->sex);
		printf("��ͥסַ��");
		scanf("%s", p->address);
		printf("�绰��");
		scanf("%s", p->phone);
		p->chinese = p->math = p->english = p->average = p->pinde = p->rank_all = p->rank_main = p->score_all = p->teacher = p->huping = -1;

		p->next = NULL; /*�������������β�����*/
		r->next = p;  /*���½��Ľ���������β����*/
		r = p;
	}

	return;
}

void Modify_info(Stu* l)
{
	Stu* p, * t;  /*ʵ����Ӳ�������ʱ�Ľṹ��ָ�����*/
	char find_data[20];
	char ch[30] = "\0", chy;
temp:
	if (!l->next)
	{
		system("cls");
		printf("\n\t\t\t\t\t\t=====>�ļ���û�����ݣ�\n");
		getchar();
		return;
	}
	system("cls");
	Disp(l, 0);
	stringinput(find_data, 15, "������Ҫ�޸�ѧ����ѧ�ţ�"); /*���벢����ñ��*/
	p = Locate(l, find_data, 0); /*��ѯ���ýڵ�*/
	if (p) /*��p!=NULL,�����Ѿ��ҵ��ýڵ�*/
	{
		system("cls");
		printf("���ҵ�������Ϣ��\n");
		printf(HEADER1);
		printf(FORMAT1, DATA1);
		printf(HEADER3);
		printf(FORMAT3, DATA3);
		printf("\n�������ʾ����Ҫ�޸ĵ���Ϣ������0���޸Ĵ��");
		printf("\nѧ�ţ�");
		gets();
		gets(ch);
		if (strcmp(ch, "0") != 0) {
			while (t = Locate(l, ch, 0)) {
				printf("\n��ѧ���Ѵ��ڣ��볢������ѧ�ţ�");
				printf("\nѧ�ţ�");
				gets(ch);
			}
			strcpy(p->num, ch);
		}
		printf("\n���֣�");
		gets(ch);
		if (strcmp(ch, "0") != 0)
			strcpy(p->name, ch);
		printf("\n�Ա�");
		gets(ch);
		if (strcmp(ch, "0") != 0)
			strcpy(p->sex, ch);
		printf("\n��ͥסַ��");
		gets(ch);
		if (strcmp(ch, "0") != 0)
			strcpy(p->address, ch);
		printf("\n�绰��");
		gets(ch);
		if (strcmp(ch, "0") != 0)
			strcpy(p->phone, ch);
		printf("\n=====>�޸ĳɹ����޸ĺ���ϢΪ��\n");
		printf(HEADER1);
		printf(FORMAT1, DATA1);
		printf(HEADER3);
		printf(FORMAT3, DATA3);
		Save(l);

		system("pause");
		system("cls");
		return;
	}
	else
	{
		getchar();
		printf("=====>ѧ�� %s ����Ϣ��δ��¼�룬Ҫ��Ҫ��һ���أ�(y/n):", find_data);
		scanf("%c", &chy);
		if (chy == 'y' || chy == 'Y') {
			system("cls");
			goto temp;
		}
		else {
			system("cls");
			return;
		}
	}
}

void Del(Stu* l)
{
	int sel;
	Stu* p, * r;
	char find_data[20], chy;
temp_del:
	if (!l->next)
	{
		system("cls");
		printf("\n\t\t\t\t\t\t=====>�ļ���û�����ݣ�\n");
		getchar();
		return;
	}
	system("cls");
	Disp(l, 0);
	printf("\n        =====>1 ����ѧ��ɾ��   =====>2 ��������ɾ��   =====>0 ������һ��\n");
	printf("       ���������ѡ��[0,2]:");
	scanf("%d", &sel);
	if (sel == 0)
		return;
	else if (sel == 1)
	{
		stringinput(find_data, 15, "������Ҫɾ��ѧ����ѧ�ţ�");
		p = Locate(l, find_data, 0);
	}
	else if (sel == 2) /*�Ȱ�������ѯ���ü�¼���ڵĽڵ�*/
	{
		stringinput(find_data, 10, "������Ҫɾ��ѧ����������");
		p = Locate(l, find_data, 1);
	}
	else
	{
		Wrong(1, 2);
		system("pause");
		goto temp_del;
	}
	if (p)  /*p!=NULL*/
	{
		system("cls");
		printf("���ҵ��������ݣ�\n");
		printf(HEADER1);
		printf(FORMAT1, DATA1);
		printf(HEADER3);
		printf(FORMAT3, DATA3);
		printf(HEADER4);
		printf(FORMAT4, DATA4);
		printf(HEADER5);
		printf(FORMAT5, DATA5);
		printf("�Ƿ�ȷ��ɾ���������ݣ�(y/n)��");
		getchar();
		scanf("%c", &chy);
		if (chy == 'y' || chy == 'Y')
		{
			r = l;
			while (r->next != p)
				r = r->next;
			r->next = p->next;/*��p��ָ�ڵ��������ȥ��*/
			free(p); /*�ͷ��ڴ�ռ�*/
			printf("\n=====>�ѳɹ�ɾ����\n");
			getchar();
			Save(l);
			system("pause");
			system("cls");
			return;
		}
		else
		{
			system("cls");
			goto temp_del;
		}
	}
	else
	{
		getchar();
		printf("=====>%s ����Ϣ��δ��¼�룬Ҫ��Ҫ��һ���أ�(y/n):", find_data);
		scanf("%c", &chy);
		if (chy == 'y' || chy == 'Y')
		{
			system("cls");
			goto temp_del;
		}
		else
		{
			system("cls");
			return;
		}
	}
}


void Add_score(Stu* l)
{
	Stu* p;  /*ʵ����Ӳ�������ʱ�Ľṹ��ָ�����*/
	char find_data[20];
	char ch;
	if (!l->next)
	{
		system("cls");
		printf("\n\t\t\t\t\t\t=====>�ļ���û�����ݣ�\n");
		getchar();
		return;
	}
	system("cls");
	Disp(l, 1);
	while (1) /*һ�ο����������¼��ֱ��������Ϊ0�ļ�¼�����Ӳ���*/
	{

		stringinput(find_data, 15, "������ѧ�ţ�"); /*���벢����ñ��*/
		if (strcmp(find_data, "0") == 0) /*����Ϊ0�����˳���Ӳ���������������*/
		{
			Save(l);
			return;
		}
		p = Locate(l, find_data, 0); /*��ѯ���ýڵ�*/
		if (p) /*��p!=NULL,�����Ѿ��ҵ��ýڵ�*/
		{
			printf("ѧ�ţ�%s\t������%s\n", p->num, p->name);
			printf("���ģ�");
			scanf("%d", &p->chinese);
			printf("��ѧ��");
			scanf("%d", &p->math);
			printf("Ӣ�");
			scanf("%d", &p->english);
			printf("˼��Ʒ�£�");
			scanf("%d", &p->pinde);
			printf("������");
			scanf("%d", &p->huping);
			printf("ʦ����");
			scanf("%d", &p->teacher);

			p->average = ((p->chinese) + (p->math) + (p->english)) / 3;//����ƽ����
			/*�����ۺϲ����÷֣�����Ӣƽ����60%��˼��Ʒ��10%������10%��ʦ��20%��*/
			p->score_all = (p->average) * 0.6 + (p->huping) * 0.1 + (p->pinde) * 0.1 + (p->teacher) * 0.2;

			printf("ƽ���ɼ���%.2lf", p->average);
			printf("�ۺϲ����÷֣�%.2lf", p->score_all);
		}
		else
		{
			getchar();
			printf("=====>ѧ�� %s ����Ϣ��δ��¼�룬Ҫ��Ҫ��һ���أ�(y/n):", find_data);
			scanf("%c", &ch);
			if (ch == 'y' || ch == 'Y')
				continue;
			else
				return;
		}
	}
}

void Modify_score(Stu* l)
{
	Stu* p, * t;  /*ʵ����Ӳ�������ʱ�Ľṹ��ָ�����*/
	char find_data[20];
	char chy;
	int tmp;
temp:
	if (!l->next)
	{
		system("cls");
		printf("\n\t\t\t\t\t\t=====>�ļ���û�����ݣ�\n");
		getchar();
		return;
	}
	system("cls");
	Disp(l, 1);
	stringinput(find_data, 15, "������Ҫ�޸�ѧ����ѧ�ţ�"); /*���벢����ñ��*/
	p = Locate(l, find_data, 0); /*��ѯ���ýڵ�*/
	if (p) /*��p!=NULL,�����Ѿ��ҵ��ýڵ�*/
	{
		system("cls");
		printf("���ҵ������ɼ���\n");
		printf(HEADER2);
		printf(FORMAT2, DATA2);
		printf(HEADER4);
		printf(FORMAT4, DATA4);
		printf(HEADER5);
		printf(FORMAT5, DATA5);
		printf("\n�������ʾ����Ҫ�޸ĵĳɼ�������-1���޸Ĵ��");
		printf("\n���ģ�");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->chinese = tmp;
		printf("\n��ѧ��");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->math = tmp;
		printf("\nӢ�");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->english = tmp;
		printf("\n˼��Ʒ�£�");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->pinde = tmp;
		printf("\n������");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->huping = tmp;
		printf("\nʦ����");
		scanf("%d", &tmp);
		if (tmp != -1)
			p->teacher = tmp;
		p->average = ((p->chinese) + (p->math) + (p->english)) / 3;//����ƽ����
			/*�����ۺϲ����÷֣�����Ӣƽ����60%��˼��Ʒ��10%������10%��ʦ��20%��*/
		p->score_all = (p->average) * 0.6 + (p->huping) * 0.1 + (p->pinde) * 0.1 + (p->teacher) * 0.2;
		printf("\n=====>�޸ĳɹ����޸ĺ���ϢΪ��\n");
		printf(HEADER2);
		printf(FORMAT2, DATA2);
		printf(HEADER4);
		printf(FORMAT4, DATA4);
		printf(HEADER5);
		printf(FORMAT5, DATA5);
		Save(l);

		system("pause");
		system("cls");
		return;
	}
	else
	{
		getchar();
		printf("=====>ѧ�� %s ����Ϣ��δ��¼�룬Ҫ��Ҫ��һ���أ�(y/n):", find_data);
		scanf("%c", &chy);
		if (chy == 'y' || chy == 'Y') {
			system("cls");
			goto temp;
		}
		else {
			system("cls");
			return;
		}
	}
}

void look_feedback()
{
	FILE* fp;
	fp = fopen("score_feedback.dat", "a+");
	printf("ѧ���ɼ����߷�����Ϣ\n");
	while (!feof(fp))
		putchar(fgetc(fp));
	fclose(fp);
	printf("\n\n");
	system("pause");
	system("cls");
	return;
}

void teacher_main_menu(Stu* l, Stu* p, Stu* r) {
	int option;
	while (1) {
		toxy(35, 5);
		printf("==================================================");
		toxy(44, 7);
		printf("��ӭʹ��ѧ���ۺϲ���ϵͳ(��ʦ��)");
		toxy(36, 10);
		printf("-----ѧ����Ϣ����-----   -----ѧ���ɼ�����-----");
		toxy(36, 11);
		printf("|                    |   |                    |");
		toxy(36, 12);
		printf("|  1. ���ѧ����Ϣ   |   |  5. ¼��ɼ�����   |");
		toxy(36, 13);
		printf("|  2. �޸�ѧ����Ϣ   |   |  6. �޸ĳɼ�����   |");
		toxy(36, 14);
		printf("|  3. ɾ��ѧ����Ϣ   |   |  7. �鿴�ɼ���Ϣ   |");
		toxy(36, 15);
		printf("|  4. �鿴ѧ����Ϣ   |   |  8. �鿴�ɼ�����   |");
		toxy(36, 16);
		printf("|                    |   |                    |");
		toxy(36, 17);
		printf("----------------------   ----------------------");
		toxy(36, 19);
		printf("   9. ������ƽ���֣�       10. �������ۺϷ֣�");
		toxy(36, 20);
		printf("  11. ��ʾȫ��ѧ������      0. �˳�ϵͳ");
		toxy(47, 22);
		printf("���������ѡ��0--11����");
		toxy(35, 24);
		printf("==================================================");
		p = r;
		toxy(60, 25);
		scanf("%d", &option);
		switch (option)
		{
		case 0:exit(0);
		case 1:Add_info(l); Sort(l, 0); system("cls"); break;
		case 2:Modify_info(l); Sort(l, 0); system("cls"); break;
		case 3:Del(l); system("cls"); break;
		case 4:system("cls"); Sort(l, 0); Disp(l, 0); system("pause"); system("cls"); break;
		case 5:Add_score(l); Sort(l, 1); Sort(l, 2); Sort(l, 0); system("cls"); break;
		case 6:Modify_score(l); Sort(l, 1); Sort(l, 2); Sort(l, 0); system("cls"); break;
		case 7:system("cls"); Sort(l, 0); Disp(l, 1); system("pause"); system("cls"); break;
		case 8:system("cls"); look_feedback(); break;
		case 9:Sort(l, 1); system("cls"); Disp(l, 2); system("pause"); system("cls"); break;
		case 10:Sort(l, 2); system("cls"); Disp(l, 3); system("pause"); system("cls"); break;
		case 11:Sort(l, 0); Disp(l, 4); system("pause"); system("cls"); break;
		default:Wrong(0, 11); system("pause"); system("cls"); break;
		}

	}


	system("pause");
}

void Stu_score_feedback(Stu* p)
{
	FILE* fp;
	char i;
	fp = fopen("score_feedback.dat", "ab+");
	printf("��������ĳɼ������ʣ��������������ʦ���Է�����\n");
	printf("ֱ�Ӱ�i����ʼ���뷴�������������ɷ��أ�\n");
	i = getch();
	if (i != 'i')
	{
		fclose(fp);
		system("cls");
		return;
	}
	else
	{
		system("cls");
		printf("����������������ԣ���ɺ󰴻س���������\n");
		fputs("------------------------------------\n", fp);
		char fdbk[512], tmp2[256];
		memset(tmp2, 0, sizeof(tmp2));
		time_t timep;
		struct tm* t;
		time(&timep);
		t = gmtime(&timep);
		sprintf(tmp2, "%d��%d��%d�� %d:%d:%d\nѧ�ţ�%s ������%s\n", 1900 + t->tm_year, 1 + t->tm_mon, t->tm_mday, 8 + t->tm_hour, t->tm_min, t->tm_sec, p->num, p->name);//��¼����ʱ��
		fwrite(tmp2, 1, strlen(tmp2), fp);
		scanf("%s", fdbk);
		fputs(fdbk, fp);
		fputs("\n------------------------------------\n", fp);
		fclose(fp);
		printf("====>�ɼ��������ύ����ʦ�������ĵȴ���");
		system("pause");
		system("cls");
		return;
	}
}

void stu_menu(Stu* l)
{

	Stu* p, * t;  /*ʵ����Ӳ�������ʱ�Ľṹ��ָ�����*/
	char find_data[20];
	char chy;
temp_stu:
	toxy(35, 12);
	printf("==================================================");
	toxy(52, 14);
	printf("ѧ��ϵͳ��¼����");
	if (!l->next)
	{
		system("cls");
		toxy(49, 12);
		printf("=====>��ʱû��ѧ�����ݣ�");
		getchar();
		toxy(54, 14);
		system("pause");
		return;
	}
	toxy(50, 16);
	stringinput(find_data, 15, "������ѧ�ţ�"); /*���벢����ñ��*/
	p = Locate(l, find_data, 0); /*��ѯ���ýڵ�*/
	if (p) /*��p!=NULL,�����Ѿ��ҵ��ýڵ�*/
	{
		int i;
		while (1)
		{
			system("cls");
			toxy(35, 12);
			printf("==================================================");
			toxy(44, 14);
			printf("��ӭʹ��ѧ���ۺϲ���ϵͳ(ѧ����)");
			toxy(47, 15);
			printf("%15s %-10s", p->num, p->name);
			toxy(48, 18);
			printf("1.�ɼ���ѯ");
			printf("\t2.�ɼ�����");
			toxy(48, 20);
			printf("\t3.���ص�¼");
			printf("\t0.�˳�ϵͳ");
			toxy(50, 22);
			printf("�������Ӧ���[0-3]��");
			toxy(35, 24);
			printf("==================================================");
			scanf("%d", &i);
			switch (i) {
			case 1:system("cls"); printscore(p); system("pause"); system("cls"); break;
			case 2:system("cls"); Stu_score_feedback(p); break;
			case 3:system("cls");  goto temp_stu; break;
			case 0:exit(0);
			default:Wrong(0, 3); system("pause"); system("cls");
			}

		}
	}
	else
	{
		getchar();
		printf("=====>ѧ�� %s �����ڣ�Ҫ��Ҫ��һ���أ�(y/n):", find_data);
		scanf("%c", &chy);
		if (chy == 'y' || chy == 'Y') {
			system("cls");
			goto temp_stu;
		}
		else {
			system("cls");
			return;
		}
	}
}
void about_us() {
	printf("==================================================");
	printf("\n\t      ��  ��  ��  ��\n\n");
	printf("      ϵͳΪ������Сѧ��������������ϰϵͳ��\n");
	printf("  ϵͳ��C���Ա�д�����Խ���100���ڵ���������\n");
	printf("  ��ϰ��ÿ����ϰ��������ָ����Ŀ������ÿ����\n");
	printf("  ���δ�����ᣬ��һ�δ�Ե����֣��ڶ��δ��\n");
	printf("  ��һ��ķ֣�����÷֡���ϰ��ɲ鿴ÿ����\n");
	printf("  ϰ�Ĵ��⡣\n");
	printf("\n\t   Powered by Edward_du\n");
	printf("\n\t   \t2019.4.19\n");
	printf("==================================================");

}

int main() {
	Stu* l;      /*��������*/
	FILE* fp, * fpp;    /*�ļ�ָ��*/
	int select;     /*����ѡ��������*/
	char ch;     /*����(y,Y,n,N)*/
	int count = 0; /*�����ļ��еļ�¼���������������*/
	Stu* p, * r;   /*�����¼ָ�����*/


	l = (Stu*)malloc(sizeof(Stu));
	if (!l)
	{
		printf("\n �ڴ�����ʧ�ܣ��볢�Ի�ȡ����Ȩ�ޣ� "); /*��û�����뵽����ӡ��ʾ��Ϣ*/
		return;             /*����������*/
	}
	l->next = NULL;
	r = l;
	fp = fopen("student_info.dat", "ab+"); /*��׷�ӷ�ʽ��һ���������ļ����ɶ���д�������ļ������ڣ��ᴴ�����ļ�*/
	if (fp == NULL)
	{
		printf("\n=====>�޷����ļ��������ԣ�\n");
		exit(0);
	}

	fpp = fopen("score_feedback.dat", "ab+"); /*��׷�ӷ�ʽ��һ���������ļ����ɶ���д�������ļ������ڣ��ᴴ�����ļ�*/
	if (fpp == NULL)
	{
		printf("\n=====>�޷����ļ��������ԣ�\n");
		exit(0);
	}

	while (!feof(fp))
	{
		p = (Stu*)malloc(sizeof(Stu));
		if (!p)
		{
			printf("\n �ڴ�����ʧ�ܣ��볢�Ի�ȡ����Ȩ�ޣ� \n");    /*û�������ڴ�ɹ�*/
			exit(0);       /*�˳�*/
		}

		if (fread(p, sizeof(Stu), 1, fp) == 1) /*һ�δ��ļ��ж�ȡһ����ʦ���¼�¼*/
		{
			p->next = NULL;
			r->next = p;
			r = p;                            /*rָ�������һ��λ��*/
			count++;
		}
	}

	fclose(fp); /*�ر��ļ�*/
	fclose(fpp);
	system("mode con cols=120 lines=40");

	main_menu(l, p, r);

}