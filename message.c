//message.c
#include "main.h"

unsigned char transfbuf[32];
unsigned char rcvbuf[32];

void send(msg_header send)
{
	unsigned char* transfptr=transfbuf;
	unsigned char* rcvptr=rcvbuf;
	SSC_vSendData(send.type);
	while(SSC_ubBusy() ); 
	SSC_vGetData();
	SSC_vSendData(send.len);
	while(SSC_ubBusy() ); 
	SSC_vGetData();
	while(send.len>2){
		SSC_vSendData(*transfptr++);
		while(SSC_ubBusy() ); 
		*rcvptr++=SSC_vGetData();

		send.len--;
	}

}
