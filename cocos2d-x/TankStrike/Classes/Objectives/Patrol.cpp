#include "Patrol.h"

Patrol::Patrol(uint16_t x, uint16_t y) 
	: IObjective(ObjectiveType::PATROL)
	, points({ std::tuple<uint16_t, uint16_t> (x, y)})
{}

Patrol::Patrol(const std::tuple<uint16_t, uint16_t> &point) 
	: IObjective(ObjectiveType::PATROL)
	, points({ point })
{}

Patrol::Patrol(const std::vector<std::tuple<uint16_t, uint16_t>> &points) 
	: IObjective(ObjectiveType::PATROL)
	, points(points)
{}

void Patrol::process() {

}
