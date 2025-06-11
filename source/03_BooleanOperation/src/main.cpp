#include <iostream>
#include "gmsh.h"

int main() {
    gmsh::initialize();

 int v1=gmsh::model::occ::addBox(0,0,0,1,1,1);
    int v2=gmsh::model::occ::addCylinder(0,0,0,0,0,1,1);

    gmsh::vectorpair out_dim_tags{};
    std::vector<gmsh::vectorpair> out_dim_tags_map{};

    gmsh::model::occ::fuse(
        {{3,v1}},
        {{3,v2}},
        out_dim_tags,
        out_dim_tags_map);


    // gmsh::model::occ::intersect(
    //    {{3,v1}},
    //    {{3,v2}},
    //    out_dim_tags,
    //    out_dim_tags_map);

    // gmsh::model::occ::cut(
    //    {{3,v1}},
    //    {{3,v2}},
    //    out_dim_tags,
    //    out_dim_tags_map);

    gmsh::model::occ::synchronize();
    // gmsh::model::mesh::generate(3);
    // 可视化（可选）
    gmsh::fltk::run();
    gmsh::finalize();

    return 0;
}
