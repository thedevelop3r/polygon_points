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

void generate_points(point_t* inputs, point_t* points, char from, char to)
{
  for(char i = from; i < to; i++)
  {
    if(i < 3)
    {
      points[i].x = inputs[i].x;
      points[i].y = inputs[i].y;
    }
    else
    {
      //printf("pt1: %.16lf, %.16lf\n", points[i-3].x, points[i-3].y);
      //printf("pt2: %.16lf, %.16lf\n", points[i-2].x, points[i-2].y);
      //printf("pt3: %.16lf, %.16lf\n", points[i-1].x, points[i-1].y);
    
      // calculate required distances
      double d12 = distance(&inputs[i-3], &inputs[i-2]);
      double d13 = distance(&inputs[i-3], &inputs[i-1]);
      //printf("d12: %.16lf\n", d12);
      //printf("d13: %.16lf\n", d13);
    
      // calculate required angles
      double theta = 2 * atan2(d12 , sqrt(d12*d12 - d13*d13/4));
      double phi = atan2(inputs[i-1].y - inputs[i-2].y, inputs[i-1].x - inputs[i-2].x);
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
      points[i].x = inputs[i-1].x - delta_x;
      points[i].y = inputs[i-1].y + delta_y;
    }
    printf("pt%d: %.16lf, %.16lf\n", i+from, points[i].x, points[i].y);   
  }
}


int main()
{
  // declare input set
  point_t inputs[] = 
    {
      {2.1, 4.3},
      {3.2618187593136714, 5.248776670511476},
      {4.229518090705041, 6.394882252046046},
      {4.970144154070997, 7.699287493626686},
      {5.4584758171066685, 9.117572439213015},
      {5.677883530716649, 10.601439096028392},
      {5.620895628364498, 12.10035616477686},
      {5.289452764715364, 13.563279822435065},
      {4.694841828968918, 14.940391958424991},
      {3.857311583384793, 16.18479667061946},
      {2.8053831159695455, 17.25411724904363},
      {1.574878589031866, 18.11193926390795},
      {0.20770135840910497, 18.729050615340313},
      {-1.2495909950582316, 19.08443631641118},
      {-2.7473721281023433, 19.165994133308747},
      {-4.234636900627881, 18.97094671239639},
      {-5.66073829458397, 18.505936159659683},
      {-6.9771121374195335, 17.786797851753388},
      {-8.138930896733212, 16.83802118124192},
      {-9.10663022812459, 15.691915599707357},
      {-9.847256291490558, 14.387510358126725}
    };
  point_t* points = calloc(21, sizeof(point_t));

  // print calculated points
  generate_points(inputs, points, 0, 21);  
}
