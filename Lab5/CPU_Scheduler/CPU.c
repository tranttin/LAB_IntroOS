/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include <stdio.h>

#include "task.h"

// run this task for the specified time slice
void run(Task *task, int start, int slice) {
    printf("Running task = [%s] [%d] [%d] [%d] from %d to %d.\n",task->name, task->priority, task->arrival, task->burst, start, slice+start);
}
