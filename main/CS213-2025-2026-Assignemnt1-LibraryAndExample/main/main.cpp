#include <iostream>
#include <string>
#include "Image_Class.h"

using namespace std;

int main()
{
    Image image;

    string image_filename = "arrow.jpg";

    bool loaded = image.loadNewImage(image_filename);

    if (loaded) {
        cout << "Image loaded successfully from: " << image_filename << endl;
        cout << "Image Dimensions: Width = " << image.width << ", Height = " << image.height << endl;
        cout << "Number of channels: " << image.channels << endl;
    } else {
        cout << "Program will now exit due to image loading failure." << endl;
        return 1;
    }

    if (image.width > 0 && image.height > 0) {
        unsigned char red = image.getPixel(0, 0, 0);
        unsigned char green = image.getPixel(0, 0, 1);
        unsigned char blue = image.getPixel(0, 0, 2);
        cout << "Pixel (0,0) - R: " << (int)red << ", G: " << (int)green << ", B: " << (int)blue << endl;

        image.setPixel(10, 10, 0, 255);
        image.setPixel(10, 10, 1, 0);
        image.setPixel(10, 10, 2, 0);
    }

    string output_filename = "output_test.jpg";
    bool saved = image.saveImage(output_filename);

    if (saved) {
        cout << "Image saved successfully as: " << output_filename << endl;
    } else {
        cout << "Failed to save image: " << output_filename << endl;
    }

    return 0;
}
