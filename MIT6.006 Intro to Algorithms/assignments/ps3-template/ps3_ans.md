### Problem 3-1
    (a)
    |0| |1| |2| |3| |4| |5| |6|
    36              56  47  52
    82                  61
                        33
    (b) 13

### Problem 3-2
    pass.

### Problem 3-3
    pass

### Problem 3-4
    pass

### Problem 3-5
    (a) string A has |A|-k+1 contiguour substrings of length k.
        For each of them, calculate the frequency of each letter, and store in a dictionary d[freq]+=1.
        Note that the frequency of a substring can be calculated from the previous substring.
        The build will take O(|A|) time.
        Then to return the anagram substring count of B, calculate the frequency of B, and look up in the dictionary.
    (b) build: O(|T|)
        calculate for each S_i: O(k)
        Total: O(|T|+nk)
    (c) see codes.
