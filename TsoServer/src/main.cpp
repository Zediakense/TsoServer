#include<iostream>
#include "NetWork/Net.h"

int main(){
	TServer::Net::Init(8082);
	std::cout<<"greet from src dir"<<std::endl;
	return 0;
}