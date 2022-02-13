### Problem 2-1
    Master Theorem: T(n) = a*T(n/b) + f(n). Let c = log_b(a).
    Consider the recursion tree. The tree has height of log_b(n).
    At each depth k there is additional cost of a^k*f(n/b^k).
    At the bottom there is base case cost of a^(log_b(n))*f(1) = a^(log_b(n)) = n^(log_b(a)) = n^c
    Therefore, the total cost T(n) = sum_{k=0}^{log_b(n)-1} {a^k*f(n/b^k)} + a^(log_b(n))*f(1) = sum_{k=0}^{log_b(n)} {a^k*f(n/b^k)}
    The final result is determined by the relationship between f(n) and n^c.
    (a) a = 4, b = 2, c = 2. f(n) = n < n^c, so T(n) = Theta(n^c) = Theta(n^2)
    (b) a = 3, b = sqrt(2), c < 4, f(n) = n^4 > n^c. so T(n) = Theta(n^4)
    (c) a = 2, b = 2, c = 1. f(n) = nlog(n)>n^c, so T(n) = Theta(n*log(n))
    (d) T(n) = n + (n-2) + (n-4) + ... = Theta(n^2)
 
### Problem 2-3
    First determine whether in north half or south half, by checking midpoing (n/2)
    Then check 1, 2, 4, ..., until find k within adjacent powers of 2.
    Then use binary search.
    
### Problem 2-4
    See solution.
    An item can be included in multiple linked lists, to maintain different orders.

### Problem 2-5
    See code.