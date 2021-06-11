//2021 Jun 11
//Author: Tran Trung Tin
//Receive 6 message in oder of priority
#include <unistd.h>

#include <sys/types.h>

#include <mqueue.h>

#include <fcntl.h>

#include <stdlib.h>

#include <errno.h>

#include <stdio.h>

#include <assert.h>

#include "task4_1queue.h"

int main() {
  /* Code Listing 3.8:
     Opening a POSIX message queue and retrieving a message
   */

  /* Open the message queue for reading */
  mqd_t mqd = mq_open(key, O_RDONLY);
  assert(mqd != -1);

  /* Get the message queue attributes */
  struct mq_attr attr;
  assert(mq_getattr(mqd, & attr) != -1);

  char * buffer = calloc(attr.mq_msgsize, 1);
  assert(buffer != NULL);

  /* Retrieve message from the queue and get its priority level */
  unsigned int priority = 0;
  for (int i = 0; i < MsgCount; i++) {
    queuedMessage msg;
    if ((mq_receive(mqd, (char * ) & msg, attr.mq_msgsize, & priority)) == -1)
      printf("Failed to receive message\n");
    else
      printf("Received [priority %3u]: '%s'\n", priority, (char * ) msg.payload);
  }
  /* Clean up the allocated memory and message queue */
  free(buffer);
  buffer = NULL;
  mq_close(mqd);
  return 0;
}
