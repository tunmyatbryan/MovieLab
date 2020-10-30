/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"
#include "ImageList.h"

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height);

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height);

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file);

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/* Print the command-line arguments usage of the program */
void PrintUsage();

int main(int argc, char *argv[])
{
        MOVIE *movie = NULL;
        IENTRY *e, *tempE;
        int x = 0, i = 0, Aaging = 0, Hhflip = 0, Eedge = 0, Ccrop = 0, Ffast = 0, Rreverse = 0, Wwatermark = 0, Sspotlight = 0, Zzoom = 0, StartCrop, EndCrop, FastForwardFactor = 0;
        char *fin = NULL;
        char *fout = NULL;
        char *NameWaterMark = NULL;
        unsigned int NumFrame;
        unsigned int width = 480;
        unsigned int height = 270;

        /* the while loop to check options in the command line */
        while (x < argc) {
                /* the input file name */
                if (strcmp(argv[x], "-i") == 0) {
                        if (x < argc - 1) {
                                fin = argv[x + 1];
                        } /*fi*/
                        else {
                                printf("Missing argument for the input file name!\n");
                                return 5;
                        } /*esle*/
                        x += 2;
                        continue;
                } /*fi*/

                /* the output file name */
                if (strcmp(argv[x], "-o") == 0) {
                        if (x < argc - 1) {
                                fout = argv[x + 1];
                        } /*fi*/
                        else {
                                printf("Missing argument for the output file name!\n");
                                return 5;
                        } /*esle*/
                        x += 2;
                        continue;
                } /*fi*/

                /* the help option */
                if (strcmp(argv[x], "-h") == 0) {
                        PrintUsage();
                        return 0;
                } /*fi*/


                /* to be implemented */

                /* Number of frames to read */
                if (strcmp(argv[x], "-f") == 0) {
                        if(x < argc - 1){
                                if(sscanf(argv[x+1], "%u", &NumFrame) == 1) {
                                        assert(NumFrame);
                                }
                                else {
                                        printf("Input frame number is not valid!\n");
                                        return 6;
                                }
                        }
                        else {
                                printf("Missing value for frame number!\n");
                        }
                                x += 2;
                                continue;
                } /*fi*/

                /* Set width and height */
                if (strcmp(argv[x], "-s") == 0) {
                        if(x < argc - 1){
                                if(sscanf(argv[x+1], "%ux%u", &width, &height) == 2) {
                                        assert(width);
                                        assert(height);
                                }
                                else {
                                        printf("Input Width & Height are not valid!\n");
                                        return 7;
                                }
                        }
                        else {
                                printf("Missing value for Width & Height!\n");
                        }
                                x += 2;
                                continue;
                } /*fi*/

                /* Set Watermark Image and activate watermark function*/
                if (strcmp(argv[x], "-watermark") == 0) {
                        if(x < argc - 1){
                                int WaterLength = strlen(argv[x+1]) + strlen(".ppm") + 1;
                                NameWaterMark = (char *)malloc(sizeof(char) * WaterLength);
                                strcpy(NameWaterMark, argv[x+1]);
                        }
                        else {
                                printf("Missing value for Watermark image!\n");
                        }
                                Wwatermark = 1;
                                x += 2;
                                continue;
                } /*fi*/

                /* Activate spotlight function */
                if (strcmp(argv[x], "-spotlight") == 0) {
                        if(NumFrame < 60 ){
                                printf("The frame numbers are not enough!\n");
                                return 5;
                        }
                        Sspotlight = 1;
                        x += 2;
                        continue;
                } /*fi*/

                /* Set crop start point and end point */
                if (strcmp(argv[x], "-crop") == 0) {
                        if(x < argc - 1){
                                if(sscanf(argv[x+1], "%d-%d", &StartCrop, &EndCrop) == 2) {
                                        assert(StartCrop);
                                        assert(EndCrop);
                                }
                                else {
                                        printf("Input Start & End points are not valid!\n");
                                        return 8;
                                }
                        }
                        else {
                                printf("Missing value for Start & End point!\n");
                        }
                                x += 2;
                                Ccrop = 1;
                                continue;
                }

                /* Fast Forward Factor to read and activate */
                if (strcmp(argv[x], "-fast") == 0) {
                        if(x < argc - 1){
                                if(sscanf(argv[x+1], "%d", &FastForwardFactor) == 1) {
                                        assert(FastForwardFactor);
                                }
                                else {
                                        printf("Input Fast Forward Factor is not valid!\n");
                                        return 9;
                                }
                        }
                        else {
                                printf("Missing value for Fast Forward Factor!\n");
                        }
                                x += 2;
                                Ffast = 1;
                                continue;
                } /*fi*/



                /* to activate Aaging function */
                if (strcmp(argv[x], "-aging") == 0) {
                        Aaging = 1;
                } /*fi*/

                /* to activate horizontal flip */
                if (strcmp(argv[x], "-hflip") == 0) {
                        Hhflip = 1;
                } /*fi*/

                /* to activate edge */
                if (strcmp(argv[x], "-edge") == 0) {
                        Eedge = 1;
                } /*fi*/

                /* to activate zoom */
                if (strcmp(argv[x], "-zoom") == 0) {
                        Zzoom = 1;
                } /*fi*/

                /* to activate crop */
                if (strcmp(argv[x], "-crop") == 0) {
                        Ccrop = 1;
                } /*fi*/

                /* to activate reverse */
                if (strcmp(argv[x], "-reverse") == 0) {
                        Rreverse = 1;
                } /*fi*/

                x++;
        } /*elihw*/

        if (fin == NULL) {
                printf("Missing argument for the input file name!\n");
                PrintUsage();
                return 5;
        }

        if (fout == NULL) {
                printf("Missing argument for the output file name!\n");
                PrintUsage();
                return 5;
        }

        /* to be implemented */

        if (NumFrame == 0){
                printf("Missing argumet for the frame number!\n");
                return 6;
        }

        if (width == 0 || height == 0){
                printf("Missing argument for Width & Height!\n");
                return 7;
        }

        movie = LoadMovie(fin, NumFrame, width, height);

        if (Aaging == 1){
                e = NULL;
                tempE = NULL;
                YUV2RGBMovie(movie);
                e = movie -> Frames -> First;
                for (i = 0; i < NumFrame; i++){
                        tempE = e -> Next;
                        e -> RGBImage = Aging(e -> RGBImage);
                        e = tempE;
                }
                RGB2YUVMovie(movie);
                printf("Operation Aging is done!\n");
        }

        if (Hhflip == 1){
                e = NULL;
                tempE = NULL;
                YUV2RGBMovie(movie);
                e = movie -> Frames -> First;
                for (i = 0; i < NumFrame; i++){
                        tempE = e -> Next;
                        e -> RGBImage = HFlip(e -> RGBImage);
                        e = tempE;
                }
                RGB2YUVMovie(movie);
                printf("Operation HFlip is done!\n");
        }

        if (Eedge == 1){
                e = NULL;
                tempE = NULL;
                YUV2RGBMovie(movie);
                e = movie -> Frames -> First;
                for (i = 0; i < NumFrame; i++){
                        tempE = e -> Next;
                        e -> RGBImage = Edge(e -> RGBImage);
                        e = tempE;
                }
                RGB2YUVMovie(movie);
                printf("Operation Edge is done!\n");
        }

        if (Zzoom == 1){
                e = NULL;
                tempE = NULL;
                int PerCount = 0;
                int PerCent = -2;
                YUV2RGBMovie(movie);
                e = movie -> Frames -> First;
                for (i = 0; i < NumFrame; i++){
                        if(PerCount == 0){
                                PerCent += 2;
                        }else{
                                PerCent -= 2;
                        }
                        tempE = e -> Next;
                        e -> RGBImage = Zoom(e -> RGBImage, PerCent);
                        e = tempE;

                        if(PerCent == 100){
                                PerCount = 1;
                        }
                        if(PerCent == 0){
                                PerCount = 0;
                        }
                }
                RGB2YUVMovie(movie);
                printf("Operation Zoom is done!\n");
        }

        if (Wwatermark == 1){
                e = NULL;
                tempE = NULL;
                unsigned int TopX, TopY;
                int FrameCount = 0;
                IMAGE *WaterMark = LoadImage(NameWaterMark);
                YUV2RGBMovie(movie);
                e = movie -> Frames -> First;
                for (i = 0; i < NumFrame; i++){
                        if(FrameCount == 0){
                                TopX = rand() % width;
                                TopY = rand() % height;
                        }
                        tempE = e -> Next;
                        e -> RGBImage = Watermark(e -> RGBImage, WaterMark, TopX, TopY);
                        e = tempE;
                        FrameCount ++;
                        if(FrameCount == 15){
                                FrameCount = 0;
                        }
                }
                RGB2YUVMovie(movie);
                printf("Operation watermark is done!\n");
        }

        if(Sspotlight == 1){
                e = NULL;
                tempE = NULL;
                int x = 20;
                double MaxRadius, Radius;
                Radius = ( ((width/2)*(width/2)) + ((height/2)*(height/2)));
                MaxRadius = sqrt(Radius);
                YUV2RGBMovie(movie);
                e = movie -> Frames -> First;
                for (i = 0; i < NumFrame; i++){
                        if( i >= 0 && i < 40){
                                Radius = MaxRadius * i/40;
                        }
                        else if(i >= NumFrame - 20 && i < NumFrame){
                                Radius = MaxRadius * x/20;
                                x--;
                        }
                        else{
                                Radius = MaxRadius;
                        }

                        tempE = e -> Next;
                        e -> RGBImage = Spotlight(e -> RGBImage, width/2, height/2, Radius);
                        e = tempE;
                }
                RGB2YUVMovie(movie);
                printf("Operation Spotlight is done!\n");
        }

        if(Ccrop == 1){
                CropImageList(movie -> Frames, StartCrop, EndCrop);
                printf("Operation Crop is done! New number of frames is %d.\n", movie -> Frames -> Length);
        }

        if(Rreverse == 1){
                ReverseImageList(movie -> Frames);
                printf("Operation Revrse is done.\n");
        }

        if(Ffast == 1){
                FastImageList(movie -> Frames, FastForwardFactor);
                printf("Operation Fast Forward is done! New number of frames is %d.\n", movie -> Frames -> Length);
        }

        SaveMovie(fout, movie);


        fin = NULL;
        fout = NULL;

        return 0;
}

void PrintUsage()
{
        printf("\nUsage: MovieLab -i <file> -o <file> -f <framenum> -s <WIDTHxHEIGHT> [options]\n"
               "Options:\n"
               "-aging                Activate the aging filter on every movie frame\n"
               "-hflip                Activate horizontal flip on every movie frame\n"
               "-edge                 Activate the edge filter on every movie frame\n"
               "-crop <start-end>     Crop the movie frames from <start> to <end>\n"
               "-fast <factor>        Fast forward the movie by <factor>\n"
               "-reverse              Reverse the frame order of the input movie\n"
               "-watermark <file>     Add a watermark from <file> to every movie frame\n"
               "-spotlight            Spotlight the fade in and fade out\n"
               "-zoom                 Zoom in and out the input movie\n"
               "-h                    Display this usage information\n"
              );
}

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height)
{
        FILE *file;
        unsigned int x, y;
        unsigned char c;
        YUVIMAGE* YUVimage;

        /* Check errors */
        assert(fname);
        assert(n >= 0);

        YUVimage = CreateYUVImage(width, height);
        if (YUVimage == NULL) {
                return NULL;
        }

        /* Open the input file */
        file = fopen(fname, "r");
        if (file == NULL) {
                DeleteYUVImage(YUVimage);
                return NULL;
        }

        /* Find the desired frame */
        fseek(file, 1.5 * n * width * height, SEEK_SET);

        for (y = 0; y < height; y++) {
                for (x = 0; x < width; x++) {
                        c = fgetc(file);
                        SetPixelY(YUVimage, x, y, c);
                } /*rof*/
        }

        for (y = 0; y < height; y += 2) {
                for (x = 0; x < width; x += 2) {
                        c = fgetc(file);
                        SetPixelU(YUVimage, x, y, c);
                        SetPixelU(YUVimage, x + 1, y, c);
                        SetPixelU(YUVimage, x, y + 1, c);
                        SetPixelU(YUVimage, x + 1, y + 1, c);
                }
        }

        for (y = 0; y < height; y += 2) {
                for (x = 0; x < width; x += 2) {
                        c = fgetc(file);
                        SetPixelV(YUVimage, x, y, c);
                        SetPixelV(YUVimage, x + 1, y, c);
                        SetPixelV(YUVimage, x, y + 1, c);
                        SetPixelV(YUVimage, x + 1, y + 1, c);
                }
        }

        /* Check errors */
        assert(ferror(file) == 0);


        /* Close the input file and return */
        fclose(file);
        file = NULL;
        return YUVimage;
}

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height)
{
        /* to be implemented */
        MOVIE *m = CreateMovie();
        ILIST *l = CreateImageList();

        int x;
        assert(m);
        assert(l);
        assert(fname);
        assert(frameNum >= 0);

        for(x = 0; x < frameNum; x++){
                AppendYUVImage(l, LoadOneFrame(fname, x, width, height));
        }
        m -> Frames = l;
        return m;
}

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{
        int count;
        FILE *file;
        IENTRY *curr;

        /* Open the output file */
        file = fopen(fname, "w");
        if (file == NULL) {
                return 1;
        }

        count = 0;
        curr = movie->Frames->First;
        while (curr != NULL) {

                SaveOneFrame(curr->YUVImage, fname, file);
                curr = curr->Next;
                count++;
        }

        fclose(file);
        file = NULL;

        printf("The movie file %s has been written successfully!\n", fname);
        printf("%d frames are written to the file %s in total.\n", count, fname);
        return 0;
}

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file)
{
        int x, y;
        for (y = 0; y < image->H; y++) {
                for (x = 0; x < image->W; x++) {
                        fputc(GetPixelY(image, x, y), file);
                }
        }

        for (y = 0; y < image->H; y += 2) {
                for (x = 0; x < image->W; x += 2) {
                        fputc(GetPixelU(image, x, y), file);
                }
        }

        for (y = 0; y < image->H; y += 2) {
                for (x = 0; x < image->W; x += 2) {
                        fputc(GetPixelV(image, x, y), file);
                }
        }
}

/* EOF */

