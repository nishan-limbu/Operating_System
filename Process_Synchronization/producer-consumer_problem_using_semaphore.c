#include<stdio.h>
#include<stdlib.h>

//initialize a mutex to 1
int mutex=1;

//number of full slots as 0
int full =0;

//number of empty slots as size of buffer
int empty = 10, x=0;

//function to produce an itema nd add it to the buffer
void producer()
{
    //decrease mutex value by 1
    --mutex;

    //increase the number of full slots by 1
    ++full;

    //decrease the number of empty slots by 1
    --empty;

    //item produced
    x++;
    printf("\nProducer produces item : %d", x);

    //increase mutex value by 1
    ++mutex;

}

//function to consume an item and remove it from buffer
void consumer()
{
    //decrease mutex value by 1
    --mutex;

    //decrease the number of full slots by 1
    --full;

    //increase the number of empty slots by 1
    ++emtpy;
    printf("\nConsumer consumes item: %d", x);
    x--;

    //increase mutex value by 1
    ++mutex;

}

//Driver Code
int main()
{
    int n, i;
    printf("\n1. Press 1 for Producer\n2. Press 2 for Consumer\n3.Press 3 for Exit");

    //using '#pragma omp paralled for'
    //can give wrong value due to synchronisation issues
    //'critical' specifies that code is executed by only one thread at a time i.e., only thread enters the critical section at a given time
    #pragma omp critical
    for(i=1;i>0;i++)
    {
        printf("\nEnter your choice: ");
        scanf("%d", &n);

        //switch cases
        switch(n)
        {
            case 1:
                //if mutex is 1 and empty is non-zero, then it is possible to produce
                if((mutex==1)&&(empty!=0))
                {
                    producer();
                }
                //otherwise, print buffer is full
                else
                {
                    printf("Buffer is full.");
                }
                break;
            case 2:
                //if mutex is 1 and full is non-zero, then it is possible to consume
                if((mutex==1)&&(full!=0))
                {
                    consumer();
                }
                //otherwise, print Buffer is empty
                else
                {
                    printf("Buffer is empty.");
                }
                break;
            //Exit condition
            case 3:
                exit(0);
                break;
        }
    }

    return 0;
}