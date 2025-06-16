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
    gmsh::model::mesh::getNodes(nodeTags, coords, parametricCoords,
                                -1, -1, false, true);
    for (std::size_t i = 0; i < nodeTags.size(); i++) {
        std::cout << nodeTags[i] << " ";
        std::cout << coords[3 * i] << " " << coords[3 * i + 1] << " " << coords[3 * i + 2] << " " << std::endl;
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
    gmsh::model::mesh::getNodesByElementType(1, nodeTags, coords, parametricCoords
    );
    for (std::size_t i = 0; i < nodeTags.size(); i++) {
        std::cout << nodeTags[i] << " ";
        std::cout << coords[3 * i] << " " << coords[3 * i + 1] << " " << coords[3 * i + 2] << " " << std::endl;
    }
}

void create_extrude_demo() {
    int s1 = gmsh::model::occ::addDisk(0, 0, 0, 2, 2);
    gmsh::vectorpair outDimTags;
    gmsh::model::occ::extrude({{2, s1}}, 0, 0, 3, outDimTags);
    gmsh::model::occ::synchronize();

    gmsh::option::setNumber("Mesh.MeshSizeMin", 0.5);
    gmsh::option::setNumber("Mesh.MeshSizeMax", 0.5);

    // 设置表面网格算法为Frontal-Delaunay，尝试生成四边形
    gmsh::option::setNumber("Mesh.Algorithm", 8);
    // 设置重组所有二维面为四边形

    gmsh::option::setNumber("Mesh.RecombinationAlgorithm", 1); // 或2, 3, 4等，具体选择哪种重组算法
    gmsh::option::setNumber("Mesh.RecombineAll", 1);
    // 设置体网格算法为自动（尝试生成六面体）
    gmsh::option::setNumber("Mesh.Algorithm3D", 7); // 自动尝试六面体

    // 先生成二维网格（表面网格），然后生成三维网格
    gmsh::model::mesh::generate(2); // 生成表面网格（四边形）
    gmsh::model::mesh::generate(3); // 生成体网格（尝试六面体）
}

void test_set_option_number() {
    gmsh::model::add("t1");
    gmsh::model::occ::addBox(1, 1, 1, 1, 1, 1);
    gmsh::model::occ::synchronize();
    gmsh::vectorpair outDimTags;
    gmsh::model::getEntities(outDimTags, 0);
    gmsh::model::mesh::setSize(outDimTags, 0.05);
    gmsh::option::setNumber("Mesh.Algorithm3D", 1);
    gmsh::model::mesh::generate(3);
}

void set_field() {
    //https://blog.csdn.net/qq_74083422/article/details/134760424
    gmsh::model::add("filed");
    float lc = 0.15;

    gmsh::model::occ::addRectangle(0, 0, 0, 1, 1, 1);
    gmsh::model::occ::synchronize();
    //=========================================Box field==========
    //Box field
    gmsh::model::mesh::field::add("Box", 1); //定义box尺寸场，标号1

    gmsh::model::mesh::field::setNumber(1, "VIn", lc / 15);
    gmsh::model::mesh::field::setNumber(1, "VOut", lc);
    gmsh::model::mesh::field::setNumber(1, "XMin", 0.4);
    gmsh::model::mesh::field::setNumber(1, "YMin", 0.4);
    gmsh::model::mesh::field::setNumber(1, "XMax", 0.6);
    gmsh::model::mesh::field::setNumber(1, "YMax", 0.6);
    gmsh::model::mesh::field::setNumber(1, "Thickness", 0.3);
    //gmsh::model::mesh::field::setAsBackgroundMesh(1);
    //==================================================================

    //=========================Distance Threshold===========
    gmsh::model::mesh::field::add("Distance", 2);
    std::vector<double> pointLists{1};
    gmsh::model::mesh::field::setNumbers(2, "PointsList", pointLists);
    std::vector<double> curvesList{2};
    gmsh::model::mesh::field::setNumbers(2, "CurvesList", curvesList);
    gmsh::model::mesh::field::setNumber(2, "Sampling", 100);

    gmsh::model::mesh::field::add("Threshold", 3);
    gmsh::model::mesh::field::setNumber(3, "InField", 2); // 引用 Distance 字段
    gmsh::model::mesh::field::setNumber(3, "SizeMin", lc / 30);
    gmsh::model::mesh::field::setNumber(3, "SizeMax", lc);
    gmsh::model::mesh::field::setNumber(3, "DistMin", 0.15);
    gmsh::model::mesh::field::setNumber(3, "DistMax", 0.5);

    //gmsh::model::mesh::field::setAsBackgroundMesh(3);

    //===================================================================

    //==============MathEval 尺寸场，可以直接通过输入数学函数作为尺寸场生成网格====
    gmsh::model::mesh::field::add("MathEval",4);
    gmsh::model::mesh::field::setString(4, "F","Cos(4*3.14*x) * Sin(4*3.14*y) / 10 + 0.101");
    //gmsh::model::mesh::field::setAsBackgroundMesh(4);

    /*
     *若我们定义了多种尺寸场，还可以使用 Min 尺寸场将所有尺寸场整合到一起,如果不进行整合的话，只有最后一个起作用
     *Min 尺寸场可将其他尺寸场作为输入，取所有尺寸场的网格尺寸最小值
     */

    gmsh::model::mesh::field::add("Min",5);
    gmsh::model::mesh::field::setNumbers(5, "FieldsList", {1,3,4});
   gmsh::model::mesh::field::setAsBackgroundMesh(5);


    gmsh::model::mesh::generate(2);
}

int main() {
    gmsh::initialize();
    //1
    //test_set_option_number();

    //2
    //create_extrude_demo();

    //3
    set_field();

    //4
    // transfinite_demo();


    // 可视化（可选）
    gmsh::fltk::run();
    gmsh::finalize();

    return 0;
}
