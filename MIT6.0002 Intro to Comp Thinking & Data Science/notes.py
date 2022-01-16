# study of DFS code from Lecture 3
import sys
sys.path.append('./lecture-slides-and-files')
from lectureGraphs import Node, Edge, Digraph, Graph, printPath

def buildCityGraph(graphType):
    g = graphType()
    for name in ('Boston', 'Providence', 'New York', 'Chicago',
                 'Denver', 'Phoenix', 'Los Angeles'): #Create 7 nodes
        g.addNode(Node(name))
    g.addEdge(Edge(g.getNode('Boston'), g.getNode('Providence')))
    g.addEdge(Edge(g.getNode('Boston'), g.getNode('New York')))
    g.addEdge(Edge(g.getNode('Providence'), g.getNode('Boston')))
    g.addEdge(Edge(g.getNode('Providence'), g.getNode('New York')))
    g.addEdge(Edge(g.getNode('New York'), g.getNode('Chicago')))
    g.addEdge(Edge(g.getNode('New York'), g.getNode('Denver')))
    g.addEdge(Edge(g.getNode('Chicago'), g.getNode('Phoenix')))
    g.addEdge(Edge(g.getNode('Chicago'), g.getNode('Denver')))
    g.addEdge(Edge(g.getNode('Denver'), g.getNode('Phoenix')))
    g.addEdge(Edge(g.getNode('Denver'), g.getNode('New York')))
    g.addEdge(Edge(g.getNode('Los Angeles'), g.getNode('Boston')))
    return g

def DFS(graph, current, end, path, shortest, toPrint = False):
    """Assumes graph is a Digraph; current and end are nodes;
          path and shortest are lists of nodes
       Returns a shortest path from start to end in graph
       where start is path[0] is path is not null else current

   Parameters:
       - graph: constant graph storing nodes and edges
       - current: currently visited node, which will be updated in recursions
       - end: constant end node
       - path: the path from start(inclusive) to current(exclusive)
       - shortest: the global best path, set as None at beginning; updated when a path is found for first time or a better path is found

      Returns: The function returns when (1) reaches the end point; (2)there is no nodes can be further visited
   """
    path = path + [current] # WARN: cannot use path += [current], otherwise the modification of path will be retained
    if toPrint:
        print('Current DFS path:', printPath(path))
    if current == end:
        return path # current == end only means we find a path; but the check of len(path) < len(shortest) ensures that path is optimal, so return as shortest path
    for node in graph.childrenOf(current):
        if node not in path: #avoid cycles
            if shortest == None or len(path) < len(shortest) : # newPath is 1 step longer than path, so it ensures that newPath wont be longer than shortest
          # can change to below, so that if exist multiple shortest path, it returns the first
          # if shortest == None or len(path) < len(shortest) -1:
                newPath = DFS(graph, node, end, path, shortest,
                              toPrint)
                if newPath != None:
                    shortest = newPath
        elif toPrint:
            print('Already visited', node)
    return shortest

def DFS_firstshortest(graph, current, end, path, shortest, toPrint = False):
    path = path + [current]
    if toPrint:
        print('Current DFS path:', printPath(path))
    if current == end:
        return path
    for node in graph.childrenOf(current):
        if node not in path: #avoid cycles
            if shortest == None or len(path) < len(shortest) - 1 :
                newPath = DFS_firstshortest(graph, node, end, path, shortest,
                              toPrint)
                if newPath != None:
                    shortest = newPath
        elif toPrint:
            print('Already visited', node)
    return shortest

def DFS_no_early_exit(graph, current, end, path, shortest, toPrint = False):
    path = path + [current]
    if toPrint:
        print('Current DFS path:', printPath(path))
    if current == end:
        if shortest is None or len(path) <=  len(shortest):
            return path
        else:
            return shortest
    for node in graph.childrenOf(current):
        if node not in path:
            newPath = DFS_no_early_exit(graph, node, end, path, shortest, toPrint)
            if newPath is not None and (shortest is None or len(newPath) <= len(shortest)):
                shortest = newPath
        elif toPrint:
            print('Already visited', node)
    return shortest

def shortestPath(graph, start, end, func, toPrint = False):
    """Assumes graph is a Digraph; start and end are nodes
       Returns a shortest path from start to end in graph"""
    return func(graph, start, end, [], None, toPrint)

def testSP(source, destination, func):
    g = buildCityGraph(Digraph)
    sp = shortestPath(g, g.getNode(source), g.getNode(destination), func,
                      toPrint = True)
    if sp != None:
        print('Shortest path from', source, 'to',
              destination, 'is', printPath(sp))
    else:
        print('There is no path from', source, 'to', destination)

def BFS(graph, start, end, toPrint):
    pathQueue =[[start]]
    while len(pathQueue)!=0:
        currentPath = pathQueue.pop(0)
        if currentPath[-1]
if __name__ == '__main__':
    testSP('New York', 'Phoenix', DFS)
    print('------------------------------------------')
    testSP('New York', 'Phoenix', DFS_firstshortest)
    print('------------------------------------------')
    testSP('New York', 'Phoenix', DFS_no_early_exit)

    # testSP('Boston', 'Phoenix')
    # print()



