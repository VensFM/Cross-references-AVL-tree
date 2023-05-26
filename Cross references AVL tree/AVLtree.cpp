#include "AVLtree.h"

AVLtree::Node::Node(std::string key, size_t page, Node* left, Node* right, Node* p, int balance)
{
	key_ = key;
	list_.push_back(page);
	left_ = left;
	right_ = right;
	p_ = p;
	balance_ = balance;
}

AVLtree::AVLtree() : root_(nullptr) {}

AVLtree::AVLtree(AVLtree&& src)noexcept
{
	swap(*this, src);
}

AVLtree& AVLtree::operator=(AVLtree&& src)noexcept
{
	if (root_ == src.root_)
	{
		return *this;
	}
	swap(*this, src);
	deleteSubtree(src.root_);
	return *this;
}

AVLtree::~AVLtree()
{
	deleteSubtree(root_);
}

bool AVLtree::insert(std::string& key, size_t page)
{
	lowercase(key);
	if (!isItWord(key))
	{
		std::cerr << "\n This key isn't a word!!!\n\n";
		return false;
	}
	if (root_ == nullptr)
	{
		root_ = new Node(key, page, nullptr, nullptr, nullptr);
		return true;
	}
	Node* temp = root_;
	while (temp != nullptr)
	{
		if (key > temp->key_)
		{
			if (temp->right_ == nullptr)
			{
				temp->right_ = new Node(key, page, nullptr, nullptr, temp);
				checkBalance(temp);
				return true;
			}
			temp = temp->right_;
			continue;
		}
		if (key < temp->key_)
		{
			if (temp->left_ == nullptr)
			{
				temp->left_ = new Node(key, page, nullptr, nullptr, temp);
				checkBalance(temp);
				return true;
			}
			temp = temp->left_;
			continue;
		}
		if (key == temp->key_)
		{
			temp->list_.push_back(page);
			return true;
		}
	}
	return false;
}

bool AVLtree::search(std::string& key)
{
	lowercase(key);
	if (!isItWord(key))
	{
		std::cerr << "\n This key isn't a word!!!\n\n";
		return false;
	}
	Node* temp = root_;
	while (temp != nullptr && key != temp->key_)
	{
		if (key > temp->key_)
		{
			temp = temp->right_;
		}
		else
		{
			temp = temp->left_;
		}
	}
	return (temp != nullptr);
}

bool AVLtree::deleteKey(std::string& key)
{
	lowercase(key);
	if (!isItWord(key))
	{
		std::cerr << "\n This key isn't a word!!!\n\n";
		return false;
	}
	return remove(root_, key);
}

void AVLtree::getTable(std::ostream& out) const
{
	inorderWalk(root_, out);
}

void AVLtree::deleteSubtree(Node* node)
{
	if (node == nullptr)
	{
		return;
	}
	deleteSubtree(node->left_);
	deleteSubtree(node->right_);
	delete node;
}

bool AVLtree::remove(Node* node, std::string& key)
{
	if (node != nullptr && node->key_ < key)
	{
		return remove(node->right_, key);
	}
	else if (node != nullptr && node->key_ > key)
	{
		return remove(node->left_, key);
	}
	else if (node != nullptr && node->key_ == key)
	{
		return removeNode(node);
	}
	return false;
}

bool AVLtree::removeNode(Node* node)
{
	if (node->left_ == nullptr && node->right_ == nullptr)
	{
		if (node->p_ != nullptr)
		{
			if (node == node->p_->right_)
			{
				node->p_->right_ = nullptr;
			}
			else
			{
				node->p_->left_ = nullptr;
			}
			checkBalance(node->p_);
			delete node;
			return true;
		}
		else
		{
			root_ = nullptr;
			delete node;
			return true;
		}
	}

	if (node->left_ != nullptr && node->right_ == nullptr)
	{
		if (node->p_ != nullptr)
		{
			if (node == node->p_->right_)
			{
				node->p_->right_ = node->left_;
			}
			else
			{
				node->p_->left_ = node->left_;
			}
			node->left_->p_ = node->p_;
			checkBalance(node->p_);
			delete node;
			return true;
		}
		else
		{
			root_ = node->left_;
			root_->p_ = nullptr;
			delete node;
			return true;
		}
	}

	if (node->left_ == nullptr && node->right_ != nullptr)
	{
		if (node->p_ != nullptr)
		{
			if (node == node->p_->right_)
			{
				node->p_->right_ = node->right_;
			}
			else
			{
				node->p_->left_ = node->right_;
			}
			node->right_->p_ = node->p_;
			checkBalance(node->p_);
			delete node;
			return true;
		}
		else
		{
			root_ = node->right_;
			root_->p_ = nullptr;
			delete node;
			return true;
		}
	}

	if (node->left_ != nullptr && node->right_ != nullptr)
	{
		Node* temp = treeSuccessor(node);
		node->key_ = temp->key_;
		std::swap(node->list_, temp->list_);
		return removeNode(temp);
	}
	return false;
}

AVLtree::Node* AVLtree::treeSuccessor(Node* node)
{
	if (node->right_ != nullptr)
	{
		return treeMin(node->right_);
	}
	Node* temp = node->p_;
	while (node != nullptr && node == temp->right_)
	{
		node = temp;
		temp = temp->p_;
	}
	return temp;
}

AVLtree::Node* AVLtree::treeMin(Node* node)
{
	while (node->left_ != nullptr)
	{
		node = node->left_;
	}
	return node;
}

void AVLtree::swap(AVLtree& left, AVLtree& right)
{
	std::swap(left.root_, right.root_);
}

void AVLtree::lowercase(std::string& key)
{
	size_t i = 0;
	while (key[i] != '\0')
	{
		if (key[i] >= 'A' && key[i] <= 'Z')
		{
			key[i] += 32;
		}
		++i;
	}
}

bool AVLtree::isItWord(const std::string& key)
{
	if (key.length() < 1)
	{
		return false;
	}
	if (key[0] < 'a' || key[0] > 'z')
	{
		return false;
	}
	for (size_t i = 1; i < key.length(); ++i)
	{
		if ((key[i] < 'a' || key[i] > 'z') && key[i] != '\'')
		{
			return false;
		}
	}
	return true;
}

void AVLtree::inorderWalk(const Node* node, std::ostream& out) const
{
	if (node == nullptr)
	{
		return;
	}
	inorderWalk(node->left_, out);
	out.width(20);
	out << node->key_ << " | ";
	for (auto iter = node->list_.begin(); iter != node->list_.end(); ++iter)
	{
		out << *iter << " ";
	}
	out << "\n";
	inorderWalk(node->right_, out);
}

int AVLtree::getHeight(Node* node) const
{
	if (node == nullptr)
	{
		return 0;
	}
	int leftHeight = getHeight(node->left_);
	int rightHeight = getHeight(node->right_);
	if (leftHeight > rightHeight)
	{
		return leftHeight + 1;
	}
	else
	{
		return rightHeight + 1;
	}
}

void AVLtree::updateBalance(Node* node)
{
	node->balance_ = getHeight(node->right_) - getHeight(node->left_);
}

void AVLtree::checkBalance(Node* node)
{
	while (node != nullptr)
	{
		updateBalance(node);
		if (node->balance_ > 1 || node->balance_ < -1)
		{
			fixBalance(node);
		}
		node = node->p_;
	}
}

void AVLtree::fixBalance(Node* node)
{
	if (node->balance_ == 2)
	{
		if (node->right_->balance_ < 0)
		{
			node->right_ = rotateRight(node->right_);
		}
		if (node->p_ != nullptr)
		{
			Node* buf = node->p_;
			if (buf->right_ == node)
			{
				buf->right_ = rotateLeft(node);
			}
			if (buf->left_ == node)
			{
				buf->left_ = rotateLeft(node);
			}
		}
		else
		{
			rotateLeft(node);
		}
		return;
	}
	if (node->balance_ == -2)
	{
		if (node->left_->balance_ > 0)
		{
			node->left_ = rotateLeft(node->left_);
		}
		if (node->p_ != nullptr)
		{
			Node* buf = node->p_;
			if (buf->right_ == node)
			{
				buf->right_ = rotateRight(node);
			}
			if (buf->left_ == node)
			{
				buf->left_ = rotateRight(node);
			}
		}
		else
		{
			rotateRight(node);
		}
		return;
	}
}

AVLtree::Node* AVLtree::rotateRight(Node* node)
{
	Node* buf = node->left_;
	node->left_ = buf->right_;
	if (buf->right_ != nullptr)
	{
		buf->right_->p_ = node;
	}
	buf->right_ = node;
	buf->p_ = node->p_;
	node->p_ = buf;
	updateBalance(node);
	updateBalance(buf);
	if (buf->p_ == nullptr)
	{
		root_ = buf;
	}
	return buf;
}

AVLtree::Node* AVLtree::rotateLeft(Node* node)
{
	Node* buf = node->right_;
	node->right_ = buf->left_;
	if (buf->left_ != nullptr)
	{
		buf->left_->p_ = node;
	}
	buf->left_ = node;
	buf->p_ = node->p_;
	node->p_ = buf;
	updateBalance(node);
	updateBalance(buf);
	if (buf->p_ == nullptr)
	{
		root_ = buf;
	}
	return buf;
}