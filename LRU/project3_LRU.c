#include<stdio.h>
#include<stdlib.h>
#include "double_linklist.h"
#include<time.h>
#include<string.h>

//Structure used to store file contents
struct file_con
{
    int start_blk;
    int no_of_block;
    int ign;
    int req_no;
    struct file_con *next;
};

//Function to read file and store it in a list
struct file_con *file_enter(char *filename)
{

    FILE *fp;

    struct file_con *test,*head,*top;
    test = (struct file_con *) malloc( sizeof(struct file_con) );
    head=test;
    top=test;
    fp=fopen(filename,"r");
    while (fscanf(fp,"%d %d %d %d",&(test->start_blk),&(test->no_of_block),&(test->ign),&(test->req_no))==4)
    {
        test->next= (struct file_con *) malloc( sizeof(struct file_con) );
        test=test->next;

    }
    test->next=NULL;

    fclose(fp);

    return top;
}


//Calaculate no of bits for a no.
int bit_size(int c)
{
    int count=0;
    while(c != 0)
    {
        c=(c>>1);
        count++;
    }
    return count;
}

//To provide starting block
struct block *start_blk(struct block *head)
{
    head=(struct block *) malloc( sizeof(struct block) );
    head->next=NULL;
    return head;
}

//Function where LRU algorithm is implemented
int LRU(int c, char *filename,struct file_con *top)//make it read from link list
{
    int tag;
    int no_of_blk;
    int ign;
    int req_no;
    int block_no;
    struct block *found=NULL, *head=NULL, *tail;
    int miss=0;
    int count=0,entry=0;
    int i=0;
    FILE *fp;
    float no_of_request=0;
    float hit_ratio=0;

    while(top->next != NULL)
    {
        tag=top->start_blk;
        no_of_blk=top->no_of_block;
        ign=top->ign;
        req_no=top->req_no;
        no_of_request +=no_of_blk;
        for (i=0;i<no_of_blk;i++)
        {

            block_no =tag+i;

            found=hash_search(block_no,1);

            if (found==NULL)
            {
                miss++;
                if (count<c)
                {
                    if (head == NULL)
                    {
                        head=push(block_no,0,&head,&tail,1);
                        count ++;
                    }
                    else
                    {
                        head=push(block_no,0,&head,&tail,1);
                        count ++;
                    }

                }
                else
                {
                    pop(&tail,&head,1);
                    head=push(block_no,0,&head,&tail,1);
                }

            }
            else
            {
                if (found->next != NULL)
                {
                    head=remove_push(&head,&head,found,&tail,&tail,1,1);

                }
            }
        }
        top=top->next;

    }

    hit_ratio=(no_of_request- miss)/no_of_request;
    printf("\nNo.of requests:%f\nHit ratio:%f",no_of_request,hit_ratio);
    return miss;
}

int main (int argc, char *argv[])
{
    if ( argc != 3 ) /* argc should be 3 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf( "\nMissing arguments!!\nUsage: ./project3.o <Trace_file_name> <size_of_cache> ");
        return 0;
    }
    else
    {
        printf("\nNote: This program is guaranteed to work on P3.lis with 2048 cache size");
    }

    char *filename=argv[1];

    clock_t begin, end, full_begin, full_end;
    double time_spent,tot_time_spent;
    struct file_con *top;
    int cache_size=0;
    printf("\nFile:%s",filename);
    top=file_enter(filename);
    if (strcmp(argv[2],"1024")==0)
    {
        cache_size=1024;
    }
    else if(strcmp(argv[2],"2048")==0)
    {
        cache_size=2048;
    }
    else if(strcmp(argv[2],"4096")==0)
    {
        cache_size=4096;
    }
    else if(strcmp(argv[2],"8192")==0)
    {
        cache_size=8192;
    }
    else if(strcmp(argv[2],"16384")==0)
    {
        cache_size=16384;
    }
    else if(strcmp(argv[2],"32768")==0)
    {
        cache_size=32768;
    }
    else if(strcmp(argv[2],"65536")==0)
    {
        cache_size=65536;
    }
    else if(strcmp(argv[2],"131072")==0)
    {
        cache_size=131072;
    }
    else if(strcmp(argv[2],"262144")==0)
    {
        cache_size=262144;
    }
    else if(strcmp(argv[2],"524288")==0)
    {
        cache_size=524288;
    }
    else
    {
        printf("\nInvalid cache size entered. Working with default: cache_size=2048");
        cache_size=2048;
    }

        full_begin = clock();

        begin = clock();
        printf("\nStarting for cache size:%d",cache_size);
        printf("\nNo. of Misses:%d",LRU(cache_size,filename,top));
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        printf("\nOK,Time:%lf",time_spent);

        full_end=clock();
        tot_time_spent = (double)(full_end - full_begin) / CLOCKS_PER_SEC;

        printf("\nComplete Time:%lf\n",tot_time_spent);


    return 0;
}
