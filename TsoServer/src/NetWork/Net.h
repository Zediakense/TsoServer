#include<string>
#include "../Core/Base.h"
#include <queue>
#include<set>
#include <thread>
struct sockaddr_in;
namespace TServer{

struct Message
{
	int connectId = -1;
	uint32_t size = 0;
	uint32_t timestamp = 0;//TODO: to be impleted
	void* message = nullptr;
	/* data */
};

	class Net{
	public:
		static bool Init(const uint16_t& port);
		static bool Shutdown();
		static bool Reply(const Message& rcv , void* msg);
		static bool BroadCast(void* message);
		static void BeginListen();
		static void ReadMessages();
		
		Net() = default;
		Net(const uint16_t& port);

		//test
		static void DisplayMsgs();


	private:
		bool InitNet(const uint16_t& port);
		void Listen();
		void Reply(const int& connectId , void* msg);
		void BroadCastMsg(void* msg);

		void GenListener();
		void InstanceReadMessages();
		void ReceiveMessages(std::set<int>& conectIDs , std::queue<Message> messages );//TODO: add callback func as prama

		static void WaitConnection(bool& isListening , const int& listenID , std::set<int>& conectIDs ,std::queue<Message>& messages , Ref<sockaddr_in>socket);
		static void ListenTask(std::set<int>& conectIDs , const int& listenFd , std::queue<Message>& messages , Ref<sockaddr_in>socket);

		void DisplayMsg();


	private:
		uint16_t m_Port = 0;
		int m_ListenFd = -1;
		std::set<int> m_ConnectFds;
		Ref<sockaddr_in> m_Servaddr = nullptr;
		std::thread m_Listener;
		std::queue<Message> m_Messages; 
	};



}