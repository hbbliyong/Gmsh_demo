#include <iostream>
#include "hello.h"
#include "gmsh.h"

int main() {
    gmsh::initialize();
    //01 通过点线组成矩形
    // gmsh::model::occ::addPoint(0.0f,0,0);
    // gmsh::model::occ::addPoint(1.0f,0,0);
    // gmsh::model::occ::addPoint(1.0f,1,0);
    // gmsh::model::occ::addPoint(0.0f,1,0);
    // gmsh::model::occ::addLine(1,2);
    // gmsh::model::occ::addLine(2,3);
    // gmsh::model::occ::addLine(3,4);
    // gmsh::model::occ::addLine(4,1);

    //02 直接使用矩形api
    // gmsh::model::occ::addRectangle(0.0, 0.0, 1.0, 1.0, 1);

    //03 生成圆盘
    gmsh::model::occ::addDisk(0, 0, 0, 1, 0.6);
    gmsh::model::occ::synchronize();
    gmsh::model::mesh::generate(2);
    // 可视化（可选）
    gmsh::fltk::run();
    gmsh::finalize();

    return 0;
}
