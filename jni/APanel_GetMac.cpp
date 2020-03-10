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
	#define MAXINTERFACES 16    		/* ���ӿ��� */
	int fd;         					/* �׽��� */
	int if_len;     					/* �ӿ����� */
	struct ifreq buf[MAXINTERFACES];    /* ifreq�ṹ���� */
	struct ifconf ifc;                  /* ifconf�ṹ */

	char* returnip()
	{
		return hostip;
	}

	char* get_mac()
	{
		char* mymac ="null";
		/* ����IPv4��UDP�׽���fd */
		if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		{
			Avtronsys::Log::error("socket(AF_INET, SOCK_DGRAM, 0)");
			return mymac;
		}

		/* ��ʼ��ifconf�ṹ */
		ifc.ifc_len = sizeof(buf);
		ifc.ifc_buf = (caddr_t) buf;

		/* ��ýӿ��б� */
		if (ioctl(fd, SIOCGIFCONF, (char *) &ifc) == -1)
		{
			Avtronsys::Log::error("SIOCGIFCONF ioctl");
			return mymac;
		}

		if_len = ifc.ifc_len / sizeof(struct ifreq); /* �ӿ����� */

		Avtronsys::Log::info("count:%d\n\n", if_len);

		while (if_len > 0) /* ����ÿ���ӿ� */
		{
			Avtronsys::Log::info("jc:%s\n", buf[if_len].ifr_name); /* �ӿ����� */

			/* ��ýӿڱ�־ */
			if (!(ioctl(fd, SIOCGIFFLAGS, (char *) &buf[if_len])))
			{
				/* �ӿ�״̬ */
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

			/* IP��ַ */
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

			/* �������� */
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

			/* �㲥��ַ */
			if (!(ioctl(fd, SIOCGIFBRDADDR, (char *) &buf[if_len])))
			{
				Avtronsys::Log::info("gbdz:%s\n",(char*)inet_ntoa(((struct sockaddr_in*) (&buf[if_len].ifr_addr))->sin_addr));
			}
			else
			{
				Avtronsys::Log::info("SIOCGIFADDR ioctl %s", buf[if_len].ifr_name);
			}

			/*MAC��ַ */
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
				//�ر�socket
				close(fd);
				return mymac;
			}
			else
			{
				Avtronsys::Log::info("SIOCGIFHWADDR ioctl %s", buf[if_len].ifr_name);
			}
			if_len--;
		}//�Cwhile end

		//�ر�socket
		close(fd);
		return mymac;
	}

	//���ļ���ȡ�ļ�����
	bool openfile(char* filechar)
	{
		FILE * fp;
		fp=fopen("mnt/sdcard/mac.lic","r");
		if(fp==NULL)
		{
			Avtronsys::Log::info( "no file��");
			return false;
		}
		else
		{
			fgets(filechar,36,fp);
			Avtronsys::Log::info( "filechar:%s",filechar);
			//�ر��ļ�
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
			return 0;	//δ��Ȩ
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
			return 1;//����Ȩ������
		}
		else
		{
			Avtronsys::Log::info("Init111111111:%s",returnip());
			Avtronsys::Log::info("Init111111111:%s",hostip);
			Avtronsys::Log::info( "false");	//����Ȩδ���ӣ�����δ��Ȩ��
			return 2;
		}
	}
}

