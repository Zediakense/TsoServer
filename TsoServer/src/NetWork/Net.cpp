#include "Net.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>


#define MAXLINE 4096

namespace TServer
{
	static Net* s_Instance = nullptr;


	bool Net::Init(const uint16_t& port){
		if(s_Instance == nullptr){
			s_Instance = new Net;
		}

		if(!s_Instance->InitNet(port)){
			//TODO: logINFO
			return false;
		}
		return true;
	}

	bool Net::InitNet(const uint16_t& port){
		bool res = true;
		int listen_fd = -1, connect_fd = -1;//初始化为-1
		m_Servaddr = std::make_shared<sockaddr_in>();//定义服务器对应的套接字地址
		//服务器接收和发送缓冲区
		char sendbuf[MAXLINE], recbuf[MAXLINE];
	
		//初始化套接字地址结构体
		// memset(m_Servaddr, 0, sizeof(sockaddr_in));
		m_Servaddr->sin_family = AF_INET;//IPv4
		m_Servaddr->sin_port = htons(port);//设置监听端口
		m_Servaddr->sin_addr.s_addr = htonl(INADDR_ANY);//表示接收任意IP的连接请求
	
		//创建套接字
		if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
			//如果创建套接字失败，返回错误信息
			//strerror(int errnum)获取错误的描述字符串
			res = false;
		}
	
		//绑定套接字和本地IP地址和端口
		if(bind(listen_fd, (struct sockaddr*)&(*m_Servaddr), sizeof(sockaddr_in)) == -1){
			//绑定出现错误
			res = false;
		}
	
		//使得listen_fd变成监听描述符
		if(listen(listen_fd, 10) == -1){
			res = false;
		}

		return res;
	}


} // namespace TServer
