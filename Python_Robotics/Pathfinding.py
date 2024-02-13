
import random
from Map import Map

# -1 = unexplored
unexplored = [80, 57, 49]
# 0 = wall
wall = [0, 0, 0]
# 1 = start
start = [0, 255, 0]
# 2 = finish
finish = [0, 0, 255]
# 3 = corridor, for data grid only
# 4 = Current
current = [255, 0, 0]
# 5 = Visible Path
visible = [59, 40, 96]
# 6 = Explored
explored = [180, 176, 173]
# 7 = Node
node = [255, 255, 255]


maze = [
	[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
	[0,3,0,0,0,3,3,3,3,0,0,3,3,3,0],
	[0,3,3,1,0,3,0,0,0,0,0,3,0,0,0],
	[0,3,0,0,0,3,0,0,3,3,3,3,3,0,0],
	[0,3,0,3,0,3,0,3,0,0,0,3,0,0,0],
	[0,3,3,3,3,3,3,3,0,0,0,3,0,3,0],
	[0,3,0,3,0,0,0,3,3,3,3,3,3,3,0],
	[0,3,0,3,0,3,0,0,0,3,0,0,0,3,0],
	[0,3,3,3,0,3,0,0,0,3,0,0,0,3,0],
	[0,0,3,0,0,3,3,3,0,3,3,3,0,3,0],
	[0,0,3,0,3,3,0,0,0,0,3,0,0,3,0],
	[0,3,3,0,3,0,0,3,3,3,3,3,3,3,0],
	[0,0,3,3,3,0,0,3,0,0,3,0,0,3,0],
	[0,0,0,0,3,3,3,3,0,0,3,3,3,2,0],
	[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
]

exploredMap = [
	[-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
	[-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
	[-1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
	[-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
	[-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
	[-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
	[-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
	[-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
	[-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
	[-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
	[-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
	[-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
	[-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],
	[-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2, -1],
	[-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1]
]

displayMap = [
	[unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored,unexplored, unexplored, unexplored, unexplored, unexplored],
	[unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored,unexplored, unexplored, unexplored, unexplored, unexplored],
	[unexplored, unexplored, unexplored, start, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored,unexplored, unexplored, unexplored, unexplored, unexplored],
	[unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored,unexplored, unexplored, unexplored, unexplored, unexplored],
	[unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored,unexplored, unexplored, unexplored, unexplored, unexplored],
	[unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored,unexplored, unexplored, unexplored, unexplored, unexplored],
	[unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored,unexplored, unexplored, unexplored, unexplored, unexplored],
	[unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored,unexplored, unexplored, unexplored, unexplored, unexplored],
	[unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored,unexplored, unexplored, unexplored, unexplored, unexplored],
	[unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored,unexplored, unexplored, unexplored, unexplored, unexplored],
	[unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored,unexplored, unexplored, unexplored, unexplored, unexplored],
	[unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored,unexplored, unexplored, unexplored, unexplored, unexplored],
	[unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored,unexplored, unexplored, unexplored, unexplored, unexplored],
	[unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored,unexplored, unexplored, unexplored, finish, unexplored],
	[unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored, unexplored,unexplored, unexplored, unexplored, unexplored, unexplored]
]

'''
startPos = [2, 3] #y, x
directions = [
	[1, 0],
	[-1, 0],
	[0, 1],
	[0, -1]
]

pos = startPos
'''

def check(position, cellType):
	data = maze[position[0]][position[1]]
	known = exploredMap[position[0]][position[1]]
	if(data == 0):
		displayMap[position[0]][position[1]] = wall
		exploredMap[position[0]][position[1]] = 0
		cellType[2].append(position)
	elif(data == 1):
		displayMap[position[0]][position[1]] = start
		exploredMap[position[0]][position[1]] = 1
	elif(data == 2):
		displayMap[position[0]][position[1]] = finish
		exploredMap[position[0]][position[1]] = 2
	elif(data == 3):
		if(known == -1):
			known = 5

	if(known == 4):
		displayMap[position[0]][position[1]] = current
		exploredMap[position[0]][position[1]] = 4
	elif(known == 5):
		displayMap[position[0]][position[1]] = visible
		exploredMap[position[0]][position[1]] = 5
		cellType[0].append(position)
	elif(known == 6):
		displayMap[position[0]][position[1]] = explored
		exploredMap[position[0]][position[1]] = 6
		cellType[1].append(position)
	elif(known == 7):
		displayMap[position[0]][position[1]] = node
		exploredMap[position[0]][position[1]] = 7
		cellType[1].append(position)

	return cellType

def normalizeVector(arrayToNorm):
	normalizedResult = []
	for i in arrayToNorm:
		if(i < 0):
			normalizedResult.append(-1)
		elif(i > 0):
			normalizedResult.append(1)
		else:
			normalizedResult.append(0)
	
	return normalizedResult


position = [2, 3, 1]
nodeMap = Map('Node', 1, 1, 'None', position, [13, 13, 1], 0)
forwardDirection = [0, 0, 0]
def move2(unexploredTiles, exploredTiles, wallTiles):
	global forwardDirection, position
	placeNode = False
	hitWall = False
	isOnNode = False
	alternatePath = False

	for w in wallTiles:
		if(
			(w[0] == (position[0] + forwardDirection[0])) and 
			(w[1] == (position[1] + forwardDirection[1])) #and 
			#(w[2] == (position[2] + forwardDirection[2]))
		):
			hitWall = True
	if(len(wallTiles) == 3):
		hitWall = True


	if(len(unexploredTiles) > 1) or (hitWall):
		nodeID = nodeMap.spawnMarker(position, "Intersection")

		if(nodeID == -1):
			nodeMap._generatedNodes[nodeID].addUnexploredPath(unexploredTiles)
			unexploredPathCount = len(unexploredTiles)
			placeNode = True
		else:
			unexploredPathCount = nodeMap._generatedNodes[nodeID].getNumberOfUnexploredPaths()
			nodeMap._generatedNodes[nodeID].visited()

		if(unexploredPathCount > 0):
			randomNumber = random.randrange(0, unexploredPathCount)
			newPath = nodeMap._generatedNodes[nodeID].getUnexploredPath(randomNumber)
			nodeMap._generatedNodes[nodeID].removeUnexploredPath(randomNumber)
			forwardDirection[0] = newPath[0] - position[0]
			forwardDirection[1] = newPath[1] - position[1]
			#forwardDirection[2] = newPath[2] - position[2]
		else:
			alternatePath = True

	if(alternatePath):
		isOnNode = nodeMap.searchNodesForLocation(position)
		if(isOnNode != False):
			leastID = nodeMap.checkForLeastTraveledNode(isOnNode)
			if(leastID != False):
				newPath = nodeMap._generatedNodes[leastID]._position
				forwardDirection[0] = newPath[0] - position[0]
				forwardDirection[1] = newPath[1] - position[1]
			#forwardDirection[2] = newPath[2] - position[2]


	if((placeNode == True) or (isOnNode != False)):
		displayMap[position[0]][position[1]] = node
		exploredMap[position[0]][position[1]] = 7
	else:
		displayMap[position[0]][position[1]] = explored
		exploredMap[position[0]][position[1]] = 6

	forwardDirection = normalizeVector(forwardDirection)

	if( exploredMap[(position[0] + forwardDirection[0])][(position[1] + forwardDirection[1])] == 0 ):
		forwardDirection = [0, 0, 0]

	if(
		(exploredMap[position[0]][position[1]] == 2) or
		(exploredMap[position[0] + forwardDirection[0]][position[1] + forwardDirection[1]] == 2)
	):
		return 1

	position[0] += forwardDirection[0]
	position[1] += forwardDirection[1]
	#position[2] += forwardDirection[2]


	displayMap[position[0]][position[1]] = current
	exploredMap[position[0]][position[1]] = 4
	

cellTypes = [[], [], []]
def startPathfinding():
	global cellTypes, position
	cellTypes = check( [position[0] + 1, position[1]], cellTypes )
	cellTypes = check( [position[0] - 1, position[1]], cellTypes )
	cellTypes = check( [position[0], position[1] + 1], cellTypes )
	cellTypes = check( [position[0], position[1] - 1], cellTypes )
	check( position, cellTypes )
	nodeMap._generatedNodes[1].addUnexploredPath(cellTypes[0])

def pathfinder():
	global cellTypes, position
	#move()
	move2(cellTypes[0], cellTypes[1], cellTypes[2])
	del cellTypes[:]
	cellTypes = [[], [], []]
	cellTypes = check( [position[0] + 1, position[1]], cellTypes )
	cellTypes = check( [position[0] - 1, position[1]], cellTypes )
	cellTypes = check( [position[0], position[1] + 1], cellTypes )
	cellTypes = check( [position[0], position[1] - 1], cellTypes )
	check( position, cellTypes )
