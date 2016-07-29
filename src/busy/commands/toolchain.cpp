#include "commands.h"

#include "NeoWorkspace.h"
#include <iostream>

using namespace busy;

namespace commands {

void toolchain(std::string const& _toolchain) {
	NeoWorkspace ws;

	auto toolchains = ws.getToolchains();

	auto iter = toolchains.find(_toolchain);
	if (iter == toolchains.end()) {
		std::cout << "Toolchain not found" << std::endl;
		return;
	}

	std::cout << "found toolchain: " << _toolchain << " but this function is not implemented yet" << std::endl;
}

}
