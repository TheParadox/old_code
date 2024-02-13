#include "Star.hpp"

Star::Star()
{

}

Star::Star(long long systemID)
{
	id_ = systemID;
}

Star::~Star()
{

}

int Star::getSatelliteCount()
{
	return satelliteCount_;
}

std::string Star::getStarName()
{
	return starName_;
}

double Star::getStarMass()
{
	return starMass_;
}

double Star::getActualInnerLimit()
{
	return actualInnerLimit_;
}

double Star::getCHZInner()
{
	return chzInner_;
}

double Star::getCHZOuter()
{
	return chzOuter_;
}

double Star::getSnowLine()
{
	return snowLine_;
}

double Star::getLH2Line()
{
	return lh2Line_;
}

double Star::getOuterLimit()
{
	return outerLimit_;
}


void Star::updateSatelliteCount(int count)
{
	satelliteCount_ = count;
}

double Star::generateStar(std::mt19937_64 gen)
{
	double volume = 0.0;
	volume = generateSystemVolume(gen);
	generateStarVolume(gen, volume);
	determineStarRatio();
	generateStarData(gen, volume);

	volume -= starVolume_;

	return volume;
}

double Star::generateSystemVolume(std::mt19937_64 gen)
{
	//std::random_device rd;
	//std::mt19937_64 gen(rd());
	std::uniform_int_distribution<> dist(0, 1000);
	int chance = dist(gen);

	double data = 1.9911; // (1.9891 * 10^30) * 1.001

	int min = 0, max = 0;
	if(chance <= 820)
	{
		min = 6;
		max = 51;
	}
	else if(chance <= 910)
	{
		min = 52;
		max = 79;
	}
	else if(chance <= 955)
	{
		min = 80;
		max = 105;
	}
	else if(chance <= 985)
	{
		min = 106;
		max = 160;
	}
	else if(chance <= 992)
	{
		min = 161;
		max = 290;
	}
	else if(chance <= 999){
		min = 291;
		max = 1700;
	}
	else if(chance <= 1000)
	{
		min = 1701;
		max = 12000;
	}

	dist = std::uniform_int_distribution<>(min, max);

	data *= ( dist(gen) / 100.0 );
	//dist.reset();

	return data;
}
void Star::generateStarVolume(std::mt19937_64 gen, double systemVolume)
{
	//std::random_device rd;
	//std::mt19937_64 gen(rd());
	std::uniform_int_distribution<> dist(-10, 10);
	double data = (0.9990 + ( dist(gen) / 10000.0));
	//dist.reset();

	starVolume_ = (systemVolume * data);
	starMass_ = (starVolume_ * 1.9891);
}

void Star::determineStarRatio()
{
	double sun = 1.9891; //* 10^30

	double ratio = (starMass_ / sun);
	if(ratio < 0.1)
	{
		ratio = 0.1;
	}

	starRatio_ = ratio;
}

void Star::generateStarData(std::mt19937_64 gen, double systemVolume)
{
	double sunDensity = 1.9891; // * 10^30
	double convertedMass = (starMass_ / sunDensity);

	std::string starClass = "";
	for(int i = 0; i < 13; i += 2)
	{
		int ti = i + 1;
		if( (STAR_CLASS_MASS[i] > convertedMass) && (STAR_CLASS_MASS[ti] < convertedMass) )
		{
			scArrayUpper_ = i;
			scArrayLower_ = ti;
		}
		else 
		{
			//error... mass not found...
		}
	}

	scPercentage_ = ( ( convertedMass - STAR_CLASS_MASS[scArrayLower_] ) / ( STAR_CLASS_MASS[scArrayUpper_] - STAR_CLASS_MASS[scArrayLower_] ) );

	if(scPercentage_ > 1.0)
	{
		//error...
		scPercentage_ = 1.0;
		scArrayUpper_ = 0;
		scArrayLower_ = 0;
	}

	starRadius_ = ( (( STAR_CLASS_RADIUS[scArrayUpper_] - STAR_CLASS_RADIUS[scArrayLower_]) * scPercentage_ ) + STAR_CLASS_RADIUS[scArrayLower_]);

	starLuminosity_ = ( (( STAR_CLASS_LUMINOSITY[scArrayUpper_] - STAR_CLASS_LUMINOSITY[scArrayLower_]) * scPercentage_ ) + STAR_CLASS_LUMINOSITY[scArrayLower_]);

	starTemp_ = (((STAR_CLASS_TEMPERATURE[scArrayUpper_] - STAR_CLASS_TEMPERATURE[scArrayLower_]) * scPercentage_ ) + STAR_CLASS_TEMPERATURE[scArrayLower_]);

	if( STAR_CLASS_TYPE[scArrayUpper_] == STAR_CLASS_TYPE[scArrayLower_] )
	{
		starClass = STAR_CLASS_TYPE[scArrayUpper_];
		int tempDesg = (9 - std::floor(scPercentage_ * 9));
		starClass += std::to_string(tempDesg);
	}

	gravity_ = (((6.67 * pow(10, -11)) * starMass_) / pow( (starRadius_ * 695700 * 1000), 2 ));
	escapeVelocity_ = (gravity_ * 1.5);

	//std::random_device rd;
	//std::mt19937_64 gen(rd());
	std::uniform_int_distribution<> num(1, 9);
	std::uniform_int_distribution<> chance(0, 100);

	starName_ = starClass + "-";

	std::string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for(int i = 0; i < 10; i++)
	{
		if(chance(gen) < 50)
		{
			shuffle(alpha.begin(), alpha.end(), gen);
			starName_ += alpha.substr(1, 1);
		}
		else 
		{
			starName_ += std::to_string(num(gen));
		}
		num.reset();
		chance.reset();
	}

	starDensity_ = (starMass_ / starVolume_);

	/****************STAR REGIONS******************/
	//all values in AU
	//circumstellar habitable zone
	chzInner_ = (sqrt(starLuminosity_ / 1.2));
	chzOuter_ = (sqrt(starLuminosity_ / 0.63));

	//system inner limits
	innerGravLimit_ = (0.2 * starRatio_);
	innerLightLimit_ = (sqrt(starLuminosity_ / 16.0));

	if(innerGravLimit_ < innerLightLimit_)
	{
		actualInnerLimit_ = innerLightLimit_;
	}
	else 
	{
		actualInnerLimit_ = innerGravLimit_;
	}

	//system outer limit
	outerLimit_ = (40 * starRatio_); // radius of the system in AU

	//snow line - Jupiter stars...
	snowLine_ = (sqrt(starLuminosity_ / 0.04));

	//liquid hydrogen line - roughly Uranus/Neptune
	lh2Line_ = (sqrt(starLuminosity_ / 0.0025));
	/****************STAR REGIONS******************/

	std::uniform_int_distribution<> dist(-10, 10);
	double remainingSystemVolume = systemVolume - starVolume_;
	//double remainingSystemVolume = 0.0;
	if(remainingSystemVolume > 0)
	{
		satelliteCount_ = 10 + dist(gen);
		//dist.reset();
	}
	else 
	{
		satelliteCount_ = 0;
	}
}

std::string Star::dataToFile()
{
	std::string data = "";

	data += "{";

	data += "\"id\":" + std::to_string(id_) + ",";
	data += "\"name\":\"" + starName_ + "\","; 
	data += "\"volume\":" + std::to_string(starVolume_) + ",";
	data += "\"mass\":" + std::to_string(starMass_) + ",";
	data += "\"density\":" + std::to_string(starDensity_) + ","; 
	data += "\"luminosity\":" + std::to_string(starLuminosity_) + ","; 
	data += "\"temp\":" + std::to_string(starTemp_) + ","; 
	data += "\"radius\":" + std::to_string(starRadius_) + ","; 
	data += "\"chzInner\":" + std::to_string(chzInner_) + ","; 
	data += "\"chzOuter\":" + std::to_string(chzOuter_) + ","; 
	data += "\"satellites\":" + std::to_string(satelliteCount_) + ","; 
	data += "\"gravity\":" + std::to_string(gravity_) + ",";
	data += "\"escapeVelocity\":" + std::to_string(escapeVelocity_) + ","; 
	data += "\"innerGravLimit\":" + std::to_string(innerGravLimit_) + ","; 
	data += "\"innerLightLimit\":" + std::to_string(innerLightLimit_) + ","; 
	data += "\"actualInnerLimit\":" + std::to_string(actualInnerLimit_) + ","; 
	data += "\"snowLine\":" + std::to_string(snowLine_) + ",";
	data += "\"lh2Line\":" + std::to_string(lh2Line_) + ",";
	data += "\"outerLimit\":" + std::to_string(outerLimit_) + ",";
	
	data += "\"ratio\":" + std::to_string(starRatio_) + ",";
	
	//data += ":" + std::to_string(scArrayUpper_) + ",";
	//data += "id:" + std::to_string(scArrayLower_) + ",";
	//data += "id:" + std::to_string(scPercentage_) + ",";
	
	data += "\"x\":" + std::to_string(xPos_) + ","; 
	data += "\"y\":" + std::to_string(yPos_) + ","; 
	data += "\"z\":" + std::to_string(zPos_); 

	data += "}";

	return data;
}