#include "APanel_AndroidPing.h"
namespace APanel
{
	RawSock:: RawSock(int protocol )
	{
		sock = socket(AF_INET, SOCK_RAW, protocol);
		setuid(getuid());
		if( sock == -1 ) error = 1;
		else error = 0;
	}


	RawSock:: ~RawSock()
	{
		close(sock);
	}

	int RawSock:: send(const void* msg, int msglen, struct sockaddr* to, unsigned int len)
	{
		if (error)
			return -1;
		int length = sendto(sock, msg, msglen, 0, (const struct sockaddr *)to, len);
		if( length == -1)
		{
			error = 2;
			return -1;
		}
		return length;
	}


	int RawSock:: send(const void* msg, int msglen, char *hostname)
	{
		sockaddr_in sin;
		if(error)
		return -1;

		if(hostname)
		{
			hostent *hostnm = gethostbyname(hostname);
			if( hostnm == (struct hostent *)0)
			{
				return -1;
			}
			sin.sin_addr = *((struct in_addr *)hostnm->h_addr);
		}
		else
		return -1;

		sin.sin_family = AF_INET;
		return send(msg, msglen, (sockaddr *)&sin, sizeof(sin));
	}


	int RawSock::receive(void *buf, int buflen, sockaddr* from, socklen_t *len)
	{
		if(error) return -1;
		while(1)
		{
			int length =recvfrom(sock, buf, buflen, 0, from, len);
			if(length == -1)
				if( error == EINTR )
					continue;
				else
				{
					error = 3;
					return -1;
				}
			return length;
		}
	}

	ICMP::ICMP() : RawSock(IPPROTO_ICMP)
	{
		max_len = MAXICMPLEN;
		packet = (struct icmp *)new char [max_len];

		packet->icmp_code = 0;
		packet->icmp_id = 0;
		packet->icmp_seq = 0;
		packet->icmp_type = ICMP_ECHO;
	}


	ICMP::ICMP(int len) : RawSock(IPPROTO_ICMP)
	{
		max_len = len;
		packet = (struct icmp *) new char [max_len];
		packet->icmp_code = 0;

		packet->icmp_id = 0;
		packet->icmp_seq = 0;
		packet->icmp_type = ICMP_ECHO;

	}

	ICMP::~ICMP()
	{
		delete [] (char *)packet;
	}

	uint16_t ICMP::checksum(uint16_t *addr, int len)
	{
		int nleft = len;
		int sum =0;
		unsigned short *w = addr;
		unsigned short answer = 0;

		while(nleft > 1)
		{
			sum += *w++;
			nleft -=2;
		}

		if(nleft == 1)
		{
			*(unsigned char *) (&answer) = *(unsigned char *) w;
			sum += answer;
		}

		sum = (sum >> 16) + (sum & 0xffff);
		sum += (sum >> 16);
		answer = ~sum;
		return (answer);
	}


	int ICMP:: send_icmp(char *host, void *buf, int len)
	{
		memcpy(packet->icmp_data, buf, len);
		packet->icmp_cksum =0;
		packet->icmp_cksum = checksum((uint16_t *)packet, ICMPHEAD + 6);
		int err = send(packet, MAXICMPLEN, host);
		return err;

	}


	int ICMP:: recv_icmp(sockaddr *from)
	{
		char buf[MAXICMPLEN + 100];
		int hlen1, icmplen;
		struct ip *ip;
		struct icmp *icmp;

		if( Error() )
		{
			printf("Error() = %d\n", Error());
			return -1;
		}

		socklen_t addrlen = 0;
		int len = receive(buf, MAXICMPLEN+100, from , &addrlen);

		if ( len == -1)
		{
			cout<<"Receive Failed\n";
			return -1;
		}

		ip = (struct ip *)buf;
		hlen1 = ip->ip_hl << 2;

		icmp = (struct icmp *) (buf + hlen1);

		if( (icmplen = len -hlen1) < 8)
		{
			cout<<"Receive Fail\n";
			return -1;
		}

		memcpy(packet, icmp , icmplen);
	   // printf("11111\n");
		return 0;
	}


	/*
	int main(int argc, char *argv[])
	{
		ICMP icmp;
		struct sockaddr from;
		char *host;
		int count;

		if(argc < 2)
		{
			printf("can shu you wu\n");
			exit(1);
		}

		if(argc == 2)
		{
			host = argv[1];
			count = 5;
		}
		if( argc == 3)
		{
			host = argv[1];
			count = 3;
		}

		for( int i=0; i<=count; i++)
		{
			icmp.setId(getpid());
			icmp.setSeq(i);
			char *test_data = "abcde";
			icmp.send_icmp(host, test_data, strlen(test_data));
			printf("count = %d\n", count);
		}

		int num = 1;
		while(1)
		{
			if(icmp.recv_icmp(&from) < 0)
				continue;
			if(icmp.packet->icmp_type == ICMP_ECHOREPLY)
			{
				if( icmp.packet->icmp_id == getpid())
				{
				printf("%d bypes form %s: seq=%u, data=%s\n",
					icmp.length, host, icmp.packet->icmp_seq, icmp.packet->icmp_data);
				num++;
				if(num > count)
					break;
				}

			}
		}
	}
	*/
}
