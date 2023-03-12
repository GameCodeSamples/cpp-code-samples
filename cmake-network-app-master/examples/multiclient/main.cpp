#include <iostream>
#include "network/net.hpp"

enum class CustomMsgTypes : uint32_t
{
	ServerAccept,
	ServerDeny,
	ServerPing,
	MessageAll,
	ServerMessage,
};

class CustomClient : public net::client_interface<CustomMsgTypes>
{
public:
	void PingServer()
	{
		net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::ServerPing;

		// Caution with this...
		std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

		std::cout << "Size of timeNow: " << sizeof(timeNow) << std::endl;

		msg << timeNow;
		Send(msg);
	}

	void MessageAll()
	{
		net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::MessageAll;
		Send(msg);
	}
};

int main()
{
	const uint32_t millisecondsSleep = 100;
	const uint32_t numMessages = 1000;
	const uint32_t numClients = 100;
	CustomClient c[numClients];

	for (size_t i = 0; i < numClients; i++)
	{
		c[i].Connect("127.0.0.1", 4468);
	}

	for (size_t i = 0; i < numMessages; i++)
	{
		for (size_t i = 0; i < numClients; i++)
		{
			c[i].MessageAll();
		}
		Sleep(millisecondsSleep);
	}

	return 0;
}