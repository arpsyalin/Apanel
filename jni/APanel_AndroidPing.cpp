#include "APanel_AndroidPing.h"
#include "Avtronsys/Avtronsys_Log.h"

bool send_echo_req(int sockfd, struct sockaddr_in *dstaddr)
{
	char buf[100];
	size_t len = sizeof(struct icmp);
	struct icmp *icmp;
	socklen_t dstlen = sizeof(struct sockaddr_in);
	bzero(buf, sizeof(buf));
	icmp = (struct icmp *)buf;
	Avtronsys::Log::info("1111111111111111111aaa");
	icmp->icmp_type = ICMP_ECHO;
	Avtronsys::Log::info("2222222222222222222222");
	icmp->icmp_code = 0;
	icmp->icmp_id = getpid();
	icmp->icmp_seq = 1;
	icmp->icmp_cksum = in_cksum((uint16_t *) icmp, sizeof(struct icmp));
	if (sendto(sockfd, buf, len, 0, (struct sockaddr *)&dstaddr, dstlen) == -1)
	return false;
	return true;
		//err_sys("sendto");
}

bool recv_echo_reply(int sockfd)
{
	char buf[100];
	ssize_t n;
	struct ip *ip;
	struct icmp *icmp;
	while (1)
	{
		alarm(5);
		/* set timeout */
		if ((n = read(sockfd, buf, sizeof(buf))) == -1)
			return false;
			//err_sys("read");
		ip = (struct ip *)buf;
		if (ip->ip_p != IPPROTO_ICMP)
		{
			fprintf(stderr, "protocol error.  ");
			return false;
			//exit(1);
		}
		icmp = (struct icmp *)(buf + sizeof(struct ip));
		if (icmp->icmp_type == ICMP_ECHOREPLY)
		{
			if (icmp->icmp_id != getpid())
			{
				fprintf(stderr, "not this process.  ");
				//exit(1);
				return false;
			}
			else
			{
				printf("destination host is alive.");
				return true;
				break;
			}
		}
	}
}
uint16_t in_cksum(uint16_t *addr, int len)
{
	int nleft = len;
	uint32_t sum = 0;
	uint16_t *w = addr;
	uint16_t answer = 0;
	while (nleft > 1)
	{
		sum += *w++;
		nleft -= 2;
	}
	if (nleft == 1)
	{
		*(unsigned char *)(&answer) = *(unsigned char *)w ;
		sum += answer;
	}
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return(answer);
}

void err_sys(const char *errmsg)
{
	perror(errmsg);
	exit(1);
}
