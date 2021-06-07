


#include <stdio.h>

#include <sys/ipc.h>

#include <sys/msg.h>

#include <stdlib.h>

#include "key.h"

void report_and_exit(const char * msg) {
  perror(msg);
  exit(-1); /* EXIT_FAILURE */
}

int main() {
  key_t key = ftok(PathName, ProjectId); /* key to identify the queue */
  if (key < 0) report_and_exit("key not gotten...");

  int qid = msgget(key, 0666 | IPC_CREAT); /* access if created already */
  if (qid < 0) report_and_exit("no access to queue...");

  int priority[MsgCount];
  int i;
  for (i = 0; i < MsgCount; i++) {
    queuedMessage msg; /* defined in key.h */
    if (msgrcv(qid, & msg, sizeof(msg), &priority[i], MSG_NOERROR | IPC_NOWAIT) < 0)
      puts("msgrcv trouble...");
    printf("%s (priority %i\n", msg.payload, (int) msg.priority);
  }

  /** remove the queue **/
  if (msgctl(qid, IPC_RMID, NULL) < 0) /* NULL = 'no flags' */
    report_and_exit("trouble removing queue...");

  return 0;
}
