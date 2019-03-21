#pragma once

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

template<class ...T>
static const void PrintLog(String Msg, T...Args)
{
	std::printf(Msg.c_str(), Args...);
	std::cout << std::endl;
}

#define LOG(Msg) std::cout << Msg << std::endl;
#define FMT_LOG(Msg, args...) PrintLog(Msg, args);