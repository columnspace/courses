### Part A.5
1. Greedy algorithm takes 0.02 seconds, while brute force method takes 0.57 seconds on my PC. Greedy algorithm is faster than brute force algorithm, since it searches in a smaller solution space. 
2. Greedy algorithm does not return the optimal solution, because greedy algorithm only search in a subset of solution space, and it does not guarantee an optimal solution exists in the subset, unless a proof can be established.
3. Brute force algorithm returns the optimal solution, because brute force method enumerates the entire solution space, and can guarantee an optimal solution. 

### Part B.
1. It's difficult to list all combinations that add up to a given weight.
2. The objective function is min x1+...+xn, s.t. w1* x1+ ...+ wn*xn = W. The strategy for a greedy algorithm would be to start from the maximum weight. Specifically, let w1 > ... > wn. Then x1 = W//w1, x2 = (W%w1)//w2, etc.
3. No. For example, available weights are (4,3,1), and target is 6. The greedy algorithm will return 4+1+1, while the optimal solution is 3+3.