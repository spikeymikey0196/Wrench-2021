#include "TCPSocketSet.h"

namespace Wrench
{
	TCPSocketSet::TCPSocketSet()
	{
		set = NULL;
	};

	TCPSocket *TCPSocketSet::AddSocket(TCPSocket *socket)
	{
		sockets.push_back(socket);

		if (set) SDLNet_FreeSocketSet(set);
		set = SDLNet_AllocSocketSet(sockets.size());

		for (auto it : sockets)
			SDLNet_TCP_AddSocket(set, it->socket);

		return socket;
	};

	void TCPSocketSet::RemoveSocket(TCPSocket *socket)
	{
		sockets.remove(socket);

		if (set) SDLNet_FreeSocketSet(set);
		set = SDLNet_AllocSocketSet(sockets.size());

		for (auto it : sockets)
			SDLNet_TCP_AddSocket(set, it->socket);
	};

}
