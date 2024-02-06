#include <catch2/benchmark/catch_chronometer.hpp>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <gp_Pnt.hxx>
#include <GeomAbs_Shape.hxx>
#include <Standard_TypeDef.hxx>
#include <Adaptor3d_Surface.hxx>
#include <Standard_Handle.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <GeomAPI_PointsToBSplineSurface.hxx>

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

static const int N_ROW = 25;
static const int N_COL = 3;

void read_points(TColgp_Array2OfPnt&);
int BSplineSurfFitting(const TColgp_Array2OfPnt&, int, int, double);

// int main() {
//     // create a set of points
//     TColgp_Array2OfPnt points(1, N_ROW, 1, N_COL);
//     // read data into points
//     read_points(points);
    
//     BSplineSurfFitting(points, 179, 170, 0.01);
// }

int BSplineSurfFitting(TColgp_Array2OfPnt& points, int mindeg, int maxdeg, double tol) {
    // create GeomAPI_PointsToBSplineSurface Object and fit
    GeomAPI_PointsToBSplineSurface pointsToSurf(points, mindeg, maxdeg, GeomAbs_C2, tol);
    Handle(Geom_BSplineSurface) bSplineSurf = pointsToSurf.Surface();
    if (bSplineSurf.IsNull()) {
        // std::cout << "Unable to build surface by points" << std::endl;
        return EXIT_FAILURE;
    }
 
    // std::cout << "Success!" << std::endl;
    return EXIT_SUCCESS;
}

void read_points(TColgp_Array2OfPnt& points) {
    std::ifstream file("points.csv");
    std::string line;

    int irow = 1, icol = 1;
    while (std::getline(file, line)) {
        std::stringstream linestream(line);
        std::string value;
        Standard_Real x, y, z;

        std::getline(linestream, value, ',');
        x = std::stod(value);
        std::getline(linestream, value, ',');
        y = std::stod(value);
        std::getline(linestream, value);
        z = std::stod(value);

        gp_Pnt pnt(x, y, z);
        // pnt.DumpJson(std::cerr);
        // std::cerr << std::endl;

        points.SetValue(irow, icol, pnt);

        icol = 1;
        ++irow;
    }
}


TEST_CASE("Benchmark GeomAPI_PointsToBSplineSurface", "[benchmark]") {
    BENCHMARK_ADVANCED("min=3, max=8, tol=0.01")(Catch::Benchmark::Chronometer meter) {
        TColgp_Array2OfPnt points(1, N_ROW, 1, N_COL);
        read_points(points);

        meter.measure([&points]() {
            BSplineSurfFitting(points, 3, 8, 0.01);
        });
    };

    BENCHMARK_ADVANCED("min=0, max=50, tol=0.01")(Catch::Benchmark::Chronometer meter) {
        TColgp_Array2OfPnt points(1, N_ROW, 1, N_COL);
        read_points(points);

        meter.measure([&points]() {
            BSplineSurfFitting(points, 0, 50, 0.01);
        });
    };

    BENCHMARK_ADVANCED("min=179, max=180, tol=0.01")(Catch::Benchmark::Chronometer meter) {
        TColgp_Array2OfPnt points(1, N_ROW, 1, N_COL);
        read_points(points);

        meter.measure([&points]() {
            BSplineSurfFitting(points, 179, 180, 0.01);
        });
    };

    BENCHMARK_ADVANCED("min=1000, max=1000, tol=0.01")(Catch::Benchmark::Chronometer meter) {
        TColgp_Array2OfPnt points(1, N_ROW, 1, N_COL);
        read_points(points);

        meter.measure([&points]() {
            BSplineSurfFitting(points, 1000, 1000, 0.01);
        });
    };

    BENCHMARK_ADVANCED("min=0, max=1, tol=0.01")(Catch::Benchmark::Chronometer meter) {
        TColgp_Array2OfPnt points(1, N_ROW, 1, N_COL);
        read_points(points);

        meter.measure([&points]() {
            BSplineSurfFitting(points, 0, 1, 0.01);
        });
    };
}
