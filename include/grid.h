#pragma once
#include "interplib.h"

class Grid {
    private:
       point lower_left_point;
       point lower_right_point;    
       point upper_left_point;
       point upper_right_point;
       double step_x;
       double step_y;
       double size_x;
       double size_y;   

    public:  
        Grid(point llp, point lrp, point ulp, point urp, double step_x, double step_y) {
          this->lower_left_point = llp;
          this->lower_right_point = lrp;
          this->upper_left_point = ulp;
          this->upper_right_point = urp;
          this->step_x = step_x;
          this->step_y = step_y;
          this->size_x = lrp.lin_x - llp.lin_x;
          this->size_y = urp.lin_y - lrp.lin_y;
          std::cout << "Grid X size: " << this->size_x << ", Y size: " << this->size_y << std::endl;
        }; 

        int get_lin_coords(std::vector<double>& x_coords, std::vector<double>& y_coords) {
            x_coords.clear();
            y_coords.clear();
            for (double y = this->lower_left_point.lin_y; y <= this->size_y; y+=step_y) {
              for (double x = this->lower_left_point.lin_x; x <= this->size_x; x+=step_x) {
                x_coords.push_back(x);
                y_coords.push_back(y);
              }
            }            
            return 0;
        }
       
       int get_geo_coords(std::vector<double>& x_coords, std::vector<double>& y_coords) {
            x_coords.clear();
            y_coords.clear();
            double x1;
            double x2;
            double y1;
            double y2;
            double val11;
            double val22;
            double val21;
            double val12;
            for (double y = this->lower_left_point.lin_y; y <= this->size_y; y+=step_y) {
              for (double x = this->lower_left_point.lin_x; x <= this->size_x; x+=step_x) {                
                x1 = this->lower_left_point.lin_x;
                x2 = this->lower_right_point.lin_x;
                y1 = this->lower_left_point.lin_y;
                y2 = this->upper_right_point.lin_y;
                val11 = this->lower_left_point.geo_x;
                val12 = this->upper_left_point.geo_x;
                val21 = this->lower_right_point.geo_x;
                val22 = this->upper_right_point.geo_x;
                x_coords.push_back(bilinearInterpolation(x1, y1, x2, y2, val11, val21, val12, val22, x, y));
                val11 = this->lower_left_point.geo_y;
                val12 = this->upper_left_point.geo_y;
                val21 = this->lower_right_point.geo_y;
                val22 = this->upper_right_point.geo_y;
                y_coords.push_back(bilinearInterpolation(x1, y1, x2, y2, val11, val21, val12, val22, x, y));
              }
            }
            return 0;
        }

        int get_inl_xln(std::vector<double>& inlines, std::vector<double>& xlines) {
          inlines.clear();
          xlines.clear();
          double x1;
          double x2;
          double y1;
          double y2;
          double val11;
          double val22;
          double val21;
          double val12;
          for (double y = this->lower_left_point.lin_y; y <= this->size_y; y+=step_y) {
            for (double x = this->lower_left_point.lin_x; x <= this->size_x; x+=step_x) {                
                x1 = this->lower_left_point.lin_x;
                x2 = this->lower_right_point.lin_x;
                y1 = this->lower_left_point.lin_y;
                y2 = this->upper_right_point.lin_y;
                val11 = this->lower_left_point.inline_no;
                val12 = this->upper_left_point.inline_no;
                val21 = this->lower_right_point.inline_no;
                val22 = this->upper_right_point.inline_no;
                inlines.push_back(bilinearInterpolation(x1, y1, x2, y2, val11, val21, val12, val22, x, y));
                val11 = this->lower_left_point.xline_no;
                val12 = this->upper_left_point.xline_no;
                val21 = this->lower_right_point.xline_no;
                val22 = this->upper_right_point.xline_no;
                xlines.push_back(bilinearInterpolation(x1, y1, x2, y2, val11, val21, val12, val22, x, y));
            }            
          }
        return 0;  
        }

        int setNewBounds(double linX1, double linY1, double linX2, double linY2) {
            point new_llp;
            point new_lrp;
            point new_ulp;
            point new_urp;

            new_llp.lin_x = linX1;
            new_llp.lin_y = linY1;
            new_lrp.lin_x = linX2;
            new_lrp.lin_y = linY1;
            new_ulp.lin_x = linX1;
            new_ulp.lin_y = linY2;
            new_urp.lin_x = linX2;
            new_urp.lin_y = linY2;

            std::vector<point> new_points = {new_llp, new_lrp, new_ulp, new_urp};
            point P;
            double x1;
            double x2;
            double y1;
            double y2;
            double val11;
            double val22;
            double val21;
            double val12;
            for (int i=0; i<4; i++) {
                P = new_points[i];
                x1 = this->lower_left_point.lin_x;
                x2 = this->lower_right_point.lin_x;
                y1 = this->lower_left_point.lin_y;
                y2 = this->upper_right_point.lin_y;
                val11 = this->lower_left_point.geo_x;
                val12 = this->upper_left_point.geo_x;
                val21 = this->lower_right_point.geo_x;
                val22 = this->upper_right_point.geo_x;
                P.geo_x = bilinearInterpolation(x1, y1, x2, y2, val11, val21, val12, val22, P.lin_x, P.lin_y);
                val11 = this->lower_left_point.geo_y;
                val12 = this->upper_left_point.geo_y;
                val21 = this->lower_right_point.geo_y;
                val22 = this->upper_right_point.geo_y;
                P.geo_y = bilinearInterpolation(x1, y1, x2, y2, val11, val21, val12, val22, P.lin_x, P.lin_y);
                val11 = this->lower_left_point.inline_no;
                val12 = this->upper_left_point.inline_no;
                val21 = this->lower_right_point.inline_no;
                val22 = this->upper_right_point.inline_no;
                P.inline_no = bilinearInterpolation(x1, y1, x2, y2, val11, val21, val12, val22, P.lin_x, P.lin_y);
                val11 = this->lower_left_point.xline_no;
                val12 = this->upper_left_point.xline_no;
                val21 = this->lower_right_point.xline_no;
                val22 = this->upper_right_point.xline_no;
                P.xline_no = bilinearInterpolation(x1, y1, x2, y2, val11, val21, val12, val22, P.lin_x, P.lin_y);     
                new_points[i] = P;          
            }
            this->lower_left_point = new_points[0];
            this->lower_right_point = new_points[1];
            this->upper_left_point = new_points[2];
            this->upper_right_point = new_points[3];
            this->size_x = lower_right_point.lin_x - lower_left_point.lin_x;
            this->size_y = upper_left_point.lin_y - lower_left_point.lin_y;
            return 0;
        }

        
        void printGridPoints() {
            std::vector<point> points = {this->lower_left_point, this->lower_right_point, this->upper_left_point, this->upper_right_point};
            for (int i=0; i<4; i++) {
                 point P = points[i];
                 std::cout << "LLP: LinX = " << std::fixed << std::setprecision(1) << P.lin_x << ", LinY = " \
                      << std::fixed << std::setprecision(1) << P.lin_y << ", GeoX = " \
                      << std::fixed << std::setprecision(1) << P.geo_x << ", GeoY = " \
                      << std::fixed << std::setprecision(1) << P.geo_y << ", Inline = " \
                      << std::fixed << std::setprecision(1) << P.inline_no << ", XLine = " \
                      << std::fixed << std::setprecision(1) << P.xline_no << std::endl;
            }           
        }
};
