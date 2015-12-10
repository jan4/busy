#include "commands.h"

using namespace aBuild;

namespace commands {

std::set<std::string> getLsFiles(std::string const& _cwd) {
	utils::Cwd cwd(_cwd);
	utils::Process p1 ({"git", "ls-files"});
	utils::Process p2 ({"git", "ls-files", "-o", "--exclude-standard"});
	auto files1 = utils::explode(p1.cout(), "\n");
	auto files2 = utils::explode(p2.cout(), "\n");
	std::set<std::string> files;
	for (auto const& s : files1) {
		files.insert(s);
	}
	for (auto const& s : files2) {
		files.insert(s);
	}
	return files;
}
void printLsFiles(std::string const& _prefix, std::string const& _cwd) {
	auto files = getLsFiles(_cwd);
	for (auto const& s : files) {
		if (_cwd == ".") {
			std::cout << _prefix << s << std::endl;
		} else {
			std::cout << _prefix <<_cwd << "/" << s << std::endl;
		}
	}
}

int listFiles(std::string const& _relPath) {
	if (not utils::fileExists("aBuild.json")) return EXIT_FAILURE;
	printLsFiles(_relPath, ".");
	auto projectDirs = utils::listDirs("packages", true);
	for (auto const& d : projectDirs) {
		auto path = std::string("packages/")+d;
		printLsFiles(_relPath, path);
	}

	return EXIT_SUCCESS;
}

}
