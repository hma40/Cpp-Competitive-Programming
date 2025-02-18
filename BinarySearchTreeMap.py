class BinartSearchTreeMap:
    class Item:
        def __init__(self, key, value=None):
            self.key = key
            self.value = value


    class Node:
        def __init__(self, item):
            self.item = item
            self.parent = None
            self.subSize = 1
            self.left = None
            self.right = None

        def num_children(self):
            count = 0
            if(self.left is not None):
                count += 1
            if(self.right is not None):
                count += 1
            return count

        def disconnect(self):
            self.item = None
            self.parent = None
            self.left = None
            self.right = None


    def __init__(self):
        self.root = None
        self.n = 0

    def __len__(self):
        return self.n

    def is_empty(self):
        return (len(self) == 0)


    # returns value, or raises exception if not found
    def __getitem__(self, key):
        node = self.find_node(key)
        if(node is None):
            raise KeyError(str(key) + " not found")
        else:
            return node.item.value

    # return node with key, or None if not found
    def find_node(self, key):
        cursor = self.root
        while(cursor is not None):
            if(cursor.item.key == key):
                return cursor
            elif(cursor.item.key > key):
                cursor = cursor.left
            else: # (cursor.item.key < key
                cursor = cursor.right
        return None


    # updates value if key already exists
    def __setitem__(self, key, value):
        node = self.find_node(key)
        if(node is not None):
            node.item.value = value
        else:
            self.insert(key, value)

    # assumes that key is not in the tree
    def insert(self, key, value):
        new_item = BinartSearchTreeMap.Item(key, value)
        new_node = BinartSearchTreeMap.Node(new_item)
        if(self.is_empty() == True):
            self.root = new_node
            self.n = 1
        else:
            parent = None
            cursor = self.root
            while(cursor is not None):
                parent = cursor
                if(key < cursor.item.key):
                    cursor = cursor.left
                else:
                    cursor = cursor.right
            if(key < parent.item.key):
                parent.left = new_node
            else:
                parent.right = new_node
            new_node.parent = parent
            new_node = new_node.parent
            while new_node is not None:
                new_node.subSize+=1
                new_node = new_node.parent
            self.n += 1


    # raises an exceprion if ket not in the tree
    def __delitem__(self, key):
        node = self.find_node(key)
        if (node is None):
            raise KeyError(str(key) + " not found")
        else:
            self.delete_node(node)

    # assumes the key is in the tree + returns item that was removed from the tree
    def delete_node(self, node_to_delete):
        item = node_to_delete.item
        num_children = node_to_delete.num_children()
        if(node_to_delete is self.root):
            if (num_children == 0):
                self.root = None
                node_to_delete.disconnect()
                self.n -= 1
            elif (num_children == 1):
                if (self.root.left is not None):
                    self.root = self.root.left
                else:
                    self.root = self.root.right
                self.root.parent = None
                node_to_delete.disconnect()
                self.n -= 1
            else:  # num_children == 2
                max_of_left = self.subtree_max(node_to_delete.left)
                node_to_delete.item = max_of_left.item
                self.delete_node(max_of_left)
        else:
            if(num_children == 0):
                temp = node_to_delete.parent
                while temp is not None:
                    temp.subSize-=1
                    temp=temp.parent
                parent = node_to_delete.parent
                if(node_to_delete is parent.left):
                    parent.left = None
                else:
                    parent.right = None
                node_to_delete.disconnect()
                self.n -= 1
            elif(num_children == 1):
                parent = node_to_delete.parent
                if(node_to_delete.left is not None):
                    child = node_to_delete.left
                else:
                    child = node_to_delete.right
                if(node_to_delete is parent.left):
                    parent.left = child
                else:
                    parent.right = child
                child.parent = parent
                node_to_delete.disconnect()
                self.n -= 1
                temp = parent
                while temp is not None:
                    temp.subSize-=1
                    temp=temp.parent

            else: #(num_children == 2)
                max_in_left = self.subtree_max(node_to_delete.left)
                node_to_delete.item = max_in_left.item
                self.delete_node(max_in_left)

        return item

    def subtree_max(self, subtree_root):
        cursor = subtree_root
        while(cursor.right is not None):
            cursor = cursor.right
        return cursor


    def inorder(self):
        def subtree_inorder(root):
            if (root is None):
                return
            else:
                yield from subtree_inorder(root.left)
                yield root
                yield from subtree_inorder(root.right)

        yield from subtree_inorder(self.root)

    def __iter__(self):
        for node in self.inorder():
            yield node.item.key
    def get_ith_smallest(self, i):
        if self.n<i:
            raise Exception()
        def solve(node, i):
            # print(node.item.key,i)
            lSize = 0
            if node.left is not None:
                lSize = node.left.subSize
            if lSize==i-1:
                return node.item.key
            if lSize<i:
                return solve(node.right, i-lSize-1)
            return solve(node.left, i)
        return solve(self.root, i)
    
# bst = BinartSearchTreeMap()
# bst[7] = None
# bst[5] = None
# bst[1] = None
# bst[14] = None
# bst[10] = None
# bst[3] = None
# bst[9] = None
# bst[13] = None
# print(bst.get_ith_smallest(3))
# print(bst.get_ith_smallest(6))
# del bst[14]
# del bst[5]
# print(bst.get_ith_smallest(3))
# print(bst.get_ith_smallest(6))