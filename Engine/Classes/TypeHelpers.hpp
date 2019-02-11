#pragma once

#define LOG(x) std::cout << x << std::endl;

namespace InitSetting
{
	enum Type
	{
		ZeroInit,
		ForceInit,
		FullInit,
		DefaultInit,
	};
};

using int8		=	signed		char;
using uint8		=	unsigned	char;
using int16		=	signed		short int;
using uint16	=	unsigned	short int;
using int32		=	signed		int;
using uint32	=	unsigned	int;
using int64		=	long		long;
using uint64	=	unsigned	long  long;

using String 	=	std::string;