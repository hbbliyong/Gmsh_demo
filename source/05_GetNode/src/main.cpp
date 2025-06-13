#include <iostream>
#include "gmsh.h"


void get_nodes_demo() {
    int s1 = gmsh::model::occ::addRectangle(0, 0, 0, 1, 1, -1, 0.0);
    gmsh::model::occ::synchronize();

    gmsh::model::mesh::setSize({{0, 1}, {0, 2}, {0, 3}, {0, 4}}, 0.333);
    //1处超级加密
    // gmsh::model::mesh::setSize({{0, 1}}, 0.02);

    gmsh::model::mesh::generate(2);

    std::vector<std::size_t> nodeTags{};
    std::vector<double> coords{};
    std::vector<double> parametricCoords{};
    gmsh::model::mesh::getNodes(nodeTags,coords,parametricCoords,
        -1,-1,false,true);
    for (std::size_t i = 0; i < nodeTags.size(); i++) {
        std::cout << nodeTags[i] << " ";
        std::cout << coords[3*i] << " "<< coords[3*i+1] << " "<< coords[3*i+2] << " "<< std::endl;
    }
}
void get_nodes_by_element_type_demo() {
    int s1 = gmsh::model::occ::addRectangle(0, 0, 0, 1, 1, -1, 0.0);
    gmsh::model::occ::synchronize();

    gmsh::model::mesh::setSize({{0, 1}, {0, 2}, {0, 3}, {0, 4}}, 0.333);
    //1处超级加密
    // gmsh::model::mesh::setSize({{0, 1}}, 0.02);

    gmsh::model::mesh::generate(2);

    std::vector<std::size_t> nodeTags{};
    std::vector<double> coords{};
    std::vector<double> parametricCoords{};
    gmsh::model::mesh::getNodesByElementType(1,nodeTags,coords,parametricCoords
        );
    for (std::size_t i = 0; i < nodeTags.size(); i++) {
        std::cout << nodeTags[i] << " ";
        std::cout << coords[3*i] << " "<< coords[3*i+1] << " "<< coords[3*i+2] << " "<< std::endl;
    }
}



int main() {
    gmsh::initialize();
    //1
    //generate_demo();

    //2
    // clear_demo();

    //3
    get_nodes_by_element_type_demo();

    //4
    // transfinite_demo();


    // 可视化（可选）
    gmsh::fltk::run();
    gmsh::finalize();

    return 0;
}
