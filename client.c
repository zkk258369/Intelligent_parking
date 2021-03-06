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
	return sockfd;
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
	system("clear");
	printf("\n\t欢迎进入登录界面\n\n");
	printf("输入手机号:");
	char phoneNum[12] = { 0 };
	scanf("%s",phoneNum);
	strcat(phoneNum,"|");

	printf("输入密码:");
	char password[50] = {0};
	scanf("%s",password);

	char str[128] = { 0 };
	sprintf(str,"1|%.12s%.50s",phoneNum,password);
	puts(str);

	send(sockfd,str,strlen(str),0);
	memset(str,0,sizeof(str));
	recv(sockfd,str,127,0);
	if(strcmp(str,"true") == 0)
	{
		printf("Login true\n");
	}
	else 
	{
		printf("Login false\n");
	}
}

void Registration(int sockfd)
{
	char sex[10] = { 0 };
    char memberName[20] = { 0 };
    char phone[12] = { 0 };
    char birthday[11] = { 0 };
    char password[5] = { 0 };
    system("clear");
    printf("\n\t欢迎进入注册界面\n\n");
    printf("会员名字：");
    scanf("%s",memberName);
    puts(memberName);
    
    printf("性别：(man or woman)");
    scanf("%s",sex);
    puts(sex);
    
    printf("手机号：");
    scanf("%s",phone);

    printf("请输入出生年月日：(2000-1-1)");
    scanf("%s",birthday);

    printf("请输入密码：(至多49位)");
    scanf("%s",password);

    char str[128] = { 0 };
    sprintf(str,"2|%.20s|%.10s|%.11s|%.11s|%.5s",memberName,sex,phone,birthday,password);
    puts(str);

    send(sockfd,str,strlen(str),0);
    memset(str,0,sizeof(str));
    recv(sockfd,str,127,0);
    if(strcmp(str,"true") == 0)
    {
        printf("Register true\n");
    }
    else 
    {
        printf("Register false\n");
    }
    
}

int main()
{
	int sockfd = connect_sock();

	while(1)
	{
		int choose = face();

		switch(choose)
		{
			case 0:
				break;
			case 1:
				Login(sockfd);
				break;
			case 2:
                Registration(sockfd);
				break;
			case 3:
				break;
		}
	}



	close(sockfd);
	exit(0);
}
