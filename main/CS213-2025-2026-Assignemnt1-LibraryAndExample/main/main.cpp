#include <iostream>
#include <string>
#include "Image_Class.h"

using namespace std;
void Revert(Image&img){
    for(int i = 0; i < img.width ; i++){
        for(int j = 0; j < img.height; j++){
            for(int k =0; k < 3; k++){
                img(i,j,k) = 255 -img(i,j,k);
            }
        }
    }

}
void AddingFrame(Image&img, char color){
    int frame_size = min(img.width,img.height) *0.05;
    Image framed_pic(img.width +2*frame_size , img.height +2*frame_size);
    for(int i = 0; i < framed_pic.width ; i++){
        for(int j = 0; j < framed_pic.height; j++){
                if(i < frame_size || j < frame_size || i >= frame_size + img.width || j >= frame_size + img.height){
                     if(color == 'W'){
                        framed_pic(j, i, 0) = 255;
                        framed_pic(j, i, 1) = 255;
                        framed_pic(j, i, 2) = 255;
                     }
                     else if (color == 'B'){
                        framed_pic(j, i, 0) = 0;
                        framed_pic(j, i, 1) = 0;
                        framed_pic(j, i, 2) = 0;
                     }

                    else if (color == 'R'){
                       framed_pic(j, i, 0) = 255;
                       framed_pic(j, i, 1) = 0;
                       framed_pic(j, i, 2) = 0;
                    }
                    else if (color == 'U'){
                       framed_pic(j, i, 0) = 0;
                       framed_pic(j, i, 1) = 0;
                       framed_pic(j, i, 2) = 255;
                    }
                    else if (color == 'G'){
                        framed_pic(j, i, 0) = 0;
                        framed_pic(j, i, 1) = 255;
                        framed_pic(j, i, 2) = 0;

                    }
                    }

                else {
                    for(int k =0; k <3; k++){
                        framed_pic(j,i,k) = img(j-frame_size , i-frame_size , k);
                    }
                }
        }
    }
    img = framed_pic;

}
void PrintTheList(){
    cout << "WELCOME IN BABY PS APP ENTER THE NAME OF NUM OF THE FILTER" << endl;
    cout << "1. \n";
    cout << "2. \n";
    cout << "3.Revert the image \n";
    cout << "4. \n";
    cout << "5. \n";
    cout << "6. \n";
    cout << "7. \n";
    cout << "8. \n";
    cout << "9.Adding frame \n";
    cout << "10. \n";
    cout << "11. \n";
    cout << "12. \n";


}

int main()
{
    string filename , output_filename;
    cout << "Enter your image name *with extension* : \n";
    cin >> filename;
    Image img(filename);
    PrintTheList();
    int num;
    cin >> num;
    if(num == 3){
        Revert(img);
    }
    else if (num == 9) {
        char color;
        cout << "\nPlease choose a color for the frame:\n";
        cout << "Enter 'W' for White\n";
        cout << "Enter 'B' for Black\n";
        cout << "Enter 'R' for Red\n";
        cout << "Enter 'G' for Green\n";
        cout << "Enter 'U' for Blue\n";
        cout << "Your choice: ";
        cin >> color;
        AddingFrame(img , color);
    }
    cout << "\nEnter the desired name for the new image (e.g., inverted_image.png).\n";
    cout << "Supported extensions are: .jpg, .jpeg, .png, .bmp, .tga: ";
    cin >> output_filename;
    img.saveImage(output_filename);
}
