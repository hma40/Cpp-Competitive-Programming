#include <iostream>
/*
This file contains the implementation of Segment Tree, a data structure that acts as a container that can support the following operations:
- set the value at some index (a[i]:=x) in ϴ(log(n))
- query the minimum, maximum, and sum of a range in ϴ(log(n))
*/
template <typename T> class Node {
    /*
	A structure that can hold data in an interval
	*/
private:
	T data;
    Node<T> *leftChild, *rightChild;
    const size_t left, right;
public:
	size_t getLeft() const {
		/*
		Returns the left bound of the node

		Paremeters: None

		Returns:
		- size_t: the left bound
		*/
		return left;
	}
	size_t getRight() const {
		/*
		Returns the right bound of the node

		Parameters: None

		Returns:
		- size_t: the right bound
		*/
		return right;
	}
	T getData() const {
		/*
		Returns the data in the node

		Parameters: None
		
		Returns: 
		- T: the data in the node
		*/
		return data;
	}
	T setData(T d) {
		/*
		Sets the data in the node

		Parameters: 
		- d (T): the data to replace the current data

		Returns:
		- T: the new data in the node
		*/
		data=d;
		return d;
	}
	Node<T>* getLeftChild() const {
		/*
		Returns a pointer to left child of the node

		Parameters: None

		Returns:
		- Node<T>: the left child of the node
		*/
		return leftChild;
	}
	Node<T>* getRightChild() const {
		/*
		Returns a pointer to right child of the node

		Parameters: None
		
		Returns:
		- Node<T>: the right child of the node
		*/
		return rightChild;
	}
    Node(size_t l, size_t r): leftChild(nullptr), rightChild(nullptr), left(l), right(r) {
		/*
		Constructor for Node given Left and Right bounds

		Parameters:
		- l (size_t): the left bound of the node
		- r (size_t): the right bound of the node
		*/
        if(l==r) return;
        size_t mid = (l+r)/2; //Left child will cover the range [l, (l+r)/2], right child will cover range [(l+r)/2+1, r]
        leftChild = new Node(l, mid);
        rightChild = new Node(mid+1, r);
    }
    Node(T d, size_t l, size_t r): Node(l,r) {
		/*
		Constructor for Node given Left bound, Right bound, and data
		
		Parameters:
		- l (size_t): the left bound of the node
		- r (size_t): the right bound of the node
		- d (T): the data in the node
		*/
        data=d;
    }
    ~Node() {
		/*
		Destructor: recursively deletes leftChild and rightChild to free memory
		*/
        delete leftChild;
        delete rightChild;
    }
    bool intersectsRange(size_t l, size_t r) {
		/*
		Returns whether or not the range [l,r] intersects with [this->left, this->right], the range of this node

		Parameters: 
		- l (size_t): the left bound of the interval
		- r (size_t): the right bound of the interval

		Returns: 
		- bool: 1 if [l,r] intersects [this->left,this->right], 0 otherwise
		*/
        return std::max(l, left)<=std::min(r,right);
    }
};

template <typename T> class SegmentTree {
/*
A data structure that can act as a container supporting the following operations:
- set the value at some index (a[i]:=x) in ϴ(log(n))
- query the minimum, maximum, and sum of a range in ϴ(log(n))

As the implementation will differ for different types, this will be an abstract class
*/
protected:
    Node<T> *root; 
    /*
	Given a root, combines the data from its children to obtain its data

	Parameters:
	- nd (Node<T>&): the node to be updated

	Returns: None
	*/
	virtual void combine(Node<T>& nd) const = 0; 
	 
    T set(Node<T>& currentNode, size_t index, T value) {
		/*
		Sets the data at given index to be value, given that the current Node is currentNode. Returns the new data

		Parameters:
		- currentNode (Node<T>&): the node currently accessed
		- index (size_t): the index of the modification
		- value (T): the data to replace the data at position index with

		Returns: 
		- T: the new data
		*/
        if(currentNode.getLeft()==index&&currentNode.getRight()==index) {
			/*
			This is the base case: the node covers only the index, so we can set the data of the node to value and return
			*/
            currentNode.setData(value);
            return value;
        }
        if(currentNode.getLeftChild()->intersectsRange(index, index)) {
			/*
			This means that leftChild contains the index we want to modify, so we recursively call set() on leftChild
			*/
            set(*(currentNode.getLeftChild()), index, value);
        } else {
			/*
			Otherwise, rightChild contains the index we want to modify, so we recursively call set() on rightChild
			*/
            set(*(currentNode.getRightChild()), index, value);
        }
		//after recursively calling leftChild or rightChild, use the combine() function to update the data on current node
        combine(currentNode);
		return value;
    }
public:
    SegmentTree(size_t size) {
		/*
		Constructor for Segment Tree given size of the tree. Initialize the root Node to cover [0, size-1].

		Parameters:
		- size (size_t): the size of the tree
		*/
        root = new Node<T>(0, size-1);
    }
    ~SegmentTree() {
		/*
		Destructor for Segment Tree: deletes the root
		*/
        delete root;
    }
    T set(size_t index, T value) {
		/*
		Set the data at given index to be value. Returns the new data

		Parameters:
		- index (size_t): the index to be modified
		- value (T): the data to replace the data at position index with

		Returns:
		- T: the new data
		*/
		if(index>root->getRight()) {
			/*
			invalid index, throw an exception
			*/
			throw std::out_of_range("Index out of bounds.");
		}
		//Valid index: call the set() function with root as parameter
        return set(*root, index, value);
    }
};
class SumSegmentTree: public SegmentTree<int> {
/*
A data structure that can act as a container supporting the following operations:
- set the value at some index (a[i]:=x) in ϴ(log(n))
- query the sum of a range in ϴ(log(n))

Each node's data will be the sum of the range it encompasses.
*/
protected:
    void combine(Node<int>& nd) const override {
		/*
		Combine the data from children into this node. In this case, replaces the data of the node to be sum of data from children

		Parameters:
		- nd (Node<int>&): the node to update

		Returns: None
		*/
		nd.setData(nd.getLeftChild()->getData()+nd.getRightChild()->getData());
    }
    int getSum(Node<int>& currentNode, size_t left, size_t right) const {
		/*
		Returns the sum from left to right, given that the current node is currentNode

		Parameters:
		- currentNode (Node<int>&): the current node used
		- left (size_t): the left bound of the sum
		- right (size_t): the right bound of the sum

		Returns:
		- int: the sum from left to right
		*/
        if(left==currentNode.getLeft()&&right==currentNode.getRight()) {
			//base case: the interval of the node is exactly the intervals of the sum. Just return the data in currentNode
			return currentNode.getData();
		}
        int ans = 0;
        if(currentNode.getLeftChild()->intersectsRange(left,right)&&currentNode.getRightChild()->intersectsRange(left,right)) {
			//both leftChild and rightChild intersects the range, so we have to recurse down both children
			//use of min and max here to make sure the range is always valid
            ans = getSum(*(currentNode.getLeftChild()), left, std::min(right, currentNode.getLeftChild()->getRight())) 
				+ getSum(*(currentNode.getRightChild()), std::max(left, currentNode.getRightChild()->getLeft()), right);
        } else if(currentNode.getLeftChild()->intersectsRange(left,right)) {
			//only leftChild intersects the range, so we recurse down left child
            ans = getSum(*(currentNode.getLeftChild()), left, std::min(right, currentNode.getLeftChild()->getRight()));
        } else {
			//only rightChild intersects the range, so we recurse down right child
            ans = getSum(*(currentNode.getRightChild()), std::max(left, currentNode.getRightChild()->getLeft()), right);
        }
        return ans;
    }
public:
    SumSegmentTree(size_t size) : SegmentTree<int>(size) {
		/*
		Constructor for Sum Segment Tree given size of the tree.

		Parameters:
		- size (size_t): the size of the tree
		*/
	}
    int getSum(size_t left, size_t right) const {
		/*
		Returns the sum from left to right

		Parameters:
		- left (size_t): the left bound of the sum
		- right (size_t): the right bound of the sum

		Returns:
		- int: the sum from left to right
		*/
		if(left>right || right>root->getRight()) {
			/*
			invalid index, throw an exception
			*/
			throw std::out_of_range("Index out of bounds.");
		}
        return getSum(*root, left, right);
    }
};
class MinimumMaximumSegmentTree: public SegmentTree<std::pair<int,int>> {
/*
A data structure that can act as a container supporting the following operations:
- set the value at some index (a[i]:=x) in ϴ(log(n))
- query the sum of a range in ϴ(log(n))

Each node's data will be the a pair, containing the minimum and maximum of the range it encompasses.
*/
protected:
    void combine(Node<std::pair<int,int>>& nd) const override {
		/*
		Combine the data from children into this node. In this case, replaces the data of the node with a pair containing both the maximum and minimum

		Parameters:
		- nd (Node<pair<int,int>>&): the node to update

		Returns: None
		*/
		std::pair<int,int> newData;
		newData.first = std::min(nd.getLeftChild()->getData().first, nd.getRightChild()->getData().first);
		newData.second = std::max(nd.getLeftChild()->getData().second, nd.getRightChild()->getData().second);
		nd.setData(newData);
    }
    int getMax(Node<std::pair<int,int>>& currentNode, size_t left, size_t right) const {
		/*
		Returns the max from left to right, given that the current node is currentNode

		Parameters:
		- currentNode (Node<pair<int,int>>&): the current node used
		- left (size_t): the left bound of the range
		- right (size_t): the right bound of the range

		Returns:
		- int: the max value from left to right
		*/
        if(left==currentNode.getLeft()&&right==currentNode.getRight()) {
			//base case: the interval of the node is exactly the range we want. Just return the data in currentNode
			return currentNode.getData().second;
		}
        int ans;
        if(currentNode.getLeftChild()->intersectsRange(left,right)&&currentNode.getRightChild()->intersectsRange(left,right)) {
			//both leftChild and rightChild intersects the range, so we have to recurse down both children
			//use of min and max here to make sure the range is always valid
            ans = std::max(getMax(*(currentNode.getLeftChild()), left, std::min(right, currentNode.getLeftChild()->getRight())), 
			getMax(*(currentNode.getRightChild()), std::max(left, currentNode.getRightChild()->getLeft()), right));
        } else if(currentNode.getLeftChild()->intersectsRange(left,right)) {
			//only leftChild intersects the range, so we recurse down left child
            ans = getMax(*(currentNode.getLeftChild()), left, std::min(right, currentNode.getLeftChild()->getRight()));
        } else {
			//only rightChild intersects the range, so we recurse down left child
            ans = getMax(*(currentNode.getRightChild()), std::max(left, currentNode.getRightChild()->getLeft()), right);
        }
        return ans;
    }
    int getMin(Node<std::pair<int,int>>& currentNode, size_t left, size_t right) const {
		/*
		Returns the min from left to right, given that the current node is currentNode

		Parameters:
		- currentNode (Node<pair<int,int>>&): the current node used
		- left (size_t): the left bound of the range
		- right (size_t): the right bound of the range

		Returns:
		- int: the min value from left to right
		*/
        if(left==currentNode.getLeft()&&right==currentNode.getRight()) {
			//base case: the interval of the node is exactly the range we want. Just return the data in currentNode
			return currentNode.getData().first;
		}
        int ans;
        if(currentNode.getLeftChild()->intersectsRange(left,right)&&currentNode.getRightChild()->intersectsRange(left,right)) {
			//both leftChild and rightChild intersects the range, so we have to recurse down both children
			//use of min and max here to make sure the range is always valid
            ans = std::min(getMin(*(currentNode.getLeftChild()), left, std::min(right, currentNode.getLeftChild()->getRight())), 
			getMin(*(currentNode.getRightChild()), std::max(left, currentNode.getRightChild()->getLeft()), right));
        } else if(currentNode.getLeftChild()->intersectsRange(left,right)) {
			//only leftChild intersects the range, so we recurse down left child
            ans = getMin(*(currentNode.getLeftChild()), left, std::min(right, currentNode.getLeftChild()->getRight()));
        } else {
			//only rightChild intersects the range, so we recurse down left child
            ans = getMin(*(currentNode.getRightChild()), std::max(left, currentNode.getRightChild()->getLeft()), right);
        }
        return ans;
    }
public:
    MinimumMaximumSegmentTree(int size) : SegmentTree<std::pair<int,int>>(size) {
		/*
		Constructor for Minimum Maximum Segment Tree given size of the tree.

		Parameters:
		- size (size_t): the size of the tree
		*/
	}
    int set(size_t index, int val) {
		/*
		sets the data at index to be val

		Parameters:
		- index (size_t)
		- val: the value to set

		Returns:
		- int: the value that was set
		*/
        SegmentTree<std::pair<int,int>>::set(index, {val, val});
		return val;
	}
    int getMin(size_t left, size_t right) const {
		/*
		Returns the minimum from left to right

		Parameters:
		- left (size_t): the left bound of the sum
		- right (size_t): the right bound of the sum

		Returns:
		- int: the minimum from left to right
		*/
		if(left>right || right>root->getRight()) {
			/*
			invalid index, throw an exception
			*/
			throw std::out_of_range("Index out of bounds.");
		}
        return getMin(*root, left, right);
    }
    int getMax(size_t left, size_t right) const {
		/*
		Returns the maximum from left to right

		Parameters:
		- left (size_t): the left bound of the sum
		- right (size_t): the right bound of the sum

		Returns:
		- int: the maximum from left to right
		*/
		if(left>right || right>root->getRight()) {
			/*
			invalid index, throw an exception
			*/
			throw std::out_of_range("Index out of bounds.");
		}
        return getMax(*root, left, right);
    }
};
int main() {
	//driver code
	//initiate a minimum maximum segment tree
    MinimumMaximumSegmentTree seg(10);
	int nextNumber = 0;
    for(size_t i = 0; i < 10; i++) {
		//set the data to 0, 1, 2, ..., 9
		seg.set(i, nextNumber++);
	}
	//test the getMax and getMin functions
    std::cout << seg.getMax(2,3) << " " << seg.getMin(4,8) << std::endl; //expecting (3,4)
    
	//initiate a sum segment tree
	SumSegmentTree seg2(15);
	nextNumber = 0;
    for(size_t i = 0; i < 15; i++) {
		seg2.set(i, nextNumber++);
	}
	//test the getSum function
    std::cout << seg2.getSum(3,5) << std::endl; //expecting 3+4+5=12
}