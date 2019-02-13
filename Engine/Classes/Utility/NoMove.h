#pragma once

struct NoMove
{
	NoMove() = default;
	NoMove& operator= (NoCopy&&) = delete;
	NoMove(NoCopy&&) = delete;
};