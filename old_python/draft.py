import matplotlib.pyplot as plt
import networkx as nx
import numpy as np
import scipy.sparse as ss
from progress.bar import Bar
import time

G = nx.Graph()  # создаём объект графа

# определяем список узлов (ID узлов)
nodes = [1, 2, 3, 4, 5]

# определяем список рёбер
# список кортежей, каждый из которых представляет ребро
# кортеж (id_1, id_2) означает, что узлы id_1 и id_2 соединены ребром
edges = [(1, 2), (1, 3), (2, 3), (2, 4), (3, 5), (5, 5)]

# добавляем информацию в объект графа
G.add_nodes_from(nodes)
G.add_edges_from(edges)

k_vetrex = 7
k_edges = 10
randomGraph = nx.dense_gnm_random_graph(k_vetrex, k_edges)

# рисуем граф и отображаем его
#print(ss.csr_matrix(nx.adjacency_matrix(randomGraph)).toarray())

def generateRandomGraph(k_vetrex, k_edges):
    nodes = [i + 1 for i in range(k_vetrex)]

#print(-1*ss.csr_matrix(nx.incidence_matrix(randomGraph)).transpose().toarray())

#nx.draw(randomGraph, with_labels=True, font_weight='bold')
#plt.show()

#print(np.round(np.array([1.2, 0.5, 1.1, 9.8, 6.7]), 0))
s1 = frozenset({1, 2})
s2 = frozenset({3, 4})
'''
bar = Bar('Progressing', fill='#', suffix='%(percent)d%%', max=100000)

for i in range(100000):
    bar.next()
    if i == 5:
        pass

#bar.goto(8)

bar.finish()

print([i for i in range(9, -1, -1)])
'''
def supremum(n):
    Sum = 0
    prev = 1
    for i in range(n, 0, -1):
        prev = prev * i
        Sum = Sum + prev
    return Sum

print(supremum(1000))