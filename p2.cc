#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;
using namespace ComputerVisionProjects;

void mark(Image & an_image, int & cur_obj_num, vector<pair<int, int>> & equivalency_list, int i, int j);
void find_equivalency(Image & an_image, vector<pair<int, int>> equivalency_list, int i, int j);


int main(int argc, char **argv){
  
    if (argc!=3) {
        printf("Usage: %s file1 threshold_value file2\n", argv[0]);
        return 0;
    }
    const string input_file(argv[1]);
    const string output_file(argv[2]);
    const int white = 255;
    const int black = 0;

    Image an_image;
    if (!ReadImage(input_file, &an_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }

    vector<pair<int, int>> equivalency_list; 
    int cur_obj_num = 1;

    //first pass
    for(int i = 0; i < an_image.num_rows(); i++){
        for(int j = 0; j < an_image.num_columns(); j++){
            if(an_image.GetPixel(i,j) != 0){
                mark(an_image, cur_obj_num, equivalency_list, i, j);
            }
        }
    } 

    //second pass
    for(int i = 0; i < an_image.num_rows(); i++){
        for(int j = 0; j < an_image.num_columns(); j++){
            if(an_image.GetPixel(i,j) != 0){
                find_equivalency(an_image, equivalency_list, i, j);
            }
        }
    }


    //third pass to get number of objects
    unordered_set<int> objects;
    for(int i = 0; i < an_image.num_rows(); i++){
        for(int j = 0; j < an_image.num_columns(); j++){
            if(an_image.GetPixel(i ,j) != 0){
                objects.insert(an_image.GetPixel(i, j));
            }
        }
    }
    cout << objects.size() << endl;
    an_image.SetNumberGrayLevels(objects.size());

    if (!WriteImage(output_file, an_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }
}

void find_equivalency(Image & an_image, vector<pair<int, int>> equivalency_list, int i, int j){
    for(pair<int, int> item : equivalency_list){
        if(item.first == an_image.GetPixel(i, j)){
            if(item.first == item.second){
                return; //equivilency found
            }
            else{
                an_image.SetPixel(i, j, item.second);
                find_equivalency(an_image, equivalency_list, i, j);
                return;
            }
        }
    }
}

void mark(Image & an_image, int & cur_obj_num, vector<pair<int, int>> & equivalency_list, int i, int j){
    int left, above;
    if(i - 1 < 0){
        above = 0;
    }
    else{
        above = an_image.GetPixel(i-1, j);
    }
    if(j-1 < 0){
        left = 0;
    }
    else{
        left = an_image.GetPixel(i, j-1);
    }

    if(left == 0 && above == 0){
        an_image.SetPixel(i, j, cur_obj_num);
        equivalency_list.push_back(make_pair(cur_obj_num, cur_obj_num));
        cur_obj_num++;
    }
    else if(left == above){ //will only happen if both are not equal to 0.
        an_image.SetPixel(i, j, left);
    }
    else if(above == 0 && left != 0){
        an_image.SetPixel(i, j, left);
    }
    else if(left == 0 && above != 0){
        an_image.SetPixel(i, j, above);
    }
    //case conflict
    else if((left != above) && left != 0 && above != 0){
        an_image.SetPixel(i, j, min(left, above));
        for(pair<int,int> &item : equivalency_list){
            if(item.first == max(left, above)){
                item.second = min(left,above);
                break;
            }
        }
    }
    else{
        cerr << "ERROR: should not happen" << endl;
    }
}