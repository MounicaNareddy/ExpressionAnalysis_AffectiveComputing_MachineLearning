#include "Preprocess.hpp"

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
	  std::cout << "Usage: <Operation Type> <Input File> <Output File>" << std::endl;
	}
	else
	{
		//read in arff file
		PreProcess pre(argv[2]);
		if (strcmp(argv[1], "translate_origin") == 0)
		{
			//translate to origin
			pre.Translate("origin");
		}
		else if (strcmp(argv[1], "translate_random") == 0)
		{
			//translate randomly
			pre.Translate("random");
		}
		else if (strcmp(argv[1], "rotate_x") == 0)
		{
			//rotate over x axis
			pre.Rotate('x');
		}
		else if (strcmp(argv[1], "rotate_y") == 0)
		{
			//rotate over y axis
			pre.Rotate('y');
		}
		else if (strcmp(argv[1], "rotate_z") == 0)
		{
			//rotate over z axis
			pre.Rotate('z');
		}
		else if (strcmp(argv[1], "scale") == 0)
		{
			pre.Scale();
		}
		else if (strcmp(argv[1], "features") == 0)
		{
			//calculate 3D features
		    pre.CalculateFeatures();
		}
		else
		{
			//error state, operation type doesn't exist so exit.
			std::cerr << "Incorrect operation type." << std::endl;
			return 1;
		}
		//write new arrf file
		pre.WriteOutput(argv[3]);
	}
	return 0;
}
