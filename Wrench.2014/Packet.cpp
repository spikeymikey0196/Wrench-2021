#include "Packet.h"
#include <cstdlib>

using namespace std;

namespace Wrench
{
	Packet::Packet()
	{
		Opcode = 0;
		Length = 0;
		Data = NULL;
	};

	Packet::Packet(int nOpcode, int nLength)
		: Packet()
	{
		Setup(nOpcode, nLength);
	};

	Packet::~Packet()
	{
		Free();
	};

	void Packet::Setup(int nOpcode, int nLength)
	{
		Opcode = nOpcode;
		Length = nLength;

		Data = (unsigned char*)calloc(Length + 1, 1);
	};

	void Packet::Free()
	{
		if (Data)
		{
			delete[] Data;
			Data = NULL;
		}
	};

}
