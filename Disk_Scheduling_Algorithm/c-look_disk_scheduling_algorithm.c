#include <stdio.h>
#include <stdlib.h>

void clook(int requests[], int num_requests, int start)
{
    int i, j, temp, current, total_head_movement = 0;

    // Sort the requests in ascending order
    for (i = 0; i < num_requests - 1; i++)
    {
        for (j = i + 1; j < num_requests; j++)
        {
            if (requests[i] > requests[j])
            {
                temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    int current_index = 0;
    for (i = 0; i < num_requests; i++)
    {
        if (requests[i] >= start)
        {
            current_index = i;
            break;
        }
    }

    printf("C-LOOK Sequence: ");

    // Process requests to the right of the current head position
    for (i = current_index; i < num_requests; i++)
    {
        current = requests[i];
        printf("%d ", current);
        total_head_movement += abs(current - start);
        start = current;
    }

    // Process requests from the beginning of the disk to the current head position
    for (i = 0; i < current_index; i++)
    {
        current = requests[i];
        printf("%d ", current);
        total_head_movement += abs(current - start);
        start = current;
    }

    printf("\nTotal Head Movement: %d\n", total_head_movement);
}

int main()
{
    int num_requests, start;

    printf("Enter the number of disk requests: ");
    scanf("%d", &num_requests);

    printf("Enter the starting position of the disk head: ");
    scanf("%d", &start);

    int requests[num_requests];

    printf("Enter the disk requests: ");
    for (int i = 0; i < num_requests; i++)
        scanf("%d", &requests[i]);

    clook(requests, num_requests, start);

    return 0;
}
