import numpy
from PIL import Image
import array


class aStarNode:
	def __init__(self, able, position):
		self.passable = able
		self.gCost = 0
		self.hCost = 0
		self.gridX = position[0]
		self.gridY = position[1]
		self.parentNode = None

	def fCost(self):
		return self.gCost + self.hCost

class aStarPathfinding:
	def __init__(self, map, resolution, worldSize):
		self.grid = [[None for x in range(resolution[0])]
						for y in range(resolution[1])]
		self.gridWorldSizeX = worldSize[0]
		self.gridWorldSizeY = worldSize[1]

		for x in range(resolution[0]):
			for y in range(resolution[1]):
				if(map[(x * resolution[0]) + y] == 0):
					passable = False
				else:
					passable = True
				
				self.grid[x][y] = aStarNode(passable, [x, y])

		print(map[0])

		imageByteArray = array.array('b', map)

		im = Image.frombuffer("RGB", (resolution[0], resolution[1]), imageByteArray, "raw", "RGB", 0, 1)
		im.show()

	def nodeFromWorldPosition(self, position):
		percentX = (position[0] + self.gridWorldSizeX / 2) / self.gridWorldSizeX
		percentY = (position[1] + self.gridWorldSizeY / 2) / self.gridWorldSizeY

		percentX = numpy.clip(percentX, 0, 1)
		percentY = numpy.clip(percentY, 0, 1)

		x = int(round(self.gridWorldSizeX - 1) * percentX)
		y = int(round(self.gridWorldSizeY - 1) * percentY)

		return self.grid[x][y]

	def getNeighbours(self, node):
		neighbours = []
		gridSizeX = len(self.grid)
		gridSizeY = len(self.grid[0])

		for x in range(-1, 1):
			for y in range(-1, 1):
				if(x == 0 and y == 0):
					continue

				checkX = node.gridX + x
				checkY = node.gridY + y

				if(checkX >= 0 and checkX <= gridSizeX) and (checkY >= 0 and checkY <= gridSizeY):
					neighbours.append(self.grid[checkX][checkY])

		return neighbours

	def contains(self, objArray, obj):
		for i in range(len(objArray)):
			if(objArray[i].gridX == obj.gridX and objArray[i].gridY == obj.gridY):
				return True

		return False

	def getDistance(self, nodeA, nodeB):
		distanceX = abs(nodeA.gridX - nodeB.gridX)
		distanceY = abs(nodeA.gridY - nodeB.gridY)

		if(distanceX > distanceY):
			return ((14*distanceY) + (10 * (distanceX - distanceY)))
			
		return ((14*distanceX) + (10 * (distanceY - distanceX)))

	def retracePath(self, startNode, endNode):
		path = []
		currentNode = endNode

		while currentNode != startNode:
			path.append(currentNode)
			currentNode = currentNode.parentNode

		forwardPath = reversed(path)	

		print(forwardPath)

	def findPath(self, startPos, targetPos):
		startNode = self.nodeFromWorldPosition(startPos)
		targetNode = self.nodeFromWorldPosition(targetPos)

		openSet = []
		closedSet = []
		openSet.append(startNode)

		while(len(openSet) > 0):
			currentNode = openSet[0]
			print(currentNode.gridX, '--', currentNode.gridY)
			openSetID = -1
			for i in range(len(openSet)):
				if(openSet[i].fCost < currentNode.fCost) or (openSet[i].fCost == currentNode.fCost and openSet[i].hCost < currentNode.hCost):
					currentNode = openSet[i]
					openSetID = i
				
			openSet.pop(openSetID)
			closedSet.append(currentNode)

			if(currentNode == targetNode):
				self.retracePath(startNode, targetNode)
				return 1

			neighbours = self.getNeighbours(currentNode)
			for nb in neighbours:
				if(not(nb.passable) or self.contains(closedSet, nb)):
					continue

				newMovementCost = currentNode.gCost + self.getDistance(currentNode, nb)
				if(newMovementCost < nb.gCost or not(self.contains(closedSet, nb))):
					nb.gCost = newMovementCost
					nb.hCost = self.getDistance(nb, targetNode)
					nb.parentNode = currentNode

					if(not(self.contains(openSet, nb))):
						openSet.append(nb)

		print("A* Finished! Printing Path")
		self.findPath(startNode, targetNode)	




