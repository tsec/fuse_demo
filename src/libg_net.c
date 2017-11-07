#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include "libg/libg_net.h"
#include "libg/libg_log.h"

int libg_net_get_mac(char *mac)
{
	int sockfd;
	struct ifreq tmp;

	if(mac == NULL)
	{
		return -1;
	}
	sockfd=socket(AF_INET,SOCK_STREAM, 0);
	if(sockfd<0)
	{
		libg_log_err("create socket fail!");
		return -1;
	}

	memset(&tmp,0,sizeof(struct ifreq));

	strncpy(tmp.ifr_name,"wlan0",sizeof(tmp.ifr_name)-1);

	if((ioctl(sockfd,SIOCGIFHWADDR,&tmp)) < 0)
	{
		libg_log_err("mac ioctl error!");
		return -1;
	}

	sprintf(mac, "%02x-%02x-%02x-%02x-%02x-%02x",
			(unsigned char)tmp.ifr_hwaddr.sa_data[0],
			(unsigned char)tmp.ifr_hwaddr.sa_data[1],
			(unsigned char)tmp.ifr_hwaddr.sa_data[2],
			(unsigned char)tmp.ifr_hwaddr.sa_data[3],
			(unsigned char)tmp.ifr_hwaddr.sa_data[4],
			(unsigned char)tmp.ifr_hwaddr.sa_data[5]
		   );
	close(sockfd);

	return 0;
}

