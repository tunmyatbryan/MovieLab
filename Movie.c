/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "Movie.h"
#include "Image.h"
#include "ImageList.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
        /* to be implemented */
        MOVIE *m;
        m = malloc(sizeof(MOVIE));

        if(!m){
                perror("Out of memory! Aborting...");
                exit(10);
        }
        m -> Frames = CreateImageList();
        return m;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
        /* to be implemented */
        assert(movie);
        DeleteImageList(movie -> Frames);
        free(movie);
        movie = NULL;
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
        /* to be implemented */
        int C, D, E, Y, U, V, R, G, B, x, y;
        IENTRY *curr, *temp;

        curr = movie -> Frames -> First;

        unsigned int WIDTH = curr -> YUVImage -> W;
        unsigned int HEIGHT = curr -> YUVImage -> H;

        while(curr){
                curr -> RGBImage = CreateImage(WIDTH, HEIGHT);
                temp = curr -> Next;

                for (y = 0; y < HEIGHT; y++){
                        for(x = 0; x < WIDTH; x++){
                                Y = GetPixelY(curr -> YUVImage, x, y);
                                U = GetPixelU(curr -> YUVImage, x, y);
                                V = GetPixelV(curr -> YUVImage, x, y);

                                C = Y - 16;
                                D = U - 128;
                                E = V - 128;
                                R = clip (( 298 * C + 409 * E + 128 ) >> 8);
                                G = clip (( 298 * C - 100 * D - 208 * E + 128) >> 8);
                                B = clip (( 298 * C + 516 * D + 128) >> 8);

                                SetPixelR(curr -> RGBImage, x, y, R);
                                SetPixelG(curr -> RGBImage, x, y, G);
                                SetPixelB(curr -> RGBImage, x, y, B);
                        }
                }
                DeleteYUVImage(curr -> YUVImage);
                curr -> YUVImage = NULL;
                curr = temp;
        }
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
        /* to be implemented */

        int Y, U, V, R, G, B, x, y;
        IENTRY *curr, *temp;

        curr = movie -> Frames -> First;

        unsigned int WIDTH = curr -> RGBImage -> W;
        unsigned int HEIGHT = curr -> RGBImage -> H;

        while(curr){
                curr -> YUVImage = CreateYUVImage(WIDTH, HEIGHT);
                temp = curr -> Next;

                for (y = 0; y < HEIGHT; y++){
                        for(x = 0; x < WIDTH; x++){
                                R = GetPixelR(curr -> RGBImage, x, y);
                                G = GetPixelG(curr -> RGBImage, x, y);
                                B = GetPixelB(curr -> RGBImage, x, y);

                                Y = clip(((66 * R + 129 * G + 25 * B + 128) >> 8) + 16);
                                U = clip(((-38 * R - 74 * G + 112 * B + 128) >> 8) + 128);
                                V = clip(((112 * R - 94 * G - 18 * B + 128) >> 8) + 128);

                                SetPixelY(curr -> YUVImage, x, y, Y);
                                SetPixelU(curr -> YUVImage, x, y, U);
                                SetPixelV(curr -> YUVImage, x, y, V);
                        }
                }
                DeleteImage(curr -> RGBImage);
                curr -> RGBImage = NULL;
                curr = temp;
        }
}

int clip(int x){
        if( x < 0){
                x = 0;
        }
        if( x > 255){
                x = 255;
        }
        return x;
}

/* EOF */

