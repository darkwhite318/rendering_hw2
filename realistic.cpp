
#include "stdafx.h"
#include "cameras/realistic.h"
#include <iostream>
#include <fstream>



RealisticCamera::RealisticCamera(const AnimatedTransform &cam2world,
				 float hither, float yon, 
				 float sopen, float sclose, 
				 float filmdistance, float aperture_diameter, string specfile, 
				 float filmdiag, Film *f)
	: Camera(cam2world, sopen, sclose, f) // pbrt-v2 doesnot specify hither and yon
{
	this->hither = hither;
	this->yon = yon;
	this->filmdistance = filmdistance;
	this->aperture_diameter = aperture_diameter;
	this->filmdiag = filmdiag;

	readFile(specfile);


   // YOUR CODE HERE -- build and store datastructures representing the given lens
   // and film placement.


	

}


void RealisticCamera::readFile(string fileName){	
	
	std::ifstream inFile (fileName.c_str());
	string line;

	while(std::getline(inFile,line)){
		
		if(line[0] == '#')
			continue;

		else{
			float radius, axpos, n, aperture;
			if(sscanf(line.c_str(),"%f %f %f %f",&radius, &axpos, &n, &aperture)>4){
				std::cerr<<fileName<<" not found."<<std::endl;
				exit(1);
			}

			LensKit lens = {radius, axpos, n, aperture};
			lensKitSet.push_back(lens);			
		}
	}
	inFile.close();
	
}





float RealisticCamera::GenerateRay(const CameraSample &sample, Ray *ray) const {
  // YOUR CODE HERE -- make that ray!
  
  // use sample->imageX and sample->imageY to get raster-space coordinates
  // of the sample point on the film.
  // use sample->lensU and sample->lensV to get a sample position on the lens
   return 0;
}


RealisticCamera *CreateRealisticCamera(const ParamSet &params,
        const AnimatedTransform &cam2world, Film *film) {
	// Extract common camera parameters from \use{ParamSet}
	float hither = params.FindOneFloat("hither", -1);
	float yon = params.FindOneFloat("yon", -1);
	float shutteropen = params.FindOneFloat("shutteropen", -1);
	float shutterclose = params.FindOneFloat("shutterclose", -1);

	// Realistic camera-specific parameters
	string specfile = params.FindOneString("specfile", "");
	float filmdistance = params.FindOneFloat("filmdistance", 70.0); // about 70 mm default to film
 	float fstop = params.FindOneFloat("aperture_diameter", 1.0);	
	float filmdiag = params.FindOneFloat("filmdiag", 35.0);

	Assert(hither != -1 && yon != -1 && shutteropen != -1 &&
		shutterclose != -1 && filmdistance!= -1);
	if (specfile == "") {
	    Severe( "No lens spec file supplied!\n" );
	}
	return new RealisticCamera(cam2world, hither, yon,
				   shutteropen, shutterclose, filmdistance, fstop, 
				   specfile, filmdiag, film);
}
