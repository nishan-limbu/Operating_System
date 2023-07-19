#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int work[MAX_RESOURCES];
int finish[MAX_PROCESSES];

int num_processes, num_resources;

void input()
{
    int i, j;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter the available resources: ");
    for (i = 0; i < num_resources; i++)
        scanf("%d", &available[i]);

    printf("Enter the maximum resources required by each process: \n");
    for (i = 0; i < num_processes; i++)
    {
        printf("Process %d: ", i);
        for (j = 0; j < num_resources; j++)
            scanf("%d", &maximum[i][j]);
    }

    printf("Enter the resources allocated to each process: \n");
    for (i = 0; i < num_processes; i++)
    {
        printf("Process %d: ", i);
        for (j = 0; j < num_resources; j++)
            scanf("%d", &allocation[i][j]);
    }
}

void calculate_need()
{
    int i, j;

    for (i = 0; i < num_processes; i++)
    {
        for (j = 0; j < num_resources; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

int is_safe_state()
{
    int i, j, k;

    for (i = 0; i < num_resources; i++)
        work[i] = available[i];

    for (i = 0; i < num_processes; i++)
        finish[i] = 0;

    int safe_sequence[MAX_PROCESSES];
    int sequence_count = 0;

    for (i = 0; i < num_processes; i++)
    {
        for (j = 0; j < num_processes; j++)
        {
            if (finish[j] == 0)
            {
                int can_execute = 1;
                for (k = 0; k < num_resources; k++)
                {
                    if (need[j][k] > work[k])
                    {
                        can_execute = 0;
                        break;
                    }
                }

                if (can_execute)
                {
                    for (k = 0; k < num_resources; k++)
                        work[k] += allocation[j][k];

                    finish[j] = 1;
                    safe_sequence[sequence_count++] = j;
                }
            }
        }
    }

    if (sequence_count == num_processes)
    {
        printf("Safe state sequence: ");
        for (i = 0; i < num_processes - 1; i++)
            printf("P%d -> ", safe_sequence[i]);
        printf("P%d\n", safe_sequence[num_processes - 1]);

        return 1;
    }
    else
    {
        printf("Unsafe state - deadlock detected!\n");
        return 0;
    }
}

int request_resources(int process_id, int request[])
{
    int i;
    for (i = 0; i < num_resources; i++)
    {
        if (request[i] > need[process_id][i])
        {
            printf("Invalid request! Requested resources exceed the maximum required.\n");
            return -1;
        }

        if (request[i] > available[i])
        {
            printf("Insufficient resources available. Process P%d must wait.\n", process_id);
            return 0;
        }
    }

    for (i = 0; i < num_resources; i++)
    {
        available[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }

    if (is_safe_state())
        return 1;
    else
    {
        for (i = 0; i < num_resources; i++)
        {
            available[i] += request[i];
            allocation[process_id][i] -= request[i];
            need[process_id][i] += request[i];
        }

        return 0;
    }
}

int main()
{
    input();
    calculate_need();

    printf("\nInitial State:\n");
    printf("Available resources: ");
    for (int i = 0; i < num_resources; i++)
        printf("%d ", available[i]);
    printf("\n");

    printf("Maximum resources:\n");
    for (int i = 0; i < num_processes; i++)
    {
        printf("Process %d: ", i);
        for (int j = 0; j < num_resources; j++)
            printf("%d ", maximum[i][j]);
        printf("\n");
    }

    printf("Allocated resources:\n");
    for (int i = 0; i < num_processes; i++)
    {
        printf("Process %d: ", i);
        for (int j = 0; j < num_resources; j++)
            printf("%d ", allocation[i][j]);
        printf("\n");
    }

    if (is_safe_state())
    {
        int process_id;
        int request[MAX_RESOURCES];

        printf("\nEnter the process ID for resource request: ");
        scanf("%d", &process_id);

        printf("Enter the resource request for Process %d: ", process_id);
        for (int i = 0; i < num_resources; i++)
            scanf("%d", &request[i]);

        request_resources(process_id, request);
    }

    return 0;
}
