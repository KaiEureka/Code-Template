#include <stdio.h>
#include <stdlib.h>
struct cell 
{
 int x;
 struct cell* next;
};
struct cell* build(void) 
{
 	struct cell* head;
 	head = NULL;
 	int n;
 	scanf("%d",&n);
 	if(n==0)return head;
	head=(struct cell *)malloc(sizeof(struct cell *));
	head->x=n;
	head->next=build();
	return head;
}
void print(struct cell* head) //打印以head为头的链表，数据用空格分隔，结尾无空格
{
	if(head!=NULL)printf("%d",head->x);
	if(head->next!=NULL)
	{
		printf(" ");
		print(head->next);
	}
}



void release(struct cell* head) //释放链表空间
{
	if(head!=NULL&&head->next!=NULL)release(head->next);
	if(head!=NULL)free(head);
}
int find(struct cell* head,int num)//从以head为头的链表中寻找num，找到了就返回1，否则返回0
{
	if(head==NULL)return 0;
	if(head->x==num)return 1;
	if(head->next==NULL)return 0;
	else return find(head->next,num);
}
struct cell* del(struct cell* head,int n)//从以head为头的链表中删去n
{
	if(head==NULL)return NULL;
	if(head->x!=n)
	{
		if(head->next!=NULL)head->next=del(head->next,n);
		return head;
	}
	if(head->next!=NULL) head->next=del(head->next,n);
	return head->next;
}
struct cell* del1one(struct cell* head)//去重，但有重复的就保留第一个
{
	if(head!=NULL&&head->next!=NULL)
	{
		if(find(head->next,head->x)==1)
		{
			head->next=del(head->next,head->x);
		}
		head->next=del1one(head->next);
	}
	return head;
}
struct cell* del2one(struct cell* head)//去重，但有重复的就保留最后一个
{
	if(head!=NULL&&head->next!=NULL)
	{
		if(find(head->next,head->x)==1)
		{
			head->next=del2one(head->next);
			return head->next;
		}
		else 
		{
			head->next=del2one(head->next);
			return head;
		}
	}
	if(head!=NULL&&head->next==NULL)return head;
	return NULL;
}
int getlen(struct cell* head)//取以head为头的链表的长度
{
	if(head==NULL)return 0;
	if(head->next==NULL)return 1;
	else return 1+getlen(head->next);
}
struct cell* getnode(struct cell* head,int index)//取以head为头的链表的第index元素的指针，将头视为第一个元素，越界就返回NULL
{
	if(head==NULL)return NULL;
	if(index==1)return head;
	else return getnode(head->next,index-1);
}
void listsort(struct cell* head)
{
	struct cell *temp,*lpi=NULL,*lpj=head;
	for(struct cell * pi=head;pi->next!=NULL;pi=pi->next)
	{
		for(struct cell * pj=pi->next;pj!=NULL;pj=pj->next)
		{
			if( pi->x > pj->x )
			{
				int t=pi->x;
				pi->x=pj->x;
				pj->x=t;
			}
		}
	}
}
int main(void) 
{
	
	return 0;
}