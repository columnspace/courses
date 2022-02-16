### Problem 4-1
    (a)
    skew(16) = 2
    skew(37)= -2
    (b)
    insert 2: left child of 3
    delete 49: remove directly
    delete 35: swap 35 and 28 and delete
    insert 85: insert as left child of 86
    delete 84: swap 84 and 49 and delete
    (c) 
    complete. Leave out details.

### Problem 4-2
    (a)              4
               12           8
          21       14   9      17
        It's a min heap.
    (b)             701
            253             24
        229    17       22
        It's a max heap.
    (c)            2
            9             13
       8        0     2
        Neither max heap nor min heap.
        
        Heapify down from last to first:
        step 1: move 13
                   2
            9             2
       8        0     13
        step 2: move 9
                   2
            0             2
       8        9     13
        step 3: move 2
                   0
            2             2
       8        9     13
    (d)           1
           3             6
       5      4      9      7
        Min heap.

### Problem 4-3
    (a) Build a max heap from A with time O(|A|)
        Delete_max for k times, with time O(k*log(|A|))
    (b) When search in the max heap, if a node is less than x, we do not need to search its subtree.
        
### Problem 4-6
    (a) xi = max{x_k|x_k<=x'}, yj = max{y_k|y_k<=y'}
    (b) Augmentation with 3 subtree properties:
            - sum: sum of all nodes in the subtree
            - max_prefix: maximum of prefix among all nodes in the subtree
            - max_prefix_node: which node takes the maximum prefix
    (c) - Sort all toppings (xi, yi, ti), ordered by xi. Takes O(nlog(n))
        - For i = 1 to n:
            insert toppings into the set AVL with augmentation.
            calculate the max_prefix from root
        - find the max of max_prefix among all steps

                        