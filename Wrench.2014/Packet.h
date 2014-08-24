#ifndef PACKET_H
#define PACKET_H

namespace Wrench
{
	class Packet
	{
	public:
		int Opcode;
		int Length;
		unsigned char *Data;

		Packet();
		Packet(int nOpcode, int nLength);
		~Packet();
		void Setup(int nOpcode, int nLength);
		void Free();
	};
}

#endif