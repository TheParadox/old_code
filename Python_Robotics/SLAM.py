import time
from matplotlib import pyplot as plt
import numpy as np
import math

import keyboard

try:
	import sim
except:
	print("Unable to load sim")

import time



def liveDemo(clientID, plt, leftSensor, rightSensor, i):
	[rCode, leftDS, leftPD, doh, dsnv] = sim.simxReadProximitySensor(clientID, leftSensor, sim.simx_opmode_buffer)
	[rCode, rightDS, rightPD, doh, dsnv] = sim.simxReadProximitySensor(clientID, rightSensor, sim.simx_opmode_buffer)

	x = []
	y = []

	if leftDS and rightDS:
		x[0] = leftPD[0] + 5 + (i / 10000)
		x[1] = rightPD[0] + 5 + (i / 10000)

		y[0] = leftPD[1] + 4 + (i / 10000)
		y[1] = rightPD[1] + 4 + (i / 10000)
		#print(leftPD[0], leftPD[1])
		plt.plot([x], [y], 'bo')
		plt.pause(0.05)
	elif leftDS:
		x = leftPD[0] + 5 + (i / 10000)
		y = leftPD[1] + 4 + (i / 10000)
		#print(leftPD[0], leftPD[1])
		plt.plot([x], [y], 'r+')
		plt.pause(0.05)
	elif rightDS:
		x = rightPD[0] + 5 + (i / 10000)
		y = rightPD[1] + 4 + (i / 10000)
		#print(rightPD[0], rightPD[1])
		plt.plot([x], [y], 'go--')
		plt.pause(0.05)
	

def plottingGraph(x1, y1, x2, y2):
	plt.axis([0, 7500, 0, 25])
	plt.plot(x1, y1, 'b+')
	plt.plot(x2, y2, 'r+')
	plt.show()



sim.simxFinish(-1)
clientID = sim.simxStart('127.0.0.1', 19999, True, True, 5000, 5)

currentPos = [0.5, 0.5]

if(clientID != -1):
	print('Connected to remote API server')
	[errorCode, leftSensor] = sim.simxGetObjectHandle(clientID, 'Pioneer_p3dx_ultrasonicSensor3', sim.simx_opmode_blocking)
	[errorCode, rightSensor] = sim.simxGetObjectHandle(clientID, 'Pioneer_p3dx_ultrasonicSensor6', sim.simx_opmode_blocking)
	[rCode, detectionState, detectedPoint, doh, dsnv] = sim.simxReadProximitySensor(clientID, leftSensor, sim.simx_opmode_streaming)
	[rCode, detectionState, detectedPoint, doh, dsnv] = sim.simxReadProximitySensor(clientID, rightSensor, sim.simx_opmode_streaming)

	xPoints1 = []
	yPoints1 = []
	xPoints2 = []
	yPoints2 = []

	for i in range(1250):
		[rCode, leftDS, leftPD, doh, leftdsnv] = sim.simxReadProximitySensor(clientID, leftSensor, sim.simx_opmode_buffer)
		[rCode, rightDS, rightPD, doh, rightdsnv] = sim.simxReadProximitySensor(clientID, rightSensor, sim.simx_opmode_buffer)

		currentPos[0] = currentPos[0] + (i / 100)

		if leftDS and rightDS:
			#print(leftdsnv, " - ", rightdsnv)
			x = (leftdsnv[0] * 2.5 * math.sin(0.7854)) + currentPos[0]
			y = (leftdsnv[2] * 2.5 * math.cos(0.7854)) + currentPos[1]
			
			xPoints1 = np.append(xPoints1, x)
			yPoints1 = np.append(yPoints1, y)


			x = (rightdsnv[0] * 2.5 * math.sin(0.7854)) + currentPos[0]
			y = (rightdsnv[2] * 2.5 * math.cos(0.7854)) + currentPos[1]
			
			xPoints2 = np.append(xPoints2, x)
			yPoints2 = np.append(yPoints2, y)
			#something
		elif leftDS:
			#print('left', leftdsnv)
			x = (leftdsnv[0] * 2.5 * math.sin(0.7854)) + currentPos[0]
			y = (leftdsnv[2] * 2.5 * math.cos(0.7854)) + currentPos[1]

			xPoints1 = np.append(xPoints1, x)
			yPoints1 = np.append(yPoints1, y)
			#something
		elif rightDS:
			#print('right',  rightdsnv)
			x = (rightdsnv[0] * 2.5 * math.sin(0.7854)) + currentPos[0]
			y = (rightdsnv[2] * 2.5 * math.cos(0.7854)) + currentPos[1]
			
			xPoints2 = np.append(xPoints2, x)
			yPoints2 = np.append(yPoints2, y)
			#something

		if False:
			#print(leftPD, " - ", rightPD)
			xPoints1 = np.append(xPoints1, (leftPD[0] * 2) + currentPos[0])
			yPoints1 = np.append(yPoints1, leftPD[2] + currentPos[1])

			xPoints2 = np.append(xPoints2, (rightPD[0] * 2) + currentPos[0])
			yPoints2 = np.append(yPoints2, rightPD[2] + currentPos[1])
		elif False:
			#print(leftPD)
			xPoints1 = np.append(xPoints1, (leftPD[0] * 2) + currentPos[0])
			yPoints1 = np.append(yPoints1, leftPD[2] + currentPos[1])
		elif False:
			#print(rightPD)
			xPoints2 = np.append(xPoints2, (rightPD[0] * 2) + currentPos[0])
			yPoints2 = np.append(yPoints2, rightPD[2] + currentPos[1])

		time.sleep(0.01)	



	plottingGraph(xPoints1, yPoints1, xPoints2, yPoints2)


sim.simxFinish(-1)
