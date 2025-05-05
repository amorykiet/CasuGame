#pragma once

#include <string>

class NodePath {
public:
	NodePath() = default;
	NodePath(const std::string& path) : path(path) {}
	NodePath(const NodePath& other) : path(other.path) {}
	NodePath& operator=(const NodePath& other) {
		if (this != &other) {
			path = other.path;
		}
		return *this;
	}
	const std::string& GetPath() const { return path; }
	void SetPath(const std::string& newPath) { path = newPath; }


private:
	std::string path;
};