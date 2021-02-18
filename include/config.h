#include <inttypes.h>

// choose sqrt instead of math for a non-float dependent implementation
#include "sqrt.h"
// #include <math.h>

// type for the accelerometer samples
typedef int32_t accel_t;
// type used for time: warning the algorithm is not robust to roll-over of this variable
// reset the algorithm if time overflows
// preferably, time should be in ms, if not, use timeScalingFactor in the preprocessing stage to adjust it to ms
typedef int64_t time_t;

// magnitude of acceleration
// this should be 1 bit bigger than accel_t
// example: if the accelerometer works at 12 bits, magnitude should be 13 bits, therefore choosing int16_t for both will do
typedef int64_t magnitude_t;

// accumulator of magnitude, shuold be bigger than magnitude
// the size depends on the length of the filter in the filtering stage
// example: accelerometer works at 12 bits, the filter has 8 taps -> accumualtor should be at least 12 + 3 bits -> using int16_t will work fine
typedef int64_t accumulator_t;

// steps count type
// the size of this depends on what is the maximum number of steps you are willing to show and store
// example: is the step count is reset every 24h and one walks no more than 20k / day (reasonable) -> 16 bits should be enough
typedef int32_t steps_t;

// uncomment this line to disable interpolation
#define STEP_INTERPOLATION_DISABLE

// incomment to skip filtering step
#define SKIP_FILTER

// use this to allow dumping each stage on file, useful for debugging
// #define DUMP_FILE
#define DUMP_MAGNITUDE_FILE_NAME "magnitude.csv"
#define DUMP_INTERPOLATED_FILE_NAME "interpolated.csv"
#define DUMP_FILTERED_FILE_NAME "filtered.csv"
#define DUMP_SCORING_FILE_NAME "scoring.csv"
#define DUMP_DETECTION_FILE_NAME "detection.csv"
#define DUMP_POSTPROC_FILE_NAME "postproc.csv"