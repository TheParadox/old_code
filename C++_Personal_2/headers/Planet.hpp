#ifndef PLANET_HPP
#define PLANET_HPP

#include "Star.hpp"

#include <string>
#include <random>
#include <math.h>
#include <vector>

class Planet 
{
public:
	Planet();
	Planet(long long id, long long systemID);
	~Planet();

	void generatePlanet(Star* star, std::mt19937_64 gen, int count, double systemVolume, double sma, double e, bool isJovian);
	long long generateMoons(std::mt19937_64 gen, std::string planetName, std::string planetType, long long moonID, double* remainingMaterial, int moonCount, int num, double planetRadius, double planetDensity, double planetMass);
	void generateOrbit(std::mt19937_64 gen, double starMass, double e);
	void generateTerrestrial(std::mt19937_64 gen, double chzInner, double chzOuter, double innerLimit);
	void generateJovian(std::mt19937_64 gen, double lh2Line);
	
	std::string dataToFile();

private:
	long long id_;
	long long systemID_;
	std::string name_;
	std::string type_;
	std::string subType_;
	double mass_;
	double radius_;
	double density_;

	double semiMajorAxis_;
	double periapsis_;
	double apoapsis_;
	double orbitalPeriod_;
	double orbitalVelocity_;
	double orbitalInclination_;
	double orbitalEccentricity_;

	double gravity_;
	double escapeVelocity_;
	int numberOfMoons_;
	std::vector<Planet*> moons_;
	double hillSphere_;

};

#endif //PLANET_HPP