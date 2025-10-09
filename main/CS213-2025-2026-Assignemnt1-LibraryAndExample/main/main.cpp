#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <algorithm>
#include "Image_Class.h"

using namespace std;

enum enFilterType {
    Grayscale = 1,
    BlackAndWhite = 2,
    Invert = 3,
    Merge = 4,
    Flip = 5,
    Rotate = 6,
    DarkenAndLighten = 7,
    Crop = 8,
    Frame = 9,
    DetectEdges = 10,
    Resizing = 11,
    Blur = 12,
    PurbleFilter =13
};

enum enMergeType {
    ResizeLarger = 1,
    MergeCommon = 2
};

// For take th image in the main by karim
Image loadImageFromUser() {
    string filename;
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";    cin >> filename;
    return Image(filename);
}

// to save in the main by karim
void saveTheEdit(Image& img) {
    string output_filename;
    cout << "\nEnter the desired name for the new image (e.g., inverted_image.png).\n";
    cout << "Supported extensions are: .jpg, .jpeg, .png, .bmp, .tga: ";
    cin >> output_filename;
    img.saveImage(output_filename);

}

// this the 3rd filter by karim
void getInvertFilter(Image& img) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                img(i, j, k) = 255 - img(i, j, k);
            }
        }
    }

}

/* this list for taking the color of frame
this will work only when the Adding frame is called
by karim
*/
char getColorFromUser() {
    char color;
    cout << "\nPlease choose a color for the frame:\n";
    cout << "Enter 'W' for White\n";
    cout << "Enter 'B' for Black\n";
    cout << "Enter 'R' for Red\n";
    cout << "Enter 'G' for Green\n";
    cout << "Enter 'U' for Blue\n";
    cout << "Your choice: ";
    cin >> color;
    return color;

}

// this the 9th frame by karim
void getAddFrameFilter(Image& img) {
    char color = getColorFromUser();
    int frame_size = min(img.width, img.height) * 0.05;
    Image framed_pic(img.width + 2 * frame_size, img.height + 2 * frame_size);
    for (int i = 0; i < framed_pic.width; i++) {
        for (int j = 0; j < framed_pic.height; j++) {
            if (i < frame_size || j < frame_size || i >= frame_size + img.width || j >= frame_size + img.height) {
                if (color == 'W') {
                    framed_pic(j, i, 0) = 255;
                    framed_pic(j, i, 1) = 255;
                    framed_pic(j, i, 2) = 255;
                }
                else if (color == 'B') {
                    framed_pic(j, i, 0) = 0;
                    framed_pic(j, i, 1) = 0;
                    framed_pic(j, i, 2) = 0;
                }
                else if (color == 'R') {
                    framed_pic(j, i, 0) = 255;
                    framed_pic(j, i, 1) = 0;
                    framed_pic(j, i, 2) = 0;
                }
                else if (color == 'U') {
                    framed_pic(j, i, 0) = 0;
                    framed_pic(j, i, 1) = 0;
                    framed_pic(j, i, 2) = 255;
                }
                else if (color == 'G') {
                    framed_pic(j, i, 0) = 0;
                    framed_pic(j, i, 1) = 255;
                    framed_pic(j, i, 2) = 0;
                }
            }
            else {
                for (int k = 0; k < 3; k++) {
                    framed_pic(j, i, k) = img(j - frame_size, i - frame_size, k);
                }
            }
        }
    }
    img = framed_pic;
}

// this the 6th frame by karim
void getRotateFilter(Image& img) {
    int degree;
    cout << "\nPlease choose the degree of rotating\n";
    cout << "(90,180,270) : \n";
    cin >> degree;
    Image rotating_image(img.height, img.width);
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                if (degree == 90) rotating_image(j, i, k) = img(i, img.height - j - 1, k);
                else if (degree == 270) rotating_image(j, i, k) = img(img.width - i - 1, j, k);
                else if (degree == 180) rotating_image(j, i, k) = img(img.height - j - 1, img.width - i - 1, k);
            }
        }
    }
    img = rotating_image;
}

// this th 12th frame by karim
void getBlurFilter(Image& img, int passes) {
    if (passes == 0) return;
    Image temp = img;
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                if ((i == 0 && j == 0) || (i == img.width - 1 && j == 0) || (i == 0 && j == img.height - 1) || (i == img.width - 1 && j == img.height - 1)) {
                    temp(j, i, k) = (img(j, i, k) + img(j, i + 1, k) + img(j + 1, i, k) + img(j + 1, i + 1, k)) / 4;
                }
                else if ((j == 0 && i <= img.width - 2) || (j == img.height - 1 && i <= img.width - 2) || (j <= img.height - 2 && i == 0) || (j <= img.height - 2 && i == img.width - 1)) {
                    if (j == 0) temp(j, i, k) = (img(j, i, k) + img(j + 1, i + 1, k) + img(j + 1, i, k) + img(j, i + 1, k) + img(j, i - 1, k) + img(j + 1, i - 1, k)) / 6;
                    else if (j == img.height - 1) temp(j, i, k) = (img(j, i, k) + img(j - 1, i, k) + img(j, i + 1, k) + img(j, i - 1, k) + img(j - 1, i - 1, k) + img(j - 1, i + 1, k)) / 6;
                    else if (i == 0) temp(j, i, k) = (img(j, i, k) + img(j + 1, i, k) + img(j - 1, i, k) + img(j, i + 1, k) + img(j - 1, i + 1, k) + img(j + 1, i + 1, k)) / 6;
                    else if (i == img.width - 1) temp(j, i, k) = (img(j, i, k) + img(j + 1, i, k) + img(j - 1, i, k) + img(j, i - 1, k) + img(j - 1, i - 1, k) + img(j + 1, i - 1, k)) / 6;
                }
                else {
                    temp(j, i, k) = (img(j, i, k) + img(j + 1, i, k) + img(j - 1, i, k) + img(j, i + 1, k) + img(j, i - 1, k) + img(j - 1, i + 1, k) + img(j + 1, i + 1, k) + img(j - 1, i - 1, k) + img(j + 1, i - 1, k)) / 9;
                }
            }
        }
    }

    img = temp;
    getBlurFilter(img, passes - 1);
}
// the bonus filter by Karim to Phase#2
void getPurbleFilter(Image&img){
    Image purpled(img.height , img.width);
    double s;
    cout << "Enter The Strength Of The Filter (0 <= s <= 1) : ";
    cin >> s;
    while(true){

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max() , '\n');
            cout << "Invalid input! Please enter a number between 0 and 1.\n";
            continue;
        }
        if( s<0 || s>1 ) {
            cout << "Error: strength must be between 0 and 1.\n";
            continue;
        }
        break;
    }
    double purple[3] = {0.502, 0.0, 0.502};
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            for(int k = 0; k < 3; k++){
                double base = img(j, i , k) / 255.0;
                double c;
                if(base >= 0.5){
                    c = 1 - 2*(1-base)*(1-purple[k]);

                }
                else {
                    c = 2*base*purple[k];
                }
                purpled(j , i , k) = c * 255;
            }
        }

    }
    string outfile;
    cout << "Enter output filename (.jpg/.png/.bmp/.tga): ";
    cin>>outfile;
    purpled.saveImage(outfile);

}










// This function related to filter 4 (Merge) that merges the common part of both images
void getMergeCommon(Image img1, Image img2) {

    int maxWidth = max(img1.width, img2.width);
    int maxHeight = max(img1.height, img2.height);

    Image resized(maxWidth, maxHeight);

    for (int x = 0; x < maxWidth; ++x) {
        for (int y = 0; y < maxHeight; ++y) {
            for (int c = 0; c < 3; ++c) {
                int v1 = (x < img1.width && y < img1.height) ? img1(x, y, c) : 0;
                int v2 = (x < img2.width && y < img2.height) ? img2(x, y, c) : 0;
                resized(x, y, c) = static_cast<unsigned char>((v1 + v2) / 2);
            }
        }
    }
    string outFile;
    cout << "Enter output filename (.jpg/.png/.bmp/.tga): ";
    cin >> outFile;
    resized.saveImage(outFile);
}

// This function related to filter 4 (Merge) that resizes the smaller image to the biggest height and the biggest width and then merges
void getResizeImageFilter(Image img1, Image img2) {
    string outFile;

    // Determine target size = bigger width and height
    int targetW = max(img1.width, img2.width);
    int targetH = max(img1.height, img2.height);

    // Create final image
    Image merged(targetW, targetH);

    // Scale factors for each image
    double scaleX1 = static_cast<double>(img1.width) / targetW;
    double scaleY1 = static_cast<double>(img1.height) / targetH;

    double scaleX2 = static_cast<double>(img2.width) / targetW;
    double scaleY2 = static_cast<double>(img2.height) / targetH;

    // Merge loop with inline resize
    for (int x = 0; x < targetW; ++x) {
        for (int y = 0; y < targetH; ++y) {
            int sx1 = min(static_cast<int>(x * scaleX1), img1.width - 1);
            int sy1 = min(static_cast<int>(y * scaleY1), img1.height - 1);
            int sx2 = min(static_cast<int>(x * scaleX2), img2.width - 1);
            int sy2 = min(static_cast<int>(y * scaleY2), img2.height - 1);

            for (int c = 0; c < 3; ++c) {
                int v1 = img1(sx1, sy1, c);
                int v2 = img2(sx2, sy2, c);
                merged(x, y, c) = static_cast<unsigned char>((v1 + v2) / 2);
            }
        }
    }
    cout << "Enter output filename (.jpg/.png/.bmp/.tga): ";
    cin >> outFile;
    merged.saveImage(outFile);

    cout << "Merged image saved to " << outFile << '\n';
}

void getGrayFilter(Image& image1) {

    for (int i = 0; i < image1.width; ++i) {
        for (int j = 0; j < image1.height; ++j) {
            unsigned  int avg = 0; // Initialize average value

            for (int k = 0; k < 3; ++k) {
                avg += image1(i, j, k); // Accumulate pixel values
            }

            avg /= 3; // Calculate average

            // Set all channels to the average value
            image1(i, j, 0) = avg;
            image1(i, j, 1) = avg;
            image1(i, j, 2) = avg;
        }
    }

}

void showMergeType(Image img1, Image img2) {

    enMergeType type;
    int choice = 0;
    cout << "Choose Merge Type:\n";
    cout << "1. Resize the smaller image to the biggest height and the biggest width and then merge\n";
    cout << "2. Merge the common part of both images (the part that is in both images)\n";
    cin >> choice;

    switch ((enMergeType)choice) {
    case ResizeLarger:
        getResizeImageFilter(img1, img2);
        break;
    case MergeCommon:
        getMergeCommon(img1, img2);
        break;
    }
}

void getFlipFilter(Image& img, char direction) {
    Image temp(img.width, img.height);
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                if (direction == 'H') {
                    temp(i, j, k) = img(i, img.width - j, k);
                }
                else if (direction == 'V') {
                    temp(i, j, k) = img(img.height - i, j, k);
                }


            }
        }
    }
    img = temp;
}

void getBlackAndWhiteFilter(Image& img) {

    getGrayFilter(img);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                if (img(i, j, k) >= 128) {
                    img(i, j, k) = 255;
                }
                else if (img(i, j, k) < 128) {
                    img(i, j, k) = 0;
                }

            }
        }
    }
}

void getMergeFilter() {
    string file1, file2;
    cout << "Enter first image filename (with extension .jpg/.png/.bmp/.tga): ";
    cin >> file1;

    cout << "Enter second image filename (with extension .jpg/.png/.bmp/.tga): ";
    cin >> file2;

    Image img1(file1);
    Image img2(file2);
    // If sizes match we can merge directly
    if (img1.width == img2.width && img1.height == img2.height) {
        for (int i = 0; i < img1.width; ++i) {
            for (int j = 0; j < img1.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    img1(i, j, k) = (img1(i, j, k) + img2(i, j, k)) / 2;
                }
            }
        }
        cout << "Pls enter image name to store new image\n";
        cout << "and specify extension .jpg, .bmp, .png, .tga: ";
        string filename;
        cin >> filename;
        img1.saveImage(filename);
        cout << "Merged Successfully\n";
    }
    else {
        showMergeType(img1, img2);
    }

}

void getCropFilter(Image& img) {
    int x1, y1, x2, y2;
    cout << "\n Enter the points of crop x1 , y1 , x2 then y2: \n";
    cin >> x1 >> y1 >> x2 >> y2;
    Image crop(x2 - x1 + 1, y2 - y1 + 1);

    for (int i = 0; i < crop.width; i++) {
        for (int j = 0; j < crop.height; j++) {
            for (int k = 0; k < 3; k++) {
                crop(j, i, k) = img(j + y1, i + x1, k);
            }
        }
    }
    img = crop;
}
// Filter 7
void getDarkenAndLightenFilter(Image& img) {

    float factor;
    cout << "Enter factor to darken (<1) or to lighten (>1): ";
    cin >> factor;

    for (int x = 0; x < img.width; ++x) {
        for (int y = 0; y < img.height; ++y) {
            for (int c = 0; c < 3; ++c) {
                int v = static_cast<int>(img(x, y, c) * factor);
                // clamp to 0�255
                img(x, y, c) = static_cast<unsigned char>(min(255, max(0, v)));
            }
        }
    }
}

void getDetectEdgesFilter(Image& img, int threshold = 30) {
    int width = img.width;
    int height = img.height;

    // calculate the intensity difference between neighboring pixels

    for (int x = 0; x < width - 1; ++x) {
        for (int y = 0; y < height - 1; ++y) {

            // current pixel intensity
            float intensity = 0.299f * img(x, y, 0) +
                0.587f * img(x, y, 1) +
                0.114f * img(x, y, 2);

            // right neighbor
            float right = 0.299f * img(x + 1, y, 0) +
                0.587f * img(x + 1, y, 1) +
                0.114f * img(x + 1, y, 2);

            // bottom neighbor
            float down = 0.299f * img(x, y + 1, 0) +
                0.587f * img(x, y + 1, 1) +
                0.114f * img(x, y + 1, 2);

            float diff = fabs(intensity - right) + fabs(intensity - down); // fabs for absolute value of float

            unsigned char color = (diff > threshold) ? 0 : 255; // black = edge

            for (int c = 0; c < 3; ++c)
                img(x, y, c) = color;
        }
    }
}

void getResizeFilter(Image& img) {
    int newWidth, newHeight;
    cout << "Enter the new width: ";
    if (!(cin >> newWidth)) return;
    cout << "Enter the new height: ";
    if (!(cin >> newHeight)) return;

    if (newWidth <= 0 || newHeight <= 0) {
        cout << "invalid_numbers\n";
        return;
    }

    Image newImage(newWidth, newHeight);
    const int oldW = img.width;
    const int oldH = img.height;
    const int channels = 3;

    float scaleX = (newWidth > 1) ? float(oldW - 1) / float(newWidth - 1) : 0.0f;
    float scaleY = (newHeight > 1) ? float(oldH - 1) / float(newHeight - 1) : 0.0f;

    for (int j = 0; j < newHeight; ++j) {         // y (row)
        for (int i = 0; i < newWidth; ++i) {      // x (col)
            float src_x = i * scaleX;
            float src_y = j * scaleY;

            int x1 = clamp(int(floor(src_x)), 0, oldW - 1);
            int y1 = clamp(int(floor(src_y)), 0, oldH - 1);
            int x2 = min(x1 + 1, oldW - 1);
            int y2 = min(y1 + 1, oldH - 1);

            float x_diff = src_x - x1;
            float y_diff = src_y - y1;

            for (int k = 0; k < channels; ++k) {
                float pA = static_cast<float>(img(x1, y1, k));
                float pB = static_cast<float>(img(x2, y1, k));
                float pC = static_cast<float>(img(x1, y2, k));
                float pD = static_cast<float>(img(x2, y2, k));

                float value = pA * (1 - x_diff) * (1 - y_diff) +
                    pB * (x_diff) * (1 - y_diff) +
                    pC * (1 - x_diff) * (y_diff)+
                    pD * (x_diff) * (y_diff);

                int iv = int(round(value));
                iv = clamp(iv, 0, 255);
                newImage(i, j, k) = static_cast<unsigned char>(iv);
            }
        }
    } }

void getMainMenu() {
    cout << "\nEnter a number to choose a filter : \n";
    cout << "1.Grayscale Image \n";
    cout << "2.B&W Filter \n";
    cout << "3.Invert The Image \n";
    cout << "4.Merge Images \n";
    cout << "5.Flip Image \n";
    cout << "6.Rotate The Image With Specific Degree (90,180,270)\n";
    cout << "7.Darken and Lighten Image \n";
    cout << "8.Crop Image \n";
    cout << "9.Adding Frame \n";
    cout << "10.Detect Image Edges \n";
    cout << "11.Resizing Image \n";
    cout << "12.Blur Filter \n";
    cout << "13.Purple Filter \n";
}
void getFilterFromUser() {
    int choice;
    cin >> choice;

    Image img = loadImageFromUser();

    switch (enFilterType(choice))
    {
    case enFilterType::Grayscale:
        getGrayFilter(img);
        break;
    case enFilterType::BlackAndWhite:
        getBlackAndWhiteFilter(img);
        break;
    case enFilterType::Invert:
        getInvertFilter(img);
        break;
    case enFilterType::Merge:
        getMergeFilter();
        break;
    case enFilterType::Flip:
        getFlipFilter(img, 'H'); // 'H' for horizontal, 'V' for vertical
        break;
    case enFilterType::Rotate:
        getRotateFilter(img);
        break;
    case enFilterType::DarkenAndLighten:
        getDarkenAndLightenFilter(img);
        break;
    case enFilterType::Crop:
        getCropFilter(img);
        break;
    case enFilterType::Frame:
        getAddFrameFilter(img);
        break;
    case enFilterType::DetectEdges:
        getDetectEdgesFilter(img);
        break;
    case enFilterType::Resizing:
        getResizeFilter(img);
        break;
    case enFilterType::Blur:
        getBlurFilter(img, 12);
        break;
    case enFilterType::PurbleFilter:
        getPurbleFilter(img);
        break;
    default:
        cout << "Invalid filter choice!\n";
        break;
    }
    saveTheEdit(img); //  saves the final result
    cout << "\nImage processed and saved successfully!\n";
    cout << "THx for using our app (: , Come again ASAP\n";

}
void waitForKey() {
    cout << "\nPress Enter to return to the main menu...";
    cin.ignore(); // clears leftover img (like the '\n')
    cin.get();    // waits for user to press Enter
    system("cls"); // clear the console (Windows-specific)
}
int main() {
    while (true) {
        getMainMenu();
        getFilterFromUser();
        waitForKey();
    }
}

