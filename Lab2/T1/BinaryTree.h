#pragma once
#include "tree_exception.h"
#include "AssociativeContainer.h"
#include "Comparer.h"
template <typename TKey, typename TValue>

class BinaryTree :
    public AssociativeContainer<TKey, TValue>
{
private:
	struct Node 
	{
		TKey _key;
		TValue _value;
		Node* _left;
		Node* _right;

		Node(const TKey& key, const TValue& value, Node* left = nullptr, Node* right = nullptr) {
			_key = key;
			_value = value;
			_left = left;
			_right = right;
		};

		Node(Node* node) {
			if (node->_left && node->_right) {
				node = new Node(node->_key, node->_value, new Node(node->_left), new Node(node->_right));
			}
			else if (node->_left && !node->_right) {
				node = new Node(node->_key, node->_value, new Node(node->_left));
			}
			else if (!node->_left && node->_right) {
				node = new Node(node->_key, node->_value, nullptr, new Node(node->_right));
			}
			else
			{
				node = new Node(node->_key, node->_value);
			}
		}
	};

	class _incerter 
	{
		Comparer<TKey> *_comparer;
	public:
		_incerter(Comparer<TKey>* comparer) {
			_comparer = comparer;
		};

		void invoke(const TKey& key, const TValue& value, Node** head) {
			preIncert();
			
			if (!*head){
				*head = new Node(key, value);
			}
			else {
				Node* previousNode = *head;
				Node* currentNode = *head;
				
				while (currentNode) {
					previousNode = currentNode;
					if (_comparer->compare(key, currentNode->_key) > 0) {
						currentNode = currentNode->_right;
					}
					else if (_comparer->compare(key, currentNode->_key) < 0) {
						currentNode = currentNode->_left;
					}
					else {
						throw tree_exception("Pizdec incesrt");
					}
				}

				if (_comparer->compare(key, previousNode->_key) > 0) {
					currentNode->_right = new Node(key, value);
				}
				else {
					currentNode->_left = new Node(key, value);
				}

			}
			postIncert();
		};
	private:
		void preIncert() {};
		void postIncert() {};
	};

	class _finder
	{
		Comparer<TKey>* _comparer;
	public:
		_finder(Comparer<TKey>* comparer) {
			_comparer = comparer;
		};

		TValue& invoke(const TKey& key, Node* head) {
			preFind();
			const Node* currentNode = head;
			if (currentNode) {
				while (_comparer->compare(key, currentNode->_key)) {
					if (_comparer->compare(key, currentNode->_key) < 0)
					{
						currentNode = currentNode->_left;
					}
					else {
						currentNode = currentNode->_right;
					}

					if (!currentNode) {
						throw tree_exception("Pizda. Net takoy nody");
					}
				}


			}
			
			throw tree_exception("Pizda. Net takoy nody");
			
			postFind();
		};
	private:
		void preFind() {};
		void postFind() {};
	};

	class _remover
	{
		Comparer<TKey>* _comparer;
	public:
		_remover(Comparer<TKey>* comparer) {
			_comparer = comparer;
		};

		void invoke(const TKey& key, Node** head) {
			preRemove();

			Node* currentNode = *head;
			Node* previousNode = *head;
			bool leftFlag = 0;

			if (currentNode) {
				while (_comparer->compare(key, currentNode->_key)) {
					previousNode = currentNode;
					if (_comparer->compare(key, currentNode->_key) < 0)
					{
						currentNode = currentNode->_left;
						leftFlag = 1;
					}
					else {
						currentNode = currentNode->_right;
						leftFlag = 0;
					}


					if (!currentNode) {
						throw tree_exception("Pizda. Net takoy nody");
					}
				}

				if (!currentNode->_left) {
					if (leftFlag) {
						previousNode->_left = currentNode->_right;
						delete currentNode;
					}
					else {
						previousNode->_right = currentNode->_right;
						delete currentNode;
					}
				}
				else if (!currentNode->_right) {
					if (leftFlag) {
						previousNode->_left = currentNode->_left;
						delete currentNode;
					}
					else {
						previousNode->_right = currentNode->_left;
						delete currentNode;
					}
				}
				else {
					Node* previousNodeForTransportation = currentNode->_left;
					Node* nodeForTransportation = currentNode->_left;

					while (nodeForTransportation->_right || nodeForTransportation->_left) {
						previousNodeForTransportation = nodeForTransportation;
						if (nodeForTransportation->_right) {
							nodeForTransportation = nodeForTransportation->_right;
						}
						else{
							nodeForTransportation = nodeForTransportation->_left;
						}
						
					}
					previousNodeForTransportation->_left = nullptr;
					previousNodeForTransportation->_right = nullptr;
					if (leftFlag) {
						previousNode->_left = nodeForTransportation;
						previousNode->_left->_left = currentNode->_left;
						previousNode->_left->_right = currentNode->_right;
					}
					else {
						previousNode->_right = nodeForTransportation;
						previousNode->_right->_left = currentNode->_left;
						previousNode->_right->_right = currentNode->_right;
					}

				}
			}
			else
			{
				throw tree_exception("Pizda. Net takoy nody");
			}

			postRemove();
		};
	private:
		void preRemove() {};
		void postRemove() {};
	};

	Comparer<TKey>* comparer;
	_remover* remover;
	_finder* finder;
	_incerter* incerter;
	Node* head;

protected:
	void _prefixBypass(void (*func) (TKey, TValue, int), Node* node, int depth) {
		if (node) {
			func(node->_key, node->_value, depth);
			_prefixBypass(func, node->_left, depth + 1);
			_prefixBypass(func, node->_right, depth + 1);
		}
	};
	void _infixBypass(void (*func) (TKey, TValue, int), Node* node, int depth) {
		if (node) {
			_prefixBypass(func, node->_left, depth + 1);
			func(node->_key, node->_value, depth);
			_prefixBypass(func, node->_right, depth + 1);
		}
	}
	void _postfixBypass(void (*func) (TKey, TValue, int), Node* node, int depth) {
		if (node) {
			func(node->_key, node->_value, depth);
			_prefixBypass(func, node->_left, depth + 1);
			_prefixBypass(func, node->_right, depth + 1);
		}
	};

	void deleteBypass(Node* node) {
		if (node) {
			deteleBypass(node->_left);
			deteleBypass(node->_right);
			delete node;
		}
		
	}
public:
	BinaryTree(Comparer<TKey>* _comparer) {
		comparer = _comparer;
		finder = new _finder(comparer);
		incerter = new _incerter(comparer);
		remover = new _remover(comparer);
		head = nullptr;
	};

	void incert(const TKey& key, const TValue& value) override {
		incerter->invoke(key, value, &head);
	};

	TValue& find(const TKey& key) {
		return finder->invoke(key, head);
	};

	void remove(const TKey& key) override {
		remover->invoke(key, &head);
	};

	void prefixBypass(void (*func) (TKey, TValue, int)) {
		_prefixBypass(func, head, 0);
	}

	void infixBypass(void (*func) (TKey, TValue, int)) {
		_infixBypass(func, head, 0);
	}

	void postfixBypass(void (*func) (TKey, TValue, int)) {
		_postfixBypass(func, head, 0);
	}

	BinaryTree(BinaryTree<TKey, TValue>& tree) {
		comparer = tree.comparer;
		finder = new _finder(comparer);
		incerter = new _incerter(comparer);
		remover = new _remover(comparer);
		deleteBypass(this->head);
		if (head) {
			head = new Node(tree.head);
		}

		
	}

	~BinaryTree() {
		deleteBypass(this->head);
		delete incerter;
		delete remover;
		delete finder;
	}
};

