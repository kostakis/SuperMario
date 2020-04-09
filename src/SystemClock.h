#pragma once
#ifndef SYSTEMCLOCK_H
#define SYSTEMCLOCK_H
#include <chrono>

class SystemClock final
{
private:
	std::chrono::high_resolution_clock clock;
public:
	static SystemClock& Get();
	uint64_t milli_secs() const;
	uint64_t micro_secs() const;
	uint64_t nano_secs() const;
};

uint64_t GetSystemTime(void);
#endif // !SYSTEMCLOCK_H
