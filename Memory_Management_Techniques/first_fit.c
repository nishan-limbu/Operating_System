#include<stdio.h>

int main()
{
    int bsize[10], psize[10], bno, pno, flags[10], allocation[10], i, j;
    
    for(i=0;i<10;i++)
    {
        flags[i]=0;
        allocation[i]=-1;
    }

    printf("Enter no. of blocks: ");
    scanf("%d", &bno);

    printf("Enter size of each block: ");
    for(i=0;i<bno;i++)
    {
        scanf("%d", &bsize[i]);
    }
    printf("Enter no. of processes: ");
    scanf("%d", &pno);
    printf("Enter size of each process: ");
    for(i=0;i<pno;i++)
    {
        scanf("%d", &psize[i]);
    }

    for(i=0;i<pno;i++)//allocation as per first fit
    {
        for(j=0;j<bno;j++)
        {
            if(flags[j]==0 && bsize[j]>=psize[i])
            {
                allocation[j]= i;
                flags[j]=1;
                break;
            }
        }
    }
    //display allocation details:
    printf("\nBlock no\tSize\t\tProcess no.\t\tSize");
    for(i=0;i<bno;i++)
    {
        printf("\n%d\t\t%d\t\t", i+1, bsize[i]);
        if(flags[i]==1)
        {
            printf("%d\t\t%d", allocation[i]+1, psize[allocation[i]]);
        }
        else
        {
            printf("Not allocated");
        }
    }

    return 0;
}