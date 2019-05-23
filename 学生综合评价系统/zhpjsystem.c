#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>

void Wrong();
void main_menu();
void teacher_menu();
void stu_menu();
void about_us();
int pswd_check();
char mod_pswd();
void login_teacher();
void pswd_create();

int flag_pswd = 0;			//��ʾ��ʦ�˻���ʼ�����Ƿ��޸ģ�1�Ǳ��޸�
int check_result = 0;	//��¼������ı���

typedef struct student {
	int num;			//ѧ��
	char name[15];		//ѧ������
	char sex[4];		//�Ա�
	char address[100];	//��ͥסַ
	char phone[14];		//�绰
}Stu;

typedef struct studata {
	int num;							//ѧ��
	int chinese, math, english, pinde;	//�����Ӣ��˼��Ʒ�³ɼ�
	int rank_main, rank_all;			//����Ӣ�������Σ��ۺϲ�������
	int huping, teacher;				//�����֣���ʦ����
	float average, score_all;			//����ƽ���֣��ۺ��ܷ�
}StuDt;

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

void main_menu() {  //��ҳ��
	printf("=============================================\n");
	printf("\n\t      ѧ���ۺϲ���ϵͳ\n\n");
	printf("\t1.��ʦ�˻�");
	printf("\t2.ѧ���˻�\n\n");
	printf("\t3.��������");
	printf("\t4.�˳�ϵͳ\n\n");
	printf("\t      �������Ӧ���: \n");
	printf("\n=============================================\n");
	int option;
	scanf("%d", &option);
	switch (option) {
	case 1:system("cls"); teacher_menu(); system("cls");
	case 2:system("cls"); stu_menu(); system("cls");
	case 3:system("cls"); about_us(); main();
	case 4:exit(0);
	}
}

void teacher_menu() {
	pswd_create();
	FILE* fp_pswd;
	int i;
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
	case 1:system("cls"); login_teacher();
	case 2:system("cls"); mod_pswd();
	case 3:system("cls"); main();
	case 4:exit(0);
	default:Wrong(); system("pause"); system("cls"); teacher_menu();
	}
}

void login_teacher() {
	char a[16];
	FILE* fp;
	fp = fopen("pswd_teacher", "r"); //�򿪴���������ļ�
	fread(&a, sizeof(a), 1, fp);	 //��ȡ���뵽����a��	
	printf("===================================\n");
	printf("\t��ʦ��¼����\n");
	if (strcmp(a,"123456")==0) {
		printf("  ������ʹ�ó�ʼ���룬�뼰ʱ��������\n");
	}
	printf("\n���������룺");
	pswd_check();
	if (check_result == 1) {
		printf("\n\n��¼�ɹ������������ʦ��\n");
		printf("\n===================================\n");
		system("pause");
		system("cls");
		teacher_menu();
	}
	fclose(fp);
}

int pswd_check() {		//���������ȷ��
	char a[16],b[16];
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
		teacher_menu();
	}
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
	system("pause");
	system("cls");
}

int main() {
	int flag_;
	system("color 8F");
	main_menu();

}