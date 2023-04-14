#ifndef CALIBRATION_H
#define CALIBRATION_H
#include <string.h>
#include <vector>
Int_t fCh;
Int_t nCh;
Int_t nPoints;
Int_t evMaxCell;
Int_t evMaxSample;
Int_t evMaxTc;
Int_t evMaxTgc;

vector<float> vValues;
vector<string> sDirs;

string ampDir;
string lcTDir;
string gbTDir;


void Init(){
	printf("Start of the Calibration Code\n");
	ifstream settingReader;
	settingReader.open("./Settings.ini");
	if(!settingReader){ printf("No setting file found; quiting. \n"); exit(0);}
	string settingField;
	string settingValue;
	int settingCounter =0;
	while(settingReader>>settingField>>settingValue){
		settingCounter++;
		if(settingField=="_FRST_CHN_") fCh = stoi(settingValue);
		if(settingField=="_N_CHNNLS_") nCh 		= stoi(settingValue);
		if(settingField=="_N_POINTS_") nPoints	= stoi(settingValue);
		if(settingField=="_VLTG_VAL_")
		{
			string tempString;
			for(int i=1; settingValue[i] !='\0'; i++){
				if(settingValue[i] != ',' && settingValue[i] != ']') 
				tempString = tempString+settingValue[i];
				if(settingValue[i]==','){
					vValues.push_back(stof(tempString.c_str()));
					//printf("-->%s\n",tempString.c_str());	
					tempString="";
				}		
			}
			if(nPoints!=(int)(vValues.size())){printf("Voltage point mismatch; quiting \n"); exit(0);};
		}
		if(settingField=="_EMX_CELL_") evMaxCell = stoi(settingValue);
		if(settingField=="_EMX_SAMP_") evMaxSample = stoi(settingValue);
		if(settingField=="_EMX_TLOC_") evMaxTc = stoi(settingValue);
		if(settingField=="_EMX_TGLB_") evMaxTgc = stoi(settingValue);
		if(settingField=="_AMPL_DIR_") ampDir = settingValue;
		if(settingField=="_AMP_SDIR_")
		{
			string tempString;
			for(int i=1; settingValue[i] !='\0'; i++){
				if(settingValue[i] != ',') 
				tempString = tempString+settingValue[i];
				if(settingValue[i]==','){
					sDirs.push_back(tempString);
					//printf("-->%s\n",tempString.c_str());	
					tempString="";
				}		
			}
			if(nPoints!=sDirs.size()){printf("Number of Sub Dir mismatch; quiting \n"); exit(0);};
		}
		if(settingField=="_TLOC_DIR_") lcTDir = settingValue;
		if(settingField=="_TGLB_DIR_") gbTDir = settingValue;
	}	
	//printf("File read; %d settings value read and %d channels read\n", settingCounter, nPoints);
}

void AmplitudeCorrection(){
	TString fileString;
	for(int i=0; i<nCh; i++){
		for(int j=0; j<nPoints; j++){
			fileString.Form("%sch_%d/%s",ampDir.c_str(),fCh+i,sDirs[j].c_str());
			printf("Reading File: %s\n",fileString.Data());
		}
	}	
}
#endif

