// Authors      :                       Ahmed Ehab Salah                                     |                          Youssef Saleh Elhelw                                 |          Mostafa tarek hassanin
// IDs          :                          20230011                                          |                                20230499                                       |                20230402
// filters      :Graysacale--Merge--Darken and lighten--Detect imgae edges--Infrared--violet |  Invert--Rotate--Frame--Blur--sunny filter--oil Painting--Water drop          | Black and white--Flip--Crop--Resizing--skew--light blue--Old TV        
// Version      :                                                                                                     1
// Email        :                      eltohfa01@gmail.com                                   |                        youssefelhelwai@gmail.com                              |            seso63412@gmail.com
//repo link     :                                                                                             https://github.com/Ahmed-eltohfa/photokoshk
#include <iostream>
#include <cmath>
#include "Image_Class.h"
#include <stdio.h>
#include <string>
#include <random>
#include <ctime>
using namespace std;

void saveImg(Image sora)
{
    string name;
point:
    cout << "enter the saving name with the RIGHT extention to save the image: ";
    cin >> name;
    try
    {
        sora.saveImage(name);
    }
    catch (const std::exception &e)
    {
        cout << "Error: invalid extention\n";
        goto point;
    }
}

void grayScaling(string filename, Image &sora)
{
    Image image(filename);
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k)
            {
                avg += image(i, j, k);
            }
            avg /= 3;
            for (int k = 0; k < 3; ++k)
            {
                image(i, j, k) = avg;
            }
        }
    }
    sora = image;
}

void darken(string filename, Image &sora)
{
    Image image(filename);
    int prcntg;
    cout << "Enter the percentage to the darkeness from 1 to 100: ";
    cin >> prcntg;

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {

            for (int k = 0; k < 3; ++k)
            {
                image(i, j, k) -= image(i, j, k) * prcntg / 100;
            }
        }
    }
    sora = image;
}

void lighten(string filename, Image &sora)
{
    Image image(filename);
    int prcntg;
    cout << "Enter the percentage to the darkeness from 1 to 100: ";
    cin >> prcntg;
    prcntg /= 20;
    while (prcntg--)
    {
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    if (image(i, j, k) + 20 < 255)
                    {
                        image(i, j, k) += 20;
                    }
                }
            }
        }
    }
    sora = image;
}

void blackandwhite(string filename, Image &sora)
{
    Image image(filename);

    // for loop that make the image blackandwhite
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0;
            // for loop that sum every pixels three colors
            for (int k = 0; k < 3; ++k)
            {
                avg += image(i, j, k);
            }
            avg /= 3; // Calculate average
            for (int k = 0; k < 3; ++k)
            {
                if (avg >= 128)
                {
                    // if sum pf every pixels three colors > 128 make the pixel white
                    image(i, j, k) = 255;
                }
                else
                {
                    image(i, j, k) = 0;
                    // if sum pf every pixels three colors > 128 make the pixel black
                }
            }
        }
    }
    sora = image;
}

void flipped(string filename, Image &sora)
{
    // take char from user and make sure that he choose valid
    string x;
    cout << "which flip do u want\nA)Vetical flip\nB)Horizontal flip\n";
    getline(cin, x);
    //cin.ignore();
    while ((x != "a") && (x != "b") && (x != "A") && (x != "B"))
    {
        cout << "\nplease enter valid char\nwhich flip do u want\nA)vetical flip\nB)Horizontal flip\n";
        getline(cin, x);
    }

    Image image(filename);

    // image2 is a white copy photo from the orignal that we will pass pixel pixel from orignal to image2
    Image image2(image.width, image.height);
    for (unsigned int i = 0; i < image2.width; ++i)
    {
        for (unsigned int j = 0; j < image2.height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                image2(i, j, k) = 255;
            }
        }
    }
    // for loop that flip every pixel then add it to image to
    for (unsigned int i = 0; i < image.width; ++i)
    {
        for (unsigned int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                int temp;
                if (x == "a" || x == "A")
                {
                    // if temp = i that flip vertical
                    temp = i;
                }
                else
                {
                    // if temp = i that flip horizontal
                    temp = image.width - i - 1;
                }
                // add every  flipped pixel from orignal image to image2
                image2(i, j, k) = image(temp, image.height - j - 1, k);
            }
        }
    }
    sora = image2;
}

void ResizingImages(string filename, Image &sora, int newWidth = 0, int newHeight = 0)
{
    Image image(filename);
    string choice;
    if (newWidth == 0 && newHeight == 0)
    {
        // take choice from user to Enter new dimensions or Enter ratio of reduction/increase
        cout << "Choose resizing option:\nA) Enter new dimensions\nB) Enter ratio of reduction/increase\nEnter your choice: " << endl;
        getline(cin, choice);

        // make sure that choice valid
        while (choice != "A" && choice != "a" && choice != "B" && choice != "b")
        {
            cout << "\nPls enter valid option\nA) Enter new dimensions\nB) Enter ratio of reduction/increase\nEnter your choice:  " << endl;
            getline(cin, choice);
        }
    }
    else
    {
        choice = "a";
    }

    // if choice = a user Enter new dimensions else user Enter ratio of reduction/increase
    if (choice == "A" || choice == "a")
    {

        // define and take new width and height
        if (newWidth == 0 && newHeight == 0)
        {
            // int newWidth, newHeight;
            cout << "Enter new width and new height: ";
            cin >> newWidth >> newHeight;
        }

        // make new photo that have the new dimensions
        Image resizedImage(newWidth, newHeight);

        // for loop that edit and take every pixel to new photo
        for (int y = 0; y < newHeight; y++)
        {
            for (int x = 0; x < newWidth; x++)
            {
                int srcX = static_cast<int>(x * static_cast<float>(image.width) / newWidth);
                int srcY = static_cast<int>(y * static_cast<float>(image.height) / newHeight);

                // change the dimensions and doesnot change the color
                for (int c = 0; c < image.channels; c++)
                {
                    resizedImage(x, y, c) = image(srcX, srcY, c);
                }
            }
        }

        sora = resizedImage;
    }
    else
    {

        // take ratio of reduction/increase
        float ratio;
        cout << "Enter the ratio of reduction/increase: ";
        cin >> ratio;

        // set new Width and Height
        int newWidth = static_cast<int>(image.width * ratio);
        int newHeight = static_cast<int>(image.height * ratio);

        // make new photo that have the new dimensions
        Image resizedImage(newWidth, newHeight);

        // for loop that edit and take every pixel to new photo
        for (int y = 0; y < newHeight; y++)
        {
            for (int x = 0; x < newWidth; x++)
            {
                int srcX = static_cast<int>(x / ratio);
                int srcY = static_cast<int>(y / ratio);

                // change the dimensions and doesnot change the color
                for (int c = 0; c < image.channels; c++)
                {
                    resizedImage(x, y, c) = image(srcX, srcY, c);
                }
            }
        }
        sora = resizedImage;
    }
}

void merge(string fileName, Image &sora)
{
    string temp = fileName;
    Image img1(fileName);
re:
    cout << "enter the second image to merge: ";
    cin >> fileName;
    try
    {
        Image test;
        test.loadNewImage(fileName);
    }
    catch (const std::exception &e)
    {
        cout << "Error: unvalid image name... Please write right image name\n";
        goto re;
    }
    Image img2(fileName);

    string ch;
    cout << "A)Risize the small image and merge\nB)Merge the commaon area\n";
    cin.ignore();
    getline(cin, ch);
    cout << "\n";
    ch[0] = tolower(ch[0]);
    string validChoice = "ab";
    while (!(validChoice.find(ch) < validChoice.length()) || (ch.length() != 1))
    {
        cout << "Please insert a valid char:\n";
        getline(cin, ch);
        ch[0] = tolower(ch[0]);
    }

    if (ch == "b")
    {
        /* code */
        int minW, minH;
        minW = min(img1.width, img2.width);
        minH = min(img1.height, img2.height);
        Image merged(minW, minH);
        int s1, s2, s3, s4;
        s1 = img1.width - minW;
        s2 = img1.height - minH;
        s3 = img2.width - minW;
        s4 = img2.height - minH;
        for (int i = 0; i < merged.width; i++)
        {
            for (int j = 0; j < merged.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    merged(i, j, k) = (img1(i + s1, j + s2, k) + img2(i + s3, j + s4, k)) / 2;
                }
            }
        }
        sora = merged;
    }
    else
    {
        int maxW, maxH;
        maxW = max(img1.width, img2.width);
        maxH = max(img1.height, img2.height);
        ResizingImages(temp, img1, maxW, maxH);
        ResizingImages(fileName, img2, maxW, maxH);
        Image merged(maxW, maxH);
        for (int i = 0; i < merged.width; i++)
        {
            for (int j = 0; j < merged.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    merged(i, j, k) = (img1(i, j, k) + img2(i, j, k)) / 2;
                }
            }
        }
        sora = merged;
    }
}

void crop(string filename, Image &sora)
{
    int x, y;
    cout << "Enter x and y input as the starting point:\n ";
    cin >> x >> y;

    int w, h;
    cout << "Enter w and h as the dimensions of the area to cut:\n ";
    cin >> w >> h;

    Image image(filename);

    Image image2(w, h); // Create a new image to store the cropped region

    for (int i = 0; i < w; ++i)
    {
        for (int j = 0; j < h; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                // Copy pixel values from the original image to the cropped image
                image2(i, j, k) = image(x + i, y + j, k);
            }
        }
    }
    sora = image2;
}

void edges(string fileName, Image &sora)
{
    Image img;
    blackandwhite(fileName, img);

    int cnt = 0;
    for (int i = 1; i < img.width - 1; ++i)
    {
        for (int j = 1; j < img.height - 1; ++j)
        {
            if (img(i, j, 0) < 128)
            {
                int cnt = 0;
                if (img(i - 1, j, 0) < 128)
                {
                    cnt++;
                }
                if (img(i, j + 1, 0) < 128)
                {
                    cnt++;
                }
                if (img(i + 1, j, 0) < 128)
                {
                    cnt++;
                }
                if (img(i, j - 1, 0) < 128)
                {
                    cnt++;
                }
                if (cnt == 4)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        img(i, j, 1) = 255;
                    }
                }
            }
        }
    }
    for (int i = 0; i < img.width; ++i)
    {
        for (int j = 0; j < img.height; ++j)
        {
            if (img(i, j, 1) > 150)
            {
                img(i, j, 0) = 255;
                img(i, j, 2) = 255;
            }
        }
    }
    sora = img;
}

void invert(string filename, Image &sora)
{
    Image image(filename);
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
    sora = image;
}

void red(string fileName, Image &sora)
{
    Image img(fileName);
    grayScaling(fileName, img);
    invert(fileName, img);
    for (int i = 0; i < img.width; ++i)
    {
        for (int j = 0; j < img.height; ++j)
        {
            img(i, j, 0) = 255;
        }
    }
    sora = img;
}

void blur(string filename, Image &sora)
{
    Image image(filename);
    int n;
    cout << "\nenter the level of blur from 1 to 10: ";
    cin >> n;
    int level = 1;
    if (n < 0 || n > 10)
    {
        cout << "different level Please\n";
        cin >> n;
    }
    while (level <= n)
    {
        for (int i = 1; i < image.width - 1; i += 2)
        {
            for (int j = 1; j < image.height - 1; j += 2)
            {
                for (int k = 0; k < 3; k++)
                {
                    int avg = (image(i - 1, j, k) + image(i + 1, j, k) + image(i, j - 1, k) + image(i, j + 1, k) + image(i - 1, j - 1, k) + image(i + 1, j + 1, k) + image(i - 1, j + 1, k) + image(i + 1, j - 1, k) + image(i, j, k) * 2) / 10;
                    image(i - 1, j, k) = avg;
                    image(i + 1, j, k) = avg;
                    image(i, j - 1, k) = avg;
                    image(i, j + 1, k) = avg;
                    image(i - 1, j - 1, k) = avg;
                    image(i + 1, j + 1, k) = avg;
                    image(i - 1, j + 1, k) = avg;
                    image(i + 1, j - 1, k) = avg;
                    image(i, j, k) = avg;
                }
            }
        }
        level++;
    }
    sora = image;
}

void frame_filter(string filename, Image &sora)
{
    cout << "\nwhice frame do you want\nA)white frame\nB)Zebra frame\n";
    string charr;
    getline(cin, charr);
    while (charr.length() != 1)
    {
        cout << "Please just insert one char\n";
        getline(cin, charr);
    }
    charr = toupper(charr[0]);
    while (charr != "A" && charr != "B")
    {
        cout << "Please just insert a valid char('A','B')\n";
        getline(cin, charr);
        charr = toupper(charr[0]);
    }
    Image image(filename);
    if (charr == "A")
    {
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                if (i <= 20 || i >= image.width - 21 || j <= 20 || j >= image.height - 21)
                {
                    for (int k = 0; k < 3; ++k)
                    {
                        image(i, j, k) = 255;
                    }
                }
            }
        }
        sora = image;
    }
    else if (charr == "B")
    {
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                if (i <= 20 || i >= image.width - 21 || j <= 20 || j >= image.height - 21)
                {
                    for (int k = 0; k < 3; ++k)
                    {
                        image(i, j, k) = 255;
                    }
                }
                if (i == 0 || i == 5 || i == 10 || i == image.width - 1 || i == image.width - 6 || i == image.width - 11 || j == 0 || j == 5 || j == 10 || j == image.height - 1 || j == image.height - 6 || j == image.height - 11)
                {
                    for (int k = 0; k < 3; ++k)
                    {
                        image(i, j, k) = 0;
                    }
                }
            }
        }
        sora = image;
    }
}

void rotate(string filename, Image &sora)
{
    cout << "A)Rotate 90\nB)Rotate 180\nC)Rotate 270\n";
    string charr;
    getline(cin, charr);
    while (charr.length() != 1)
    {
        cout << "Please just insert one char\n";
        getline(cin, charr);
    }
    charr = toupper(charr[0]);
    while (charr != "A" && charr != "B" && charr != "C")
    {
        cout << "Please just insert a valid char('A','B','C')\n";
        getline(cin, charr);
    }
    if (charr == "A")
    {
        Image image(filename);
        Image image2(image.height, image.width);
        for (int i = 0; i < image.height; ++i)
        {
            for (int j = 0; j < image.width; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    image2(i, j, k) = 255;
                }
            }
        }
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                // for loop that sum every pixels three colors
                for (int k = 0; k < 3; ++k)
                {
                    image2(image.height - j - 1, i, k) = image(i, j, k);
                }
            }
        }
        sora = image2;
    }
    else if (charr == "B")
    {
        Image image(filename);
        Image image2(filename);
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    image2(i, j, k) = 255;
                }
            }
        }
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                // for loop that sum every pixels three colors
                for (int k = 0; k < 3; ++k)
                {
                    image2(image.width - i - 1, image.height - j - 1, k) = image(i, j, k);
                }
            }
        }
        sora = image2;
    }
    else
    {
        Image image(filename);
        Image image2(image.height, image.width);
        for (int i = 0; i < image.height; ++i)
        {
            for (int j = 0; j < image.width; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    image2(i, j, k) = 255;
                }
            }
        }
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                // for loop that sum every pixels three colors
                for (int k = 0; k < 3; ++k)
                {
                    image2(image.height - j - 1, image.width - i - 1, k) = image(i, j, k);
                }
            }
        }
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                // for loop that sum every pixels three colors
                for (int k = 0; k < 3; ++k)
                {
                    image2(j, image.width - i - 1, k) = image(i, j, k);
                }
            }
        }
        sora = image2;
    }
}

void SunnyImage(string filename, Image &sora)
{
    Image image(filename);
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (k == 2)
                {
                    if (image(i, j, k) > 50)
                    {
                        image(i, j, k) -= 50;
                    }
                }
            }
        }
    }
    sora = image;
}

void violetImg(string fileName, Image &sora)
{
    Image image(fileName);
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (k == 1)
                {
                    if (image(i, j, k) > 50)
                    {
                        image(i, j, k) -= 50;
                    }
                }
            }
        }
    }
    sora = image;
}

void oilPainting(string fileName,Image& sora) {
    Image image(fileName);
    cout<<"Enter the radius\n";
    int radius;cin>>radius;
    cout<<"Enter the IntensityLevels\n";
    int intensityLevels;cin>>intensityLevels;
    // Create temporary arrays to store counts and sums for each intensity bin
    int intensityCount[intensityLevels] = {0};
    int averageR[intensityLevels] = {0};
    int averageG[intensityLevels] = {0};
    int averageB[intensityLevels] = {0};

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            // Reset the intensity count and sums for each pixel
            memset(intensityCount, 0, sizeof(intensityCount));
            memset(averageR, 0, sizeof(averageR));
            memset(averageG, 0, sizeof(averageG));
            memset(averageB, 0, sizeof(averageB));

            // Iterate through the neighborhood of the current pixel
            for (int dy = -radius; dy <= radius; ++dy) {
                for (int dx = -radius; dx <= radius; ++dx) {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && ny >= 0 && nx < image.width && ny < image.height) {
                        // Get the color values of the neighbor pixel
                        int r = image(nx,ny,0);
                        int g = image(nx, ny,1);
                        int b = image(nx, ny,2);

                        // Calculate the intensity of the neighbor pixel
                        int curIntensity = ((r + g + b) / 3) * intensityLevels / 255;

                        // Increment the count and accumulate color values for the corresponding intensity bin
                        intensityCount[curIntensity]++;
                        averageR[curIntensity] += r;
                        averageG[curIntensity] += g;
                        averageB[curIntensity] += b;
                    }
                }
            }

            // Find the intensity bin with the highest count (dominant intensity)
            int maxIndex = 0;
            int curMax = intensityCount[0];
            for (int i = 1; i < intensityLevels; ++i) {
                if (intensityCount[i] > curMax) {
                    curMax = intensityCount[i];
                    maxIndex = i;
                }
            }

            // Calculate the final color of the pixel using the dominant intensity level
            int finalR = averageR[maxIndex] / curMax;
            int finalG = averageG[maxIndex] / curMax;
            int finalB = averageB[maxIndex] / curMax;

            // Update the color of the current pixel in the oil painting image
            for(int k=0;k<3;k++){
                if(k==0){
                    image(x,y,k)=finalR;
                }else if(k==1){
                    image(x,y,k)=finalG;
                }else{
                    image(x,y,k)=finalB;
                }
            }
        }
    }
    sora=image;
} 


void light_blue(string fileName,Image& sora) {
    Image image(fileName);
    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            // Get the pixel at (x, y)
            unsigned char& red = image(x, y, 0);
            unsigned char& green = image(x, y, 1);
            unsigned char& blue = image(x, y, 2);
            
            // Increase the blue channel value
            blue = (blue > 200) ? 255 : blue + 55;
        }
    }
    sora = image;
}


void skew_filter(string filename, Image &sora) {
    // Load the input image
    Image inputImage(filename);

    // Get the width and height of the image
    int width = inputImage.width;
    int height = inputImage.height;

    // Prompt the user to enter the degree of skewness
    int degree;
    cout << "Enter the degree of skewness: ";
    cin >> degree;

    // Calculate the skew factor
    double skewFactor = tan((90-degree) * M_PI / 180.0);

    // Create a new image with increased width for skew effect
    int skewedWidth = width + static_cast<int>(height * skewFactor);
    Image skewedImage(skewedWidth, height);

    // Apply skew effect to the new image
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < skewedWidth; x++) {
            // Calculate the corresponding position in the original image
            int sourceX = x - static_cast<int>((height - y - 1) * skewFactor);

            // Check if the calculated position is within the bounds of the original image
            if (sourceX >= 0 && sourceX < width) {
                // Get the pixel value from the original image at the calculated position
                unsigned char red = inputImage(sourceX, y, 0);
                unsigned char green = inputImage(sourceX, y, 1);
                unsigned char blue = inputImage(sourceX, y, 2);

                // Assign the pixel value to the current pixel in the new image
                skewedImage(x, y, 0) = red;
                skewedImage(x, y, 1) = green;
                skewedImage(x, y, 2) = blue;
            }
        }
    }
    sora = skewedImage;
}
double angleW(int x, int y, int centerX, int centerY, double factor) {
    int distanceX = x - centerX;
    int distanceY = y - centerY;
    double distance = sqrt(pow(distanceX,2) +pow(distanceY,2));
    double angle = atan2(distanceX,distanceY);// arc tan :)
    double newAngle = angle + factor * distance;
    return newAngle;
}
void water_drop(string fileName,Image &sora){
    Image image(fileName);
    int centerX = image.width / 2;
    int centerY = image.height / 2;
    double factor = 0.09;
    
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            double angle = angleW(j, i, centerX, centerY, factor);
            int distanceX = j - centerX;
            int distanceY = i - centerY;
            double distance = sqrt(pow(distanceX,2) +pow(distanceY,2));
            double radius = distance;
            double xTwirled = centerX + radius * cos(angle);
            double yTwirled = centerY + radius * sin(angle);
            if (xTwirled >= 0 && xTwirled < image.width && yTwirled >= 0 && yTwirled < image.height) {
                for(int k=0;k<3;k++){
                    image(j,i,k)=image(xTwirled,yTwirled,k);
                }
            }
        }
    }
    sora=image;
}
void old_TV(string filename, Image &sora) {
    Image image(filename);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int randomNumber = rand() % 11;
            if(randomNumber < 1){
                for (int k = 0; k < 3; ++k) {
                image(i, j, k)=180;
                }
            }
        }
    }
    sora = image;
}
int main()
{
    cout << "\nWelcome to our program **PhotoKoshk**\n";

    while (true)
    {
        // ================= Check on the fileName ================= //
        string fileName;
        Image currentImg;
        while (true)
        {
            cout << "Enter the image name you want to apply the filter on:\n";
            cin >> fileName;
            cin.ignore();
            Image test;
            try
            {
                test.loadNewImage(fileName);
                break;
            }
            catch (const std::exception &e)
            {
                cout << "Error: unvalid image name... Please write right image name\n";
            }
        }
        // ===================== choose upply which func ==================== //
        while (true)
        {
            // getting started and choosing filter //
            string choice;
            cout << "Choose one of these filters:\nA)grayScaling\nB)darken\nC)lighten\nD)black and white\nE)Flipped\nF)Merge two pictures\nG)Crop\nH)Get edges\nI)Resizing Image\nJ)Blur Image\nK)frame image\nL)Rotate Image\nM)Invert Image\nN)Infrared filter\nO)Sunny filter\nP)Violet filter\nQ)Oil Painting\nR)light_blue\nS)Skew Filter\nT)Water drop\nU)Old TV\n";
            getline(cin, choice);
            cout << "\n";
            choice[0] = tolower(choice[0]);
            string validChoice = "abcdefghijklmnopqrstu";
            while (!(validChoice.find(choice) < validChoice.length()) || (choice.length() != 1))
            {
                cout << "Please insert a valid char:\n";
                getline(cin, choice);
                choice[0] = tolower(choice[0]);
            }

            if (choice == "a")
            {
                grayScaling(fileName, currentImg);
            }
            else if (choice == "b")
            {
                darken(fileName, currentImg);
            }
            else if (choice == "c")
            {
                lighten(fileName, currentImg);
            }
            else if (choice == "d")
            {
                blackandwhite(fileName, currentImg);
            }
            else if (choice == "e")
            {
                flipped(fileName, currentImg);
            }
            else if (choice == "f")
            {
                merge(fileName, currentImg);
            }
            else if (choice == "g")
            {
                crop(fileName, currentImg);
            }
            else if (choice == "h")
            {
                edges(fileName, currentImg);
            }
            else if (choice == "i")
            {
                ResizingImages(fileName, currentImg);
            }
            else if (choice == "j")
            {
                blur(fileName, currentImg);
            }
            else if (choice == "k")
            {
                frame_filter(fileName, currentImg);
            }
            else if (choice == "l")
            {
                rotate(fileName, currentImg);
            }
            else if (choice == "m")
            {
                invert(fileName, currentImg);
            }
            else if (choice == "n")
            {
                red(fileName, currentImg);
            }
            else if (choice == "o")
            {
                SunnyImage(fileName, currentImg);
            }
            else if (choice == "p")
            {
                violetImg(fileName, currentImg);
            }else if (choice == "q")
            {
                oilPainting(fileName,currentImg);
            }else if (choice == "r")
            {
                light_blue(fileName,currentImg);
            }else if (choice == "s")
            {
                skew_filter(fileName,currentImg);
            }else if (choice == "t")
            {
                water_drop(fileName,currentImg);
            }else if (choice == "u")
            {
                old_TV(fileName,currentImg);
            }
            cout << "Choose an option\nA)Save image\nB)Add more filters\nC)Skip\n";
            string choice2;
            getline(cin, choice2);
            
            choice2[0] = tolower(choice2[0]);
            while (choice2 != "a" && choice2 != "b" && choice2 != "c" || (choice2.length() != 1))
            {
                cout << "Please insert a valid char\n";
                // cin.ignore();
                getline(cin, choice2);
                choice2[0] = tolower(choice2[0]);
            }
            if (choice2 == "a")
            {
                saveImg(currentImg);
                remove("temp.jpg");
                break;
            }
            else if (choice2 == "b")
            {
                currentImg.saveImage("temp.jpg");
                fileName = "temp.jpg";
                continue;
            }
            else
            {
                remove("temp.jpg");
                break;
            }
        cin.ignore();
        }

        cout << "\nthank you for using our program\nA)Again\nB)Exit\n";
        string goOut;
        cin.ignore();
        getline(cin, goOut);
        cout << "\n";
        goOut[0] = tolower(goOut[0]);
        while (goOut != "a" && goOut != "b" || (goOut.length() != 1))
        {
            cout << "Please insert a valid char\nA)Again\nB)Exit\n";
            getline(cin, goOut);
            goOut[0] = tolower(goOut[0]);
        }
        if (goOut == "b")
        {
            break;
        }
    }
    cout << "Bye :)";
    return 0;
}