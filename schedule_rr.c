#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "list.h"
#include "cpu.h"
#include "task.h"
#include "schedulers.h"

struct node *head;
char *lastName = 0;

void add(char *name, int priority, int burst)
{
    Task *temp = (Task *)malloc(sizeof(Task));
    temp->name = strdup(name);
    temp->priority = priority;
    temp->burst = burst;
    insert(&head, temp);
}

void reverseList(struct node **head)
{
    struct node *prev = NULL;
    struct node *current = *head;
    struct node *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void schedule()
{
    reverseList(&head);

    int time = 0;
    int timeQuantum = 10;
    struct node *current = head; // Start with the head of the list

    while (head != NULL)
    {
        Task *task = current->task;

        // Determine burst time to execute (either full burst or timeQuantum)
        int timeSlice = task->burst <= timeQuantum ? task->burst : timeQuantum;
        run(task, timeSlice);
        time += timeSlice;
        task->burst -= timeSlice;

        if (task->burst <= 0)
        {
            // Task is complete, so remove it from the list
            struct node *toDelete = current;
            current = current->next;        // Move to the next task before deletion
            delete (&head, toDelete->task); // Delete task from list

            // Free memory to prevent leaks
            free(toDelete->task->name);
            free(toDelete->task);
            free(toDelete);
        }
        else
        {
            // Move current pointer to the next task
            current = current->next;
        }

        // If we've reached the end of the list, wrap around to the head
        if (current == NULL)
        {
            current = head;
        }

        printf("\tTime is now: %d\n", time);
    }
}