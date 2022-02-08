class Doubly_Linked_List_Node:
    def __init__(self, x):
        self.item = x
        self.prev = None
        self.next = None

    def later_node(self, i):
        if i == 0: return self
        assert self.next
        return self.next.later_node(i - 1)

class Doubly_Linked_List_Seq:
    def __init__(self):
        self.head = None
        self.tail = None

    def __iter__(self):
        node = self.head
        while node:
            yield node.item
            node = node.next

    def __str__(self):
        return '-'.join([('(%s)' % x) for x in self])

    def build(self, X):
        for a in X:
            self.insert_last(a)

    def get_at(self, i):
        node = self.head.later_node(i)
        return node.item

    def set_at(self, i, x):
        node = self.head.later_node(i)
        node.item = x

    def insert_first(self, x):
        ###########################
        # Part (a): Implement me! #
        ###########################
        node = Doubly_Linked_List_Node(x)
        if self.head is None:
            self.head = node
            self.tail = node
        else:
            node.next = self.head
            self.head.prev = node
            self.head = node

    def insert_last(self, x):
        ###########################
        # Part (a): Implement me! #
        ###########################
        node = Doubly_Linked_List_Node(x)
        if self.tail is None:
            self.head = node
            self.tail = node
        else:
            node.prev = self.tail
            self.tail.next = node
            self.tail = node

    def delete_first(self):
        ###########################
        # Part (a): Implement me! #
        ###########################
        assert self.head is not None
        node = self.head
        x = node.item
        if self.head.next is None:
            self.head = None
            self.tail = None
        else:
            self.head = node.next
            self.head.prev = None
        del node
        return x

    def delete_last(self):
        ###########################
        # Part (a): Implement me! #
        ###########################
        assert self.tail is not None
        node = self.tail
        x = node.item
        if self.tail.prev is None:
            self.head = None
            self.tail = None
        else:
            self.tail = node.prev
            self.tail.next = None
        del node
        return x

    def remove(self, x1, x2):
        L2 = Doubly_Linked_List_Seq()
        ###########################
        # Part (b): Implement me! # 
        ###########################
        L2.head = x1
        L2.tail = x2
        if x1.prev is None:
            self.head = x2.next
        else:
            x1.prev.next = x2.next
        if x2.next is None:
            self.tail = x1.prev
        else:
            x2.next.prev = x1.prev
        x1.prev = None
        x2.next = None
        return L2

    def splice(self, x, L2):
        ###########################
        # Part (c): Implement me! # 
        ###########################
        if L2.head is None:
            return
        xnext = x.next
        x.next = L2.head
        L2.head.prev = x
        L2.tail.next = xnext
        if xnext is None:
            self.tail = L2.tail
        else:
            xnext.prev = L2.tail
        L2.head = None
        L2.tail = None