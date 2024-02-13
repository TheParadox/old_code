import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import cm
from numpy.random import random
import time
from Pathfinding import displayMap, pathfinder, startPathfinding


fig = plt.figure()
im = plt.imshow(displayMap, interpolation='nearest', cmap=cm.get_cmap("Spectral"))

def update(data):
    im.set_array(data)

def data_gen():
	pathfinder()
	yield displayMap

startPathfinding()
ani = animation.FuncAnimation(fig, update, data_gen, interval=500)

plt.show()
