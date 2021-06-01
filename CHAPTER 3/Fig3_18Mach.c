#include<mach/mach.h>

struct message {
  mach msg header t header;
  int data;
};
mach port t client;
mach port t server;
/* Client Code */
struct message message;
// construct the header
message.header.msgh size = sizeof(message);
message.header.msgh remote port = server;
message.header.msgh local port = client;
// send the message
mach msg( & message.header, // message header
  MACH SEND MSG, // sending a message
  sizeof(message), // size of message sent
  0, // maximum size of received message - unnecessary
  MACH PORT NULL, // name of receive port - unnecessary
  MACH MSG TIMEOUT NONE, // no time outs
  MACH PORT NULL // no notify port
);
/* Server Code */
struct message message;
// receive the message
mach msg( & message.header, // message header
  MACH RCV MSG, // sending a message
  0, // size of message sent
  sizeof(message), // maximum size of received message
  server, // name of receive port
  MACH MSG TIMEOUT NONE, // no time outs
  MACH PORT NULL // no notify port
);
