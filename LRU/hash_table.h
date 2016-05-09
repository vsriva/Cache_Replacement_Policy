#include<stdio.h>
#include<stdlib.h>
struct block
{
    int tag;
    //char data[512];
    int data;
    struct block *prev;
    struct block *next;
};


struct block **hash_table1[1000][100];
struct block **hash_table2[1000][100];
struct block **hash_table3[1000][100];
struct block **hash_table4[1000][100];

//int *hash_table1[999][99];
//int *hash_table2[999][99];
//int *hash_table3[999][99];
//int *hash_table4[999][99];


int cal_row(int key)
{
    while(key>=1000)
    {
        key /=10;
    }
    return key;
}
int cal_col(int key)
{
    while(key>=100000)
    {
        key /=10;
    }
    return key%100;
}
int addr(int key)
{
    int a,count=0;
    a=key;
    while(key>=100000)
    {
        key /=10;
        count++;
    }
    while(count--)
    {
        key *=10;
    }

    return (a-key);
}

struct block *hash_search(int key,int table)
{
    int row=0,column=0,address=0;
    column=cal_col(key);
    row=cal_row(key);
    address=addr(key);
    if (table==1)
    {
        if (hash_table1[row][column] !=NULL)
        {
            return *(hash_table1[row][column] + address);
        }
    }
    else if (table==2)
    {
        if (hash_table2[row][column] !=NULL)
        {
            return *(hash_table2[row][column] + address);
        }
    }
    else if (table==3)
    {
        if (hash_table3[row][column] !=NULL)
        {
            return *(hash_table3[row][column] + address);
        }
    }
    else if (table==4)
    {
        if (hash_table4[row][column] !=NULL)
        {
            return *(hash_table4[row][column] + address);
        }
    }
    else
    {
        printf("\nHash Table missing!");
    }


    return 0;
}

int hash_display(int key,int table)
{
    int row=0,column=0,address=0;
    column=cal_col(key);
    row=cal_row(key);
    address=addr(key);
    if (table==1)
    {
        if (hash_table1[row][column] !=NULL)
        {
            printf("\nDisplay Table:%d Value:%x",table,*((hash_table1[row][column]) + address));
        }
    }
    else if (table==2)
    {
        if (hash_table2[row][column] !=NULL)
        {
            printf("\nDisplay Table:%d Value:%x",table,*((hash_table2[row][column]) + address));
        }
    }
    else if (table==3)
    {
        if (hash_table3[row][column] !=NULL)
        {
            printf("\nDisplay Table:%d Value:%x",table,*((hash_table3[row][column]) + address));
        }
    }
    else if (table==4)
    {
        if (hash_table4[row][column] !=NULL)
        {
            printf("\nDisplay Table:%d Value:%x",table,*((hash_table4[row][column]) + address));
        }
    }
    else
    {
        printf("\nHash Table missing!");
    }
    return 0;
}

int hash_insert(int key, struct block *node, int table)
{
    int row=0,column=0,address=0;
    column=cal_col(key);
    row=cal_row(key);
    address=addr(key);
    if (table==1)
    {
        //printf("Tab:1");
        if (hash_table1[row][column]==NULL)
        {
            //printf("First");
            hash_table1[row][column]=(struct block **)calloc(1000,sizeof(struct block *));
            *((hash_table1[row][column]) + address)=node;

        }
        else
        {
            *((hash_table1[row][column]) + address)=node;
        }
    }
    else if (table==2)
    {
        if (hash_table2[row][column]==NULL)
        {
            hash_table2[row][column]=(struct block **)calloc(1000,sizeof(struct block *));
            *((hash_table2[row][column]) + address)=node;
        }
        else
        {
            *((hash_table2[row][column]) + address)=node;
        }
    }
    else if (table==3)
    {
        if (hash_table3[row][column]==NULL)
        {
             hash_table3[row][column]=(struct block **)calloc(1000,sizeof(struct block *));
            *((hash_table3[row][column]) + address)=node;
        }
        else
        {
            *((hash_table3[row][column]) + address)=node;
        }
    }

    else if (table==4)
    {
        if (hash_table4[row][column]==NULL)
        {
            hash_table4[row][column]=(struct block **)calloc(1000,sizeof(struct block *));
            *((hash_table4[row][column]) + address)=node;
        }
        else
        {
            *((hash_table4[row][column]) + address)=node;
        }
    }
    else
    {
        printf("\nHash Table missing!");
    }

    return 0;
}

int hash_remove(int key, int table)
{
    int row=0,column=0,address=0;
    column=cal_col(key);
    row=cal_row(key);
    address=addr(key);
    if (table==1)
    {
        if (hash_table1[row][column] !=NULL)
        {
            *((hash_table1[row][column]) + address)=NULL;
        }
    }
    else if (table==2)
    {
        if (hash_table2[row][column] !=NULL)
        {
            *((hash_table2[row][column]) + address)=NULL;
        }
    }
    else if (table==3)
    {
        if (hash_table3[row][column] !=NULL)
        {
            *((hash_table3[row][column]) + address)=NULL;
        }
    }
    else if (table==4)
    {
        if (hash_table4[row][column] !=NULL)
        {
            *((hash_table4[row][column]) + address)=NULL;
        }
    }
    else
    {
        printf("\nHash Table missing!");
    }
    return 0;
}

//int main()
//{
//    struct block nodes[100];
//    //printf("\nP0 %x",&nodes[0]);
//
//    hash_insert(2230556,&nodes[0],1);
//    //printf("\nP1");
//    hash_display(2230556,1);
//    hash_insert(2230524,&nodes[1],1);
//    //printf("\nP2");
//    hash_display(2230556,1);
//    hash_insert(2230556,&nodes[2],1);
//    //printf("\nP3");
//    hash_display(2230556,1);
//    hash_insert(1228920,&nodes[3],1);
//    //printf("\nP4");
//
//    hash_display(1228928,1);
//    hash_insert(1228928,&nodes[4],1);
//    //printf("\nP5");
//    hash_display(1228928,1);
//    hash_remove(1228928,1);
//    //printf("\nP6");
//    hash_display(1228928,1);
//
//    printf("\nSearch: Table:%d Return:%x",1,hash_search(2230556,1));
//    hash_display(2130678,1);
//    return 0;
//}
