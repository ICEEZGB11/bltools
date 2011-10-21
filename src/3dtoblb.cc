#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stdlib.h>

#include "../deps/boost/boost/algorithm/string.hpp"
#include "../deps/assimp/include/assimp.hpp"
#include "../deps/assimp/include/aiVector3D.h"
#include "../deps/assimp/include/aiPostProcess.h" 
#include "../deps/assimp/include/aiScene.h"
#include "../deps/assimp/include/aiConfig.h"
#include "../deps/assimp/include/aiMesh.h"

#include "bltools.h"

#define BLTOOLS_3DTOBLB_VERSION "v0.0.1pre"

int main(int argc,char* argv[])
{
	const char* outFile = "";
	const char* inFile = "";
	const char* brickSize = "";
	unsigned int brickWidth = 1;
	unsigned int brickLength = 1;
	unsigned int brickHeight = 1;
	bool needsHelp = argc <= 1;
	
	unsigned long beganAt = bltools::timestamp();
	
	for(unsigned int i=1;i<argc;i++)
	{
		const char* arg = argv[i];
		bool hasArgument = i + 1 < argc;
		
		if(boost::equals(arg,"-h") || boost::equals(arg,"--help"))
			needsHelp = true;
		else if(boost::equals(arg,"-v") || boost::equals(arg,"--version"))
			bltools::dump(BLTOOLS_3DTOBLB_VERSION);
		else if((boost::equals(arg,"-s") || boost::equals(arg,"--size")) && hasArgument)
		{
			brickSize = argv[i + 1];
			i++;
			continue;
		}
		else if((boost::equals(arg,"-o") || boost::equals(arg,"--output")) && hasArgument)
		{
			outFile = argv[i + 1];
			i++;
			continue;
		}
		else if((boost::equals(arg,"-i") || boost::equals(arg,"--input")) && hasArgument)
		{
			inFile = argv[i + 1];
			i++;
			continue;
		}
		else if(inFile == NULL || boost::iequals(inFile,""))
			inFile = arg;
		else if(outFile == NULL || boost::iequals(outFile,""))
			outFile = arg;
	}
	
	if(needsHelp)
		bltools::dump("Usage: 3dtoblb [OPTIONS] INPUT OUTPUT\n\n"
		"  -h, --help\tdisplay this message and exit\n"
		"  -v, --version\tdisplay the version and exit\n"
		"  -s, --size\tset the brick size delimited by \'x\', defaults to \'1x1x1\'\n"
		"  -o, --output\tchange the file to write to\n"
		"  -i, --input\tchange the file to read\n");
	
	if(inFile == NULL || boost::iequals(inFile,""))
		bltools::dump("You haven't provided the input 3d model filename.",1,BLTOOLS_RED);
	if(outFile == NULL || boost::iequals(outFile,""))
		bltools::dump("You haven't provided the output BLB filename.",1,BLTOOLS_RED);
	
	std::ifstream in(inFile);
	
	if(in.fail())
		bltools::dump("Couldn't open the input 3d model for reading.",1,BLTOOLS_RED);
	else
		in.close();
		
	Assimp::Importer importer;
	
	{
		std::string path(inFile);
		std::string extension(path.substr(path.find_last_of(".")));
		
		if(!importer.IsExtensionSupported(extension.c_str()))
			bltools::dump("The input 3d model is not of a supported 3d model format.",1,BLTOOLS_RED);
	}
	
	std::ofstream out(outFile);
	
	if(out.fail())
		bltools::dump("Couldn't open the output BLB for writing.",1,BLTOOLS_RED);
	
	const aiScene* scene = importer.ReadFile(inFile,aiProcess_RemoveRedundantMaterials | aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph | aiProcess_GenNormals | aiProcess_GenUVCoords);
	
	if(scene == NULL)
		bltools::dump("Couldn't load the input 3d model. The model is probably broken, try re-exporting it.",1,BLTOOLS_RED);

	bltools::print("Converting...\n");

	std::vector<std::string> brickSizes;
	boost::split(brickSizes,brickSize,boost::is_any_of("x"));
	
	if(brickSizes.size() > 0)
		brickWidth = atoi(brickSizes[0].c_str());
	if(brickSizes.size() > 1)
		brickLength = atoi(brickSizes[1].c_str());
	if(brickSizes.size() > 2)
		brickHeight = atoi(brickSizes[2].c_str());
	if(brickWidth < 1)
		brickWidth = 1;
	if(brickLength < 1)
		brickLength = 1;
	if(brickHeight < 1)
		brickHeight = 1;
		
	out << brickWidth << " " << brickLength << " " << brickHeight << std::endl;
	out << "SPECIAL" << std::endl << std::endl;
	
	if(brickWidth == 1 && brickLength == 1 && brickHeight == 1)
		out << "b" << std::endl << std::endl;
	else
	{
		for(unsigned int x=0;x<brickWidth;x++)
		{
			for(unsigned int z=0;z<brickHeight;z++)
			{
				for(unsigned int y=0;y<brickLength;y++)
				{
					if(brickHeight == 1)
						out << "b";
					else if(z == 0)
						out << "u";
					else if(z == brickHeight - 1)
						out << "d";
					else
						out << "x";
				}
				
				out << std::endl;
			}
			
			out << std::endl;
		}
	}
	
	out << 1 << std::endl << std::endl;
	out << 0 << " " << 0 << " " << 0 << std::endl;
	out << brickWidth << " " << brickLength << " " << brickHeight << std::endl;
	
	out << "----------------top quads:" << std::endl << 0 << std::endl;
	out << "----------------bottom quads:" << std::endl << 0 << std::endl;
	out << "----------------north quads:" << std::endl << 0 << std::endl;
	out << "----------------east quads:" << std::endl << 0 << std::endl;
	out << "----------------south quads:" << std::endl << 0 << std::endl;
	out << "----------------west quads:" << std::endl << 0 << std::endl;
	out << "----------------omni quads:" << std::endl;
	
	unsigned int quadCount = 0;
	std::stringstream quadStream;

	for(unsigned int i=0;i<scene->mNumMeshes;i++)
	{
		const struct aiMesh* mesh = scene->mMeshes[i];
	
		if(!mesh->mNumVertices)
			continue;
	
		{
			std::stringstream temp;
			
			temp << i + 1;
			
			bltools::print((std::string("[Mesh ") + temp.str() + std::string("]")).c_str(),BLTOOLS_BLUE);
		}
		
		if(!mesh->HasNormals())
		{
			bltools::print("\tNo normals, skipping. You need to export with them for this to work.",BLTOOLS_RED);
		
			continue;
		}
		
		if(!mesh->GetNumUVChannels())
			bltools::print("\tNo texture coordinates available, using default.",BLTOOLS_BLUE);
			
		const char* name = mesh->mName.data;
		unsigned int faceCount = mesh->mNumFaces;
		const char* tex = "SIDE";
		
		if(name != NULL)
		{
			if(boost::iequals(name,"top"))
				tex = "SIDE";
			else if(boost::iequals(name,"ramp"))
				tex = "RAMP";
			else if(boost::iequals(name,"bottomedge"))
				tex = "BOTTOMEDGE";
			else if(boost::iequals(name,"bottomloop"))
				tex = "BOTTOMLOOP";
			else
				tex = "SIDE";
		}
		
		bool triangulated = !(mesh->mPrimitiveTypes & aiPrimitiveType_POLYGON);
		
		for(unsigned int j=0;j<faceCount;j++)
		{
			const struct aiFace* face = &mesh->mFaces[j];
			
			quadStream << std::endl << "TEX:" << tex << std::endl;
		
			unsigned int index1 = face->mIndices[0];
			unsigned int index2 = face->mIndices[1];
			unsigned int index3 = face->mIndices[2];
			unsigned int index4;
			
			if(triangulated)
				index4 = index3;
			else
				index4 = face->mIndices[3];
		
			{
				aiVector3D vertex1 = mesh->mVertices[index1];
				aiVector3D vertex2 = mesh->mVertices[index2];
				aiVector3D vertex3 = mesh->mVertices[index3];
				aiVector3D vertex4 = mesh->mVertices[index4];
			
				quadStream << "POSITION:" << std::endl;
				quadStream << vertex1.x << " " << vertex1.z << " " << vertex1.y * 2.5 << std::endl;
				quadStream << vertex2.x << " " << vertex2.z << " " << vertex2.y * 2.5 << std::endl;
				quadStream << vertex3.x << " " << vertex3.z << " " << vertex3.y * 2.5 << std::endl;
				quadStream << vertex4.x << " " << vertex4.z << " " << vertex4.y * 2.5 << std::endl;
			}
		
			if(mesh->GetNumUVChannels() >= 2)
			{
				aiVector3D* coord1 = mesh->mTextureCoords[index1];
				aiVector3D* coord2 = mesh->mTextureCoords[index2];
				aiVector3D* coord3 = mesh->mTextureCoords[index3];
				aiVector3D* coord4 = mesh->mTextureCoords[index4];
			
				quadStream << "UV COORDS:" << std::endl;
				quadStream << coord1->x << " " << coord1->y << std::endl;
				quadStream << coord2->x << " " << coord2->y << std::endl;
				quadStream << coord3->x << " " << coord3->y << std::endl;
				quadStream << coord4->x << " " << coord4->y << std::endl;
			}
			else
			{
				quadStream << "UV COORDS:" << std::endl;
				quadStream << "0 0" << std::endl;
				quadStream << "1 0" << std::endl;
				quadStream << "1 1" << std::endl;
				quadStream << "0 1" << std::endl;
			}
		
			if(mesh->GetNumColorChannels() >= 4)
			{
				aiColor4D* colour1 = mesh->mColors[index1];
				aiColor4D* colour2 = mesh->mColors[index2];
				aiColor4D* colour3 = mesh->mColors[index3];
				aiColor4D* colour4 = mesh->mColors[index4];
			
				quadStream << "COLORS:" << std::endl;
				quadStream << colour1->r << " " << colour1->g << " " << colour1->b << " " << colour1->a << std::endl;
				quadStream << colour2->r << " " << colour2->g << " " << colour2->b << " " << colour2->a << std::endl;
				quadStream << colour3->r << " " << colour3->g << " " << colour3->b << " " << colour3->a << std::endl;
				quadStream << colour4->r << " " << colour4->g << " " << colour4->b << " " << colour4->a << std::endl;
			}
		
			{
				aiVector3D normal1 = mesh->mNormals[index1];
				aiVector3D normal2 = mesh->mNormals[index2];
				aiVector3D normal3 = mesh->mNormals[index3];
				aiVector3D normal4 = mesh->mNormals[index4];

				quadStream << "NORMALS:" << std::endl;
				quadStream << normal1.x << " " << normal1.z << " " << normal1.y << std::endl;
				quadStream << normal2.x << " " << normal2.z << " " << normal2.y << std::endl;
				quadStream << normal3.x << " " << normal3.z << " " << normal3.y << std::endl;
				quadStream << normal4.x << " " << normal4.z << " " << normal4.y << std::endl;
			}
		}
		
		quadCount += faceCount;
	}
	
	out << quadCount << std::endl << quadStream.str().c_str();
	
	unsigned long finishedAt = bltools::timestamp();
	
	out.close();
	std::cout << std::endl << "Completed converting in " << finishedAt - beganAt << "ms." << std::endl;

	return 0;
}
