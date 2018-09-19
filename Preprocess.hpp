#ifndef PREPROCESS_HPP_INCLUDED
#define PREPROCESS_HPP_INCLUDED
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

struct coord
{
    float x;
    float y;
    float z;

};
struct Face
	{
		std::vector<coord>landmarks;
		std::vector<int>actionUnits;
		std::vector<float>physiologicalData;
		std::string emotionClass;
	};
	std::vector<Face>faceVec;


class PreProcess{

public:
		coord vertex;
  vector<coord> coordinates;
  vector<string> expr;
  vector<string> header;
  vector<float> features;
  vector<float> AUs;
  int sets=83,flagft=0;
  float face=0, lefteye=0,righteye=0,lefteyebrow=0,righteyebrow=0,nose=0,mouth=0;
  float euc1,euc2,euc3;

PreProcess(string str1)
{
  ifstream in(str1);
  string strtemp;
  char *tok;
  int flag=0,cnt=0;
  int i=1,j;
   char str[4000];
   char delims[] = ",";

   if(!in) {
    cout << "Cannot open input file.\n";
  }

   while(in) {
    in.getline(str, 4000);  // delim defaults to '\n'
    if(in)
    {
        strtemp= str;
        if(strtemp.find("@attribute")==0 || strtemp.find("@relation")==0 || strtemp.find("@data")==0 || strtemp.empty()==1 )
        {
            header.push_back(strtemp);
        }
        else
        {
         tok = strtok(str, delims);
         while(tok) {
          if(strcmp(tok,"T1")==0 || strcmp(tok,"T6")==0 || strcmp(tok,"T7")==0 || strcmp(tok,"T8")==0)
          {
            expr.push_back(tok);
           tok  = strtok(NULL, delims);
           cnt=0;
           continue;
          }
          if(cnt<83)
          {
            if(i==1)
            {
             vertex.x=atof(tok);
             i++;
            }

            else if(i==2)
            {
             vertex.y=atof(tok);
             i++;
            }

            else if(i==3)
             {
               vertex.z=atof(tok);
               cnt++;
               coordinates.push_back(vertex);
               i=1;
             }
          }
          else
          {
              AUs.push_back(atof(tok));
          }
          tok  = strtok(NULL, delims);
       }
      /* if(flag==0)
       {
           sets = cnt;
           flag=1;
       }*/

      }
   }
  }

}

void Translate(string str2)
{
   float sumx=0, sumy=0, sumz=0, avgx, avgy, avgz;
   int k=0;
   srand (time(NULL));
   int size1 = coordinates.size();
   if(str2.compare("origin")==0)
   {
      // cout<<"inside translate origin";
     for(int j=0; j<size1;j++)
     {
       if(k<sets-1)
       {
        sumx = sumx + coordinates[j].x;
        sumy = sumy + coordinates[j].y;
        sumz = sumz + coordinates[j].z;
        k++;
       }
       else
       {
        sumx = sumx + coordinates[j].x;
        sumy = sumy + coordinates[j].y;
        sumz = sumz + coordinates[j].z;
        k++;
        avgx = sumx/k;
        avgy = sumy/k;
        avgz = sumz/k;
        for(int m=(j+1)-k; m<j+1;m++)
        {
          coordinates[m].x = coordinates[m].x - avgx;
          coordinates[m].y = coordinates[m].y - avgy;
          coordinates[m].z = coordinates[m].z - avgz;
        }
        k=0;
        sumx=0;
        sumy=0;
        sumz=0;
        }
     }

   }
  if(str2.compare("random")==0)
  {
    float v1,v2,v3;
    for(int j=0; j<size1;j++)
    {
        if(j%sets==0)
        {
         v1 = rand() % 100 + 1;
         v2 = rand() % 100 + 1;
         v3 = rand() % 100 + 1;
        }
      coordinates[j].x = coordinates[j].x + v1;
      coordinates[j].y = coordinates[j].y + v2;
      coordinates[j].z = coordinates[j].z + v3;
    }
  }

}


void Rotate(char axis)
	{
	    int size1 = coordinates.size();
		if (axis == 'x')
		{
			for(int j=0; j<size1;j++)
            {
                coordinates[j].x = coordinates[j].x;
                coordinates[j].y = coordinates[j].y * (-1);
                coordinates[j].z = coordinates[j].z * (-1);
            }
		}
		else if (axis == 'y')
		{
			for(int j=0; j<size1;j++)
            {
                coordinates[j].x = coordinates[j].x * (-1);
                coordinates[j].y = coordinates[j].y;
                coordinates[j].z = coordinates[j].z * (-1);
            }
		}
		else if (axis == 'z')
		{
			for(int j=0; j<size1;j++)
            {
                coordinates[j].x = coordinates[j].x * (-1);
                coordinates[j].y = coordinates[j].y * (-1);
                coordinates[j].z = coordinates[j].z;
            }
		}
	}

void Scale()
	{
		//ADD CODE TO SCALE FACE TO 25% OF ORIGINAL SIZE
        int size1 = coordinates.size();
		for(int j=0; j<size1;j++)
            {
                coordinates[j].x = coordinates[j].x * (0.25);
                coordinates[j].y = coordinates[j].y * (0.25);
                coordinates[j].z = coordinates[j].z * (0.25);
            }

	}

void CalculateFeatures()
	{
		//ADD CODE TO CALCULATE FEATURES
		flagft=1;
		float difx=0.0,dify=0.0,difz=0.0, euc=0.0, avg=0.0;
		int size1 = coordinates.size();
		int k=0;
        float lreye,leyemouth,reyemouth;
		for(int m=1;m<=83;m++)
        {
            if(m>=1 && m<=83)
                face+=m;
            if(m>=29 && m<=36)
                lefteye+=m;
            if(m>=21 && m<=28)
                righteye+=m;
            if(m>=11 && m<=20)
                lefteyebrow+=m;
            if(m>=1 && m<=10)
                righteyebrow+=m;
            if(m>=37 && m<=48)
                nose+=m;
            if(m>=49 && m<=68)
                mouth+=m;
        }

        face = face/(83-1+1);
        lefteye = lefteye/(36-29+1);
        righteye = righteye/(28-21+1);
        lefteyebrow = lefteyebrow/(20-11+1);
        righteyebrow = righteyebrow/(10-1+1);
        nose = nose/(48-37+1);
        mouth = mouth/(68-49+1);
        lreye = righteye - lefteye;
        leyemouth = mouth - lefteye;
        reyemouth = mouth - righteye;
        euc1 = sqrt((lreye*lreye)+(lreye*lreye)+(lreye*lreye));
        euc2 = sqrt((leyemouth*leyemouth)+(leyemouth*leyemouth)+(leyemouth*leyemouth));
        euc3 = sqrt((reyemouth*reyemouth)+(reyemouth*reyemouth)+(reyemouth*reyemouth));

		//cout<<"size of coordinates: "<<coordinates.size()<<"\n";
		for(int j=0; j<size1-1;j++)
        {
            if(k<sets-1)
            {
                difx = coordinates[j].x - coordinates[j+1].x;
                dify = coordinates[j].y - coordinates[j+1].y;
                difz = coordinates[j].z - coordinates[j+1].z;
                euc = euc + sqrt((difx*difx)+(dify*dify)+(difz*difz));
                k++;
            }
            else
            {
                avg = euc/(sets-1);
                features.push_back(avg);
                euc = 0.0;
                k=0;
            }
            if(j==size1-2)
            {
               avg = euc/(sets-1);
               features.push_back(avg);
            }
        }
       // cout<<"size of features: "<<features.size();
	}



void WriteOutput(string str3)
{
    std::ofstream ofs;
    ofs.open (str3);
    ofs.clear();
     if(!ofs)
     {
      cout << "Cannot open output file.\n";
     }
    if(flagft==1)
    {
        int sizeh = header.size();
        for(int i=0;i<sizeh;i++)
        {
            if(header[i].find("@relation")==0)
            {
               ofs << header[i] << "\n";
               ofs<< "@attribute faceAverageX numeric\n";
               ofs<<"@attribute faceAverageY numeric\n";
               ofs<<"@attribute faceAverageZ numeric\n";
               ofs<<"@attribute leftEyeAverageX numeric\n";
               ofs<<"@attribute leftEyeAverageY numeric\n";
               ofs<<"@attribute leftEyeAverageZ numeric\n";
               ofs<<"@attribute rightEyeAverageX numeric\n";
               ofs<<"@attribute rightEyeAverageY numeric\n";
               ofs<<"@attribute rightEyeAverageZ numeric\n";
               ofs<<"@attribute leftEyebrowAverageX numeric\n";
               ofs<<"@attribute leftEyebrowAverageY numeric\n";
               ofs<<"@attribute leftEyebrowAverageZ numeric\n";
               ofs<<"@attribute rightEyebrowAverageX numeric\n";
               ofs<<"@attribute rightEyebrowAverageY numeric\n";
               ofs<<"@attribute rightEyebrowAverageZ numeric\n";
               ofs<<"@attribute noseAverageX numeric\n";
               ofs<<"@attribute noseAverageY numeric\n";
               ofs<<"@attribute noseAverageZ numeric\n";
               ofs<<"@attribute mouthAverageX numeric\n";
               ofs<<"@attribute mouthAverageY numeric\n";
               ofs<<"@attribute mouthAverageZ numeric\n";
               ofs<<"@attribute leftEyeRightEyeEuclidean numeric\n";
               ofs<<"@attribute leftEyeMouthEuclidean numeric\n";
               ofs<<"@attribute rightEyeMouthEuclidean numeric\n";
               ofs<<"@attribute faceEuclidean numeric\n";
               i = i+250;
            }
            if(header[i].find("@attribute")==0 || header[i].find("@data")==0 || header[i].empty()==1)
                ofs << header[i] << "\n";
        }
        int size2 = features.size();
        int au=0;
        for(int j=0; j<size2;j++)
        {
            ofs<<face<<","<<face<<","<<face<< ","<<lefteye<<","<<lefteye<<","<<lefteye<< ","<<righteye<<","<<righteye<<","<<righteye<< ","<<lefteyebrow<<","<<lefteyebrow<<","<<lefteyebrow<< ","<<righteyebrow<<","<<righteyebrow<<","<<righteyebrow<< ","<<nose<<","<<nose<<","<<nose<< ","<<mouth<<","<<mouth<<","<<mouth<<","<<euc1<<","<<euc2<<","<<euc3<< ","<<features[j]<< ",";
            for(int k=0;k<43;k++)
            {
               ofs << AUs[au]<<",";
               au++;
            }
            ofs<<expr[j] << "\n" ;
        }

    }
    else
    {
        int sizeh = header.size();
        for(int i=0;i<sizeh;i++)
        {
            ofs << header[i] << "\n";
        }
        int k=0, au=0;
        int size2 = coordinates.size();
        for(int j=0; j<size2;j++)
        {
            ofs<< coordinates[j].x << "," << coordinates[j].y << "," << coordinates[j].z << ",";
            if((j+1)%sets==0)
            {
                for(int k=0;k<43;k++)
                {
                  ofs << AUs[au]<<",";
                  au++;
                }
                ofs << expr[k] << "\n" ;
                k++;
            }
        }
    }
}

};


#endif // PREPROCESS_HPP_INCLUDED
