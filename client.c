#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int connect_sock()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(sockfd != -1);

	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("192.168.43.244");

	int res = connect(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));
	assert(res != -1);
	return res;
}

int main()
{
	int bool_a = connect_sock();

	//face()
	// char str1[100] = { 0 };
	// recv(sockfd, str1, 100, 0);
	// char* tmp = NULL;
	// tmp = strtok(str1,";");
	// printf("\t%s\n",tmp);
	// while(tmp)
	// {
	// 	tmp = strtok(NULL,";");
	// 	printf("%s\n",tmp);
	// }
	// char choose[2] = -1;
	// scanf("%s",&choose);
	// send(sockfd,&choose,2,0);





	exit(0);
}