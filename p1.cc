#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv){
  
    if (argc!=4) {
        printf("Usage: %s file1 threshold_value file2\n", argv[0]);
        return 0;
    }
    const string input_file(argv[1]);
    const string output_file(argv[3]);
    const string grey_value_threshold(argv[2]);
    const int threshold = stoi(grey_value_threshold); //threshold level of 140 works well for  two_objects.pmg image.
    const int white = 255;
    const int black = 0;

    Image an_image;
    if (!ReadImage(input_file, &an_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }

    //Loops through all pixels in image sets to white if above or equal theshhold otherwise black
    for(int i = 0; i < an_image.num_rows(); i++){
        for(int j = 0; j < an_image.num_columns(); j++){
            if(an_image.GetPixel(i, j) >= threshold){
                an_image.SetPixel(i, j, white);
            }
            else{
                an_image.SetPixel(i, j, black);
            }
        }
    } 

    if (!WriteImage(output_file, an_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }
}
