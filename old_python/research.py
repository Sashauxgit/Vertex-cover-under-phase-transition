import networkx as nx
import matplotlib.pyplot as plt
import copy
import scipy.sparse as ss
from scipy.optimize import linprog
from time import time
from numba import njit
from progress.bar import Bar

def optimEdgeCount(vertexCount):
    n = vertexCount
    return ((n - 2) * (n - 1)) / 2 + 1

def drawGraph(G):
    nx.draw(G, with_labels=True, font_weight='bold')
    plt.show()

def lazy_algorithm(graph):
    graph = copy.deepcopy(graph)
    solve = []
    while(True):

        #drawGraph(graph) #

        edges = list(graph.edges)
        if len(edges) == 0:
            return set(solve), len(solve)
        
        edge = edges[0]

        #print(edge) #
        #drawGraph(graph) #

        solve.extend(list(edge))

        for v1 in edge:
            adjacency = copy.deepcopy(graph.adj)[v1]
            for v2 in adjacency:
                graph.remove_edge(v1, v2)

def heuristic_algorithm(graph):
    solve = []
    while(len(list(graph.edges)) > 0):
        valencies = {len(graph.adj[d]): d for d in graph.adj}
        solveVertex = valencies[max(valencies)]

        #print(solveVertex) #
        #drawGraph(graph) #

        solve.append(solveVertex)
        adjacency = copy.deepcopy(graph.adj)[solveVertex]
        for v2 in adjacency:
            graph.remove_edge(solveVertex, v2)
        
        #drawGraph(graph) #
    
    return set(solve), len(solve)

def linear_algorithm(graph):
    C = [1 for v in graph.nodes]
    A = -1 * ss.csr_matrix(nx.incidence_matrix(graph)).transpose().toarray()
    B = [-1 for e in graph.edges]
    solution = linprog(c = C, A_ub = A, b_ub = B, method="highs").x
    solve = {i for i in range(len(solution)) if solution[i] >= 0.5}
    return solve, len(solve)

#@njit(fastmath=True)
def sol(x, graph):
    for e in graph.edges:
        if set(e) & x == set():
            return False
    return True

#@njit(fastmath=True)
def exactly_solve(graph, bar, x = frozenset(), P = set(), r = [float('inf')]):
    bar.next()
    print('/', end='')
    if sol(x, graph):
        if len(x) < r[0]:
            r[0] = len(x)
            P.clear()
            P.add(x)
        else:
            if len(x) == r[0]:
                P.add(x)
    else:
        if len(x) < r[0]:
            ext = sorted(list(set(graph.nodes) - x), key = lambda v: len(graph.adj[v]), reverse = True)
            for y in ext:
                exactly_solve(graph, bar, x | {y}, P, r)

    return P


def supremum(n):
    Sum = 0
    prev = 1
    for i in range(n, 0, -1):
        prev = prev * i
        Sum = Sum + prev
    return Sum


def process():
    k_vetrex = 14
    k_edges = 20
    randomGraph = nx.dense_gnm_random_graph(k_vetrex, k_edges)
    maximum = supremum(k_vetrex)
    bar = Bar('Progressing', fill='#', suffix='%(percent)d%%', max=maximum)
    exactly_solve(randomGraph, bar)
    bar.goto(maximum)
    bar.finish() 

#solve, _ = lazy_algorithm(randomGraph)

#solve, _ = heuristic_algorithm(randomGraph)

#solve, _ = linear_algorithm(randomGraph)
#drawGraph(randomGraph)

#start = time()
process()
#end = time()

#print(end - start, 'сек')
#print(answer)