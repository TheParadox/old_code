#ifndef STAR_HPP
#define STAR_HPP

#include <string>
#include <random>
#include <algorithm>
#include <math.h>

static const std::string STAR_CLASS_TYPE[] = {"O", "O", "B", "B", "A", "A", "F", "F", "G", "G", "K", "K", "M", "M"};
static const int STAR_CLASS_NUMBER[] = {0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9};
static const double STAR_CLASS_RADIUS[] = {20.0, 7.5, 7.5, 2.5, 2.5, 1.4, 1.4, 1.05, 1.05, 0.9, 0.9, 0.7, 0.7, 0.13};
static const double STAR_CLASS_MASS[] = {75.0, 18.0, 18.0, 2.1, 2.1, 1.4, 1.4, 1.04, 1.04, 0.8, 0.8, 0.45, 0.45, 0.08};
static const double STAR_CLASS_LUMINOSITY[] = {500000, 30000, 30000, 25, 25, 5, 5, 1.5, 1.5, 0.6, 0.6, 0.08, 0.08, 0.0008};
static const int STAR_CLASS_TEMPERATURE[] = {50000, 30000, 30000, 10000, 10000, 7500, 7500, 6000, 6000, 5200, 5200, 3700, 3700, 2400}; //kelvin

class Star 
{
public:
	Star();
	Star(long long systemID);
	~Star();

	int getSatelliteCount();
	std::string getStarName();
	double getStarMass();
	double getActualInnerLimit();
	double getCHZInner();
	double getCHZOuter();
	double getSnowLine();
	double getLH2Line();
	double getOuterLimit();

	void updateSatelliteCount(int count);
	double generateStar(std::mt19937_64 gen);
	double generateSystemVolume(std::mt19937_64 gen);
	void generateStarVolume(std::mt19937_64 gen, double systemVolume);
	void determineStarRatio();
	void generateStarData(std::mt19937_64 gen, double systemVolume);

	std::string dataToFile();

private:
	long long id_; //star/system id
	std::string starName_; //name of the star/system
	double starVolume_; //star volume - M^3
	double starMass_; //star mass - KG
	double starDensity_; //density of the star
	double starLuminosity_; //luminosity of the star
	unsigned int starTemp_; //temperature of the star - Kelvin
	double starRadius_; //radius of the star - units of "sun"
	double chzInner_; //habitable zone inner (in AU)
	double chzOuter_; //habitable zone outer (in AU)
	int satelliteCount_; //number of planets/asteroid fields
	double gravity_;
	double escapeVelocity_; //km/s ?
	double innerGravLimit_; //inner most point a planet can form (in AU)
	double innerLightLimit_; //inner most point a planet can form (in AU)
	double actualInnerLimit_; //the actual closets point that a planet can form (in AU)
	double snowLine_;
	double lh2Line_;
	double outerLimit_;
	
	double starRatio_;
	
	int scArrayUpper_;
	int scArrayLower_;
	double scPercentage_;
	
	long long xPos_; //in km
	long long yPos_; //in km
	long long zPos_; //in km
};

#endif //STAR_HPP