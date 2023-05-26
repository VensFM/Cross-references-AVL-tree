#pragma once
#include <iostream>
#include <string>
#include <list>

class AVLtree
{
public:
	AVLtree();
	AVLtree(const AVLtree&) = delete;
	AVLtree(AVLtree&& src)noexcept;
	AVLtree& operator= (const AVLtree&) = delete;
	AVLtree& operator= (AVLtree&& src)noexcept;
	~AVLtree();

	bool insert(std::string& key, size_t page);
	bool search(std::string& key);
	bool deleteKey(std::string& key);

	void getTable(std::ostream& out)const;
private:
	struct Node
	{
		std::string key_;
		std::list<size_t> list_;
		Node* left_;
		Node* right_;
		Node* p_;
		int balance_;

		Node(std::string key, size_t page, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr, int balance = 0);
	};

	Node* root_;

	void deleteSubtree(Node* node);
	bool remove(Node* node, std::string& key);
	bool removeNode(Node* node);
	Node* treeSuccessor(Node* node);
	Node* treeMin(Node* node);
	void swap(AVLtree& left, AVLtree& right);
	void lowercase(std::string& key);
	bool isItWord(const std::string& key);
	void inorderWalk(const Node* node, std::ostream& out) const;
	int getHeight(Node* node) const;
	void updateBalance(Node* node);
	void checkBalance(Node* node);
	void fixBalance(Node* node);
	Node* rotateRight(Node* node);
	Node* rotateLeft(Node* node);
};