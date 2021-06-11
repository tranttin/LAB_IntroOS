//2021 Jun 11
//Author: Tran Trung Tin
//Send 6 message with different priority
#include <unistd.h>

#include <sys/types.h>

#include "task4_1queue.h"

#include <mqueue.h>

#include <fcntl.h>

#include <stdlib.h>

#include <errno.h>

#include <stdio.h>

#include <string.h>

int main() {

  /* Create and open a message queue for writing */
  mqd_t mqd = mq_open(key, O_CREAT | O_WRONLY, 0666, NULL);

  /* Ensure the creation was successful */
  if (mqd == -1) {
    perror("mq_open");
    exit(1);
  }

  char * payloads[] = {
    "Just a note: buy candies at Circle K",
    "Urgent: Visit doctor to examine COVID-19",
    "Just a note: VN football match 23h tonight",
    "Remainder: send files to company",
    "ASAP: call me back",
    "Urgent: Deadline IntroOS this afternoon"
  };
  int priority[] = {
    0,
    10,
    0,
    10,
    255, //depends on system, might 32767
    25
  }; /* each must be >= 0 */

  for (int i = 0; i < MsgCount; i++) {
    /* build the message */
    queuedMessage msg;
    msg.priority = priority[i];
    strcpy(msg.payload, payloads[i]);
    mq_send(mqd, (const char * ) & msg, sizeof(msg), msg.priority);
  }
  mq_close(mqd);
  return 0;
}
