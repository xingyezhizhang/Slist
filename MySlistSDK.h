
#pragma once

#ifndef MYSLISTSDK_H
#define MYSLISTSDK_H
/**********单向链表**********/

/*创建链表、查询链表、销毁链表
单个 节点的添加、插入、删除
不支持多个链表
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

//创建一个用于链表的结构体 
typedef struct slist
{
	unsigned int ID;
	char *NAME;
	struct slist *NEXT;
}SLIST;

//函数声明 
bool Creat_Node(char *pname, SLIST **ppnext/*为连接新节点准备的指针的地址*/); 		//创建节点 
bool Add_Node(char *pname, SLIST *phead);   										//添加节点 
bool Input_Node(unsigned int id, char *pname, SLIST *phead); 						//插入节点
bool Find_Node(char *pname, SLIST *phead, SLIST *paccept_node);						//查询节点
bool Delete_Node(unsigned int id, SLIST *phead);									//删除节点 

SLIST *Creat_Slist(); 												//创建链表
bool Show_Slist(SLIST *phead);										//显示链表
bool Clean_Slist(SLIST **pphead);   								//销毁链表


#endif