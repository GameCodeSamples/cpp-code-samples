#pragma once

#include "net_common.hpp"

namespace net
{
	template <typename T>
	class client_interface
	{
	public:
		client_interface()
		{
			//m_socket = asio::ip::tcp::socket(m_context);
		}

		~client_interface()
		{
			Discconect();
		}

	public:
		// Send message to the server
		void Send(const message<T>& msg)
		{
			if (IsConnected())
				m_connection->Send(msg);
		}

		// Connect to a server
		bool Connect(const std::string& host, const uint16_t port)
		{
			try
			{
				// resolver to allow hostname or ip address
				asio::ip::tcp::resolver resolver = asio::ip::tcp::resolver(m_context);
				asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

				// create connection
				m_connection = std::make_unique<connection<T>>(
					connection<T>::owner::client,
					m_context,
					asio::ip::tcp::socket(m_context),
					m_qMessagesIn
				);

				// Tell the connection to connect to server
				m_connection->ConnectToServer(endpoints);

				// Start thread context (bind this)
				thrContext = std::thread([this]() { m_context.run(); });

				return true;
			}
			catch (const std::exception& e)
			{
				std::cerr << "Client exception: " << e.what() << std::endl;
				return false;
			}

		}

		// Disconnect from the server
		void Discconect()
		{
			if (IsConnected())
			{
				m_connection->Disconnect();
			}

			m_context.stop(); // Stop asio context

			if (thrContext.joinable()) // If the thread still running stop it
			{
				thrContext.join();
			}

			// Destroy the connection object (Shared pointer) 
			m_connection.release();
		}

		bool IsConnected()
		{
			if (m_connection)
				return m_connection->IsConnected();
			else
				return false;
		}

		// Allows access to the queue of messages recieved from the server
		tsqueue<owned_message<T>>& Incoming()
		{
			return this->m_qMessagesIn;
		}

	protected:
		// This I/O execution context represents your program's link to the operating system's I/O services.
		asio::io_context m_context;

		// this thread avoids that context operations block main thread
		std::thread thrContext;

		// A client has a single connextio object to the server
		std::unique_ptr<connection<T>> m_connection;


	private:
		// Queue to store incomming messages from the server
		tsqueue<owned_message<T>> m_qMessagesIn;
	};
}