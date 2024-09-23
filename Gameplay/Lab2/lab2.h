#include <iostream>
// dont use cout in any of the functions apart from PrintArray();
int ReplaceWithMinusOne(int array[4][6])
{
    bool hasCluster = false;

    // Check for horizontal clusters
    for (int row = 0; row < 4; row++)
    {
        for (int Col = 0; Col < 4; Col++) 
        {
            if (array[row][Col] == array[row][Col + 1] && array[row][Col + 1] == array[row][Col + 2])
            {
                array[row][Col] = -1;
                array[row][Col + 1] = -1;
                array[row][Col + 2] = -1;
                hasCluster = true;
            }
        }
    }

    // Return whether any cluster was found
    return hasCluster ? 1 : 0;
}

void PrintArray(int array[4][6])
{
    for (int row = 0; row < 4; row++)
    {
        for (int Col = 0; Col < 6; Col++)
        {
            std::cout << array[row][Col] << " ";
        }
        std::cout << std::endl;
    }
}

void FallDownAndReplace(int array[4][6])
{

}
