#pragma once

#include "utils.h"

namespace git {

void clone(std::string const& _cwd, std::string const& _url, std::string const& _commit, std::string const& _dir);

auto pull(std::string const& _cwd) -> std::string;
auto push(std::string const& _cwd) -> std::string;
bool isDirty(std::string const& _cwd);
void checkout(std::string const& _cwd, std::string const& _commit);
auto getBranch(std::string const& _cwd) -> std::string;

int untrackedFiles(std::string const& _cwd);
int changedFiles(std::string const& _cwd);
int commitsAhead(std::string const& _cwd);

}
