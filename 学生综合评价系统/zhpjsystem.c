#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>


int saveflag = 0;

typedef struct student {
	int num;//ѧ��
	char name[15];//ѧ������
	char sex[4];//�Ա�
	char address[100];//��ͥסַ
	char phone[14];//�绰
};

typedef struct studata {
	int num;//ѧ��
	int chinese, math, english, pinde;//�����Ӣ��˼��Ʒ�³ɼ�
	int rank_main, rank_all;//����Ӣ�������Σ��ۺϲ�������
	int huping, teacher;//�����֣���ʦ����
	float average, score_all;//����ƽ���֣��ۺ��ܷ�
};

