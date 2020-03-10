#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <setjmp.h>
#include <errno.h>
#include "APanel_linuxping.h"
#include "APanel_Type.h"

#ifndef _AVTRONSYS_LOG_H
#define _AVTRONSYS_LOG_H
#include "Avtronsys/Avtronsys_Log.h"
#endif

namespace APanel
{

	AndroidPing::AndroidPing(struct icmp* picmp):micmp(picmp)
	{

		Avtronsys::Log::info("AndroidPing2222222222222222222");
		int size=50*1024;
		pid=getpid();
		protocol=getprotobyname("icmp");
		mfd=socket(AF_INET,SOCK_RAW,protocol->p_proto);
		setuid(getuid());
		setsockopt(mfd,SOL_SOCKET,SO_RCVBUF,&size,sizeof(size));
		bzero(&mgoto_addr,sizeof(mgoto_addr));
		mgoto_addr.sin_family=AF_INET;
		memcpy( (char *)&mgoto_addr.sin_addr,hostip,strlen(hostip));
		fromlen=sizeof(mfrom_addr);
		mrecvdata=(char*)micmp;
	}

	AndroidPing::AndroidPing()
	{
		int size=50*1024;
		pid=getpid();
		Avtronsys::Log::info("AndroidPing21111111111111111111111111111");
		micmp->icmp_type=8;//ICMP_ECHO_REQUEST
		Avtronsys::Log::info("AndroidPing31111111111111111111111111111");
		micmp->icmp_code=0;
		Avtronsys::Log::info("AndroidPing41111111111111111111111111111");
		micmp->icmp_cksum=0;
		Avtronsys::Log::info("AndroidPing51111111111111111111111111111");
		micmp->icmp_seq=0;
		Avtronsys::Log::info("AndroidPing61111111111111111111111111111");
		micmp->icmp_id=pid;
		Avtronsys::Log::info("444444444444444444444444444444");
		protocol=getprotobyname("icmp");
		Avtronsys::Log::info("AndroidPing133333333333333333333");
		mfd=socket(AF_INET,SOCK_RAW,protocol->p_proto);
		Avtronsys::Log::info("AndroidPing444444444444444444444");
		setuid(getuid());
		Avtronsys::Log::info("AndroidPing5555555555555555555555");
		setsockopt(mfd,SOL_SOCKET,SO_RCVBUF,&size,sizeof(size));
		Avtronsys::Log::info("AndroidPing6666666666666666666666");
		bzero(&mgoto_addr,sizeof(mgoto_addr));
		Avtronsys::Log::info("AndroidPing7777777777777777777777");
		mgoto_addr.sin_family=AF_INET;
		Avtronsys::Log::info("AndroidPing8888888888888888888888");
		memcpy( (char *)&mgoto_addr.sin_addr,hostip,strlen(hostip));
		Avtronsys::Log::info("AndroidPing9999999999999999999999");
		fromlen=sizeof(mfrom_addr);
		mrecvdata=(char*)micmp;
	}
	AndroidPing::~AndroidPing()
	{

	}

	bool AndroidPing::AndroidPing::send_icmp(void)
	{
		Avtronsys::Log::info("send_icmp");
		if(sendto(mfd,msenddata,sizeof(msenddata),0,(struct sockaddr*)&mgoto_addr,sizeof(mgoto_addr))<0 )
		{
		  return false;
		}
		else
		{
		  return true;
		}
	}

	bool AndroidPing::recv_icmp(void)
	{
		Avtronsys::Log::info("recv_icmp");
		if((n=recvfrom(mfd,mrecvdata,sizeof(mrecvdata),0,(struct sockaddr *)&mfrom_addr,&fromlen))<0)
		{
			return false;
		}
		return unpack(mrecvdata,n);
	}

	/*剥去ICMP报头*/
	bool AndroidPing::unpack(char *buf,int len)
	{
	    int i,iphdrlen;
	    struct ip *ip;
	    struct icmp *icmp;
	    struct timeval *tvsend;
	    double rtt;
	    ip=(struct ip *)buf;
	    iphdrlen=ip->ip_hl<<2; /*求ip报头长度,即ip报头的长度标志乘4*/
	    icmp=(struct icmp *)(buf+iphdrlen); /*越过ip报头,指向ICMP报头*/
	    len-=iphdrlen; /*ICMP报头及ICMP数据报的总长度*/
	    if(len<8) /*小于ICMP报头长度则不合理*/
	    {
	    	return false;
	    }
	    /*确保所接收的是我所发的的ICMP的回应*/
	    if( (icmp->icmp_type==ICMP_ECHOREPLY) && (icmp->icmp_id==pid) )
	    {
	    	return true;
	    }
	    else  return false;
	}
}
