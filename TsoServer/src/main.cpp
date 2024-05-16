#include<iostream>
#include "NetWork/Net.h"
#include "Core/Log.h"

int main(){
	if(!TServer::Net::Init(8082)){
		std::cout<<"err init"<<std::endl;
		return 0;
	}
	TServer::Log::Init();
	TServer::Net::BeginListen();
	bool m_Run = true;
	while(m_Run){
		//deal something
		// std::cout<<"i can do something else"<<std::endl;
		TServer::Net::ReadMessages();

		// TServer::Net::DisplayMsgs();

	}
	std::cout<<"greet from src dir"<<std::endl;
	return 0;
}