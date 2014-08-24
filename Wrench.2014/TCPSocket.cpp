#include "TCPSocket.h"
#include "TCPSocketSet.h"

namespace Wrench
{
	TCPSocket::TCPSocket(TCPSocketSet *SocketSet)
	{
		set = SocketSet;
		socket = NULL;
	};

	TCPSocket::TCPSocket(TCPSocketSet *SocketSet, const char *address, int Port)
	{
		set = SocketSet;
		socket = NULL;

		Connect(address, Port);
	};

	bool TCPSocket::Connect(const char *address, int Port)
	{
		SDLNet_ResolveHost(&ip, address, Port);
		socket = SDLNet_TCP_Open(&ip);

		if (socket)
		{
			set->AddSocket(this);
			return true;
		}

		return false;
	};

	bool TCPSocket::Connected()
	{
		if (socket)
			return true;
		return false;
	};

	void TCPSocket::Disconnect()
	{
		if (socket)
		{
			SDLNet_TCP_Close(socket);
			socket = NULL;
			set->RemoveSocket(this);
		}
	};

	void TCPSocket::SendData(const Packet &msg)
	{
		char *data = (char *)calloc(msg.Length + 8, 1);

		memcpy(&data[0], &msg.Opcode, 4);
		memcpy(&data[4], &msg.Length, 4);
		memcpy(&data[8], msg.Data, msg.Length);

		SendData(msg.Length + 8, data);

		delete[] data;
	};

	bool TCPSocket::GetData(Packet &msg)
	{
		if (Connected())
		{
			if (SDLNet_CheckSockets(set->set, 0) && SDLNet_SocketReady(socket))
			{
				char headerBuffer[9] = { 0 };
				if (SDLNet_TCP_Recv(socket, headerBuffer, 8) > 0)
				{
					memcpy(&msg.Opcode, &headerBuffer[0], 4);
					memcpy(&msg.Length, &headerBuffer[4], 4);

					msg.Data = GetData(msg.Length);

					if (msg.Length > 0 && msg.Data == NULL)
						return false;
				}
				else
				{
					return false;
				}
			}
		}

		return true;
	};

	TCPSocket *TCPSocket::AcceptSocket()
	{
		TCPsocket tempSocket;
		tempSocket = SDLNet_TCP_Accept(socket);

		if (tempSocket)
		{
			TCPSocket *temp = new TCPSocket(set);
			temp->socket = tempSocket;
			set->AddSocket(temp);
			return temp;
		}

		return NULL;
	};

	bool TCPSocket::SendData(int Length, char *Data)
	{
		if (socket)
		{
			SDLNet_TCP_Send(socket, (void *)Data, Length);
			return true;
		}

		return false;
	};

	unsigned char *TCPSocket::GetData(int Length)
	{
		if (Connected() && Length > 0)
		{
			if (SDLNet_CheckSockets(set->set, 0) && SDLNet_SocketReady(socket))
			{
				unsigned char *data = (unsigned char *)calloc(Length + 1, 1);

				if (SDLNet_TCP_Recv(socket, data, Length) > 0)
				{
					return data;
				}
			}
		}

		return NULL;
	};

}
