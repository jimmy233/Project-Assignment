#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP];
static WP *head, *free_;

void init_wp_pool() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_pool[i].NO = i;
		wp_pool[i].next = &wp_pool[i + 1];
	}
	wp_pool[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */
WP* new_wp()
{
   WP *new=free_;
   free_=free_->next;
   new->next=NULL;
   return new;   
}
void free_wp(WP *wp)
{
		wp->next=free_;
		wp=free_;
}

void Create(char *expression)
{
  bool a=true;
  uint32_t number=expr(expression,&a);
  WP *new=new_wp();
  if(head==NULL)
		  new->identifier=1;
  else
  {
		  int i=1;
		  WP *temp=head;
         while(temp!=NULL)
		 {
				 i++;
				 temp=temp->next;
		 }
		 new->identifier=i;
  }
  printf("Hardware watchpoint %d:%s\n",new->identifier,expression);
  new->num=number;
  strcpy(new->expr,expression);
  WP *r;
  r=head;
  if(head==NULL)
  {
		  head=new;
  }
  else
  {
     while(r->next!=NULL)
			 r=r->next;
     r->next=new;
  }
 
}

void pinfo()
{
   WP *temp=head;
   if(temp==NULL)
   {
		   printf("You have not set watchpoints!\n");
   }
   else
   { 
		   printf("Num   Type     Disp Enb Address     What\n");
      while(temp!=NULL)
	  {
           printf("%d   hw watchpoint  keep y          %s\n",temp->identifier,temp->expr);
		   temp=temp->next;
	  }
     
   }
}

void delete(int i)
{
   WP *temp=NULL;
   if(head->identifier==i)
   {
		   temp=head;
		   head=head->next;
		   temp->next=NULL;
		   free_wp(temp);
   }
   else
   {
     WP *current=head;
     while(current->next!=NULL)
	 {
	   		 
	     if(current->next->identifier==i)
		{
             temp=current->next;
			 current->next=temp->next;
			 temp->next=NULL;
			 free_wp(temp);
		}	   
	 }	 
   }
}

bool ChangeorNot()
{
		if(head==NULL)
				return true;
		WP *temp;
        uint32_t tm;
		temp=head;
		bool success=true;
	while(temp!=NULL)
	{			
	   tm=expr(temp->expr,&success);
 	   if(tm!=temp->num)
			 return false;
	   temp=temp->next;   
	}	
    return true;         
}
void Scan()
{
     WP *temp1;
	 uint32_t tm;
	 temp1=head;
	 bool success=true;
	 while(temp1!=NULL)
	 {
			 tm=expr(temp1->expr,&success);
			 if(tm!=temp1->num)break;
	 }
     uint32_t f=expr(temp1->expr,&success);
     printf("Old value:%d\n",temp1->num);
	 printf("New value:%d\n",f);
	 temp1->num=f;
}

