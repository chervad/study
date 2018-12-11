#pragma once

#include "cocos2d.h"

#include "IObjective.h"

#include <vector>

class Patrol : public IObjective {
public:
	Patrol(uint16_t x, uint16_t y);
	Patrol(const std::tuple<uint16_t, uint16_t> &point);
	Patrol(const std::vector<std::tuple<uint16_t, uint16_t>> &points);

	void process();
private:
	std::vector<std::tuple<uint16_t, uint16_t>> points;
};
