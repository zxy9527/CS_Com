/*************************************************************************
	> File Name: Client.c
	> Author: 
	> Mail: 
	> Created Time: Sun 19 Nov 2017 07:18:17 PM PST
 ************************************************************************/
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#define _size 2048
int main()
{
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8889);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //创建客户端套接字
    int client_id = socket(AF_INET,SOCK_STREAM,0);
    if(client_id < 0)
    {
        perror("客户端套接字创建失败\n");
       return -1;
    }
    printf("客户端建立成功！\n");

    //发起连接
    int ret = connect(client_id,(struct sockaddr*) &addr,sizeof(addr));
    if(ret < 0)
    {
        perror("连接失败！\n");
        close(client_id);
        return -1;
    }
    printf("成功连接到服务器！\n");
    
    //收发消息
    while(1)
    {
        char buf[_size];
        memset(buf,0,sizeof(buf));
        ret = recv(client_id,buf,sizeof(buf),0); //收消息
        if(ret < 0)
        {
            perror("接收成功\n");
            close(client_id);
            return -1;
        }
        printf("从服务器收到如下数据:%s\n",buf);
        memset(buf,0,2048);

        printf("请输入要发送的数据:");
        gets(buf);
        if(strcmp(buf,"quit") == 0)
            break;
        
        ret = send(client_id,buf,sizeof(buf),0);  //发送消息
        if(ret < 0)
        {
            perror("发送失败！\n");
            close(client_id);
            return -1;
        }
        printf("等待接收...\n");
    }
    //关闭套接字
    close(client_id);
    return 0;
}
