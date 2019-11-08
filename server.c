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


int Login(char*);
int Registration(char*);


void* fun(void* arg)
{
	int c = (int)arg;

	while (1)
	{
		char str[128] = { 0 };
		int res = 0;
		res = recv(c,str,127,0);
		char strtmp[128] = { 0 };
		strcpy(strtmp,str);
        assert(res > 0);

        char* saveptr = NULL;
        char* choose_char = NULL;
		choose_char = strtok_r(str,"|",&saveptr);
		printf("strtmp = %s\n", strtmp);
   
    	int choose_int = choose_char[0] - 48;
    	switch(choose_int)
    	{
    		case 0:
    			break;
    		case 1:
		    	if(Login(strtmp))
				{
					send(c,"true",4,0);
				}
				else
				{
					send(c,"false",5,0);
				}
				break;
			case 2:
                if(Registration(strtmp))
                {
                	send(c,"true",4,0);
                }
                else
                {
                	send(c,"false",5,0);
                }
				break;
			case 3:
				break;
    	}
	}
	printf("one client is over(%d)\n", c);
	fflush(stdout);
	close(c);
}



int Login(char* str)
{
	//chuli shouji mima
	char* choose_char = NULL;
	char* phoneNum = NULL;
	char* password = NULL;
	char* saveptr = NULL;
	choose_char = strtok_r(str,"|",&saveptr);
	phoneNum = strtok_r(NULL,"|",&saveptr);
	password = strtok_r(NULL,"|",&saveptr);

    MYSQL mysql;
 	MYSQL_RES *res;
 	MYSQL_ROW row;
 	char *query;
 	int flag, t;
 	mysql_init(&mysql);
 	if(!mysql_real_connect(&mysql, "localhost", "root",NULL, "intelligent_park", 0, NULL, 0)) 
 	{
 		printf("Failed to connect to Mysql!\n");
 		return 0;
 	}
 	else 
 	{
 		printf("Connected to Mysql successfully!\n");
 	}
 	
 	query = "select * from ite_p_member";
 	/*查询，成功则返回0*/
 	flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
 	if(flag) 
 	{
 		printf("Query failed!\n");
 		return 0;
 	}
 	else 
 	{
 		printf("[%s] made...\n", query);
 	}
 	/*mysql_store_result讲所有的查询结果读取到client*/
 	res = mysql_store_result(&mysql);
 	printf("mysql_num_fields(res) = %d\n", mysql_num_fields(res));
 	/*mysql_fetch_row检索结果集的下一行*/ 
 	while(row = mysql_fetch_row(res)) 
 	{
 		/*mysql_num_fields返回结果集中的字段数目*/
 		if(strcmp(row[3],phoneNum) == 0)
 		{
 			if(strcmp(row[5],password) == 0)
 			{
 				mysql_close(&mysql); 
 				return 1;
 			}
 		}
 		else
 		{
 			continue;
 		}
 	}
 	mysql_close(&mysql);


 	return 0; 
}


int Registration(char* str )
{
	char* choose_char = NULL;
    char* memberName = NULL;
    char* sex = NULL;
    char* phone = NULL;
    char* birthday = NULL;
    char* password = NULL;
    char* saveptr = NULL;

    choose_char = strtok_r(str,"|",&saveptr);
    memberName = strtok_r(NULL,"|",&saveptr);
    sex = strtok_r(NULL,"|",&saveptr);
    printf("sex = %s\n",sex);
    phone = strtok_r(NULL,"|",&saveptr);
    birthday = strtok_r(NULL,"|",&saveptr);
    password = strtok_r(NULL,"|",&saveptr);
    
    MYSQL mysql;
    MYSQL mysql2;
    MYSQL_RES* res;
    MYSQL_ROW row;
    char* query = NULL;
    int flag;
    int t;
    mysql_init(&mysql);
    mysql_init(&mysql2);


    if(!mysql_real_connect(&mysql,"localhost","root",NULL,"information_schema",0,NULL,0))
    {
        printf("Resgistration Faild to connect to MYSQL information_schema!\n");
        return 0;
    }
    else
    {
        printf("Resgistration Successfully to connect to MYSQL information_schema!\n");
    }
    query = "select table_rows from tables where TABLE_SCHEMA = 'intelligent_park' && table_name = 'ite_p_member' order by table_rows desc";
    
    flag = mysql_real_query(&mysql,query,(unsigned int)strlen(query));
    if(flag)
    {
        printf("Query select table_rows from information_schema Failed!\n");
    }
    else
    {
        printf("Query select table_rows from information_schema Successfully!\n");
    }

    res = mysql_store_result(&mysql);
    row = mysql_fetch_row(res);

    //int tmp = atoi(row[0]);
    //tmp++;
    char* memberID = row[0];
    //itoa(tmp,memberID,10);

    mysql_close(&mysql);


    if(!mysql_real_connect(&mysql2,"localhost","root",NULL,"intelligent_park",0,NULL,0))
    {
        printf("Resgistration Faild to connect intelligent_park to MYSQL\n");
    }
    else
    {
        printf("Resgistration connect intelligent_park to MYSQL successfully\n");
    }

    printf("begin\n");
    puts(query);
    char query1[1024] = {0};
    sprintf(query1,"insert into ite_p_member(memberID,memberName,sex,phone,birthday,password) values(\"%.10s\",\"%.20s\",\"%.10s\",\"%.12s\",\"%.11s\",\"%.5s\")",memberID,memberName,sex,phone,birthday,password);
    printf("end\n");
    puts(query);

    flag = mysql_real_query(&mysql2,query1,(unsigned)strlen(query1));
    if ( flag )
    {
        printf("insert failed\n");
    }
    else
    {
        printf("insert sucess\n");
    }
    mysql_close(&mysql2);
    return !flag;
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
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

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


	}

	exit(0);
}
