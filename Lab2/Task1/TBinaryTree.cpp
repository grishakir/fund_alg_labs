#include "TBinaryTree.h"

tree_exception::tree_exception(std::string str) : string(str) {};

const char* tree_exception::what() const noexcept {
	return string.c_str();
}