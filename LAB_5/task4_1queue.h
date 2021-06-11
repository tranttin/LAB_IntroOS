#define ProjectId 123  // for System-V
#define PathName  "queue.h" /* any existing, accessible file would do */
#define key "/OpenCSF_MQ"
#define MsgLen    40
#define MsgCount  6

typedef struct {
  long priority;                 /* must be of type long */
  char payload[MsgLen + 1];  /* bytes in the message */
} queuedMessage;
