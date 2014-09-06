#ifndef ENUMS_H
#define ENUMS_H

enum AIStateEnum
{
	AI_IDLE			=	0x0,
	AI_WATCHNODE	=	0x1,
	AI_FOLLOWPATH	=	0x2,
};

enum ActionStateEnum
{
	ACTION_IDLE			=	0x0,
	ACTION_MOVETOPOINT	=	0x1,
};

#endif
