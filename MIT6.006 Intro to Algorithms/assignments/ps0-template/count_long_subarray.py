def count_long_subarray(A):
    '''
    Input:  A     | Python Tuple of positive integers
    Output: count | number of longest increasing subarrays of A
    '''
    count = 0
    ##################
    # YOUR CODE HERE #
    ##################
    max_length = 0
    current_length = 0
    prev = None
    for num in A:
        if prev is None or num > prev:
            current_length += 1
        else:
            current_length = 1
        if current_length > max_length:
            max_length = current_length
            count = 1
        elif current_length == max_length:
            count += 1
        prev = num
    return count
