#include "interplib.h"

std::vector<double> getUniqueSortedValues(const std::vector<double>& input) {
    // Use a set to automatically handle uniqueness and sorting
    std::set<double> uniqueSet(input.begin(), input.end());
    
    // Convert the set back to a vector
    std::vector<double> result(uniqueSet.begin(), uniqueSet.end());
    
    return result;
}

// Чтение данных из файла

int readFile(std::string filename, std::string x_col_name, std::string y_col_name, std::string z_col_name, \
            std::vector<double>& x, std::vector<double>& y, std::vector<double>& z) {
    
     std::ifstream file(filename);
    if (!file) {
        std::cerr << "ERROR: Could not open file" << filename << std::endl;
        return -1;
    }

    // Read header line to find column indices
    std::string line;
    std::istringstream iss;
    std::getline(file, line);    
    iss.str(line);
    std::string header;
    int col1Index = -1, col2Index = -1, col3Index = -1;
    int columnIndex = 0;
    while (iss >> header) {
        if (header == x_col_name) {
            col1Index = columnIndex;
        } else if (header == y_col_name) {
            col2Index = columnIndex;
        } else if (header == z_col_name) {
            col3Index = columnIndex;
        }
        columnIndex++;
    }
    if (col1Index == -1 || col2Index == -1 || col3Index == -1) {
        std::cerr << "Column not found" << std::endl;
        return -1;
    }

    // Read values
    while (std::getline(file, line)) {
        //std::cout << line << std::endl;       
        iss.clear();
        iss.str(line);
        std::string value;
        columnIndex = 0;
        while (iss >> value) {  
           // std::cout << "Value = " << value << std::endl;        
            if (columnIndex == col1Index) {
                x.push_back(std::stod(value));
            } else if (columnIndex == col2Index) {
                y.push_back(std::stod(value));
            } else if (columnIndex == col3Index) {
                z.push_back(std::stod(value));
            }
            columnIndex++;
        }
    }
    return 0;
}

void writeVectorsToFile(const std::string& filename, const std::vector<std::vector<double>>& vectors, 
                        const std::vector<std::string>& headers, int width) {
    // Check if all vectors are of the same size
    if (vectors.size() != headers.size()) {
        std::cerr << "Error: Number of vectors must be equal to number of headers" << std::endl;
        return;
    }

    // Open the file for writing
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << " for writing." << std::endl;
        return;
    }

    // Write the header
    for (const auto& header : headers) {
        outFile << std::setw(width) << std::right << header << " ";
    }
    outFile << "\n";


    // Write the data    
    for (size_t i = 0; i < vectors[0].size(); ++i) {
        for (size_t j = 0; j < vectors.size(); ++j) {
             outFile <<  std::fixed << std::setprecision(1) << std::setw(width) << std::right << vectors[j][i] << " ";
        } 
        outFile << "\n";
    }

    // Close the file
    outFile.close();
}



double bilinearInterpolation(double x1, double y1, double x2, double y2, \
                             double value11, double value21, double value12, double value22, \
                             double x, double y) {  
    
    double R1 = ((x2 - x) / (x2 - x1)) * value11 + ((x - x1) / (x2 - x1)) * value21;
  //  std::cout << "R1 = " << R1;
    double R2 = ((x2 - x) / (x2 - x1)) * value12 + ((x - x1) / (x2 - x1)) * value22;   
   // std::cout << " R2 = " << R2;  
    double P = ((y2 - y) / (y2 - y1)) * R1 + ((y - y1) / (y2 - y1)) * R2;
  // std::cout << " P = " << P << std::endl;
    return P;                       
}

