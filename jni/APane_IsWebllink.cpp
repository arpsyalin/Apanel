#include "APane_IsWebllink.h"
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <net/if.h>
#include <sys/socket.h>
#include "Avtronsys/Avtronsys_Log.h"

namespace APanel
{
	#define MAXINTERFACES 16    		/* ���ӿ��� */
	struct ethtool_value {
			__uint32_t cmd;
			__uint32_t data;
	};

	int Isweblink()
	{
		struct ethtool_value edata;
		int fd = -1, err = 0;
		int if_len;     					/* �ӿ����� */
		struct ifreq buf[MAXINTERFACES];    /* ifreq�ṹ���� */
		struct ifconf ifc;                  /* ifconf�ṹ */
		int count=0;							//����
		/* ����IPv4��UDP�׽���fd */
		fd = socket(AF_INET, SOCK_DGRAM, 0);
		if (fd < 0) {
				perror("Cannot get control socket");
				return 4;
		}

		/* ��ʼ��ifconf�ṹ */
		ifc.ifc_len = sizeof(buf);
		ifc.ifc_buf = (caddr_t) buf;

		/* ��ýӿ��б� */
		if (ioctl(fd, SIOCGIFCONF, (char *) &ifc) == -1)
		{
			Avtronsys::Log::error("SIOCGIFCONF ioctl");
		}

		if_len = ifc.ifc_len / sizeof(struct ifreq); /* �ӿ����� */
		while (if_len > 0) /* ����ÿ���ӿ� */
		{
			Avtronsys::Log::info("jc:%s\n", buf[if_len].ifr_name); /* �ӿ����� */
			edata.cmd = 0x0000000a;
			buf[if_len].ifr_data = (caddr_t)&edata;
			err = ioctl(fd, 0x8946, (char *) &buf[if_len]);
			if (err == 0)
			{
				edata.data?count++:count=count;
			}
			else if (errno != EOPNOTSUPP)
			{
					perror("Cannot get link status");
			}
			if_len--;
		}

		if(count>0)
		{
			return 2;
		}
		else
		{
			return 3;
		}
	}
}

