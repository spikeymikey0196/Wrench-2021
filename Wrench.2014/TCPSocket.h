#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "SDL_net.h"
#include "Packet.h"

namespace Wrench
{
	class TCPSocketSet;

	class TCPSocket
	{
		friend class TCPSocketSet;

	protected:
		TCPSocketSet *set;
		TCPsocket socket;
		IPaddress ip;

		bool SendData(int Length, char *Data);
		unsigned char *GetData(int Length);
	public:
		TCPSocket(TCPSocketSet *SocketSet);
		TCPSocket(TCPSocketSet *SocketSet, const char *address, int Port);
		bool Connect(const char *address, int Port);
		bool Connected();
		void Disconnect();

		void SendData(const Packet &msg);
		bool GetData(Packet &msg);
		TCPSocket *AcceptSocket();
	};
}

#endif