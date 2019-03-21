#pragma once

struct NoCopy
{
	NoCopy() = default;
	NoCopy& operator=(const NoCopy&) = delete;
};