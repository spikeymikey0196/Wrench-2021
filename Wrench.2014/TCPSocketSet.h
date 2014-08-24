#ifndef TCPSOCKETSET_H
#define TCPSOCKETSET_H

#include "SDL_net.h"
#include "TCPSocket.h"
#include <list>

using namespace std;

namespace Wrench
{
	class TCPSocket;

	class TCPSocketSet
	{
		friend class TCPSocket;

	protected:
		SDLNet_SocketSet set;
		list<TCPSocket *> sockets;

	public:
		TCPSocketSet();
		TCPSocket *AddSocket(TCPSocket *socket);
		void RemoveSocket(TCPSocket *socket);
	};
}

#endif
