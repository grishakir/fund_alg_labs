#pragma once
#include <exception>
#include <string>
#include <iostream>
#include <map>
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
	//find_tree_exception(std::string str) : tree_exception(str) {};
};

class insert_tree_exception : public tree_exception
{
	insert_tree_exception(std::string str) : tree_exception(str) {};
};

class remove_tree_exception : public tree_exception
{
	remove_tree_exception(std::string str) : tree_exception(str) {};
};

template<typename TKey, typename TValue>

class binary_search_tree : public std::map<TKey, TValue>
{
protected:
	struct Node
	{
		TKey key;
		const TValue* value;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(TKey& _key, const TValue* _value, Node* _left = nullptr, Node* _right = nullptr) {
			key = _key;
			value = _value;
			left = _left;
			right = _right;
		}
	};

	class find_template_method_bst
	{
	public:
		TValue& invoke(Node** head, Comparator<TKey>* comparer, const TKey& key) {
			auto found_node = inner_find(head, comparer, key);
			after_found(head, comparer, key);
			return *found_node.value;
		}
	private:
		Node* inner_find(Node** head, Comparator<TKey>* comparer, const TKey& key) {
			Node* currentNode = head;
			while (currentNode != nullptr) {
				if (comparer->compare(currentNode->key, key) > 0) {
					currentNode = currentNode->right;
				}
				else if (comparer->compare(currentNode->key, key) < 0) {
					currentNode = currentNode->left;
				}
				else {
					return currentNode;
				}
			}

			throw find_tree_exception("There is no such key\n");
		}
	protected:
		virtual void after_found(Node* head, Comparator<TKey>* comparer, const TKey& key)
		{
			// TODO: по умолчанию метод ничего не делает, но вызывается
		};
	};
	class insert_template_method_bst
	{
	public:
		int invoke(Node** head, Comparator<TKey>* comparer, const TKey& key, TValue* value) {
			try {
				inner_insert(head, comparer, key, value);
				after_insert(head, comparer, key, value);
				return 0;
			}
			catch (const insert_tree_exception& exception) {
				return 1;
			}
		}

	private:
		void inner_insert(Node** head, Comparator<TKey>* comparer, const TKey& key, const TValue* value) {
			if (head == nullptr) {
				*head = new Node(key, value);
			}
			else {
				Node* previousNode = *head;
				Node* currentNode = *head;

				while (currentNode != nullptr) {
					if (comparer->compare(currentNode->key, key) > 0) {
						previousNode = currentNode;
						currentNode = currentNode->right;
					}
					else if (comparer->compare(currentNode->key, key) < 0) {
						previousNode = currentNode;
						currentNode = currentNode->left;
					}
					else {
						throw insert_tree_exception("There is similar key in the tree\n");
					}
				}

				currentNode = new Node(key, value);

				if (comparer(currentNode->key, key) > 0) {
					previousNode->right = currentNode;
				}
				else {
					previousNode->left = currentNode;
				}
			}
		}
	protected:
		virtual void after_insert(Node* found_node)
		{
			// TODO: по умолчанию метод ничего не делает, но вызывается
		};
	};
	class remove_template_method_bst
	{
	public:
		int invoke(Node** head, Comparator<TKey>* comparer, const TKey& key) {
			try {
				auto incert = inner_remove(head, comparer, key);
				after_remove(head, comparer, key);
				return 0;
			}
			catch (const remove_tree_exception& exception) {
				return 1;
			}
		}

	private:
		Node* inner_remove(Node** head, Comparator<TKey>* comparer, const TKey& key) {
			Node* current_node = *head;
			Node* previous_node = *head;

			while (current_node != nullptr) {
				if (comparer->compare(current_node->key, key) > 0) {
					previous_node = current_node;
					current_node = current_node->right;
				}
				else if (comparer->compare(current_node->key, key) < 0) {
					previous_node = current_node;
					current_node = current_node->left;
				}
				else {
					break;
				}
			}

			if (current_node == nullptr) {
				throw find_tree_exception(std::string("There is no such key\n"));
			}

			if (current_node->left == nullptr) {
				if (comparer->compare(previous_node->key, current_node->key) > 0) {
					previous_node->right = current_node->right;
				}
				else {
					previous_node->left = current_node->right;
				}

				delete current_node;
			}
			else if (current_node->right == nullptr) {
				if (comparer->compare(previous_node->key, current_node->key) > 0) {
					previous_node->right = current_node->left;
				}
				else {
					previous_node->left = current_node->left;
				}

				delete current_node;
			}
			else {
				Node* previous_node_trans = current_node;
				current_node = current_node->right;

				while (current_node->left != nullptr)
				{
					previous_node_trans = current_node;
					current_node = current_node->right;
				}

				previous_node_trans->right = nullptr;

				if (comparer->compare(previous_node->key, current_node->key) > 0) {
					delete previous_node->right;
					previous_node->right = current_node;
				}
				else {
					delete previous_node->left;
					previous_node->left = current_node;
				}
			}

		}
	protected:
		virtual void after_remove(Node** head, Comparator<TKey>* comparer, const TKey& key)
		{
			// TODO: по умолчанию метод ничего не делает, но вызывается
		};
	};
private:
	find_template_method_bst _finder;
	insert_template_method_bst _inserter;
	remove_template_method_bst _remover;
	Comparator<TKey>* _comparer;
protected:
	Node* head;

	void copy_bypass(Node* node) {
		if (node != nullptr) {
			this->insert(node->key, node->value);
			copy_bypass(node->right);
			copy_bypass(node->left);
		}
	};

	void delete_bypass(Node* node) {
		if (node != nullptr) {
			delete_bypass(node->right);
			delete_bypass(node->left);
			this->remove(node->key);
		}
	}
public:
	binary_search_tree(Comparator<TKey>* comparer) {
		_finder = find_template_method_bst();
		_inserter = insert_template_method_bst();
		_remover = remove_template_method_bst();
		_comparer = comparer;
	};

	binary_search_tree(binary_search_tree& tree) {
		copy_bypass(*head);
	};

	binary_search_tree& operator=(binary_search_tree& tree) {
		binary_search_tree res(tree);
		delete_bypass(head);
		*this = res;
		return *this;
	};

	~binary_search_tree() {
		delete_bypass(head);
	};
	TValue& find(const TKey& by)
	{
		return _finder.invoke(&head, _comparer, by);
	}

	void insert(const TKey& by, const TValue* target)
	{
		_inserter.invoke(&head, _comparer, by, target);
	}

	TValue remove(const TKey& by)
	{
		return _remover.invoke(&head, _comparer, by);
	}

	void prefix_bypass(void (*function) (TKey, TValue*, int), Node* node = head, int depth = 0) {
		if (node != nullptr) {
			function(node->key, node->value, depth);
			prefix_bypass(function, node->left, depth + 1);
			prefix_bypass(function, node->right, depth + 1);
		}
	}

	void infix_bypass(void (*function) (TKey, TValue*, int), Node* node = head, int depth = 0) {
		if (node != nullptr) {
			prefix_bypass(function, node->left, depth + 1);
			function(node->key, node->value, depth);
			prefix_bypass(function, node->right, depth + 1);
		}
	}

	void postfix_bypass(void (*function) (TKey, TValue*, int), Node* node = head, int depth = 0) {
		if (node != nullptr) {
			prefix_bypass(function, node->left, depth + 1);
			prefix_bypass(function, node->right, depth + 1);
			function(node->key, node->value, depth);
		}
	}
};
