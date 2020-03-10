//#include "unp.h"
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

bool send_echo_req(int sockfd, struct sockaddr_in *dstaddr);
uint16_t in_cksum(uint16_t *addr, int len);
bool recv_echo_reply(int sockfd);
void err_sys(const char *errmsg);
