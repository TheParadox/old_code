#include "Planet.hpp"

Planet::Planet()
{

}

Planet::Planet(long long id, long long systemID)
{
	id_ = id;
	systemID_ = systemID;
}

Planet::~Planet()
{
	for(auto m : moons_)
	{
		delete m;
	}
	moons_.clear();
}

void Planet::generatePlanet(Star* star, std::mt19937_64 gen, int count, double systemVolume, double sma, double e, bool isJovian)
{
	std::uniform_int_distribution<> iDist;

	semiMajorAxis_ = sma;
	name_ = star->getStarName() + "-" + std::to_string(count);

	if(isJovian)
	{
		generateJovian(gen, star->getLH2Line());
	}
	else
	{
		generateTerrestrial(gen, star->getCHZInner(), star->getCHZOuter(), star->getActualInnerLimit());
	}

	generateOrbit(gen, star->getStarMass(), e);

	if(isJovian)
	{
		iDist = std::uniform_int_distribution<>(5, 50);
	}
	else if(!isJovian)
	{
		iDist = std::uniform_int_distribution<>(0, 3);
	}

	numberOfMoons_ = iDist(gen);
	double remaining = 1.0;

	for(int i = 0; i < numberOfMoons_; i++)
	{
		moons_.push_back(new Planet(i, systemID_));
		moons_[i]->generateMoons(gen, name_, type_, i, &remaining, numberOfMoons_, i, radius_, density_, mass_);
	}

}

long long Planet::generateMoons(std::mt19937_64 gen, std::string planetName, std::string planetType, long long moonID, double* remainingMaterial, int moonCount, int num, double planetRadius, double planetDensity, double planetMass)
{
	long long currentMoonID = moonID;
	type_ = "Moon";
	subType_ = "Dead";

	double eAvg = (0.584 * pow(moonCount, -1.2));
	name_ += planetName + "-" + std::to_string(num + 1);
	double minRadius = 0.0172;

	double endMaterial = (*remainingMaterial);
	if(endMaterial > 1) { endMaterial = 1.0; }

	double maxMass = 0.0;
	double maxRadius = 0.0;
	if(planetType == "Jovian")
	{
		maxMass = 1.25 * endMaterial;
		maxRadius = 1.25 * endMaterial;
	}
	else if(planetType == "Terrestrial")
	{
		maxMass = 0.75 * endMaterial;
		maxRadius = 0.75 * endMaterial;
	}

	maxRadius *= planetRadius;

	minRadius *= 100000.0;
	maxRadius *= 100000.0;

	std::uniform_int_distribution<> iDist;
	iDist.reset();

	iDist = std::uniform_int_distribution<>(minRadius, maxRadius);
	radius_ = (iDist(gen) / 100000.0);

	iDist = std::uniform_int_distribution<>(50, (maxMass * 100.0));
	mass_ = (iDist(gen) / 100.0);

	density_ = (mass_ / pow(radius_, 3));
	gravity_ = (mass_ / pow(radius_, 2));

	(*remainingMaterial) -= (radius_ / maxRadius);

	double rocheLimit = (1.26 * planetRadius * pow( (planetDensity / density_), (1/3)));

	iDist = std::uniform_int_distribution<>(0, 100.0);
	orbitalEccentricity_ = (eAvg * (iDist(gen) / 100.0));

	if(planetType == "Jovian")
	{
		iDist = std::uniform_int_distribution<>(100, 500);
	}
	else if(planetType == "Terrestrial")
	{
		iDist = std::uniform_int_distribution<>(100, 3000);
	}

	semiMajorAxis_ = rocheLimit * (iDist(gen) / 100.0);

	apoapsis_ = (semiMajorAxis_ * (1 + orbitalEccentricity_));
	periapsis_ = (semiMajorAxis_ * (1 - orbitalEccentricity_));
	orbitalPeriod_ = sqrt( pow(semiMajorAxis_, 3) / planetMass);
	orbitalVelocity_ = sqrt( planetMass / semiMajorAxis_);
	iDist = std::uniform_int_distribution<>(-15, 15);
	orbitalInclination_ = (iDist(gen) / 1000.0);
	escapeVelocity_ = gravity_ * 1.21;
	numberOfMoons_ = 0;

	return currentMoonID;
}

void Planet::generateOrbit(std::mt19937_64 gen, double starMass, double e)
{
	orbitalEccentricity_ = e;
	escapeVelocity_ = gravity_ * 1.21;
	apoapsis_ = (semiMajorAxis_ * (1 + orbitalEccentricity_));
	periapsis_ = (semiMajorAxis_ * (1 - orbitalEccentricity_));
	orbitalPeriod_ = sqrt( pow(semiMajorAxis_, 3) / starMass );
	orbitalVelocity_ = sqrt( starMass / semiMajorAxis_ );

	//std::random_device rd;
	//std::mt19937_64 gen(rd());
	std::uniform_int_distribution<> iDist(-30, 30);
	orbitalInclination_ = (iDist(gen) / 1000.0);
	//iDist.reset();

	hillSphere_ = (semiMajorAxis_ * (1 + orbitalEccentricity_) * pow((mass_ / (3 * starMass)), (1/3)) );
}

void Planet::generateTerrestrial(std::mt19937_64 gen, double chzInner, double chzOuter, double innerLimit)
{
	type_ = "Terrestrial";
	name_ += "T";

	//std::random_device rd;
	//std::mt19937_64 gen(rd());
	std::uniform_int_distribution<> iDist;

	int tSize = 0;
	if( (semiMajorAxis_ < chzOuter) &&
		(semiMajorAxis_ > chzInner) )
	{
		iDist = std::uniform_int_distribution<>(0, 20);
		tSize = iDist(gen);
		//iDist.reset();

		if(tSize < 15) { tSize = 1; } else { tSize = 2; }	
	}
	else 
	{
		iDist = std::uniform_int_distribution<>(1, 2);
		tSize = iDist(gen);
		//iDist.reset();
	}


	switch(tSize)
	{
		case 0:
			iDist = std::uniform_int_distribution<>(1, 1000);
			mass_ = ( iDist(gen) / 10000.0);

			iDist = std::uniform_int_distribution<>(3, 10);
			radius_ = ( iDist(gen) / 100.0);
			//iDist.reset();
			break;
		case 1:
			iDist = std::uniform_int_distribution<>(1, 35);
			mass_ = (iDist(gen) / 10.0);

			iDist = std::uniform_int_distribution<>(5, 15);
			radius_ = (iDist(gen) / 10.0);
			//iDist.reset();
			break;
		case 2:
			iDist = std::uniform_int_distribution<>(35, 100);
			mass_ = ( iDist(gen) / 10.0);

			iDist = std::uniform_int_distribution<>(15, 20);
			radius_ = ( iDist(gen) / 10.0);
			//iDist.reset();
			break;
		default:
			mass_ = -1;
			radius_ = -1;
			break;
	}

	density_ = ( mass_ / pow( radius_, 3 ) );
	gravity_ = ( mass_ / pow( radius_, 2 ) );

	if(
		((mass_ > 0.1) && (mass_ < 3.5)) &&
		((radius_ > 0.5) && (radius_ < 1.5)) &&
		((gravity_ > 0.4) && (gravity_ < 1.6)) &&
		((semiMajorAxis_ < chzOuter) && (semiMajorAxis_ > chzInner))
	)
	{
		if(
			(semiMajorAxis_ > chzInner) && 
			(semiMajorAxis_ < (chzInner * 1.1))
		)
		{
			subType_ = "Desert";
			name_ += "D";
		}
		else if(
			(semiMajorAxis_ < chzOuter) &&
			(semiMajorAxis_ > (chzOuter * 0.9))
		)
		{
			subType_ = "Ice";
			name_ += "I";
		}
		else if(density_ < 1)
		{
			subType_ = "Oceanic";
			name_ += "O";
		}
		else 
		{
			subType_ = "Earth-Analog";
			name_ += "EA";
		}
	}
	else 
	{
		if(semiMajorAxis_ > chzOuter)
		{
			if(density_ < 0.9)
			{
				subType_ = "Ice";
				name_ += "I";
			}
			else if(density_ > 1.1)
			{
				subType_ = "Iron";
				name_ += "Fe";
			}
			else 
			{
				subType_ = "Barren";
				name_ += "B";
			}
		}
		else if(semiMajorAxis_ < chzInner)
		{
			if(semiMajorAxis_ < (innerLimit * 1.17))
			{
				subType_ = "Lava";
				name_ += "L";
			}
			else if(density_ > 1.1)
			{
				subType_ = "Iron";
				name_ += "Fe";
			}
			else 
			{
				subType_ = "Barren";
				name_ += "B";
			}
		}
		else 
		{
			subType_ = "Barren";
			name_ += "B";
		}


	}

}

void Planet::generateJovian(std::mt19937_64 gen, double lh2Line)
{
	/*
	MASS (earth)
	8 < Dwarf Giant < 13
	10 < ICE < 39.5
	39.5 < LIQUID < 4131

	RADIUS (earth)
	2 < Dwarf Giant < 3.15
	3.15 < ICE < 6
	6 < LIQUID < 15

	DENSITY (ROUGH)
	1.4 < Dwarf Giant < 8.96
	1.00 < ICE < 1.85
	0.03 < LIQUID < 1.00

	if 2MassInJupiterUnits < Mass < 13 MassInJupiterUnits, radius in jupiter units = 1
	if 1Mj < Mass < 2Mj, follows parabola with 1.9j being the largest possible?
	*/

	type_ = "Jovian";
	name_ += "J";

	//std::random_device rd;
	//std::mt19937_64 gen(rd());
	std::uniform_int_distribution<> iDist;

	if(semiMajorAxis_ < lh2Line)
	{
		subType_ = "Liquid";
		name_ += "L";

		iDist = std::uniform_int_distribution<>(3950, 413100);
		mass_ = ( (iDist(gen) / 100.0) / 317.8);
		//iDist.reset();

		if(mass_ > 635.6)
		{
			radius_ = (11.2 / 11.2); //Yes == 1...
		}
		else 
		{
			iDist = std::uniform_int_distribution<>(600, 1500);
			radius_ = ( (iDist(gen) / 100.0) / 11.2);
			//iDist.reset();
		}
	}
	else if(semiMajorAxis_ > lh2Line)
	{
		subType_ = "Ice";
		name_ += "I";

		iDist = std::uniform_int_distribution<>(0, 1);
		if(iDist(gen))
		{
			//iDist.reset();
			iDist = std::uniform_int_distribution<>(1000, 3950);
			mass_ = ( (iDist(gen) / 100.0) / 317.8);

			//iDist.reset();
			iDist = std::uniform_int_distribution<>(315, 600);
			radius_ = ( (iDist(gen) / 100.0) / 11.2);
		}
		else 
		{
			//iDist.reset();
			iDist = std::uniform_int_distribution<>(800, 1300);
			mass_ = ( (iDist(gen) / 100.0) / 317.8);

			//iDist.reset();
			iDist = std::uniform_int_distribution<>(200, 315);
			radius_ = ( (iDist(gen) / 100.0) / 11.2);
		}
	}
	else 
	{

	}

	//iDist.reset();

	density_ = (mass_ / pow(radius_, 3));
	gravity_ = (mass_ / pow(radius_, 2));

}

std::string Planet::dataToFile()
{
	std::string data = "";

	data += "{";

	data += "\"id\":" + std::to_string(id_) + ",";
	data += "\"systemID\":" + std::to_string(systemID_) + ",";
	data += "\"name\":\"" + name_ + "\",";
	data += "\"type\":\"" + type_ + "\",";
	data += "\"subType\":\"" + subType_ + "\",";
	data += "\"mass\":" + std::to_string(mass_) + ",";
	data += "\"radius\":" + std::to_string(radius_) + ",";
	data += "\"density\":" + std::to_string(density_) + ",";

	data += "\"semiMajorAxis\":" + std::to_string(semiMajorAxis_) + ",";
	data += "\"periapsis\":" + std::to_string(periapsis_) + ",";
	data += "\"apoapsis\":" + std::to_string(apoapsis_) + ",";
	data += "\"orbitalPeriod\":" + std::to_string(orbitalPeriod_) + ",";
	data += "\"orbitalVelocity\":" + std::to_string(orbitalVelocity_) + ",";
	data += "\"orbitalInclination\":" + std::to_string(orbitalInclination_) + ",";
	data += "\"orbitalEccentricity\":" + std::to_string(orbitalEccentricity_) + ",";

	data += "\"gravity\":" + std::to_string(gravity_) + ",";
	data += "\"escapeVelocity\":" + std::to_string(escapeVelocity_) + ",";
	data += "\"numberOfMoons\":" + std::to_string(numberOfMoons_) + ",";
	data += "\"hillSphere\":" + std::to_string(hillSphere_) + ",";

	data += "\"moons\":[";

	if(type_ != "Moon")
	{
		for(int i = 0; i < numberOfMoons_; i++)
		{
			data += moons_[i]->dataToFile();
			if( (i + 1) < numberOfMoons_)
			{
				data += ",";
			}
		}
	}
	data += "]}";

	return data;
}