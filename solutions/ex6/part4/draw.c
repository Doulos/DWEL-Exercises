#include <stdio.h> 
 
int main() 
{ 
    int a, b; 
    double x, y; 
    const int maxiter = 32; 
    int iter; 
 
    for (b = 0; b <= 32; b++) /* rows */ 
    { 
        for (a = 0; a <= 85; a++) /* columns */ 
        { 
            /* mandelbrot is an iteration of z1 = z^2 + c 
               here, zi and zr are the imaginary and real 
               portions of z */ 
            double zi = 0.0, zr = 0.0; 
 
            /* and zni and znr are the imaginary and real 
               portions of z1 */ 
            double zni = 0.0, znr = 0.0; 
 
            /* map ascii x/y coords to the actual 
               x/y values in the mandelbrot set */ 
            x = (a - 50) / 20.0;    
            y = (b - 16.0) / 10.0;  
 
            iter = 1; 
            zi = 0.0; zr = 0.0; 
            do { 
                /* imaginary portion of z^2 + c */ 
                zni = 2 * zi * zr + y;        
                /* real portion of z^2 + c */ 
                znr = zr * zr - zi * zi + x;  
                /* new values for next iteration */ 
                zi = zni; 
                zr = znr;
                /* is the distance from the origin  
                   greater than 2?  if so, break 
                   From memory, this condition means the 
                   iteration will diverge to infinity, so 
                   no point continuing */ 
                if (zi*zi + zr*zr > 4.0) 
                    break; 
 
                iter++; 
            } while (iter < maxiter); 
            if (iter == maxiter)
            { 
                putchar(' '); 
                iter = iter / (iter - maxiter);
            }
            else 
            {
                putchar (" .:-;!/>)|&IH%*#"[iter & 15]); 
            }
        } 
        putchar ('\n'); 
    } 
    return 0; 
} 
