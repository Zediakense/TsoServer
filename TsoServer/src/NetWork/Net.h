#include<string>
#include "../Core/Base.h"
#include <queue>
#include<unordered_map>
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
		
		Net() = default;
		Net(const uint16_t& port);


	private:
		bool InitNet(const uint16_t& port);
		void Listen();
		void Reply(const int& connectId , void* msg);
		void BroadCastMsg(void* msg);

	private:
		uint16_t m_Port = 0;
		int m_ListenFd = -1;
		std::unordered_map<int , bool> m_ConnectFds;
		Ref<sockaddr_in> m_Servaddr = nullptr;
		std::queue<Message> m_Messages; 
	};



}