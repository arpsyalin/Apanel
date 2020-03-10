#include "APanel_GetMac.h"
#include "APanel_md5.h"
#include <string.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Avtronsys/Avtronsys_Log.h"
namespace APanel
{
	char* hostip;
	#define MAXINTERFACES 16    		/* 最大接口数 */
	int fd;         					/* 套接字 */
	int if_len;     					/* 接口数量 */
	struct ifreq buf[MAXINTERFACES];    /* ifreq结构数组 */
	struct ifconf ifc;                  /* ifconf结构 */

	char* returnip()
	{
		return hostip;
	}

	char* get_mac()
	{
		char* mymac ="null";
		/* 建立IPv4的UDP套接字fd */
		if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		{
			Avtronsys::Log::error("socket(AF_INET, SOCK_DGRAM, 0)");
			return mymac;
		}

		/* 初始化ifconf结构 */
		ifc.ifc_len = sizeof(buf);
		ifc.ifc_buf = (caddr_t) buf;

		/* 获得接口列表 */
		if (ioctl(fd, SIOCGIFCONF, (char *) &ifc) == -1)
		{
			Avtronsys::Log::error("SIOCGIFCONF ioctl");
			return mymac;
		}

		if_len = ifc.ifc_len / sizeof(struct ifreq); /* 接口数量 */

		Avtronsys::Log::info("count:%d\n\n", if_len);

		while (if_len > 0) /* 遍历每个接口 */
		{
			Avtronsys::Log::info("jc:%s\n", buf[if_len].ifr_name); /* 接口名称 */

			/* 获得接口标志 */
			if (!(ioctl(fd, SIOCGIFFLAGS, (char *) &buf[if_len])))
			{
				/* 接口状态 */
				if (buf[if_len].ifr_flags & IFF_UP)
				{
					Avtronsys::Log::info("jczt: UP\n");
				}
				else
				{
					Avtronsys::Log::info("jczt: DOWN\n");
				}
			}
			else
			{
				Avtronsys::Log::info( "SIOCGIFFLAGS ioctl %s", buf[if_len].ifr_name);
			}

			/* IP地址 */
			if (!(ioctl(fd, SIOCGIFADDR, (char *) &buf[if_len])))
			{
				char *strip =new char[15];
				Avtronsys::Log::info("IP :%s\n",(char*)inet_ntoa(((struct sockaddr_in*) (&buf[if_len].ifr_addr))->sin_addr));
				sprintf(strip,"%s",(char*)inet_ntoa(((struct sockaddr_in*) (&buf[if_len].ifr_addr))->sin_addr));
				hostip=strip;
				Avtronsys::Log::info("IP :%s\n",hostip);
			}
			else
			{
				Avtronsys::Log::info( "SIOCGIFADDR ioctl %s", buf[if_len].ifr_name);
			}

			/* 子网掩码 */
			if (!(ioctl(fd, SIOCGIFNETMASK, (char *) &buf[if_len])))
			{
				Avtronsys::Log::info("zwym:%s\n",(char*)inet_ntoa(((struct sockaddr_in*) (&buf[if_len].ifr_addr))->sin_addr));
			}
			else
			{
				char str[256];
				sprintf(str, "SIOCGIFADDR ioctl %s", buf[if_len].ifr_name);
				Avtronsys::Log::info("SIOCGIFADDR ioctl %s", buf[if_len].ifr_name);
			}

			/* 广播地址 */
			if (!(ioctl(fd, SIOCGIFBRDADDR, (char *) &buf[if_len])))
			{
				Avtronsys::Log::info("gbdz:%s\n",(char*)inet_ntoa(((struct sockaddr_in*) (&buf[if_len].ifr_addr))->sin_addr));
			}
			else
			{
				Avtronsys::Log::info("SIOCGIFADDR ioctl %s", buf[if_len].ifr_name);
			}

			/*MAC地址 */
			if (!(ioctl(fd, SIOCGIFHWADDR, (char *) &buf[if_len])))
			{

				char str[256];
				sprintf(str,"%02x:%02x:%02x:%02x:%02x:%02x",
						(unsigned char) buf[if_len].ifr_hwaddr.sa_data[0],
						(unsigned char) buf[if_len].ifr_hwaddr.sa_data[1],
						(unsigned char) buf[if_len].ifr_hwaddr.sa_data[2],
						(unsigned char) buf[if_len].ifr_hwaddr.sa_data[3],
						(unsigned char) buf[if_len].ifr_hwaddr.sa_data[4],
						(unsigned char) buf[if_len].ifr_hwaddr.sa_data[5]);
				Avtronsys::Log::info("%s",str);

				Avtronsys::Log::info("MAC:%02x:%02x:%02x:%02x:%02x:%02x\n\n",
						(unsigned char) buf[if_len].ifr_hwaddr.sa_data[0],
						(unsigned char) buf[if_len].ifr_hwaddr.sa_data[1],
						(unsigned char) buf[if_len].ifr_hwaddr.sa_data[2],
						(unsigned char) buf[if_len].ifr_hwaddr.sa_data[3],
						(unsigned char) buf[if_len].ifr_hwaddr.sa_data[4],
						(unsigned char) buf[if_len].ifr_hwaddr.sa_data[5]);
				mymac=str;
				//关闭socket
				close(fd);
				return mymac;
			}
			else
			{
				Avtronsys::Log::info("SIOCGIFHWADDR ioctl %s", buf[if_len].ifr_name);
			}
			if_len--;
		}//–while end

		//关闭socket
		close(fd);
		return mymac;
	}

	//打开文件获取文件数据
	bool openfile(char* filechar)
	{
		FILE * fp;
		fp=fopen("mnt/sdcard/mac.lic","r");
		if(fp==NULL)
		{
			Avtronsys::Log::info( "no file！");
			return false;
		}
		else
		{
			fgets(filechar,36,fp);
			Avtronsys::Log::info( "filechar:%s",filechar);
			//关闭文件
			fclose(fp);
			return true;
		}
	}

	int compare()
	{
		char tmp[3]={'\0'};
		char buf[38]={'\0'},filechar[38]={'\0'};
		FILE * fp;
		char*mac;
		unsigned  char MacArray[18]={'\0'},MacArrayTemp[18]={'\0'},Result[18]={'\0'};
		int len,i;
		struct MD5Context md5c;
		if(!openfile(filechar))
		{
			return 0;	//未授权
		}
		mac = get_mac();

		len=strlen(mac);
		for(i=0;i<len;i++)
		{
			switch(i)
			{
			case 2:
				MacArray[i] = 'a';
				break;
			case 5:
				MacArray[i] = 'v';
				break;
			case 8:
				MacArray[i] = 't';
				break;
			case 11:
				MacArray[i] = 'r';
				break;
			case 14:
				MacArray[i] = 'o';
				break;
			default:
				MacArray[i] = *(mac+i);
			}
			MacArrayTemp[16-i]=MacArray[i];
		}
		MacArray[17]='\0';
		MacArrayTemp[17]='\0';

		MD5Init(&md5c);
		MD5Update(&md5c,MacArrayTemp,strlen((const char*)MacArrayTemp));
		MD5Final(Result,&md5c);
		for( i=0; i<16; i++ )
		{
			sprintf(tmp,"%02X", Result[i]);
			strcat(buf,tmp);
		}

		if(memcmp(filechar,buf,17)==0)
		{
			Avtronsys::Log::info("Init111111111:%s",returnip());
			Avtronsys::Log::info("Init111111111:%s",hostip);
			Avtronsys::Log::info( "true");
			return 1;//已授权已连接
		}
		else
		{
			Avtronsys::Log::info("Init111111111:%s",returnip());
			Avtronsys::Log::info("Init111111111:%s",hostip);
			Avtronsys::Log::info( "false");	//已授权未连接（算做未授权）
			return 2;
		}
	}
}

