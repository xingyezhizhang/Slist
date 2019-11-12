#include "stdafx.h"
#include"MySlistSDK.h"


//创建节点 
bool Creat_Node(char *pname, SLIST **ppnext /*为连接新节点准备的指针的地址*/)
{
	SLIST *creat;
	//判断指针是否为空，避免出现内存丢失 
	if (NULL == *ppnext)
	{
		//创建一个新节点
		if (creat = (SLIST *)malloc(sizeof(SLIST)))
		{
			/************数据存储************/
			//计算字符长度
			creat->NAMELEN = strlen(pname) + 1;
			//开辟刚好存放字符的内存空间
			creat->NAME = (char*)malloc(creat->NAMELEN);
			//将姓名放入节点
			strcpy(creat->NAME, pname);
			/************数据存储************/

			/************节点关联***********/
			creat->NEXT = NULL;		//对新节点的指针复位
			*ppnext = creat;
			/************节点关联***********/
			return true;
		}
		else
		{
			printf("节点创建失败！\n请检测内存是否空闲！\n");
			return false;
		}
	}
	else
	{
		printf("请输入空指针，避免出现内存丢失！\n");
		return false;
	}
}


//添加节点 
bool Add_Node(char *pname, SLIST *phead)
{
	int id;
	SLIST *move;
	move = phead;

	//查找到最后一个节点 
	while (move->NEXT){
		move = move->NEXT;
	}
	//调用创建节点函数  创建一个新节点
	//并让链表的最后一个节点指针指向新节点 
	if (Creat_Node(pname, &move->NEXT))
	{
		id = move->ID; 			//获取最后节点的ID
		move = move->NEXT; 		//move指针 指向 新节点
		move->ID = id + 1;      //给新节点ID
		return true;
	}
		printf("添加节点失败！\n");
		return false;
}


//插入节点 
bool Input_Node(unsigned int id, char *pname, SLIST *phead)
{
	SLIST *move, *pinput_node;
	move = phead;
	pinput_node = NULL;

	//表头不能修改 
	if (id)
	{
		//使move指针指向id所在节点的上一个节点 
		while (id != (move->ID + 1))
		{
			move = move->NEXT;
			if (NULL == move->NEXT)
			{
				printf("当前已是最后的节点，ID为%d\n", move->ID);
				printf("插入节点将变为添加节点！\n");
				Add_Node(pname, phead);
				return true;
			}
		}
		/************节点插入************/
		//调用创建节点函数  创建新节点	
		Creat_Node(pname, &pinput_node);
		pinput_node->ID = id;					//将id放入新节点 
		pinput_node->NEXT = move->NEXT;		//新节点关联id所在的原节点 
		move->NEXT = pinput_node;		//上一个节点与新节点关联

		//维护id的唯一性
		move = pinput_node->NEXT;
		while (move)
		{
			move->ID = move->ID + 1;
			move = move->NEXT;
		}
		/************节点插入************/
		return true;
	}
		printf("不能修改表头！\n");
		return false;
}


//删除节点
bool Delete_Node(unsigned int id, SLIST *phead)
{
	SLIST *move, *del;
	move = phead;
	if (id)
	{
		//使move指针指向 要删除的节点的上一个节点
		while (id != (move->ID + 1))
		{
			move = move->NEXT;
			if (NULL == move->NEXT)
			{
				printf("当前已是最后的节点，ID为%d\n", move->ID);
				printf("请正确输入ID！\n");
				return false;
			}
		}
		/************节点删除************/
		//del指针 指向 要删除的节点 
		del = move->NEXT;
		//使上一个节点 关联 要删除的节点的下一个节点 
		move->NEXT = del->NEXT;
		free(del->NAME);  //释放数据内存
		free(del);   //删除节点
		//维护ID的连续性
		move = move->NEXT;
		while (move)
		{
			move->ID = move->ID - 1;
			move = move->NEXT;
		}
		/************节点删除************/
		return true;
	}
	printf("要删除表头，请直接销毁链表！\n");
	return false;
}


//查询节点
bool Find_Node(char *pname, SLIST *phead, SLIST *paccept_node)
{
	SLIST *move;
	int namelen = strlen(pname) + 1;
	move = phead;
	if (move)  //判断是否有链表 
	{
		if (move->ID)  //判断是否是链表的头指针 
		{
			printf("请输入头指针！\n");
			return false;
		}
		//进行字符查询
		while (strcmp(move->NAME, pname))
		{
			if (move->NEXT)
			{
				move = move->NEXT;
			}
			else
			{
				printf("当前链表没有该字符串！\n");
				return true;
			}
		}
		//将数据拷贝出去
		paccept_node->ID = move->ID;		//节点ID拷贝
		paccept_node->NAMELEN = move->NAMELEN;	//字符长度值拷贝
		//字符拷贝  先为指针开辟内存，再进行拷贝
		paccept_node->NAME = (char*)malloc(strlen(move->NAME) + 1);
		strcpy(paccept_node->NAME, move->NAME);	
		paccept_node->NEXT = NULL;   //节点的指针不返回
		printf("该字符串在链表中的ID为%d\n", move->ID);
		return true;
	}
	printf("当前没有链表，请正确输入头指针！\n");
	return false;
}


//创建链表 
SLIST *Creat_Slist()
{
	SLIST *phead = NULL;
	Creat_Node("链表表头", &phead);
	phead->ID = 0;
	return phead;
}


//显示链表
bool Show_Slist(SLIST *phead)
{
	SLIST *move;
	move = phead;
	//判断是否有链表
	if (move)
	{
		//判断是否是头指针
		if (move->ID)
		{
			printf("请输入头指针！\n");
			return false;
		}
		do
		{
			//显示节点信息
			printf("ID:%d\tnamelen:%d\tname:%s\n", move->ID, move->NAMELEN, move->NAME);
		} while (move = move->NEXT); //遍历链表
		return true;
	}
	printf("当前没有链表！\n");
	return true;
}

//销毁链表
bool Clean_Slist(SLIST **pphead)
{
	SLIST *move, *del;
	move = *pphead;
	if (move)  				//判断是否有链表 
	{
		if (move->ID)  		//判断是否是链表的头指针 
		{
			printf("请输入头指针！\n");
			return false;
		}
		/******************链表销毁******************/
		while (del = move)  //del指针移到要删除的节点
		{
			move = move->NEXT;	//move指针移到下一个节点
			free(del->NAME);  //释放数据内存
			free(del);		  //删除节点
		}
		*pphead = NULL;  //头指针清零
		/******************链表销毁******************/
		printf("链表销毁完毕！\n");
		return true;
	}
	printf("当前没有链表，无需销毁！\n");
	return true;
}
