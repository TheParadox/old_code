#pragma once

#include "sc_pch.hpp"

enum class DataEntityType {
	Base = 0,
	School,
	Library,
	Student,
	Course,
	Book,
	Lesson,
	Question,
	Quiz,
	DataRequest,
	Config
};

enum class DataLoadingType {
	View,
	Load,
	Save,
	New
};

struct DataEntity {
	DataEntityType dataType = DataEntityType::Base;
	DataLoadingType reasonForData = DataLoadingType::View;

	int entityID;
};

struct DataRequest : public DataEntity {
	DataLoadingType loadingDataType = DataLoadingType::View;
	DataEntityType requestedDataType = DataEntityType::Base;
	std::string dataToLoad = "";

	SC::RefPtr<DataEntity> dataObject;

	DataRequest() {
		dataType = DataEntityType::DataRequest;
	}
};