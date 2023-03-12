#pragma once

#include "net_common.hpp"
#include "net_message.hpp"
#include "net_tsqueue.hpp"
#include "net_connection.hpp"

namespace net
{
	template<typename T>
	class server_interface
	{
	public:
		server_interface(uint16_t port)
			: m_asioAcceptor(m_asioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) { }

		virtual ~server_interface()
		{
			Stop();
		}

		bool Start()
		{
			try
			{
				// Asio context work. give the work before execution to avoid end
				WaitForClientConnection();

				// run the context on its own thread
				m_threadContext = std::thread([this]() { m_asioContext.run(); });
			}
			catch (const std::exception& e)
			{
				std::cerr << "Client exception: " << e.what() << std::endl;
				return false;
			}

			std::cout << "[SERVER] Started" << std::endl;
			return true;
		}

		void Stop()
		{
			// Request the context to close
			m_asioContext.stop();

			// Wait to the context threath to finish possible tasks and the stop thread
			if (m_threadContext.joinable())
			{
				m_threadContext.join();
			}
			std::cout << "[SERVER] Stopped" << std::endl;
		}

		// ASYNC - Asio context will start listening for new connections
		void WaitForClientConnection()
		{
			m_asioAcceptor.async_accept([this](std::error_code ec, asio::ip::tcp::socket socket)
				{
					if (!ec)
					{
						std::cout << "[SERVER] New connection: " << socket.remote_endpoint() << std::endl;

						std::shared_ptr<connection<T>> newConnection = 
							std::make_shared<connection<T>>(
								connection<T>::owner::server, // Set the owner of the new connection
								m_asioContext, // Pass a reference of the context
								std::move(socket), // Pass the created socket for the new connection
								m_qMessagesIn // Pass a reference of the queue where to put received messages
							);

						// Call OnClientConnect
						if (OnClientConnect(newConnection))
						{
							// Here the connection is allowed. Add it to the container
							m_deqConnections.push_back(std::move(newConnection));

							m_deqConnections.back()->ConnectToClient(nIDCounter++);
							std::cout << "["<< m_deqConnections.back()->GetID() << "] Connectin approved" << std::endl;
						}
						else
						{
							std::cout << "[SERVER] Connectin denied" << std::endl;
						}
					}
					else
					{
						std::cerr << "[SERVER] New connection error: " << ec.message() << std::endl;
					}

					WaitForClientConnection();
				});
		}

		// Send a message to a specific client
		void MessageClient(std::shared_ptr<connection<T>> client, const message<T>& msg)
		{
			if (client && client->IsConnected())
			{
				client->Send(msg);
			}
			else
			{
				// If we cant communicate with client then we may as 
				// well remove the client - let the server know, it may
				// be tracking it somehow
				OnClientDisconnect(client);

				// Off you go now, bye bye!
				client.reset();

				// Then physically remove it from the container
				m_deqConnections.erase(
					std::remove(m_deqConnections.begin(), m_deqConnections.end(), client), m_deqConnections.end());
			}
		}

		// Send message to all clients
		void MessageAllClients(const message<T>& msg, std::shared_ptr<connection<T>> pIgnoreClient = nullptr)
		{
			bool bInvalidClientExists = false;

			// Iterate through all clients in container
			for (auto& client : m_deqConnections)
			{
				// Check client is connected...
				if (client && client->IsConnected())
				{
					// ..it is!
					if (client != pIgnoreClient)
						client->Send(msg);
				}
				else
				{
					// The client couldnt be contacted, so assume it has
					// disconnected.
					OnClientDisconnect(client);
					client.reset();

					// Set this flag to then remove dead clients from container
					bInvalidClientExists = true;
				}
			}

			// Remove dead clients, all in one go - this way, we dont invalidate the
			// container as we iterated through it.
			if (bInvalidClientExists)
				m_deqConnections.erase(
					std::remove(m_deqConnections.begin(), m_deqConnections.end(), nullptr), m_deqConnections.end());
		}

		// Force server to respond to incoming messages
		void Update(size_t nMaxMessages = -1, bool bWait = false)
		{
			if (bWait) m_qMessagesIn.wait();

			// Process as many messages as you can up to the value
			// specified
			size_t nMessageCount = 0;
			while (nMessageCount < nMaxMessages && !m_qMessagesIn.isEmpty())
			{
				// Grab the front message
				auto msg = m_qMessagesIn.pop_front();

				// Pass to message handler
				OnMessage(msg.remote, msg.msg);

				nMessageCount++;
			}
		}

	protected:
		// Called when a new client connects. You can veto the connection by returning false
		virtual bool OnClientConnect(std::shared_ptr<connection<T>> client)
		{
			return false;
		}

		// Called when a new client is disconnected
		virtual void OnClientDisconnect(std::shared_ptr<connection<T>> client)
		{
		}

		// Called when message arrives
		virtual void OnMessage(std::shared_ptr<connection<T>> client, message<T>& msg)
		{
		}

	protected:
		tsqueue<owned_message<T>> m_qMessagesIn;

		// ASIO context is shared by all the connections and server listening
		asio::io_context m_asioContext;

		// Container of active connections
		std::deque<std::shared_ptr<connection<T>>> m_deqConnections;

		// Thread to run asio context
		std::thread m_threadContext;

		// Aceptor for connectins
		asio::ip::tcp::acceptor m_asioAcceptor;

		// Clients will be identified int the system bia an ID
		uint32_t nIDCounter = 10000;
	};
}