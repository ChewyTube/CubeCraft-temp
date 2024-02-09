#include "Log.h"

namespace cubecraft {
	void outputLog(std::string info, bool endline) {
		std::cout << info;
		if (endline) {
			std::cout << std::endl;
		}
	}
}