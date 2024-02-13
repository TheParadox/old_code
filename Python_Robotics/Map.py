from Node import Node

class Map:
	def __init__(self, mapMethod, robotWidth, nodesAcross, searchAlgorithm, startLocation, goalLocation, accuracy):
		#mapMethod = EITHER: Node or Cell, determines how the map is formed. 
		#robotWidth = how wide the robot is in CM
		#nodesAcross = IMPORTANT IF USING CELLS, not so much with Nodes. number of cells across when generating the map
		# - example: if robotWidth = 100cm and nodesAcross = 2, then each node/cell = 50cm across
		if(mapMethod == 'Node'):
			#run the node based functions
			self._markerTypeFunction = self.placeNode
			pass
		elif (mapMethod == 'Cell'):
			#run grid cell based functions
			self._markerTypeFunction = self.placeCells
			pass
		else:
			#option not recognized, send error and set default mapping method, Node?
			pass

		self._robotWidth = robotWidth
		self._nodeWidth = self._robotWidth / nodesAcross
		self._pathAlgorithm = searchAlgorithm

		self._generatedNodes = []
		self._startNode = Node(1, startLocation, "Start")
		self._goalNode = Node(0, goalLocation, "End")
		
		self._currentNode = self._startNode
		self._generatedNodes.append(self._goalNode)
		self._generatedNodes.append(self._currentNode)
		self._checkAccuracy = accuracy
		

	def spawnMarker(self, location, nodeType):
		_foundNodeID = self.searchNodesForLocation(location)
		if(_foundNodeID != False):
			self._currentNode.linkNode(_foundNodeID)
			self._generatedNodes[_foundNodeID].linkNode(self._currentNode._id)
			_currentNode = self._generatedNodes[_foundNodeID]
			return _foundNodeID
		else:
			self._markerTypeFunction(location, nodeType)
			return -1


	def placeNode(self, location, nodeType):
		_newNode = Node(len(self._generatedNodes), location, nodeType)
		_newNode.linkNode(self._currentNode._id)
		self._currentNode.linkNode(_newNode._id)
		self._currentNode = _newNode
		self._generatedNodes.append(self._currentNode)


	def placeCells(self, location, nodeType):
		pass

	def searchNodesForLocation(self, location):
		for i in range(len(self._generatedNodes)):
			_result = self._generatedNodes[i].checkLocation(location, self._checkAccuracy)
			if(_result):
				print("SUCCESS")
				return i
			print("----")

		return False


	def changeTravelDirection(self, rotation):
		pass

	def checkForLeastTraveledNode(self, nodeID):
		nodeIDs = self._generatedNodes[nodeID].getNeighbors()
		leastID = False
		print(nodeIDs)
		for n in nodeIDs:
			print(n)
			if(leastID == False):
				leastID = n
			elif(self._generatedNodes[n]._timesVisited < self._generatedNodes[leastID]._timesVisited):
				leastID = n

		return leastID
		