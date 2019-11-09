
#pragma once

#ifndef MYSLISTSDK_H
#define MYSLISTSDK_H
/**********��������**********/

/*����������ѯ������������
���� �ڵ����ӡ����롢ɾ��
��֧�ֶ������
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

//����һ����������Ľṹ�� 
typedef struct slist
{
	unsigned int ID;
	char *NAME;
	struct slist *NEXT;
}SLIST;

//�������� 
bool Creat_Node(char *pname, SLIST **ppnext/*Ϊ�����½ڵ�׼����ָ��ĵ�ַ*/); 		//�����ڵ� 
bool Add_Node(char *pname, SLIST *phead);   										//��ӽڵ� 
bool Input_Node(unsigned int id, char *pname, SLIST *phead); 						//����ڵ�
bool Find_Node(char *pname, SLIST *phead, SLIST *paccept_node);						//��ѯ�ڵ�
bool Delete_Node(unsigned int id, SLIST *phead);									//ɾ���ڵ� 

SLIST *Creat_Slist(); 												//��������
bool Show_Slist(SLIST *phead);										//��ʾ����
bool Clean_Slist(SLIST **pphead);   								//��������


#endif