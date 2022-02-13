def merge(B1, B2):
    i, j = 0, 0 # two pointers to iter B1, B2
    t = 0 # keep track of time, since we cannot know whether we should start from s1 or s2
    B = [] # result
    while i < len(B1) and j < len(B2):
        k1, s1, t1 = B1[i]
        k2, s2, t2 = B2[j]
        if t <= min(s1, s2):
            t = min(s1, s2)
        if t1 <= s2:
            B.append((k1, t, t1))
            t=t1
            i+=1
        elif t2 <= s1:
            B.append((k2, t, t2))
            t=t2
            j+=1
        elif t < s1:
            B.append((k2, t, s1))
            t=s1
            # no increment
        elif t < s2:
            B.append((k1, t, s2))
            t=s2
            # no increment
        else:
            B.append((k1+k2, t, min(t1, t2)))
            t=min(t1,t2)
            if t1 <= t2:
                i+=1
            if t2<= t1:
                j+=1
    for l in range(i, len(B1)):
        k1,s1,t1 = B1[l]
        B.append((k1, max(s1, t), t1))
        t = t1
    for l in range(j, len(B2)):
        k2,s2,t2 = B2[l]
        B.append((k2, max(s2, t), t2))
        t = t2
    # combine adjacent with the same num of rooms
    B_ = [B[0]]
    for i in range(1, len(B)):
        cur = B_[-1]
        next = B[i]
        if cur[0] == next[0] and cur[2] == next[1]:
            B_.pop()
            B_.append((cur[0], cur[1], next[2]))
        else:
            B_.append(next)
    return B_



def satisfying_booking(R):
    '''
    Input:  R | Tuple of |R| talk request tuples (s, t)
    Output: B | Tuple of room booking triples (k, s, t)
              | that is the booking schedule that satisfies R
    '''
    ##################
    # YOUR CODE HERE #
    ##################
    if len(R) == 1:
        s,t=R[0]
        return ((1,s,t),)
    B1 = satisfying_booking(R[:len(R)//2])
    B2 = satisfying_booking(R[len(R)//2:])
    B = merge(B1,B2)
    return tuple(B)
