#include<iostream>
#include<string.h>
#include<errno.h>
#include<signal.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in_systm.h>
#include<netinet/ip.h>
#include<netinet/ip_icmp.h>
#include<sys/types.h>

#define ICMPHEAD 8
#define MAXICMPLEN 200
//typedef unsigned int socklen_t;

using namespace std;
namespace APanel
{
	class RawSock
	{
		public:
		int sock;
		int error;
		RawSock(int protocol =0);
		virtual ~RawSock();
		int send(const void* msg, int msglen, struct sockaddr* addr, unsigned int len);
		int send(const void* msg, int msglen, char *addr);
		int receive(void *buf, int buflen, sockaddr *from, socklen_t *len);
		int Error() { return error; }
	};

	class ICMP : public RawSock
	{
		public:
		struct icmp *packet;
		int max_len;
		int length;

		uint16_t checksum(uint16_t *addr, int len);
		ICMP();
		ICMP(int len);
		~ICMP();
		int send_icmp(char *to, void *buf, int len);
		int recv_icmp(sockaddr *from);
		void setCode(int c) { packet->icmp_code =c; }
		void setId(int i) { packet->icmp_id =i; }
		void setSeq(int s) { packet->icmp_seq = s; }
		void setType(int t) { packet->icmp_type = t; }
	};
}
