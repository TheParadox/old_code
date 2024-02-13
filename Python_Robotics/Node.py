import math


class Node:
	def __init__(self, id, location, nodeType):
		self._id = id
		self._nodes = []
		self._nodesDistance = []
		self._unexploredPaths = []
		self._position = [location[0], location[1], location[2]]
		self._nodeType = nodeType
		self._timesVisited = 0
		#self.nodes.append(previousNode)
		#self.nodesDistance.append(self.getDistance(previousNode))

	def linkNode(self, nodeToLink):
		self._nodes.append(nodeToLink)
		#self._nodesDistance.append(self.getDistance(nodeToLink))

	def getDistance(self, otherNode):
		return (
			((self._position[0] - otherNode._position[0]) ** 2) +
			((self._position[1] - otherNode._position[1]) ** 2) +
			((self._position[2] - otherNode._position[2]) ** 2)
		) ** 0.5

	def getAngle(self, otherNode):
		return (
			math.atan2(self._position[1] - otherNode._position[1],
						self._position[0] - otherNode._position[0]
			)
		)

	def checkLocation(self, location, accuracy):
		print(self._position)
		if(
			((self._position[0] <= (location[0] + accuracy)) and (self._position[0] >= (location[0] - accuracy))) and
			((self._position[1] <= (location[1] + accuracy)) and (self._position[1] >= (location[1] - accuracy))) #and
			#((self._position[2] <= (location[2] + accuracy)) and (self._position[2] >= (location[2] - accuracy)))
		):
			return True
		
		return False

	def addUnexploredPath(self, directions):
		for d in directions:
			self._unexploredPaths.append(d)

	def getUnexploredPath(self, id):
		return self._unexploredPaths[id]

	def getNumberOfUnexploredPaths(self):
		return len(self._unexploredPaths)

	def removeUnexploredPath(self, id):
		self._unexploredPaths.pop(id)

	def visited(self):
		self._timesVisited += 1

	def getTimesVisited(self):
		return self._timesVisited

	def getNeighbors(self):
		return self._nodes

	def getNeighborPosition(self, ID):
		return self._nodes[ID]._position
