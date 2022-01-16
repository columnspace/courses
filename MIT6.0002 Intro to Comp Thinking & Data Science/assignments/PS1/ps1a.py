###########################
# 6.0002 Problem Set 1a: Space Cows 
# Name:
# Collaborators:
# Time:

from ps1_partition import get_partitions
import time

#================================
# Part A: Transporting Space Cows
#================================

# Problem 1
def load_cows(filename):
    """
    Read the contents of the given file.  Assumes the file contents contain
    data in the form of comma-separated cow name, weight pairs, and return a
    dictionary containing cow names as keys and corresponding weights as values.

    Parameters:
    filename - the name of the data file as a string

    Returns:
    a dictionary of cow name (string), weight (int) pairs
    """
    # TODO: Your code here
    result = {}
    with open(filename) as file:
        for line in file:
            name, weight = line.split(',')
            result[name] = int(weight)
    return result

def test_load_cows():
    actual = load_cows('ps1_cow_data.txt')
    expected = {'Maggie':3,
                'Herman':7,
                'Betsy':9,
                'Oreo':6,
                'Moo Moo':3,
                'Milkshake':2,
                'Millie':5,
                'Lola':2,
                'Florence':2,
                'Henrietta':9}
    assert actual == expected, 'test load_cows FAILED!'


# Problem 2
def greedy_cow_transport(cows,limit=10):
    """
    Uses a greedy heuristic to determine an allocation of cows that attempts to
    minimize the number of spaceship trips needed to transport all the cows. The
    returned allocation of cows may or may not be optimal.
    The greedy heuristic should follow the following method:

    1. As long as the current trip can fit another cow, add the largest cow that will fit
        to the trip
    2. Once the trip is full, begin a new trip to transport the remaining cows

    Does not mutate the given dictionary of cows.

    Parameters:
    cows - a dictionary of name (string), weight (int) pairs
    limit - weight limit of the spaceship (an int)
    
    Returns:
    A list of lists, with each inner list containing the names of cows
    transported on a particular trip and the overall list containing all the
    trips
    """
    # TODO: Your code here
    sorted_cows = sorted(cows.items(), key = lambda x: x[1], reverse = True)
    result = []
    i = 0
    for name, weight in sorted_cows:
        for trip in result:
            if sum([i[1] for i in trip]) + weight <= limit:
                trip.append((name, weight))
                break
        else:
            if weight <= limit:
                result.append([(name, weight)])
    return [[cow[0] for cow in trip] for trip in result]

def test_greedy_cow_transport():
    cows = {'Jesse':6, 'Maybel': 3, 'Callie': 2, 'Maggie': 5}
    actual = greedy_cow_transport(cows, 10)
    expected = [['Jesse', 'Maybel'], ['Maggie', 'Callie']]
    assert actual==expected, 'test_greedy_cow_transport FAILED!'

# Problem 3
def brute_force_cow_transport(cows,limit=10):
    """
    Finds the allocation of cows that minimizes the number of spaceship trips
    via brute force.  The brute force algorithm should follow the following method:

    1. Enumerate all possible ways that the cows can be divided into separate trips 
        Use the given get_partitions function in ps1_partition.py to help you!
    2. Select the allocation that minimizes the number of trips without making any trip
        that does not obey the weight limitation
            
    Does not mutate the given dictionary of cows.

    Parameters:
    cows - a dictionary of name (string), weight (int) pairs
    limit - weight limit of the spaceship (an int)
    
    Returns:
    A list of lists, with each inner list containing the names of cows
    transported on a particular trip and the overall list containing all the
    trips
    """
    # TODO: Your code here
    min_trips = len(cows)
    result = None
    for partition in get_partitions(cows.items()):
        for trip in partition:
            if sum([cow[1] for cow in trip]) > limit:
                break
        else:
            if len(partition) < min_trips:
                min_trips = len(partition)
                result = [[cow[0] for cow in trip] for trip in partition]
    return result


def test_brute_force_cow_transport():
    cows = {'Jesse':6, 'Maybel': 3, 'Callie': 2, 'Maggie': 5}
    actual = brute_force_cow_transport(cows, 10)
    assert len(actual)==2 and all([sum([cows[i] for i in trip]) <= 10 for trip in actual]), 'test_brute_force_cow_transport FAILED!'

# Problem 4
def compare_cow_transport_algorithms():
    """
    Using the data from ps1_cow_data.txt and the specified weight limit, run your
    greedy_cow_transport and brute_force_cow_transport functions here. Use the
    default weight limits of 10 for both greedy_cow_transport and
    brute_force_cow_transport.
    
    Print out the number of trips returned by each method, and how long each
    method takes to run in seconds.

    Returns:
    Does not return anything.
    """
    # TODO: Your code here
    cows = load_cows('ps1_cow_data.txt')
    print(cows)
    start = time.time()
    result_greedy = greedy_cow_transport(cows)
    print(result_greedy)
    end = time.time()
    print ('Greedy method: %.2f seconds '%(end - start))
    start = time.time()
    result_bruteforce = brute_force_cow_transport(cows)
    print(result_bruteforce)
    end = time.time()
    print ('Brute force method: %.2f seconds '%(end - start))

if __name__ == '__main__':
    test_load_cows()
    test_greedy_cow_transport()
    test_brute_force_cow_transport()
    compare_cow_transport_algorithms()