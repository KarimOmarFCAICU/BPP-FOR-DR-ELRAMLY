#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <algorithm>
#include "Image_Class.h"

using namespace std;

// For take th image in the main by karim
Image LoadImageFromUser(){
    string filename;
    cout << "Enter your image name *with extension* : \n";
    cin >> filename;
    return Image (filename);
}

// to save in the main by karim
void SaveTheEdit(Image&img){
    string output_filename;
    cout << "\nEnter the desired name for the new image (e.g., inverted_image.png).\n";
    cout << "Supported extensions are: .jpg, .jpeg, .png, .bmp, .tga: ";
    cin >> output_filename;
    img.saveImage(output_filename);

}

// this the 3rd filter by karim
void InvertTheImage(Image&img){
    for(int i = 0; i < img.width ; i++){
        for(int j = 0; j < img.height; j++){
            for(int k = 0; k < 3; k++){
                img(i,j,k) = 255 - img(i,j,k);
            }
        }
    }

}

/* this list for taking the color of frame
this will work only when the Adding frame is called
by karim
*/
char TakeFrameColorFromUser(){
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
void AddingFrame(Image&img){
    char color = TakeFrameColorFromUser();
    int frame_size = min(img.width,img.height) * 0.05;
    Image framed_pic(img.width + 2*frame_size, img.height + 2*frame_size);
    for(int i = 0; i < framed_pic.width; i++){
        for(int j = 0; j < framed_pic.height; j++){
            if(i < frame_size || j < frame_size || i >= frame_size + img.width || j >= frame_size + img.height){
                if(color == 'W'){
                    framed_pic(j,i,0) = 255;
                    framed_pic(j,i,1) = 255;
                    framed_pic(j,i,2) = 255;
                }
                else if(color == 'B'){
                    framed_pic(j,i,0) = 0;
                    framed_pic(j,i,1) = 0;
                    framed_pic(j,i,2) = 0;
                }
                else if(color == 'R'){
                    framed_pic(j,i,0) = 255;
                    framed_pic(j,i,1) = 0;
                    framed_pic(j,i,2) = 0;
                }
                else if(color == 'U'){
                    framed_pic(j,i,0) = 0;
                    framed_pic(j,i,1) = 0;
                    framed_pic(j,i,2) = 255;
                }
                else if(color == 'G'){
                    framed_pic(j,i,0) = 0;
                    framed_pic(j,i,1) = 255;
                    framed_pic(j,i,2) = 0;
                }
            }
            else{
                for(int k = 0; k < 3; k++){
                    framed_pic(j,i,k) = img(j-frame_size, i-frame_size, k);
                }
            }
        }
    }
    img = framed_pic;
}

// this the 6th frame by karim
void RotatingImage(Image&img){
    int degree;
    cout << "\nPlease choose the degree of rotating\n";
    cout << "(90,180,270) : \n";
    cin >> degree;
    Image rotating_image(img.height, img.width);
    for(int i = 0; i < img.width; i++){
        for(int j = 0; j < img.height; j++){
            for(int k = 0; k < 3; k++){
                if(degree == 90) rotating_image(j,i,k) = img(i, img.height-j-1, k);
                else if(degree == 270) rotating_image(j,i,k) = img(img.width-i-1, j, k);
                else if(degree == 180) rotating_image(j,i,k) = img(img.height-j-1, img.width-i-1, k);
            }
        }
    }
    img = rotating_image;
}

// this th 12th frame by karim
void ApplyBlurFilter(Image&img ,int passes){
    if(passes == 0) return;
    Image temp = img;
    for(int i = 0; i < img.width; i++){
        for(int j = 0; j < img.height; j++){
            for(int k = 0; k < 3; k++){
                if((i == 0 && j == 0) || (i == img.width-1 && j == 0) || (i == 0 && j == img.height-1) || (i == img.width-1 && j == img.height-1)){
                    temp(j,i,k) = (img(j,i,k) + img(j,i+1,k) + img(j+1,i,k) + img(j+1,i+1,k)) / 4;
                }
                else if((j == 0 && i <= img.width-2) || (j == img.height-1 && i <= img.width-2) || (j <= img.height-2 && i == 0) || (j <= img.height-2 && i == img.width-1)){
                    if(j == 0) temp(j,i,k) = (img(j,i,k) + img(j+1,i+1,k) + img(j+1,i,k) + img(j,i+1,k) + img(j,i-1,k) + img(j+1,i-1,k))/6;
                    else if(j == img.height-1) temp(j,i,k) = (img(j,i,k) + img(j-1,i,k) + img(j,i+1,k) + img(j,i-1,k) + img(j-1,i-1,k) + img(j-1,i+1,k))/6;
                    else if(i == 0) temp(j,i,k) = (img(j,i,k) + img(j+1,i,k) + img(j-1,i,k) + img(j,i+1,k) + img(j-1,i+1,k) + img(j+1,i+1,k))/6;
                    else if(i == img.width-1) temp(j,i,k) = (img(j,i,k) + img(j+1,i,k) + img(j-1,i,k) + img(j,i-1,k) + img(j-1,i-1,k) + img(j+1,i-1,k))/6;
                }
                else{
                    temp(j,i,k) = (img(j,i,k) + img(j+1,i,k) + img(j-1,i,k) + img(j,i+1,k) + img(j,i-1,k) + img(j-1,i+1,k) + img(j+1,i+1,k) + img(j-1,i-1,k) + img(j+1,i-1,k))/9;
                }
            }
        }
    }

    img = temp;
    ApplyBlurFilter(img, passes-1);
}



enum enMergeType {
	ResizeLarger = 1,
	MergeCommon = 2
};

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

void getGrayFilter() {
	string filename;
	cout << "Pls enter colored image name to turn to gray scale: ";
	cin >> filename;

	Image image1(filename);

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

	cout << "Pls enter image name to store new image\n";
	cout << "and specify extension .jpg, .bmp, .png, .tga: ";

	cin >> filename;
	if (image1.saveImage(filename)) {
		cout << "Gray scale image saved to " << filename << '\n';
	}
	else {
		cout << "Failed to save image to " << filename << '\n';
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
void Flipping(Image&img,char direction) {
    Image temp(img.width, img.height);
    for(int i = 0; i < img.width; i++) {
        for(int j = 0; j < img.height; j++) {
            for(int k = 0; k < 3; k++) {
                if(direction == 'H') {
                    temp(i,j,k) = img(i, img.width-j, k);
                }
                else if(direction == 'V') {
                    temp(i,j,k) = img(img.height-i, j, k);
                }


            }
		}
    }
    img = temp;
}

void BlackAndWhite(Image& img) {
    GrayFilter(img);
    for(int i = 0; i < img.width; i++){
        for(int j = 0; j < img.height; j++){
            for(int k = 0; k < 3; k++){
                if(img(i,j,k) >= 128){
                    img(i,j,k) = 255;
}
                else if(img(i,j,k) < 128){
                    img(i,j,k) = 0;
}

}
}
}

}

void getMergeFilter() {
	string file1, file2;
	cout << "Enter first image filename: ";
	cin >> file1;
	cout << "Enter second image filename: ";
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
void CroppingTheImage(Image& img) {
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
void getDarkenAndLightenFilter() {
	string filename;
	cout << "Pls enter colored image name to turn to darken or lighten image: ";
	cin >> filename;

	float factor;
	cout << "Enter factor to darken (<1) or to lighten (>1): ";
	cin >> factor;

	Image img(filename);

	for (int x = 0; x < img.width; ++x) {
		for (int y = 0; y < img.height; ++y) {
			for (int c = 0; c < 3; ++c) {
				int v = static_cast<int>(img(x, y, c) * factor);
				// clamp to 0–255
				img(x, y, c) = static_cast<unsigned char>(std::min(255, std::max(0, v)));
			}
		}
	}
	cout << "Pls enter image name to store new image\n";
	cout << "and specify extension .jpg, .bmp, .png, .tga: ";
	cin >> filename;
	img.saveImage(filename);
}
enum FilterType {
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
    Blur = 12
};
void PrintTheList() {
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

}
void ChooseTheFilter(int num){

}
int main(){
    Image img = LoadImageFromUser();
    PrintTheList();
    int num;
    cin >> num;
    switch (num)
    {
    case FilterType::Grayscale:
        getGrayFilter();
        break;
    case FilterType::BlackAndWhite:
        break;
    case FilterType::Invert:
        InvertTheImage(img);
        break;
    case FilterType::Merge:
        getMergeFilter();
        break;
    case FilterType::Flip:
        break;
    case FilterType::Rotate:
        RotatingImage(img);
        break;
    case FilterType::DarkenAndLighten:
        getDarkenAndLightenFilter();
        break;
    case FilterType::Crop:
        CroppingTheImage(img);
        break;
    case FilterType::Frame:
        AddingFrame(img);
        break;
    case FilterType::DetectEdges:

        break;
    case FilterType::Resizing:
        cout << "The Next Phase haahhah XD ><";
        break;
    case FilterType::Blur:
        ApplyBlurFilter(img,12);
        break;
    default:
        cout << "Invalid filter choice!\n";
        break;
    }

    SaveTheEdit(img); //  saves the final result
    cout << "\nImage processed and saved successfully!\n";
    cout << "THx for using our app (: , Come again ASAP\n";
}


