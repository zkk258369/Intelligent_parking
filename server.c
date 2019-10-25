#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include <mysql/mysql.h>

int face(int);
void Login();


void* fun(void* arg)
{
	int c = (int)arg;

	while (1)
	{
		// char buff[128] = { 0 };
		// if (recv(c, buff, 127, 0) <= 0)
		// {
		// 	break;
		// }
		// printf("recv(%d)=%s\n", c, buff);
		// send(c, "ok", 2, 0);
		int res = 0;
		res = face(c);//denglu
		switch (res)
		{
		case 0:
			break;
		case 1:
			Login();//登录
			break;
		case 2:
			//Registration();//注册
			break;
		case 3:
			//Retrieve_password();//找回密码
			break;
		
		default:
			printf("You choose a invalid number\n");
			fflush(stdout);
			break;
		}
	}
	printf("one client over(%d)", c);
	fflush(stdout);
	close(c);
}

int face(int c)
{
	char* str1 = "智能停车场;1.登录;2.注册;3.找回密码;0.退出.";
	send(c,str1,strlen(str1) + 1,0);
	char choose = '4';
	recv(c, &choose, 1, 0);

	int res = (choose - 48);//选择

	return res;
}

void Login()
{
	printf("输入手机号:");
	char phoneNum[15] = { 0 };
	scanf("%s",phoneNum);

	printf("输入密码:");
	char password[50] = {0};
	scanf("%s",password);

	MYSQL mysql;
    mysql_init(&mysql);
    
    if ( !mysql_real_connect(&mysql,"localhost","root",NULL,"intelligent_park",0,NULL,0) )
    {
        printf("error connect!\n");
    }
    else
    {
        printf("sucess connect!\n");
    }

    char * str_sql = "insert into ite_p_member values(\"1025000001\",\"yangzhao\",\"man\",15947191111,1998-09-22,12345)";

    int res = mysql_real_query(&mysql,str_sql,strlen(str_sql));
    if ( res )
    {
        printf("insert failed\n");
    }
    else
    {
        printf("insert sucess\n");
    }

    mysql_close(&mysql);
}


int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0); //(协议族,流式传输, )
	//sockfd 监听套接字 
	assert(sockfd != -1);

	struct sockaddr_in saddr, caddr; //保存 socket（ip+端口） 
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;//Tcp/ipv4
	saddr.sin_port = htons(6000);// 0-1023知名端口，1024-4096保留端口，临时端口
	saddr.sin_addr.s_addr = inet_addr("192.168.43.244");

	//绑定
	int res = bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));
	assert(res != -1);

	//监听
	listen(sockfd, 5); //( ,监听队列长度)


	while (1)
	{
		//接收电话 accept
		int len = sizeof(caddr);
		int c = accept(sockfd, (struct sockaddr*)&caddr, &len);
		// c 连接套接字
		if (c < 0)
			continue;
		printf("Welcome terminal %d is connect!\n", c);


		pthread_t id;
		pthread_create(&id, NULL, fun, (void*)c);


		////接收话语recv
		//char buff[128] = { 0 };
		//int n = recv(c, buff, 127, 0);//n 实际接收到的字节数
		//printf("n = %d,buff = %s\n", n, buff);

		////发送
		//send(c, "ok", 2, 0);

		//close(c);
	}

	exit(0);
}
