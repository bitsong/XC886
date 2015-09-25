//ssc message
#ifndef MESSAGE_H
#define MESSAGE_H
typedef struct {
	unsigned char type;
	unsigned char len;
}msg_header;
void send(msg_header send);
extern unsigned char transfbuf[32];
extern unsigned char rcvbuf[32];
#endif
