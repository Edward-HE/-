#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define HEADER0 "      ----------------------------ѧ���б�---------------------------  \n"
#define HEADER1 "     |     ѧ ��     |   �� ��   | �Ա� |    �� ϵ �� ��     |\n"
#define FORMAT1 "     |%-15s|%-10s |%-6s|%-14s |\n"
#define HEADER2 "     |     ѧ ��     |   �� ��   |\n"
#define FORMAT2 "     |%-15s|%-10s |\n"
#define HEADER3 "     |  �� ͥ ס ַ  |"
#define FORMAT3 "     %-30s |\n"
#define HEADER4 "     |����|��ѧ|Ӣ��|ƽ����|����1|\n"
#define FORMAT4 "     |%-4d|%-4d|%-4d|%-6lf|%-4d |\n"
#define HEADER5 "     |˼Ʒ|����|ʦ��|�ۺϷ�|����2|\n"
#define FORMAT5 "     |%-4d|%-4d|%-4d|%-6lf|%-4d |\n"


#define DATA1   p->num,p->name,p->sex,p->phone
#define DATA2   p->num,p->name
#define DATA3   p->address
#define DATA4   p->chinese,p->math,p->english,p->average,p->rank_main
#define DATA5   p->pinde,p->huping,p->teacher,p->score_all,p->rank_all

#define END     "      --------------------------------------------------------------  \n"
//------------------------------- ����ȫ�ֱ���------------------------------------
int check_result = 0;		//��¼������ı���
//------------------------------- ����ѧ�����ݽṹ��------------------------------------
typedef struct Stuinfo {
	char num[15];			//ѧ��
	char name[10];		//ѧ������
	char sex[4];		//�Ա�
	char address[30];	//��ͥסַ
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
void Wrong();
void main_menu(Stu* l, Stu* p, Stu* r);
void teacher_account(Stu* l, Stu* p, Stu* r);
void stu_menu();
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
void Sort(Stu* l,int sel);
int main();

void Wrong() /*�������������Ϣ*/
{
	system("cls");
	printf("=========================================\n");
	printf("\n\n\n��ѡ��1-4�ĸ�ѡ��֮һ���벻Ҫ��������ѡ�\n\n\n");
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
		printf("\n=====>open file error!\n");
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
		getchar();
		printf("\n\n\n\n\n=====>save file complete,total saved's record number is:%d\n", count);
		getchar();
	}
	else
	{
		system("cls");
		printf("the current link is empty,no teacher record is saved!\n");
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

void Sort(Stu* l,int sel)
{
	Stu* ll;
	Stu* p, * rr, * s;
	int sel;
	//int i=0;
	if (l->next == NULL)
	{
		system("cls");
		printf("\n=====>Not teacher record!\n");
		getchar();
		return;
	}

	ll = (Stu*)malloc(sizeof(Stu)); /*���ڴ����µĽڵ�*/
	if (!ll)
	{
		printf("\n allocate memory failure "); /*��û�����뵽����ӡ��ʾ��Ϣ*/
		return;             /*����������*/
	}
	ll->next = NULL;
	system("cls");
	p = l->next;
	while (p) /*p!=NULL*/
	{
		s = (Stu*)malloc(sizeof(Stu)); /*�½��ڵ����ڱ����ԭ������ȡ���Ľڵ���Ϣ*/
		if (!s) /*s==NULL*/
		{
			printf("\n allocate memory failure "); /*��û�����뵽����ӡ��ʾ��Ϣ*/
			return;             /*����������*/
		}
		s= p; /*��������*/
		s->next = NULL;    /*ָ����Ϊ��*/
		rr = ll;
		/*rr�����ڴ洢���뵥���ڵ�󱣳����������ll����������ͷָ��,ÿ�δ�ͷ��ʼ���Ҳ���λ��*/
		if (sel == 1) {
			while (rr->next != NULL && rr->next->average >= p->average)
			{
				rr = rr->next;
			} /*ָ������ʵ�����ʱ�p��ָ�Ľڵ��ʵ������С�Ľڵ�λ��*/
		}

		if (sel == 2) {
			while (rr->next != NULL && rr->next->score_all >= p->score_all)
			{
				rr = rr->next;
			} /*ָ������ʵ�����ʱ�p��ָ�Ľڵ��ʵ������С�Ľڵ�λ��*/
		}

		if (sel == 0) {
			while (rr->next != NULL && strcmp(rr->next->num, p->num) == -1)
			{
				rr = rr->next;
			} /*ָ������ʵ�����ʱ�p��ָ�Ľڵ��ʵ������С�Ľڵ�λ��*/
		}

		if (rr->next == NULL)/*��������ll�е����нڵ��ʵ������ֵ����p->data.total��ʱ���ͽ�p��ָ�ڵ��������β��*/
			rr->next = s;
		else /*���򽫸ýڵ��������һ��ʵ�������ֶα���С�Ľڵ��ǰ��*/
		{
			s->next = rr->next;
			rr->next = s;
		}
		p = p->next; /*ԭ�����е�ָ������һ���ڵ�*/
	}

	l->next = ll->next; /*ll�д洢�ǵ�������������ͷָ��*/
	p = l->next;           /*���ź����ͷָ�븳��p��׼����д����*/
	while (p != NULL)  /*��p��Ϊ��ʱ���������в���*/
	{
		//i++;       /*������*/
		p = p->next;   /*ָ�����*/

	}
	printf("\n    =====>sort complete!\n");
	Save(l);
}

//----------------------------------------��ҳ��----------------------------------------
void main_menu(Stu* l, Stu* p, Stu* r) {
	char option;
	while (1) {
		printf("=============================================\n");
		printf("\n\t      ѧ���ۺϲ���ϵͳ\n\n");
		printf("\t1.��ʦ�˻�");
		printf("\t2.ѧ���˻�\n\n");
		printf("\t3.��������");
		printf("\t4.�˳�ϵͳ\n\n");
		printf("\t      �������Ӧ���: \n");
		printf("\n=============================================\n");
		p = r;
		scanf("%c", &option);
		switch (option) {
		case '1':system("cls"); teacher_account(l, p, r); system("cls"); break;
		case '2':system("cls"); stu_menu(); system("cls"); break;
		case '3':system("cls"); about_us(); system("pause"); getchar(); system("cls"); break;
		case '4':exit(0);
		default:Wrong(); system("pause"); getchar(); system("cls"); break;
		}
	}
}
//----------------------------------------��ʦ�����˵�----------------------------------------
void teacher_account(Stu* l, Stu* p, Stu* r) {
	pswd_create();			//ÿ�ν����ȷ��һ���Ƿ���������ļ�		
	int i;
	while (1) {
		printf("=============================================\n");
		printf("\n\t      ��ӭʹ��\n\n");
		printf("\t1.��	¼");
		printf("\t2.�޸�����\n\n");
		printf("\t3.�������˵�");
		printf("\t4.�˳�ϵͳ\n\n");
		printf("\t      �������Ӧ���: \n");
		printf("\n=============================================\n");
		scanf("%d", &i);
		switch (i) {
		case 1:system("cls"); login_teacher(l, p, r); break;
		case 2:system("cls"); mod_pswd(); break;
		case 3:system("cls"); getchar(); return;
		case 4:exit(0);
		default:Wrong(); system("pause"); system("cls");
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
	printf("===================================\n");
	printf("\t��ʦ��¼����\n");
	if (strcmp(a, a1) == 0) {	 //�ж��Ƿ�Ϊ��ʼ����
		printf("  ������ʹ�ó�ʼ���룬�뼰ʱ��������\n");
	}
	printf("\n���������룺");
	pswd_check();
	if (check_result == 1) {
		printf("\n\n��¼�ɹ������������ʦ��\n");
		printf("\n===================================\n");
		system("pause");
		system("cls");
		teacher_main_menu(l, p, r);
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
			return (check_result);
		}
		else {
			printf("\n���벻��ȷ�����������룬������%d�λ���\n", i);
			printf("���������룺");
			i--;
			scanf("%s", &a);
		}
		if (i == 0) {
			printf("���������3�Σ���������������\n");
			printf("\n===================================\n");
			system("pause");
			system("cls");
			main();
		}
	}
	fclose(fp);
}

char mod_pswd() {	//�޸�����
	char b[16];		//��ʱ����������ı���
	FILE* fp;

	printf("===================================\n");
	printf("\t��ʦ�������޸�\n");
	printf("����������룺");
	pswd_check();
	printf("�����������룺");
	fp = fopen("pswd_teacher", "w");
	scanf("%s", &b);
	fputs(b, fp);
	fclose(fp);
	printf("��ȷ�������룺");
	pswd_check();
	if (check_result == 1) {
		printf("\n\n�޸�����ɹ���\n");
		printf("\n===================================\n");
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
		printf("\n=====>Not teacher record!\n");
		getchar();
		return;
	}

	printf("\n\n");
	printf(HEADER0);
	while (p)    /*������������д洢�Ľ�ʦ��Ϣ*/
	{
		if (i == 0)
			printinfo(p);
		else
			printscore(p);
		p = p->next;  /*�ƶ�ֱ��һ�����*/
		printf(END);
	}
	getchar();
}

void printinfo(Stu* pp) /*��ʽ�������������*/
{
	Stu* p;
	p = pp;
	printf(HEADER1);
	printf(FORMAT1, DATA1);
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
		//saveflag = 1;

	}
	Save(l);
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
		printf("\n=====>No teacher record!\n");
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

void Add_score(Stu* l)
{
	Stu* p;  /*ʵ����Ӳ�������ʱ�Ľṹ��ָ�����*/
	char find_data[20];
	char ch;
	if (!l->next)
	{
		system("cls");
		printf("\n=====>No teacher record!\n");
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
		printf("\n=====>No teacher record!\n");
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

void teacher_main_menu(Stu* l, Stu* p, Stu* r) {
	int option;
	while (1) {
		printf("===================================\n");
		printf("\n\t��ӭʹ��ѧ���ۺϲ���ϵͳ\n\n");
		printf("-----ѧ����Ϣ����-----   -----ѧ���ɼ�����-----\n");
		printf("|                    |   |                    |\n");
		printf("|  1. ���ѧ����Ϣ   |   |  5. ¼�뿼�Գɼ�   |\n");
		printf("|  2. �޸�ѧ����Ϣ   |   |  6. ¼������ɼ�   |\n");
		printf("|  3. ɾ��ѧ����Ϣ   |   |  7. �޸ĳɼ�����   |\n");
		printf("|  4. �鿴ѧ����Ϣ   |   |  8. �鿴�ɼ���Ϣ   |\n");
		printf("|                    |   |                    |\n");
		printf("----------------------   ----------------------\n\n");
		printf("   9. ������ƽ���֣�      10. �������ۺϷ֣�\n");
		printf("   9. ��ʾȫ��ѧ������      10. �������ۺϷ֣�\n");
		printf("   9. ������ƽ���֣�      10. �������ۺϷ֣�\n");
		printf("\n���������ѡ��0--11����\n");
		printf("\n===================================\n");

		p = r;
		scanf("%d", &option);
		switch (option)
		{
		case 0:exit(0);
		case 1:Add_info(l); break;
		case 2:Modify_info(l); break;
		case 3:
		case 4:system("cls"); Disp(l, 0); system("pause"); break;
		case 5:Add_score(l); break;
		case 6:
		case 7:Modify_score(l);
		case 8:system("cls"); Disp(l, 1); system("pause"); break;

		}

	}


	system("pause");
}

void stu_menu() {

}
void about_us() {
	printf("==============================================\n");
	printf("\n\t      ��  ��  ��  ��\n\n");
	printf("      ϵͳΪ������Сѧ��������������ϰϵͳ��\n");
	printf("  ϵͳ��C���Ա�д�����Խ���100���ڵ���������\n");
	printf("  ��ϰ��ÿ����ϰ��������ָ����Ŀ������ÿ����\n");
	printf("  ���δ�����ᣬ��һ�δ�Ե����֣��ڶ��δ��\n");
	printf("  ��һ��ķ֣�����÷֡���ϰ��ɲ鿴ÿ����\n");
	printf("  ϰ�Ĵ��⡣\n");
	printf("\n\t   Powered by Edward_du\n");
	printf("\n\t   \t2019.4.19\n");
	printf("\n==============================================\n");

}

int main() {
	Stu* l;      /*��������*/
	FILE* fp;    /*�ļ�ָ��*/
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
	//printf("\n=====>open file sucess,the total records number is : %d.\n", count);

	system("color 8F");
	main_menu(l, p, r);

}