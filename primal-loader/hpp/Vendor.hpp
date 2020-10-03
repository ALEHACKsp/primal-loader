#pragma once

//Common headers.
#include <Windows.h>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <psapi.h>
#include <map>

//Loader stuff.
#include "loader/segment/Segment.hpp"
#include "loader/runtime/RuntimeHandler.hpp"

//Segment framework.
#include "segment/SegmentInterpreter.hpp"

//Utils.
#include "util/PanicUtil.hpp"
#include "util/CommonUtil.hpp"
#include "util/stuff/Logger.hpp"
#include "util/stuff/Singleton.hpp"