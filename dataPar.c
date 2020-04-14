#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <omp.h>

#define BUFFFER_SIZE 1024
#define DELIMITERS ","
#define DELIMITERS_WITH_END_LINE ",\n"
#define INPUT_SAMPLE_DATA_FILE_NAME "sample_data.csv"
#define INPUT_FINAL_DATA_FILE_NAME "stremflow_time_series.csv"

void findSlopeAndIntercept(float x1, float y1, float x2,float y2, float *slope, float *intercept){
   //Finding slope
   *slope = (y2 - y1) / (x2 - x1);
   //Finding intercept 
   *intercept = y1 - (*slope * x1);
}

float findSumOfDistanceOfPointsFromLine(float x[], int n, int p1ToIgnore, int p2ToIgnore, float slope, float intercept) {
   float sum = 0.00;

   float A = -(slope);
   float B = 1.00;
   float C = -(intercept);

   for (int i = 0; i<n; i++){
      if (i != p1ToIgnore && i != p2ToIgnore){
         sum += fabs((A*(i+1))+(B*x[i])+C) / sqrt(((A*A)+(B*B)));
      }
   }

   return sum;
}

float findSAR(float x[], int n, float *L1slope, float *L1Intercept) { 
   float SAR = FLT_MAX;
   float slope, intercept = 0.00;
	for (int i = 0; i<n; i++){ 
      for (int j = i+1; j<n; j++){ 
         findSlopeAndIntercept(i+1, x[i], j+1, x[j], &slope, &intercept);
         float tempSAR = findSumOfDistanceOfPointsFromLine(x, n, i, j, slope, intercept);
         if (tempSAR < SAR){
            SAR = tempSAR;
            *L1slope = slope;
            *L1Intercept = intercept;
         }
      }
	}

   return SAR;
} 

const char* getfield(char* line, int num)
{
   const char* tok;
   for (tok = strtok(line, DELIMITERS);
         tok && *tok;
         tok = strtok(NULL, DELIMITERS_WITH_END_LINE))
   {
      if (!--num)
         return tok;
   }
   return NULL;
}

float* getValuesFromCSVFile(int *n, char *fileName) {
   FILE* stream = fopen(fileName, "r");
   int position = 0, bufferSize = BUFFFER_SIZE;
   float* buffer = malloc(sizeof(float) * bufferSize);

   if(!buffer) {
      fprintf(stderr, "Internal Error: Memory allocation failed while reading input.\n");
      exit(EXIT_FAILURE);
   }

   char line[BUFFFER_SIZE];
   while (fgets(line, BUFFFER_SIZE, stream))
   {
      char* tmp = strdup(line);

      if(position == 0){
         position++;
         continue;
      }

      buffer[position-1] = atof(getfield(tmp, 2));
      position++;

      //In case the size of input exceeds the buffer.
      if (position >= bufferSize) {
         bufferSize += BUFFFER_SIZE;
         buffer = realloc(buffer, sizeof(float) * bufferSize);
         if (!buffer) {
               fprintf(stderr, "Internal Error: Memory allocation failed while reading input.\n");
               exit(EXIT_FAILURE);
         }
      }

      // NOTE strtok clobbers tmp
      free(tmp);
   }

   
   fclose(stream);

   *n = position;
   return buffer;
}

void printValues(float SAR, float L1Slope, float L1Intercept, int numThreadsUsed, int numOfDataPoints, float timeSpent) {
   printf("-----------------------------------------\n");
   printf("Calculated Values for %d data points\n", numOfDataPoints);
   printf("-----------------------------------------\n");
   printf("SAR: %f\n", SAR);
   printf("Slope: %f\n", L1Slope);
   printf("Intercept: %f\n", L1Intercept);
   printf("-----------------------------\n");

   printf("\n");
   printf("Number of threads used: %d.\n", numThreadsUsed);
   printf("Time elpased: %.2f sec.\n", timeSpent);
   printf("------------------------------------------------------------------------------------------------------------\n\n");
}

// Driver main function 
int main() {
	int n;
	float *x;
   float L1Slope, L1Intercept, SAR = 0.00;
   int numOfThreads = 0;
   double timeSpent = 0.0;

   clock_t begin = clock(); //record starting time
   clock_t end;

   printf("Hello, we will be calculating SAR value, slope and intercept for the best fit line in the given data.\n\n");

   //------------------------------------------------------------------------------------------------------------------------------
   // SAMPLE DATA TEST
   //------------------------------------------------------------------------------------------------------------------------------
   //Reading values from the csv file
   printf("Reading values from: %s.\n", INPUT_SAMPLE_DATA_FILE_NAME);
   x = getValuesFromCSVFile(&n, INPUT_SAMPLE_DATA_FILE_NAME);
   printf("Successfully retrieved values form the file.\n");

   //---------------------------------------------
   // FOR 6 DATA POINTS
   //---------------------------------------------
   printf("Starting to calculate values from the data retrieved, please be patient as this could take time.\n\n");
   SAR = findSAR(x, 6, &L1Slope, &L1Intercept);
   numOfThreads++;
   
   end = clock(); //record ending time
   
   // calculate elapsed time by finding difference (end - begin) and
	// divide by CLOCKS_PER_SEC to convert to seconds
	timeSpent += (double)(end - begin) / CLOCKS_PER_SEC;

   printValues(SAR, L1Slope, L1Intercept, numOfThreads, 6, timeSpent);

   //RESET VARIABLES
   n, numOfThreads=0; L1Slope, L1Intercept, SAR, timeSpent = 0.00; end=0;

   //---------------------------------------------
   // FOR 10 DATA POINTS
   //---------------------------------------------
   printf("Starting to calculate values from the data retrieved, please be patient as this could take time.\n\n");
   SAR = findSAR(x, 10, &L1Slope, &L1Intercept);
   numOfThreads++;
   
   end = clock(); //record ending time
   
   // calculate elapsed time by finding difference (end - begin) and
	// divide by CLOCKS_PER_SEC to convert to seconds
	timeSpent += (double)(end - begin) / CLOCKS_PER_SEC;

   printValues(SAR, L1Slope, L1Intercept, numOfThreads, 10, timeSpent);

   //RESET VARIABLES
   n, numOfThreads=0; L1Slope, L1Intercept, SAR, timeSpent = 0.00; end=0;

   //---------------------------------------------
   // FOR 14 DATA POINTS
   //---------------------------------------------
   printf("Starting to calculate values from the data retrieved, please be patient as this could take time.\n\n");
   SAR = findSAR(x, 14, &L1Slope, &L1Intercept);
   numOfThreads++;
   
   end = clock(); //record ending time
   
   // calculate elapsed time by finding difference (end - begin) and
	// divide by CLOCKS_PER_SEC to convert to seconds
	timeSpent += (double)(end - begin) / CLOCKS_PER_SEC;

   printValues(SAR, L1Slope, L1Intercept, numOfThreads, 14, timeSpent);

   //RESET VARIABLES
   n, numOfThreads=0; L1Slope, L1Intercept, SAR, timeSpent = 0.00; end=0;

   //---------------------------------------------
   // FOR 18 DATA POINTS
   //---------------------------------------------
   printf("Starting to calculate values from the data retrieved, please be patient as this could take time.\n\n");
   SAR = findSAR(x, 18, &L1Slope, &L1Intercept);
   numOfThreads++;
   
   end = clock(); //record ending time
   
   // calculate elapsed time by finding difference (end - begin) and
	// divide by CLOCKS_PER_SEC to convert to seconds
	timeSpent += (double)(end - begin) / CLOCKS_PER_SEC;

   printValues(SAR, L1Slope, L1Intercept, numOfThreads, 18, timeSpent);

   //RESET VARIABLES
   n, numOfThreads=0; L1Slope, L1Intercept, SAR, timeSpent = 0.00; end=0;

   //------------------------------------------------------------------------------------------------------------------------------
   // FINAL DATA TEST
   //------------------------------------------------------------------------------------------------------------------------------
   //Reading values from the csv file
   printf("Reading values from: %s.\n", INPUT_FINAL_DATA_FILE_NAME);
   x = getValuesFromCSVFile(&n, INPUT_FINAL_DATA_FILE_NAME);
   printf("Successfully retrieved values form the file.\n");

   printf("Starting to calculate values from the data retrieved, please be patient as this could take time.\n\n");
   #pragma omp parallel
   {
      int id = omp_get_thread_num();
      SAR = findSAR(x, n, &L1Slope, &L1Intercept);
      numOfThreads++;
   }
   
   end = clock(); //record ending time
   
   // calculate elapsed time by finding difference (end - begin) and
	// divide by CLOCKS_PER_SEC to convert to seconds
	timeSpent += (double)(end - begin) / CLOCKS_PER_SEC;

   printValues(SAR, L1Slope, L1Intercept, numOfThreads, n, timeSpent);

	return 0; 
} 


// gcc dataPar.c -o dataPar -fopenmp -lm