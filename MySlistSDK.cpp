#include "stdafx.h"
#include"MySlistSDK.h"


//�����ڵ� 
bool Creat_Node(char *pname, SLIST **ppnext /*Ϊ�����½ڵ�׼����ָ��ĵ�ַ*/)
{
	SLIST *creat;
	//�ж�ָ���Ƿ�Ϊ�գ���������ڴ涪ʧ 
	if (NULL == *ppnext)
	{
		//����һ���½ڵ�
		if (creat = (SLIST *)malloc(sizeof(SLIST)))
		{
			/************���ݴ洢************/
			//�����ַ�����
			creat->NAMELEN = strlen(pname) + 1;
			//���ٸպô���ַ����ڴ�ռ�
			creat->NAME = (char*)malloc(creat->NAMELEN);
			//����������ڵ�
			strcpy(creat->NAME, pname);
			/************���ݴ洢************/

			/************�ڵ����***********/
			creat->NEXT = NULL;		//���½ڵ��ָ�븴λ
			*ppnext = creat;
			/************�ڵ����***********/
			return true;
		}
		else
		{
			printf("�ڵ㴴��ʧ�ܣ�\n�����ڴ��Ƿ���У�\n");
			return false;
		}
	}
	else
	{
		printf("�������ָ�룬��������ڴ涪ʧ��\n");
		return false;
	}
}


//��ӽڵ� 
bool Add_Node(char *pname, SLIST *phead)
{
	int id;
	SLIST *move;
	move = phead;

	//���ҵ����һ���ڵ� 
	while (move->NEXT){
		move = move->NEXT;
	}
	//���ô����ڵ㺯��  ����һ���½ڵ�
	//������������һ���ڵ�ָ��ָ���½ڵ� 
	if (Creat_Node(pname, &move->NEXT))
	{
		id = move->ID; 			//��ȡ���ڵ��ID
		move = move->NEXT; 		//moveָ�� ָ�� �½ڵ�
		move->ID = id + 1;      //���½ڵ�ID
		return true;
	}
		printf("��ӽڵ�ʧ�ܣ�\n");
		return false;
}


//����ڵ� 
bool Input_Node(unsigned int id, char *pname, SLIST *phead)
{
	SLIST *move, *pinput_node;
	move = phead;
	pinput_node = NULL;

	//��ͷ�����޸� 
	if (id)
	{
		//ʹmoveָ��ָ��id���ڽڵ����һ���ڵ� 
		while (id != (move->ID + 1))
		{
			move = move->NEXT;
			if (NULL == move->NEXT)
			{
				printf("��ǰ�������Ľڵ㣬IDΪ%d\n", move->ID);
				printf("����ڵ㽫��Ϊ��ӽڵ㣡\n");
				Add_Node(pname, phead);
				return true;
			}
		}
		/************�ڵ����************/
		//���ô����ڵ㺯��  �����½ڵ�	
		Creat_Node(pname, &pinput_node);
		pinput_node->ID = id;					//��id�����½ڵ� 
		pinput_node->NEXT = move->NEXT;		//�½ڵ����id���ڵ�ԭ�ڵ� 
		move->NEXT = pinput_node;		//��һ���ڵ����½ڵ����

		//ά��id��Ψһ��
		move = pinput_node->NEXT;
		while (move)
		{
			move->ID = move->ID + 1;
			move = move->NEXT;
		}
		/************�ڵ����************/
		return true;
	}
		printf("�����޸ı�ͷ��\n");
		return false;
}


//ɾ���ڵ�
bool Delete_Node(unsigned int id, SLIST *phead)
{
	SLIST *move, *del;
	move = phead;
	if (id)
	{
		//ʹmoveָ��ָ�� Ҫɾ���Ľڵ����һ���ڵ�
		while (id != (move->ID + 1))
		{
			move = move->NEXT;
			if (NULL == move->NEXT)
			{
				printf("��ǰ�������Ľڵ㣬IDΪ%d\n", move->ID);
				printf("����ȷ����ID��\n");
				return false;
			}
		}
		/************�ڵ�ɾ��************/
		//delָ�� ָ�� Ҫɾ���Ľڵ� 
		del = move->NEXT;
		//ʹ��һ���ڵ� ���� Ҫɾ���Ľڵ����һ���ڵ� 
		move->NEXT = del->NEXT;
		free(del->NAME);  //�ͷ������ڴ�
		free(del);   //ɾ���ڵ�
		//ά��ID��������
		move = move->NEXT;
		while (move)
		{
			move->ID = move->ID - 1;
			move = move->NEXT;
		}
		/************�ڵ�ɾ��************/
		return true;
	}
	printf("Ҫɾ����ͷ����ֱ����������\n");
	return false;
}


//��ѯ�ڵ�
bool Find_Node(char *pname, SLIST *phead, SLIST *paccept_node)
{
	SLIST *move;
	int namelen = strlen(pname) + 1;
	move = phead;
	if (move)  //�ж��Ƿ������� 
	{
		if (move->ID)  //�ж��Ƿ��������ͷָ�� 
		{
			printf("������ͷָ�룡\n");
			return false;
		}
		//�����ַ���ѯ
		while (strcmp(move->NAME, pname))
		{
			if (move->NEXT)
			{
				move = move->NEXT;
			}
			else
			{
				printf("��ǰ����û�и��ַ�����\n");
				return true;
			}
		}
		//�����ݿ�����ȥ
		paccept_node->ID = move->ID;		//�ڵ�ID����
		paccept_node->NAMELEN = move->NAMELEN;	//�ַ�����ֵ����
		//�ַ�����  ��Ϊָ�뿪���ڴ棬�ٽ��п���
		paccept_node->NAME = (char*)malloc(strlen(move->NAME) + 1);
		strcpy(paccept_node->NAME, move->NAME);	
		paccept_node->NEXT = NULL;   //�ڵ��ָ�벻����
		printf("���ַ����������е�IDΪ%d\n", move->ID);
		return true;
	}
	printf("��ǰû����������ȷ����ͷָ�룡\n");
	return false;
}


//�������� 
SLIST *Creat_Slist()
{
	SLIST *phead = NULL;
	Creat_Node("�����ͷ", &phead);
	phead->ID = 0;
	return phead;
}


//��ʾ����
bool Show_Slist(SLIST *phead)
{
	SLIST *move;
	move = phead;
	//�ж��Ƿ�������
	if (move)
	{
		//�ж��Ƿ���ͷָ��
		if (move->ID)
		{
			printf("������ͷָ�룡\n");
			return false;
		}
		do
		{
			//��ʾ�ڵ���Ϣ
			printf("ID:%d\tnamelen:%d\tname:%s\n", move->ID, move->NAMELEN, move->NAME);
		} while (move = move->NEXT); //��������
		return true;
	}
	printf("��ǰû������\n");
	return true;
}

//��������
bool Clean_Slist(SLIST **pphead)
{
	SLIST *move, *del;
	move = *pphead;
	if (move)  				//�ж��Ƿ������� 
	{
		if (move->ID)  		//�ж��Ƿ��������ͷָ�� 
		{
			printf("������ͷָ�룡\n");
			return false;
		}
		/******************��������******************/
		while (del = move)  //delָ���Ƶ�Ҫɾ���Ľڵ�
		{
			move = move->NEXT;	//moveָ���Ƶ���һ���ڵ�
			free(del->NAME);  //�ͷ������ڴ�
			free(del);		  //ɾ���ڵ�
		}
		*pphead = NULL;  //ͷָ������
		/******************��������******************/
		printf("����������ϣ�\n");
		return true;
	}
	printf("��ǰû�������������٣�\n");
	return true;
}
