#include "Star.hpp"
#include "Planet.hpp"
#include "FileWriter.hpp"

#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>


int main(int argv, char* argc[]){

	std::cout << "Starting!" << std::endl;

	long long totalObjects = 0;
	int galaxyFloor = -1;
	int currentHeight = 0;
	long long maxSystemCount = 1;
	long long systemsPerFloor = (maxSystemCount > 1) ? (maxSystemCount / (galaxyFloor * -2)) : 1;
	long long systemID = 1;
	long long planetID = 1;
	long long moonID = 1;

	bool lastStar = false, lastPlanet = false, lastMoon = false;

	std::random_device rd;
	std::mt19937_64 gen(1);
	std::uniform_int_distribution<> iDist;
	std::uniform_real_distribution<> rDist;

	Star star;
	Planet planet;
	FileWriter writer;

	for(long long s = 0; s < maxSystemCount; s++)
	{
		gen.seed( std::chrono::system_clock::now().time_since_epoch().count() );
		double remainingSystemVolume = 0.0;
		star = Star(systemID);
		remainingSystemVolume = star.generateStar(gen);

		writer.newFile(star.getStarName());
		writer.writeDataToFile(star.dataToFile(), "star", 1, 1);

		currentHeight = galaxyFloor + floor( s / systemsPerFloor );
		//star position

		if(maxSystemCount <= s)
		{
			lastStar = true;
		}

		bool isJovian = true;
		double eAvg = (0.584 * pow(star.getSatelliteCount(), - 1.2));

		double startPoint = 0.0;
		double currentPoint = 0.0;
		double previousPoint = 0.0;
		for(int p = 0; p < star.getSatelliteCount(); p++)
		{
			planet = Planet(planetID, systemID);
			totalObjects++;

			iDist = std::uniform_int_distribution<>(0, 100);
			double e = (eAvg * (iDist(gen) / 100.0));
			//iDist.reset();

			if(p == 0)
			{
				iDist = std::uniform_int_distribution<>(10, 12);
				startPoint = (star.getSnowLine() + (iDist(gen) / 10.0));
				//iDist.reset();
				currentPoint = startPoint;
			}
			else 
			{
				iDist = std::uniform_int_distribution<>(14, 20);
				if(isJovian)
				{
					currentPoint = (previousPoint * (iDist(gen) / 10.0));
				}
				else 
				{
					currentPoint = (previousPoint / (iDist(gen) / 10.0));
				}

				if(isJovian && (currentPoint > star.getOuterLimit()))
				{
					isJovian = false;
					currentPoint = (startPoint / (iDist(gen) / 10.0));
					//iDist.reset();
				}

				if(!isJovian && (currentPoint <= star.getActualInnerLimit()))
				{
					star.updateSatelliteCount(p + 1);
					writer.earlyBreak();
					break;
				}
			}

			planet.generatePlanet(&star, gen, (p + 1), remainingSystemVolume, currentPoint, e, isJovian);
			bool isFirst = (p == 0);
			bool isLast = ( (p + 1) == star.getSatelliteCount());
			writer.writeDataToFile(planet.dataToFile(), "planet", isFirst, isLast);

			previousPoint = currentPoint;
			planetID++;

		}

		writer.finishedWriting();
		std::cout << "Finished System: " << systemID << std::endl;
		systemID++;

	}


	std::cout << "Done!" << std::endl;
	return 0;
}