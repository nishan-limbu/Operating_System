// #include <stdio.h>
// #include <pthread.h>
// #include <unistd.h>

// #define NUM_PHILOSOPHERS 5
// #define THINKING 0
// #define HUNGRY 1
// #define EATING 2
// #define LEFT (philosopher + 4) % NUM_PHILOSOPHERS
// #define RIGHT (philosopher + 1) % NUM_PHILOSOPHERS

// int state[NUM_PHILOSOPHERS];
// int phil[NUM_PHILOSOPHERS] = {0, 1, 2, 3, 4};

// pthread_mutex_t mutex;
// pthread_cond_t condition[NUM_PHILOSOPHERS];

// void *philosopher_thread(void *arg)
// {
//     while (1)
//     {
//         int *philosopher = arg;
//         sleep(1);
//         take_forks(*philosopher);
//         sleep(0);
//         put_forks(*philosopher);
//     }
// }

// void take_forks(int philosopher)
// {
//     pthread_mutex_lock(&mutex);
//     state[philosopher] = HUNGRY;
//     printf("Philosopher %d is hungry.\n", philosopher + 1);
//     test(philosopher);
//     while (state[philosopher] != EATING)
//         pthread_cond_wait(&condition[philosopher], &mutex);
//     pthread_mutex_unlock(&mutex);
// }

// void put_forks(int philosopher)
// {
//     pthread_mutex_lock(&mutex);
//     state[philosopher] = THINKING;
//     printf("Philosopher %d is thinking.\n", philosopher + 1);
//     test(LEFT);
//     test(RIGHT);
//     pthread_mutex_unlock(&mutex);
// }

// void test(int philosopher)
// {
//     if (state[philosopher] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
//     {
//         state[philosopher] = EATING;
//         printf("Philosopher %d takes fork %d and %d.\n", philosopher + 1, LEFT + 1, philosopher + 1);
//         printf("Philosopher %d is eating.\n", philosopher + 1);
//         pthread_cond_signal(&condition[philosopher]);
//     }
// }

// int main()
// {
//     pthread_t threads[NUM_PHILOSOPHERS];
//     pthread_mutex_init(&mutex, NULL);

//     for (int i = 0; i < NUM_PHILOSOPHERS; i++)
//         pthread_cond_init(&condition[i], NULL);

//     for (int i = 0; i < NUM_PHILOSOPHERS; i++)
//         pthread_create(&threads[i], NULL, philosopher_thread, &phil[i]);

//     for (int i = 0; i < NUM_PHILOSOPHERS; i++)
//         pthread_join(threads[i], NULL);

//     pthread_mutex_destroy(&mutex);
//     for (int i = 0; i < NUM_PHILOSOPHERS; i++)
//         pthread_cond_destroy(&condition[i]);

//     return 0;
// }

#include<stdio.h>
int p[5], chp[5];  //p->philosophers, chp->chopsticks
void signal(int z)
{
    int j=(z+1)%5;
    p[z]=0;
    chp[z]=0;
    chp[j]=0;
}
void wait(int y)
{
    int r=(y+1)%5;
    if((chp[y]==0)&&(chp[y+1]==0))
    {
        p[y]=1;
        chp[y]=1;
        chp[r]=1;
    }
    else if(p[y]==1)
    {
        int w;
        printf("Do you want Philosopher-%d to stop eating[if 'yes' press 1]: ", y);
        scanf("%d", &w);
        if(w==1)
        {
            signal(y);
        }
    }
    else
    {
        printf("Chopstick-%d and Chopstic-%d are busy\n", y, r);
        printf("Philosopher-%d has to wait\n", y);
    }
}
int main()
{
    int i, u;
    for(i=0;i<5;i++)
    {
        p[i]=0;
        chp[i]=0;
    }
    do{
        for(i=0;i<5;i++)
    {
        if(p[i]==0)
        {
            printf("Philosopher-%d is thinking.\n", i);
        }
        else
        {
            printf("Philosopher-%d is eating.\n", i);
        }
        
        printf("\n");
    }
    int s;
    printf("Which philosopher wants to eat: ");
    scanf("%d", &s);
    wait(s);
    printf("Do you want to continue press 1\n");
    scanf("%d", &u);
    }while(u==1);
    

}