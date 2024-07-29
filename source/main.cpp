#include "interplib.h"
#include "grid.h"

int read_params(std::string param_file, std::vector<point>& points, double& x1, double& y1, double& x2, double& y2, double& step) {
    std::ifstream file(param_file);
    if (!file) {
        std::cerr << "ERROR: Could not open file" << param_file << std::endl;
        return -1;
    }
    std::istringstream iss;
    std::string line;
    int line_num = 0;
    std::string value;
 
    
    while (std::getline(file, line) && line_num < 4) {           
        iss.clear();
        iss.str(line);        
        point P;
        if (std::getline(iss, value, ',')) P.lin_x = stod(value);
        else {
            std::cerr << "ERROR: LIN_X for point " << line_num << " must be specified in " << param_file << std::endl;
            return -1; 
        }
        if (std::getline(iss, value, ',')) P.lin_y = stod(value);
        else {
            std::cerr << "ERROR: LIN_Y for point " << line_num << " must be specified in " << param_file << std::endl;
            return -1; 
        }
        if (std::getline(iss, value, ',')) P.geo_x = stod(value);
        else {
            std::cerr << "ERROR: GEO_X for point " << line_num << " must be specified in " << param_file << std::endl;
            return -1; 
        }
        if (std::getline(iss, value, ',')) P.geo_y = stod(value);
        else {
            std::cerr << "ERROR: GEO_Y for point " << line_num << " must be specified in " << param_file << std::endl;
            return -1; 
        }
        if (std::getline(iss, value, ',')) P.inline_no = stod(value);
        else {
            std::cerr << "ERROR: INLINE for point " << line_num << " must be specified in " << param_file << std::endl;
            return -1; 
        }
        if (std::getline(iss, value, ',')) P.xline_no = stod(value);
        else {
            std::cerr << "ERROR: XLINE for point " << line_num << " must be specified in " << param_file << std::endl;
            return -1; 
        }
        points.push_back(P);
        line_num++;
    }
    if (points.size() < 4) {
        std::cerr << "ERROR: Need 4 points for interpolation!" << std::endl;
        return -1;
    }

    std::getline(file, line);
    iss.clear();
    iss.str(line);
   
    if (std::getline(iss, value, ',')) x1 = stod(value);
    else {
        std::cerr << "ERROR: X1 must be specified in " << param_file << std::endl;
        return 0;
    }
    if (std::getline(iss, value, ',')) y1 = stod(value);
    else {
        std::cerr << "ERROR: Y1 must be specified in " << param_file << std::endl;
        return 0;
    }
    if (std::getline(iss, value, ',')) x2 = stod(value);
    else {
        std::cerr << "ERROR: X2 must be specified in " << param_file << std::endl;
        return 0;
    }
    if (std::getline(iss, value, ',')) y2 = stod(value);
    else {
        std::cerr << "ERROR: Y2 must be specified in " << param_file << std::endl;
        return 0;
    }
    if (std::getline(iss, value, ',')) step = stod(value);
    else {
        std::cerr << "ERROR: Step must be specified in " << param_file << std::endl;
        return 0;
    }
    return 1;   
    
}

int main (int argc, char* argv[])
{

        // Check if the number of arguments is correct
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <grid_param_file> <target_table_file>" << std::endl;
        return 1;
    }
    std::vector<point> points;
    std::string param_file = argv[1];
    std::string target_file = argv[2];
    double x1;
    double y1;
    double x2;
    double y2;
    double step;
    if (!read_params(param_file, points, x1, y1, x2, y2, step)) {
        std::cerr << "Cannot read params file!" << std::endl;
        return 1;
    }


    point llp = points[0]; 
    point lrp = points[1];
    point ulp = points[2];  
    point urp = points[3];
    
    Grid myGrid(llp, lrp, ulp, urp, step, step);
    std::cout << "Grid points before expand:" << std::endl;
    myGrid.printGridPoints();

    myGrid.setNewBounds(x1, y1, x2, y2);
    std::cout << "Grid points after expand:" << std::endl;
    myGrid.printGridPoints();
    std::cout << "Interpolation step is: " << step << std::endl;

    std::vector<double> linx;
    std::vector<double> liny;
    myGrid.get_lin_coords(linx, liny);
    std::vector<double> inlines;
    std::vector<double> xlines;
    myGrid.get_inl_xln(inlines, xlines);   
    std::vector<double> geox;
    std::vector<double> geoy;
    myGrid.get_geo_coords(geox, geoy);
    std::vector<std::vector<double>> vectors;
    vectors.push_back(inlines);
    vectors.push_back(xlines);
    vectors.push_back(geox);
    vectors.push_back(geoy);
    vectors.push_back(linx);
    vectors.push_back(liny);
   
    writeVectorsToFile(target_file, vectors, {"Inlines", "XLines", "CDP_X", "CDP_Y", "LinX", "LinY"}, 10);
}