#include "Package.h"

#include <serializer/serializer.h>

namespace busy {

Package::Package(PackageURL const& _url, busyConfig::Package const& _package)
	: url {_url}
{
	name = _package.name;
	for (auto const& e : _package.extRepositories) {
		extRepositories.emplace_back(e);
	}
	for (auto const& e : _package.projects) {
		projects.emplace_back(e);
	}
	for (auto const& e : _package.overrides) {
		overrides.emplace_back(e);
	}
	for (auto const& e : _package.installations) {
		installations.emplace_back(e);
	}
	for (auto const& e : _package.toolchains) {
		toolchains.emplace_back(e);
	}
	for (auto const& e : _package.flavors) {
		flavors[e.first] = Flavor(e.second);
	}
	for (auto& p : projects) {
		p.setPackagePath(url.getPath());
	}
}


Package::Package(PackageURL const& _url)
	: url {_url} {}


auto Package::getName() const -> std::string const& {
	return name;
}
void Package::setName(std::string const& _name) {
	name = _name;
}

auto Package::getURL() const -> PackageURL const& {
	return url;
}

auto Package::getExtRepositories() const -> ExtRepositories const& {
	return extRepositories;
}
auto Package::getProjects() const -> Projects const& {
	return projects;
}
auto Package::accessProjects() -> Projects& {
	return projects;
}

auto Package::getOverrides() const -> Overrides const& {
	return overrides;
}

auto Package::getInstallations() const -> Installations const& {
	return installations;
}
auto Package::getToolchains() const -> Toolchains const& {
	return toolchains;
}
auto Package::getFlavors() const -> Flavors const& {
	return flavors;
}

auto readPackage(std::string const& _path, PackageURL _url) -> Package {
	static std::map<std::string, busyConfig::Package> packages;

	auto path = _path;
	if (path.size() > 2 && path.at(0) == '.' and path.at(1) == '/') {
		path = _path.substr(2);
	} else if (path.size() == 2 and path == "./") {
		path = ".";
	}


	if (packages.find(path) == packages.end()) {
		auto configPackage = busyConfig::readPackage(path);
		packages[path] = configPackage;
	}

	Package package{_url, packages.at(path)};
	return package;
}




}
