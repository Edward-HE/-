#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>


int saveflag = 0;

typedef struct student {
	int num;			//ѧ��
	char name[15];		//ѧ������
	char sex[4];		//�Ա�
	char address[100];	//��ͥסַ
	char phone[14];		//�绰
};

typedef struct studata {
	int num;							//ѧ��
	int chinese, math, english, pinde;	//�����Ӣ��˼��Ʒ�³ɼ�
	int rank_main, rank_all;			//����Ӣ�������Σ��ۺϲ�������
	int huping, teacher;				//�����֣���ʦ����
	float average, score_all;			//����ƽ���֣��ۺ��ܷ�
};

void main_menu() {  //��ҳ��
	printf("=============================================\n");
	printf("\n\t      ѧ���ۺϲ���ϵͳ\n\n");
	printf("\t1.��ʦ�˻�");
	printf("\t2.ѧ���˻�\n\n");
	printf("\t3.��������");
	printf("\t4.�˳�ϵͳ\n\n");
	printf("\t      �������Ӧ���: \n");
	printf("\n=============================================\n");
}

void teacher_menu() {
	printf("=============================================\n");
	printf("\n\t      ����һ��\n\n");
	printf("\t1.ע	��");
	printf("\t2.��	¼\n\n");
	printf("\t3.��������");
	printf("\t4.�˳�ϵͳ\n\n");
	printf("\t      �������Ӧ���: \n");
	printf("\n=============================================\n");
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
	//users_create();
	int flag_login;
	system("color 8F");
	main_menu();
	int option;
	scanf("%d", &option);
	switch (option) {

	case 1:system("cls"); teacher_menu(); system("cls"); //goto beginning;
	case 2:system("cls"); stu_menu(); system("cls");
		while (1) {
			if (flag_login == 0)
				//goto beginning;
				printf("dd");
			else
				break;
		}
	case 3:system("cls"); about_us(); main();
	}
}