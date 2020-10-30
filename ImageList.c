/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "ImageList.h"
#include "Image.h"

/* Create a new image list */
ILIST *CreateImageList(void)
{
        /* to be implemented */
        ILIST *L;
        L = malloc(sizeof(ILIST));
        if(!L){
                perror("Out of memory! Aborting...");
                exit(10);
        }
        L -> Length = 0;
        L -> First = NULL;
        L -> Last = NULL;
        return L;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
        /* to be implemented */
        IENTRY *e, *n;
        assert(list);
        e = list -> First;
        while(e){
                n = e -> Next;
                DeleteImageEntry(e);
                e = n;
        }
        free(list);
        list = NULL;
}

/* Create a new image entry */
IENTRY *CreateNewEntry(){
        IENTRY *e;
        e = malloc(sizeof(IENTRY));
        if(!e){
                perror("Out of memory! Aborting..");
                exit(10);
        }
        e -> List = NULL;
        e -> Next = NULL;
        e -> Prev = NULL;
        e -> RGBImage = NULL;
        e -> YUVImage = NULL;
        return e;
}

void DeleteImageEntry(IENTRY *e){
        assert(e);
        if(e -> YUVImage == NULL){
                DeleteImage(e -> RGBImage);
                e -> RGBImage = NULL;
        }
        else{
                DeleteYUVImage(e -> YUVImage);
                e -> YUVImage = NULL;
        }

        free(e);
        e = NULL;
}


/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
        /* to be implemented */
        IENTRY *e = NULL;
        assert(list);
        assert(RGBimage);
        e = CreateNewEntry();
        e -> RGBImage = RGBimage;
        if(list -> Last){
                e -> List = list;
                e -> Next = NULL;
                e -> Prev = list -> Last;
                list -> Last -> Next = e;
                list -> Last = e;
        }
        else{
                e -> List = list;
                e -> Next = NULL;
                e -> Prev = NULL;
                list -> First = e;
                list -> Last = e;
        }
        list -> Length++;
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
        /* to be implemented */
        IENTRY *e = NULL;
        assert(list);
        assert(YUVimage);
        e = CreateNewEntry();
        e -> YUVImage = YUVimage;
        if(list -> Last){
                e -> List = list;
                e -> Next = NULL;
                e -> Prev = list -> Last;
                list -> Last -> Next = e;
                list -> Last = e;
        }
        else{
                e -> List = list;
                e -> Next = NULL;
                e -> Prev = NULL;
                list -> First = e;
                list -> Last = e;
        }
        list -> Length++;
}

/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end)
{
        /* to be implemented */

}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
        /* to be implemented */

}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
        /* to be implemented */
        IENTRY *e = NULL;
        IENTRY *ET1 = NULL, *ET2 = NULL;
        assert(list);
        int x = 0;
        int len = list -> Length;

        e = list -> First;
        list -> Last = e;
        ET1 = e -> Next;
        ET2 = e -> Prev;
        while( x < len - 1){
                e -> Next = ET2;
                e -> Prev = ET1;
                ET2 = e;
                e = ET1;
                ET1 = ET1 -> Next;
                e -> Prev = ET1;
                e -> Next = ET2;
                x++;
        }
        list -> First = e;
}


/* EOF */

