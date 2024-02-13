import sys

class dijkstrasNodes:
	def __init__(self, data):
		self.name = data[0]
		self.x = data[1]
		self.y = data[2]
		self.parent = None

class dijkstras:
	def __init__(self, points):
		self.v = []
		self.graph = [[0 for x in range(points)]
						for y in range(points)]

		for p in points:
			self.v.append(dijkstrasNodes(p))

	def minDistance(self, distance, shortestPathSet):
		minimumDist = sys.maxsize

		for i in range(self.v):
			if distance[i] < minimumDist and shortestPathSet[i] == False:
				minimumDist = distance[i]
				minimumIndex = i

		return minimumIndex


	def findPath(self, source):
		distance = [sys.maxsize] * self.v
		distance[source] = 0
		shortestPathSet = [False] * self.v

		for p in range(self.v):
			indx = self.minDistance(distance, shortestPathSet)

			shortestPathSet[indx] = True

			for pt in range(self.v):
				if (self.graph[indx][pt] > 0) and \
					(shortestPathSet[pt] == False) and \
						(distance[pt] > distance[indx] + self.graph[indx][pt]):
					distance[pt] = distance[indx] + self.graph[indx][pt]
					self.v[pt].parent = self.v[indx].parent
