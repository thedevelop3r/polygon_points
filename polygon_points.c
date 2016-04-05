#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct point
{
  double x;
  double y;
} point_t;

double distance(point_t* p1, point_t* p2)
{
  return sqrt( (p2->x - p1->x)*(p2->x - p1->x) + (p2->y - p1->y)*(p2->y - p1->y) );  
}

void generate_points(point_t* points, char from, char to)
{
  for(char i = from; i < to; i++)
  {
    //printf("pt1: %.16lf, %.16lf\n", points[i-3].x, points[i-3].y);
    //printf("pt2: %.16lf, %.16lf\n", points[i-2].x, points[i-2].y);
    //printf("pt3: %.16lf, %.16lf\n", points[i-1].x, points[i-1].y);
    
    // calculate required distances
    double d12 = distance(&points[i-3], &points[i-2]);
    double d13 = distance(&points[i-3], &points[i-1]);
    //printf("d12: %.16lf\n", d12);
    //printf("d13: %.16lf\n", d13);
    
    // calculate required angles
    double theta = 2 * atan2(d12 , sqrt(d12*d12 - d13*d13/4));
    double phi = atan2(-points[i-2].y+points[i-1].y, -points[i-2].x+points[i-1].x);
    double alpha = theta - phi;
    //printf("theta: %.16lf\n", theta);
    //printf("phi: %.16lf\n", phi);
    //printf("alpha: %.16lf\n", alpha);
    
    // calculate deltas
    double delta_x = d12 * cos(alpha);
    double delta_y = d12 * sin(alpha);
    //printf("delta_x: %.16lf\n", delta_x);
    //printf("delta_y: %.16lf\n", delta_y);
    
    // apply changes
    points[i].x = points[i-1].x - delta_x;
    points[i].y = points[i-1].y + delta_y;
    printf("pt%d: %.16lf, %.16lf\n", i+from, points[i].x, points[i].y);
  }
}


int main()
{
  point_t* points = calloc(22, sizeof(point_t));

  // declare initial points
  points[0].x = 2.1000000000000000;
  points[0].y = 4.3000000000000000;
  points[1].x = 3.2618187593136714;
  points[1].y = 5.248776670511476;
  points[2].x = 4.229518090705041;
  points[2].y = 6.394882252046046;

  // print starting points
  printf("Initial Points (3 required):\n");
  printf("pt1: %.16lf, %.16lf\n", points[0].x, points[0].y);
  printf("pt2: %.16lf, %.16lf\n", points[1].x, points[1].y);
  printf("pt3: %.16lf, %.16lf\n", points[2].x, points[2].y);

  generate_points(points, 3, 23);  
}
