### Problem 1-1
     (a) let x = log(n), so n = 2^x
        f1 = n*log(n) = x*2^x
        f2 = [log(n)]^n = x^(2^x)
        f3 = 6006*log(n) = c*x
        f4 = [log(n)]^6006 = x^c   
        f5 = log(log(n)+log(6006)) = log(x+c)
        Therefore, (f5, f3, f4, f1, f2)
    (b) log(f1) = n*log(2)
        log(f2) = n*log(6006)
        log(f3) = 6006^n*log(2)
        log(f4) = 2^n*log(6006)
        log(f5) = n^2*log(6006)
        Therefore, (f1, f2, f5, f4, f3)
        Notice log(f1) and log(f2) are both c*n, however, f1 and f2 are not the same complexity as log(f1) and log(f2) have different constant. 
    (c) f1 = n^n
        f2 = Theta(n^6)
        f3 = Omega((3n)^(3n))
        f4 = O(n^(n/6)), 
        f5 = n^6
        Therefore, ({f2,f5},f4,f1,f3)
    (d) log(f1) = Theta(n*log(n))
        log(f2) = Theta(sqrt(n)*log(n))
        log(f3) = Theta(n*log(n))
        log(f4) = Theta(n^2)
        log(f5) = Theta(log(n))
        Compare f1 and f3: f3 = (4^log(n))^3n = (n^2)^3n=n^6n > f1
        Therefore, (f5, f2, f1, f3, f4)


### Problem 1-2
    (a) two pointers, delete and insert from two ends.
    (b) move one item is equivalent to delete and insert, which takes log(n) timme. This is equivalently moving k items, thus k*log(n) time.

### Problem 1-3
    class Binder:
        def __init__(self, pages):
            // pages is array, this build in O(n) time
            self.pages = pages
            self.bookmarks = {'A': 0, 'B': 0}
        def place_mark(self,i,m):
            self.bookmarks[m] = i
        def read_page(self, i):
            return self.pages[i]
        def shift_mark(self, m,d):
            self.bookmarks[m]+=d
        def move_page(self, m):
            
        