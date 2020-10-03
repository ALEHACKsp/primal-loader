#pragma once

#include "../Vendor.hpp"
#include "../util/stuff/Singleton.hpp"

//This class is made to maintain separation between the primal loader and the segment framework.
//Since sometimes you have to change the loader itself, this class is ideal for this purpose.
class SegmentInterpreter : public SegmentTranslator {

public:

	void CallbackWithOEP (CallbackType type) {
		//Place invoke function from own framework.
	}

};