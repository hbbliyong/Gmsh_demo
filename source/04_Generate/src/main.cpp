#include <iostream>
#include "gmsh.h"

void generate_demo() {
    int rect = gmsh::model::occ::addRectangle(0, 0, 0, 1, 1, -1, 0.0);

    gmsh::model::occ::synchronize();
    gmsh::model::mesh::generate(2);
    // gmsh::model::mesh::recombine();
    gmsh::model::mesh::refine();
    gmsh::model::mesh::refine();
    gmsh::model::mesh::recombine();
    gmsh::model::mesh::refine();
}

void clear_demo() {
    int s1 = gmsh::model::occ::addRectangle(0, 0, 0, 1, 1, -1, 0.0);
    int s2 = gmsh::model::occ::addRectangle(1, 0, 0, 1, 1, -1, 0.0);

    gmsh::vectorpair out_dim_tags;
    std::vector<gmsh::vectorpair> out_dim;
    //去除共线
    gmsh::model::occ::fragment({{2, s1}}, {{2, s2}}, out_dim_tags, out_dim);
    gmsh::model::occ::synchronize();
    gmsh::model::mesh::generate(2);
    //全清
    //  gmsh::model::mesh::clear();

    //清除指定的tag
    gmsh::model::mesh::clear({{2, s2}});
}

void set_size_demo() {
    int s1 = gmsh::model::occ::addRectangle(0, 0, 0, 1, 1, -1, 0.0);
    gmsh::model::occ::synchronize();

    gmsh::model::mesh::setSize({{0, 1}, {0, 2}, {0, 3}, {0, 4}}, 0.2);
    //1处超级加密
    gmsh::model::mesh::setSize({{0, 1}}, 0.02);

    gmsh::model::mesh::generate(2);
}

void transfinite_demo() {
    int s1 = gmsh::model::occ::addRectangle(0, 1, 0, 1, 1, -1, 0.0);
    int s2 = gmsh::model::occ::addRectangle(1, 1, 0, 1, 1, -1, 0.0);
    int s3 = gmsh::model::occ::addRectangle(0, 0, 0, 2, 1, -1, 0.0);

    gmsh::vectorpair outDimTags;
    std::vector<gmsh::vectorpair> outDimTagsMap;
    gmsh::model::occ::fragment({{2, s1}, {2, s2}}, {{2, s3}}, outDimTags, outDimTagsMap);
gmsh::model::occ::synchronize();

gmsh::model::mesh::setTransfiniteCurve(1,5);
gmsh::model::mesh::setTransfiniteCurve(2,3);
gmsh::model::mesh::setTransfiniteCurve(3,3);
gmsh::model::mesh::setTransfiniteCurve(4,3);
gmsh::model::mesh::setTransfiniteCurve(5,3);

     gmsh::model::mesh::generate(2);
}

int main() {
    gmsh::initialize();
    //1
    //generate_demo();

    //2
    // clear_demo();

    //3
    //set_size_demo();

    //4
    transfinite_demo();


    // 可视化（可选）
    gmsh::fltk::run();
    gmsh::finalize();

    return 0;
}
