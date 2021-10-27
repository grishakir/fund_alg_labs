#pragma once
#include <exception>
#include <string>
#include <iostream>
#include "Data.h"
#include "Comparator.h"

class tree_exception : public std::exception
{
	std::string string;
public:
	tree_exception(std::string str);
	const char* what() const;
};

class find_tree_exception : public tree_exception
{
};


template<typename TKey>
class TBinaryTree
{
protected:

	class Node 
	{
	public:
		Node* left = nullptr;
		Node* right = nullptr;
		const TKey* data = nullptr;
	};

	Comparator<TKey> comparator;
	Node* head = nullptr;

public:
	TBinaryTree(Comparator<TKey>& comparator) {
		this->comparator = comparator;
	};

	virtual void preInsert() = 0;

	virtual void postInsert() = 0;

	int insert(const TKey& data) {

		Node* currentNode = nullptr;
		Node* previousNode = nullptr;

		try {
			preInsert();

			if (head == nullptr) {
				head = new Node;
				head->data = &data;
			}
			else {
				currentNode = head;

				while (currentNode != nullptr) {

					if (comparator.compare(data, *(currentNode->data)) > 0) {
						previousNode = currentNode;
						currentNode = currentNode->left;

						if (currentNode == nullptr) {
							previousNode->left = new Node;
							previousNode->left->data = &data;
						}
					}
					else if (comparator.compare(data, *(currentNode->data)) < 0) {
						previousNode = currentNode;
						currentNode = currentNode->right;

						if (currentNode == nullptr) {
							previousNode->right = new Node;
							previousNode->right->data = &data;
						}
					}
					else if (comparator.compare(data, *(currentNode->data)) == 0) {
						throw tree_exception(std::string("Insert error. Detected data with the same key.\m"));
					}
					else {
						throw tree_exception("Something get wrong while insertion.\n");
					}
				}


			}

			postInsert();
		}
		catch (tree_exception exc)
		{
			std::cerr << exc.what();
			return 1;
		}
		return 0;
	};

	int find(const TKey& data) {
		Node* currentNode = nullptr;
		Node* previousNode = nullptr;

		try {
			preInsert();

			if (head == nullptr) {
				throw tree_exception("")
			}
			else {
				currentNode = head;

				while (currentNode != nullptr) {

					if (comparator.compare(data, *(currentNode->data)) > 0) {
						previousNode = currentNode;
						currentNode = currentNode->left;

						if (currentNode == nullptr) {
							previousNode->left = new Node;
							previousNode->left->data = &data;
						}
					}
					else if (comparator.compare(data, *(currentNode->data)) < 0) {
						previousNode = currentNode;
						currentNode = currentNode->right;

						if (currentNode == nullptr) {
							previousNode->right = new Node;
							previousNode->right->data = &data;
						}
					}
					else if (comparator.compare(data, *(currentNode->data)) == 0) {
						throw tree_exception(std::string("Insert error. Detected data with the same key.\m"));
					}
					else {
						throw tree_exception("Something get wrong while insertion.\n");
					}
				}


			}

			postInsert();
		}
		catch (tree_exception exc)
		{
			std::cerr << exc.what();
			return 1;
		}
		return 0;
	}
};

