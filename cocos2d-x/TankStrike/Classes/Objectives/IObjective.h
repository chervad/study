#pragma once

#include "defens.h"

class IObjective {
public:
	IObjective(ObjectiveType objective);
	virtual void process() =0;
protected:
	ObjectiveType objective;
};
