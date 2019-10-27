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

int face()
{
	printf("\t智能停车场\n");
	printf("1.登录\n");
	printf("2.注册\n");
	printf("3.找回密码\n");
	printf("0.退出\n");
	printf("请输入你的选择(数字):");
	int choose = -1;
	scanf("%d".&choose);
	return choose;
}

void Login(int sockfd)
{
	printf("输入手机号:");
	char phoneNum[15] = { 0 };
	scanf("%s",phoneNum);

	printf("输入密码:");
	char password[50] = {0};
	scanf("%s",password);
	char str[65] = { 0 };
	sprintf(str,%s;%s,phoneNum,password);
	send(sockfd,str,65,0);
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