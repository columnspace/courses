def build_freq_dict(T, k):
    d = {}
    freq = [0] * 26
    for i in range(k):
        freq[ord(T[i])-ord('a')] += 1
    d[tuple(freq)] = 1
    for i in range(k, len(T)):
        freq[ord(T[i - k])-ord('a')] -= 1
        freq[ord(T[i])-ord('a')] += 1
        d[tuple(freq)] = d.get(tuple(freq), 0) + 1
    return d


def count_anagram_substrings(T, S):
    '''
    Input:  T | String
            S | Tuple of strings S_i of equal length k < |T|
    Output: A | Tuple of integers a_i:
              | the anagram substring count of S_i in T
    '''
    A = [0] * len(S)
    d = build_freq_dict(T, len(S[0]))
    for i in range(len(S)):
        freq = [0] * 26
        for c in S[i]:
            freq[ord(c)-ord('a')] += 1
        A[i] = d[tuple(freq)]
    return tuple(A)
