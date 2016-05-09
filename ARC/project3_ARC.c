#include<stdio.h>
#include "double_linklist_ARC.h"
#include<time.h>
#include<string.h>

#define T1 1
#define B1 2
#define T2 3
#define B2 4
#define L1 5

struct file_con
{
    int start_blk;
    int no_of_block;
    int ign;
    int req_no;
    struct file_con *next;
};

//For calculation of delta
int delta(int a, int b)
{
  if (a != 0)
      return (a > b ? 1 : b/a);
  else
    return 1;
}

//For calculation of max
int max(int a, int b)
{
      return (a > b ? a : b);
}

//For calculation of min
int min(int a ,int b)
{
      return (a < b ? a : b);
}

// Following function reads the file and stores it in linked list
struct file_con *file_enter(char *filename)
{

    FILE *fp;
    int i=0,j=0;

    struct file_con *test,*head,*top;
    test = (struct file_con *) malloc( sizeof(struct file_con) );
    head=test;
    top=test;
    fp=fopen(filename,"r");
    if(fp==NULL)
    {
        printf("\nFile not found. If possible please put file next(in same directory) to the running code.");
        exit(0);
    }
    while (fscanf(fp,"%d %d %d %d",&(test->start_blk),&(test->no_of_block),&(test->ign),&(test->req_no))==4)
    {
        test->next= (struct file_con *) malloc( sizeof(struct file_con) );
        test=test->next;

    }
    test->next=NULL;

    fclose(fp);

    return top;
}


//In this function algorithm of ARC is implemented
int ARC(int c, char *filename,struct file_con *top)
{
    int tag;
    int no_of_blk;
    int ign;
    int req_no;
    int block_no;
    struct block *head_T1=NULL, *tail_T1=NULL;
    struct block *head_B1=NULL, *tail_B1=NULL;
    struct block *head_T2=NULL, *tail_T2=NULL;
    struct block *head_B2=NULL, *tail_B2=NULL;
    struct block *head_L1=NULL, *tail_L1=NULL;
    struct block *found_T2ptr=NULL,*found_T1ptr=NULL;
    struct block *found_T1=NULL,*found_B1=NULL,*found_B2=NULL,*found_T2=NULL;

    struct block *node=NULL;
    int miss=0,hit=0;
    int count=0,entry=0;
    int rem_blk;
    int i=0,p=0,d=0;
    FILE *fp;
    float no_of_request=0;
    float hit_ratio=0;
    int mod_T1=0,mod_B1=0,mod_T2=0,mod_B2=0;
    int un=0;
    int blocks=0;
    int nod=0;


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

            found_T1=hash_search(block_no,T1);
            found_T2=hash_search(block_no,T2);
            found_B1=hash_search(block_no,B1);
            found_B2=hash_search(block_no,B2);


            if (found_T1 != NULL)
            {
                hit++;
                found_T1=rem(&head_T1,found_T1,&tail_T1,T1);
                if (found_T1 != NULL)
                {
                head_T1=push(found_T1->tag,0,&head_T1,&tail_T1,T1);
                head_T2=push(found_T1->tag,0,&head_T2,&tail_T2,T2);

                }

            }
            else if (found_T2 != NULL)
            {
                hit++;
                found_T2=rem(&head_T2,found_T2,&tail_T2,T2);

                if (found_T2 != NULL)
                {
                head_T2=push(found_T2->tag,0,&head_T2,&tail_T2,T2);

                }
            }
            else if ((found_B1 != NULL))
            {
                miss++;
                mod_B1=list_length(head_B1);
                mod_B2=list_length(head_B2);
                p=min(p+delta(mod_B1,mod_B2),c);

/*Replace function is added implicitly as there were issues passing address of a NULL pointer*/
//Replace Starts
                        mod_T1=list_length(head_T1);
                        if((mod_T1 != 0)&&((mod_T1>p)||((hash_search(block_no,B2) != NULL)&&(mod_T1==p))))
                        {
                            blocks=pop(&tail_T1,&head_T1,T1);
                            if(blocks != -1)
                            head_B1=push(blocks,0,&head_B1,&tail_B1,B1);
                        }
                        else
                        {
                            blocks=pop(&tail_T2,&head_T2,T2);
                            if (blocks != -1)
                            head_B2=push(blocks,0,&head_B2,&tail_B2,B2);

                        }

//Replace Ends

                node=hash_search(block_no,B1);
                node=rem(&head_B1,node,&tail_B1,B1);
                if (found_B1 != NULL)
                head_T2=push(node->tag,0,&head_T2,&tail_T2,T2);

            }
            else if ((found_B2 != NULL))
            {
                miss++;
                mod_B1=list_length(head_B1);
                mod_B2=list_length(head_B2);
                p=min(p-delta(mod_B2,mod_B1),0);


/*Replace function is added implicitly as there were issues passing address of a NULL pointer*/
//Replace Starts

                        mod_T1=list_length(head_T1);
                        if((mod_T1 != 0)&&((mod_T1>p)||((hash_search(block_no,B2) != NULL)&&(mod_T1==p))))
                        {
                            blocks=pop(&tail_T1,&head_T1,T1);
                            if(blocks != -1)
                            head_B1=push(blocks,0,&head_B1,&tail_B1,B1);

                        }
                        else
                        {
                            blocks=pop(&tail_T2,&head_T2,T2);
                            if (blocks != -1)
                            head_B2=push(blocks,0,&head_B2,&tail_B2,B2);

                        }

//Replace Ends

                    node=hash_search(block_no,B2);

                    node=rem(&head_B2,node,&tail_B2,B2);
                    if(found_B2 != NULL)
                    head_T2=push(node->tag,0,&head_T2,&tail_T2,T2);

                }
                else
                {
                    miss++;
                    un=list_unio(head_T1,head_B1,tail_T1,tail_B1,T1,B1);
                    if(un==c)
                    {
                        if(list_length(head_T1)<c)
                        {
                            pop(&tail_B1,&head_B1,B1);



/*Replace function is added implicitly as there were issues passing address of a NULL pointer*/
//Replace Starts

                            mod_T1=list_length(head_T1);
                            if((mod_T1 != 0)&&((mod_T1>p)||((hash_search(block_no,B2) != NULL)&&(mod_T1==p))))
                            {
                                blocks=pop(&tail_T1,&head_T1,T1);
                                if(blocks != -1)
                                head_B1=push(blocks,0,&head_B1,&tail_B1,B1);

                            }
                            else
                            {
                                blocks=pop(&tail_T2,&head_T2,T2);
                                if (blocks != -1)
                                head_B2=push(blocks,0,&head_B2,&tail_B2,B2);

                            }

//Replace Ends


                    }
                    else
                    {
                        pop(&tail_T1,&head_T1,T1);
                    }
                }
                else if(un<c)
                {
                    mod_T1=list_length(head_T1);
                    mod_T2=list_length(head_T2);
                    mod_B1=list_length(head_B1);
                    mod_B2=list_length(head_B2);

                    if((mod_T1+mod_T2+mod_B1+mod_B2)>=c)
                    {
                        if((mod_T1+mod_T2+mod_B1+mod_B2)==2*c)
                        {
                            pop(&tail_B2,&head_B2,B2);
                        }


                        mod_T1=list_length(head_T1);
                        if((mod_T1 != 0)&&((mod_T1>p)||((hash_search(block_no,B2) != NULL)&&(mod_T1==p))))
                        {
                            if(tail_T1!=NULL)
                            {
                                blocks=pop(&tail_T1,&head_T1,T1);

                            }
                            else
                            {
                                blocks=-1;
                            }
                            if(blocks != -1)
                            head_B1=push(blocks,0,&head_B1,&tail_B1,B1);
                        }
                        else
                        {
                            blocks=pop(&tail_T2,&head_T2,T2);
                            if (blocks != -1)
                            head_B2=push(blocks,0,&head_B2,&tail_B2,B2);
                         }



                    }

                }
                head_T1=push(block_no,0,&head_T1,&tail_T1,T1);
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
        printf("\nNo. of Misses:%d",ARC(cache_size,filename,top));
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        printf("\nOK,Time:%lf",time_spent);

        full_end=clock();
        tot_time_spent = (double)(full_end - full_begin) / CLOCKS_PER_SEC;

        printf("\nComplete Time:%lf",tot_time_spent);


    return 0;
}
