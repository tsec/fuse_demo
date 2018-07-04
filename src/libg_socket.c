#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

#include "libg/libg_socket.h"
#include "libg/libg_log.h"

int libg_udp_send(int port, char *buf, int len)
{
	struct sockaddr_in servaddr;
	int sockfd;
	int nRet;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(port);

	nRet = sendto(sockfd, buf, len, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(nRet == -1)
	{
		libg_log_err("udp send failed!");
	}

	close(sockfd);
    return 0;
}

int libg_udp_send_recv(int port, char *data, int len, char *buf, int *size)
{
	struct sockaddr_in servaddr;
	int sockfd;
	int nRet;
	int nToRead = 0;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(port);

	nRet = sendto(sockfd, data, len, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(nRet == -1)
	{
		libg_log_err("udp send failed!");
		close(sockfd);
		return -1;
	}

	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(sockfd, &rfds);

	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 100000;

	nRet = select(sockfd + 1, &rfds, NULL, NULL, &tv);

	if(nRet == -1)
	{
		libg_log_err("select error!");
	}
	else if(nRet)
	{
		ioctl(sockfd, FIONREAD, &nToRead);
		if(nToRead > *size)
		{
			libg_log_err("recv buf too short");
			nToRead = 0;
		}
		else
		{
			nRet = recv(sockfd, buf, nToRead, 0);
			if(nRet <= 0)
			{
				libg_log_err("recv error!");
			}
		}
	}
	else
	{
		libg_log_err("recv time out");
	}

	close(sockfd);
	*size = nToRead;

	if(*size == 0)
	{
		nRet = -1;
	}
	else
	{
		nRet = 0;
	}

	return nRet;
}

int libg_udp_server(int port, int *sockfd, void *(*thread_func) (void *), void *arg)
{
	int flag;
	struct sockaddr_in addr;

	*sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(*sockfd == -1)
	{
		libg_log_err("create socket failed!");
		return -1;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;

	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

	addr.sin_port = htons(port);

	int opt = 1;
	setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	int ret = bind(*sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if(ret != 0)
	{
		close(*sockfd);
		libg_log_err("bind failed %d: %d: %s\n", ret, errno, strerror(errno));
		return -1;
	}

	flag = fcntl(*sockfd, F_GETFL);
	fcntl(*sockfd, F_SETFL, flag | FASYNC | O_NONBLOCK);

	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,  PTHREAD_CREATE_DETACHED);

	ret = pthread_create(&tid, &attr, thread_func, arg);
	if(ret != 0)
	{
        libg_log_err("thread create failed!");
        close(*sockfd);
		return -1;
	}

	return 0;
}

