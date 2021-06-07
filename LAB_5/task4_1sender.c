


#include <stdio.h>

#include <sys/ipc.h>

#include <sys/msg.h>

#include <stdlib.h>

#include <string.h>

#include "key.h"

void report_and_exit(const char * msg) {
  perror(msg);
  exit(-1); /* EXIT_FAILURE */
}

int main() {
  key_t key = ftok(PathName, ProjectId);
  if (key < 0) report_and_exit("couldn't get key...");

  int qid = msgget(key, 0666 | IPC_CREAT);
  if (qid < 0) report_and_exit("couldn't get queue id...");

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
    255,  //maximum
    25
  }; /* each must be >= 0 */
  int i;
  for (i = 0; i < MsgCount; i++) {
    /* build the message */
    queuedMessage msg;
    msg.priority = priority[i];
    strcpy(msg.payload, payloads[i]);

    /* send the message */
    msgsnd(qid, & msg, sizeof(msg), IPC_NOWAIT); /* don't block */
    printf("%s sent as type %i\n", msg.payload, (int) msg.priority);
  }
  return 0;
}
