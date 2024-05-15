#include "Net.h"
#include<stdio.h>
#include<stdlib.h>
#include <fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <iostream>
#include <string.h>


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
		// int listen_fd = -1, connect_fd = -1;//初始化为-1
		m_Servaddr = std::make_shared<sockaddr_in>();//定义服务器对应的套接字地址
		//服务器接收和发送缓冲区
		char sendbuf[MAXLINE], recbuf[MAXLINE];
	
		//初始化套接字地址结构体
		// memset(m_Servaddr, 0, sizeof(sockaddr_in));
		m_Servaddr->sin_family = AF_INET;//IPv4
		m_Servaddr->sin_port = htons(port);//设置监听端口
		m_Servaddr->sin_addr.s_addr = htonl(INADDR_ANY);//表示接收任意IP的连接请求
	
		//创建套接字
		if((m_ListenFd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
			//如果创建套接字失败，返回错误信息
			//strerror(int errnum)获取错误的描述字符串
			res = false;
		}
	
		//绑定套接字和本地IP地址和端口
		if(bind(m_ListenFd, (struct sockaddr*)m_Servaddr.get(), sizeof(sockaddr_in)) == -1){
			//绑定出现错误
			res = false;
		}
	
		//使得listen_fd变成监听描述符
		if(listen(m_ListenFd, 10) == -1){
			res = false;
		}

		return res;
	}

	void Net::BeginListen(){
		s_Instance->GenListener();
	}

	void Net::ReadMessages(){
		s_Instance->InstanceReadMessages();
	}

	void Net::InstanceReadMessages(){
		ReceiveMessages(m_ConnectFds , m_Messages);
		if(m_Messages.size() > 0)
		std::cout<<"msg.size = "<< m_Messages.size()<<std::endl;
	}


	void Net::GenListener(){
		m_Listener = std::thread(ListenTask , std::ref(m_ConnectFds) , std::cref(m_ListenFd) , std::ref(m_Messages) , m_Servaddr);
	}

	void Net::ListenTask(std::set<int>& conectIDs , const int& listenFd , std::queue<Message>& messages , Ref<sockaddr_in>socket){
		bool isListening = false;
		while(true){
			//TODO: find a time to stop it
			if(!isListening){
				std::thread listen = std::thread(WaitConnection , std::ref(isListening) , std::cref(listenFd) , std::ref(conectIDs) , std::ref(messages) , socket);
				listen.join();
			}
		}
	}


	void Net::WaitConnection(bool& isListening , const int& listenID , std::set<int>& conectIDs ,std::queue<Message>& messages , Ref<sockaddr_in>socket){
		int connectID = -1;
		std::cout<<"Waiting for connection:..."<<std::endl;
		isListening = true;
		if((connectID = accept(listenID, (struct sockaddr*)NULL, NULL)) == -1){
			//TODO: log err
			std::cout<<"err"<<std::endl;
		}
		std::cout<<"get connect id : "<<connectID<<std::endl;
		if(conectIDs.find(connectID) == conectIDs.end()){
			conectIDs.insert(connectID);
		}

		isListening = false;
	}

	void Net::ReceiveMessages(std::set<int>& conectIDs , std::queue<Message> messages){//TODO: add callback func as prama
		for(auto it = conectIDs.begin() ; it != conectIDs.end() ; it++){
			char recbuf[4096];
			int flags = fcntl(*it, F_GETFL, 0); //通过设置文件描述符的属性，来设置read函数非阻塞
			fcntl(*it, F_SETFL, flags | O_NONBLOCK);
			ssize_t len = read(*it, recbuf, sizeof(recbuf));
			if(len < 0){
				// std::cout<<"err read"<<std::endl;
				continue;
			}
			else if(len == 0){
				close(*it);
				conectIDs.erase(it);
				if(conectIDs.size() == 0){
					break;
				}
				continue;
			}
			else{
				Message msg;
				msg.connectId = *it;
				msg.message = new char[len];
				msg.size = len;
				memcpy(msg.message , recbuf , len);
				m_Messages.push(msg);
				// std::cout<<"msg.size = "<< messages.size()<<std::endl;


			}

		}
	}

	void Net::DisplayMsgs(){
		s_Instance->DisplayMsg();
	}

	void Net::DisplayMsg(){

		while(m_Messages.size() > 0){
			Message msg = m_Messages.front();
			std::cout<<"get msg : content :" << (char*)msg.message << "connectID :" << msg.connectId <<std::endl;
			m_Messages.pop();
		}
	}






} // namespace TServer
