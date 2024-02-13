#from Map import Map

#map = Map('Node', 100, 1, 'Demo', {0, 0, 0}, {0, 0, 0})

import keyboard
import time
import matplotlib.pyplot as plt
from PIL import Image
import array

from aStar import aStarNode, aStarPathfinding

try:
	import sim
except:
	print ('--------------------------------------------------------------')
	print ('"sim.py" could not be imported. This means very probably that')
	print ('either "sim.py" or the remoteApi library could not be found.')
	print ('Make sure both are in the same folder as this file,')
	print ('or appropriately adjust the file "sim.py"')
	print ('--------------------------------------------------------------')
	print ('')

import time

path = [[0, 0], [1, 0], [1, 1]  ]


print ('Program started')
sim.simxFinish(-1) # just in case, close all opened connections
clientID = sim.simxStart('127.0.0.1',19999,True,True,5000,5) # Connect to CoppeliaSim
if (clientID != -1):
	print ('Connected to remote API server')

	[returnCode, mappingCamera] = sim.simxGetObjectHandle(clientID, 'MappingCamera', sim.simx_opmode_blocking)
	sim.simxGetVisionSensorImage(clientID, mappingCamera, 0, sim.simx_opmode_streaming)
	time.sleep(1)
	[returnCode, resolution, mapImage] = sim.simxGetVisionSensorImage(clientID, mappingCamera, 0, sim.simx_opmode_buffer)

	star = aStarPathfinding(mapImage, resolution, [10, 10])
	star.findPath([-3.0, 1.8], [3.425, 3.575])

	
	#print(mapImage)
	#plt.figure(mapImage)

	[errorCode, leftMotor] = sim.simxGetObjectHandle(clientID, 'Pioneer_p3dx_leftMotor', sim.simx_opmode_oneshot_wait)
	[errorCode, rightMotor] = sim.simxGetObjectHandle(clientID, 'Pioneer_p3dx_rightMotor', sim.simx_opmode_oneshot_wait)
	[errorCode, mainBody] = sim.simxGetObjectHandle(clientID, 'Pioneer_p3dx', sim.simx_opmode_oneshot_wait)
	[returnCode, position] = sim.simxGetObjectPosition(clientID, mainBody, -1, sim.simx_opmode_streaming)

	while(not keyboard.is_pressed('t')):
		if(keyboard.is_pressed('w')):
			print("Move Forward")
			sim.simxSetJointTargetVelocity(clientID, leftMotor, 0.2, sim.simx_opmode_oneshot)
			sim.simxSetJointTargetVelocity(clientID, rightMotor, 0.2, sim.simx_opmode_oneshot)
			#sim.simxSetObjectPosition(clientID, movingHandle, -1, [1, 1, 1], sim.simx_opmode_oneshot)
		if(keyboard.is_pressed('s')):
			print("Move Backward")
			sim.simxSetJointTargetVelocity(clientID, leftMotor, -0.2, sim.simx_opmode_oneshot)
			sim.simxSetJointTargetVelocity(clientID, rightMotor, -0.2, sim.simx_opmode_oneshot)
			#sim.simxSetObjectPosition(clientID, movingHandle, -1, [-1, 1, 1], sim.simx_opmode_oneshot)
		if(keyboard.is_pressed('a')):
			print("Rotate Left")
			sim.simxSetJointTargetVelocity(clientID, leftMotor, -0.2, sim.simx_opmode_oneshot)
			sim.simxSetJointTargetVelocity(clientID, rightMotor, 0.2, sim.simx_opmode_oneshot)
			#sim.simxSetObjectPosition(clientID, movingHandle, -1, [0, 1, 1], sim.simx_opmode_oneshot)
		if(keyboard.is_pressed('d')):
			print("Rotate Right")
			sim.simxSetJointTargetVelocity(clientID, leftMotor, 0.2, sim.simx_opmode_oneshot)
			sim.simxSetJointTargetVelocity(clientID, rightMotor, -0.2, sim.simx_opmode_oneshot)
			#sim.simxSetObjectPosition(clientID, movingHandle, -1, [0, -1, 1], sim.simx_opmode_oneshot)
		if(keyboard.is_pressed('e')):
			print("Stop")
			sim.simxSetJointTargetVelocity(clientID, leftMotor, 0.0, sim.simx_opmode_oneshot)
			sim.simxSetJointTargetVelocity(clientID, rightMotor, 0.0, sim.simx_opmode_oneshot)
			#sim.simxSetObjectPosition(clientID, movingHandle, -1, [0, -1, 1], sim.simx_opmode_oneshot)
		if(keyboard.is_pressed('q')):
			print("Map Node")
			[returnCode, dummyHandle] = sim.simxCreateDummy(clientID, 0.1, [0, 0, 255], sim.simx_opmode_blocking)
			[returnCode, position] = sim.simxGetObjectPosition(clientID, mainBody, -1, sim.simx_opmode_buffer)
			sim.simxSetObjectPosition(clientID, dummyHandle, -1, position, sim.simx_opmode_oneshot)
			#[res, retInts, retFloats, reStrings, restBuffer] = sim.simxCallScriptFunction(clientID, "SpawnCuiboid", sim.sim_scripttype_childscript, 'SpawningCuboidNode', [], [], [spawnning], bytearray(), sim.simx_opmode_blocking)


	#sim.simxSetJointTargetVelocity(clientID, movingHandle, 0.2, sim.simx_opmode_streaming)
	#sim.simxSetObjectPosition(clientID, movingHandle, -1, {1, 1, 1}, sim.simx_opmode_oneshot)
	time.sleep(1)
	#sim.simxSetObjectPosition(clientID, movingHandle, -1, {2, 1, 1}, sim.simx_opmode_oneshot)
	time.sleep(1)
	#sim.simxSetObjectPosition(clientID, movingHandle, -1, {2, 2, 1}, sim.simx_opmode_oneshot)
	time.sleep(1)

	# Before closing the connection to CoppeliaSim, make sure that the last command sent out had time to arrive. You can guarantee this with (for example):
	#sim.simxGetPingTime(clientID)

	# Now close the connection to CoppeliaSim:
	#sim.simxFinish(clientID)
else:
	print ('Failed connecting to remote API server')
print ('Program ended')

