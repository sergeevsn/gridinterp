#pragma once
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <set>
#include <algorithm>
#include <gsl/gsl_interp2d.h>
#include <gsl/gsl_spline2d.h>
#include <gsl/gsl_errno.h>

struct point {
    double lin_x;
    double lin_y;
    double geo_x;
    double geo_y;
    double inline_no;
    double xline_no;    
};

std::vector<double> getUniqueSortedValues(const std::vector<double>& input);

double bilinearInterpolation(double x1, double y1, double x2, double y2, double value11, \
                             double value21, double value12, double value22, double x, double y);

void writeVectorsToFile(const std::string& filename, const std::vector<std::vector<double>>& vectors, 
                        const std::vector<std::string>& headers, int width);