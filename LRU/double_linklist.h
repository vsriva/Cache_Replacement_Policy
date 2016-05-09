#include<stdio.h>
#include<stdlib.h>
#include "hash_table.h"


//struct block *search(int block_no, struct block *head, struct block *tail, int table)
//{
//
//    if (hash_search(block_no,table)==1)
//    {
//        printf("\nFound");
//        while((head != NULL))
//        {
//            //printf("The output:%d,%d,%d,%d\n",(head->start_blk),(head->no_of_block),(head->ign),(head->req_no));
//            printf("\nSearch:%d,  %d",block_no,head->tag);
//            if(head !=NULL)
//            {
//                if (head->tag == block_no)
//                {
//                    return head;
//                }
//                head=head->next;
//
//            }
////            if(tail != NULL)
////            {
////                if (tail->tag == block_no)
////                {
////                    return tail;
////                }
////                tail=tail->prev;
////
////            }
//
//        }
//        printf("\nDone");
//    }
//    else
//    {
//        return NULL;
//    }
//    return NULL;
//}

struct block *push(int block_no, int data, struct block **head,struct block **tail,int table)
{
    struct block *temp;
    temp=(struct block *) malloc( sizeof(struct block) );
    temp->tag=block_no;
    temp->data=data;
    temp->next=*head;
    temp->prev=NULL;
    //printf("Assign");

    if(*head == NULL)
    {
        //printf("Head null");
        *head=temp;
        *tail=temp;

    }
    else
    {
        (*head)->prev=temp;
        *head=temp;
    }
    hash_insert((*head)->tag,*head,table);
    return *head;

}

int pop(struct block **tail, struct block **head,int table)
{
    struct block *temp=NULL;
    int value=0;

    if(*tail==NULL)
    {
        printf("\nTail is NULL");
        return -1;
    }
            //printf("\nOH tail:%x head:%x",*tail,*head);

    if(*head==*tail)
    {
        //printf("\nhead==tail");

        temp=*tail;
        *head=NULL;
        *tail=NULL;
        value=temp->tag;
        hash_remove(temp->tag,table);

        free(temp);
        //printf("\nPopped");
        return value;
    }
    else
    {
        temp=*tail;
    //if (tail->prev != NULL)

        //printf("OH");
        //printf("\nOH now:%x next:%x prev:%x",*tail,(*tail)->next,(*tail)->prev);

        *tail=(*tail)->prev;
        //printf("\nOH now:%x next:%x prev:%x",*tail,NULL,(*tail)->prev);

        (*tail)->next=NULL;
        //printf("\nOH");
        hash_remove(temp->tag,table);
        //printf("\ntail:%d",(*tail)->tag);
        value=temp->tag;
        free(temp);
        //printf("\nPopped");

        return value;

    }

}

int list_length(struct block *head)
{
    int len=0;
    while(head != NULL)
    {
        len++;
        head=head->next;
    }
    return len;

}

struct block *remove_push(struct block **ins_head, struct block **head, struct block *node, struct block **ins_tail,struct block **tail,int ins_tab,int tab)
{
    int value=0;
    struct block *temp=NULL;
    temp=node;
    if (temp == NULL)
    {
        printf("\nInvalid Entry!");
        return *ins_head;
    }
    if (temp==*ins_head)
    {
        return *ins_head;
    }
    if (temp == *head)
    {
        *head=(*head)->next;
        (*head)->prev=NULL;
        temp->next=*ins_head;
        (*ins_head)->prev=temp;
        *ins_head=temp;
        return *ins_head;
    }
    if (*head==*tail)
    {
        value=pop(tail,head,tab);
        *ins_head=push(value,0,ins_head,ins_tail,ins_tab);
    }
    else
    {
        node=node->prev;
        node->next=temp->next;
        node->next->prev=node;
        value=temp->tag;

        hash_remove(value,tab);
        free(temp);
        *ins_head=push(value,0,ins_head,ins_tail,ins_tab);
    }

    return *ins_head;

}

int list_unio(struct block *head1,struct block *head2,struct block *tail1,struct block *tail2,int H1,int H2)
{
    struct block *head_L1=NULL,*tail_L1=NULL,*node=NULL;
    int length=0;
    while(head1 != NULL)
    {
        head_L1=push(head1->tag,0,&head_L1,&tail_L1,5);
        head1=head1->next;
        length++;
    }
    while(head2 != NULL)
    {
        node=hash_search(head2->tag,H1);
        if(node == NULL)
        {
            head_L1=push(head2->tag,0,&head_L1,&tail_L1,5);
            length++;
        }
        head2=head2->next;
     }

     return length;

}

int print(struct block *head)
{
    printf("\n\nDisplay  ");
    while(head != NULL)
    {
        printf("%x:%d->",head,head->tag);
        head=head->next;
    }
    return 0;

}


//int main()
//{
//    struct block *found, *head=NULL, *sea=NULL, *tail=NULL;
//
////    head=(struct block *) malloc( sizeof(struct block) );
////    head->tag=-1;
////    tail=head;
//    head=push(23,0,head,&tail,1);
//
//    tail=head;
//        printf("\nUpdate1 node:%x %x",(tail),head);
//    tail=pop(tail,&head,1);
//        printf("\nUpdate2 node:%x %x",(tail),head);
//        print(head);
//    head=push(22,0,head,&tail,1);
//        printf("\nUpdate3 node:%x %x",(tail),head);
//        print(head);
//    head=push(21,0,head,&tail,1);
//        printf("\nUpdate4 node:%x %x",(tail),head);
//        print(head);
//    head=push(20,0,head,&tail,1);
//        printf("\nUpdate5 node:%x %x",(tail),head);
//        print(head);
//        printf("\nUpdate6 node:%x %x",(tail),head);
//
//    tail=pop(tail,&head,1);
////    tail=pop(tail);
//        printf("\nUpdate7 node:%x %x",(tail),head);
//
//    head=push(19,0,head,&tail,1);
//        printf("\n23Update8 node:%x %x",(tail),head);
//    sea=search(23,head,tail,1);
//        printf("\nUpdate9 node:%x %x",(tail),head);
//    head=remove_push(head,sea,&tail);
//        printf("\nUpdate10 node:%x %x",(tail),head);
//
//    sea=search(22,head,tail,1);
//    tail=pop(tail,&head,1);
//    printf("\n helllo Update11 node:%x %x",(tail),head);
//    tail=pop(tail,&head,1);
//    printf("\nUpdate12 node:%x %x",(tail),head);
//
//    sea=search(22,head,tail,1);
//    printf("\nUpdate13 node:%x %x %x",(tail),head);
//   printf("\n Search done");
//    head=remove_push(head,sea,&tail);
//
//
//
////    printf("\n%d",sea->tag);
//
//    return 0;
//
//
//}
