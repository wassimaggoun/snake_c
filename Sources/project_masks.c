#include "project_masks.h"
#include "alloc.h"


void resize_mask (mask *m, int nhsize, int nvsize) 
{
    if (nhsize < 1 || nvsize < 1)
    {
        return;
    }

    //ratio of old scale to new
    float ratioX = (float)m->hsize / nhsize;
    float ratioY = (float)m->vsize / nvsize;

    bool *newGrid = malloc(sizeof(bool) * (nhsize * nvsize));

    int nbmasked = 0;

    //loop for y axis
    for (int y = 0; y < nvsize; y++)
    {
        //loop for x axis 
        for (int x = 0; x < nhsize; x++)
        {
            //downscalling or upscalling back
            int oldX = (int)(x * ratioX);
            int oldY = (int)(y * ratioY);

            //formula to convert and find index 2D to 1D array
            int oldIndex = oldY * m->hsize + oldX;
            int newIndex = y * nhsize + x;

            newGrid[newIndex] = m->grid[oldIndex];
            if (newGrid[newIndex] == true)
                nbmasked = nbmasked + 1;
        }
    }

    free(m->grid);
    m->grid = newGrid;
    m->hsize = nhsize;
    m->vsize = nvsize;
    m->nbmasked = nbmasked;
}

mask *read_mask(const char *path) 
{
    FILE* inFile = fopen(path, "r");
    int hsize = -1;
    int vsize = 0;
    int nbmasked = 0;
    char characters[1024]; //max number 
    bool isUnmasked = false;

    //check size and lines, and if at least one cell is masked
    while (fgets(characters, sizeof(characters), inFile))
    {
        //len of line
        int len = (int)strlen(characters);
        if (len > 0 && characters[len - 1] == '\n') 
        {
            characters[--len] = '\0'; // remove newline
        }
        
        if (hsize == -1)
        {
            hsize = len;
        }
        //checks if it is the same length with the previous line
        else if (len != hsize)
        {
            fclose(inFile);
            return NULL;
        }

        for (int i = 0; i < len; i++) 
        {
            if (characters[i] == 'X') 
            {
                nbmasked++;
            } 
            else 
            {
                isUnmasked = true;
            }
        }

        vsize = vsize + 1; 
    }

    if (isUnmasked == false || hsize == -1 || vsize == 0)
    {
        fclose(inFile);
        return NULL;
    }

    mask *m = create_empty_mask(hsize, vsize);
    m->nbmasked = nbmasked;

    rewind(inFile); // go back to file start
    
    //fill mask grid
    int y = 0;
    while (fgets(characters, sizeof(characters), inFile) && y < vsize) 
    {
        int len = (int)strlen(characters);
        if (len > 0 && characters[len - 1] == '\n') 
        {
            characters[--len] = '\0'; // remove newline
        }
        for (int x = 0; x < hsize; x++)
        {
            m->grid[y * hsize + x] = (characters[x] == 'X');
        }
        y = y + 1;
    }


    fclose(inFile);
    return m;
}