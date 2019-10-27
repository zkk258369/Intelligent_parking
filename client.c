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
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int res = connect(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));
	assert(res != -1);
	return res;
}

int face()
{
	printf("\t智能停车场\n");
	printf("1.登录\n");
	printf("2.注册\n");
	printf("3.找回密码\n");
	printf("0.退出\n");
	printf("请输入你的选择(数字):");
	int choose = -1;
	scanf("%d",&choose);
	return choose;
}

void Login(int sockfd)
{
	//printf "\033c";
	printf("\n\t欢迎进入登录界面\n\n");
	printf("输入手机号:");
	char phoneNum[13] = { 0 };
	scanf("%s",phoneNum);
	phoneNum[11] = '|';

	printf("输入密码:");
	char password[50] = {0};
	scanf("%s",password);

	char str[64] = { 0 };
	sprintf(str,"%.13s%.50s",phoneNum,password);
	puts(str);
	printf("%d\n",strlen(str));

	printf("send = %d\n",send(sockfd,str,strlen(str),0));
	memset(str,0,sizeof(str));
	printf("recv = %d\n",recv(sockfd,str,63,0));
	if(strcmp(str,"true") == 0)
	{
		printf("Login true\n");
	}
	else 
	{
		printf("Login false\n");
	}
}

int main()
{
	int sockfd = connect_sock();

	int choose = face();

	switch(choose)
	{
		case 0:
			break;
		case 1:
			Login(sockfd);
			break;
	}


	close(sockfd);
	exit(0);
}