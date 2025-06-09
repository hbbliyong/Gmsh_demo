#include <iostream>
#include "gmsh.h"

int main() {
    gmsh::initialize();
    //以下无法生成网格，点线重合，生成网格报错： PLC Error:  A segment and a facet intersect at point
    // int p1 = gmsh::model::occ::addPoint(0.0f, 0, 0);
    // int p2 = gmsh::model::occ::addPoint(1.0f, 0, 0);
    // int p3 = gmsh::model::occ::addPoint(1.0f, 1, 0);
    // int p4 = gmsh::model::occ::addPoint(0.0f, 1, 0);
    // int p5 = gmsh::model::occ::addPoint(0, 0, 1);
    // int p6 = gmsh::model::occ::addPoint(1, 0, 1);
    // int p7 = gmsh::model::occ::addPoint(1, 1, 1);
    // int p8 = gmsh::model::occ::addPoint(0, 1, 1);
    //
    // int s1 = gmsh::model::occ::addBSplineSurface({p1, p2, p4, p3}, 2);
    // int s2 = gmsh::model::occ::addBSplineSurface({p5, p6, p8, p7}, 2);
    // int s3 = gmsh::model::occ::addBSplineSurface({p1, p2, p5, p6}, 2);
    // int s4 = gmsh::model::occ::addBSplineSurface({p3, p4, p7, p8}, 2);
    // int s5 = gmsh::model::occ::addBSplineSurface({p1, p4, p5, p8}, 2);
    // int s6 = gmsh::model::occ::addBSplineSurface({p2, p3, p6, p7}, 2);
    //
    // int sl1 = gmsh::model::occ::addSurfaceLoop({s1, s2, s3, s4, s5, s6});
    // gmsh::model::occ::addVolume({sl1});

    //CASE 2
    // 1. 定义 8 个点（立方体顶点）
    std::vector<std::vector<double>> points = {
        {0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0},  // 底面
        {0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 1, 1}   // 顶面
    };
    std::vector<int> pointTags;
    for (const auto &p : points) {
        pointTags.push_back(gmsh::model::occ::addPoint(p[0], p[1], p[2]));
    }

    // 2. 定义 12 条边
    std::vector<std::pair<int, int>> edges = {
        {1, 2}, {2, 3}, {3, 4}, {4, 1},  // 底面
        {5, 6}, {6, 7}, {7, 8}, {8, 5},  // 顶面
        {1, 5}, {2, 6}, {3, 7}, {4, 8}   // 侧面
    };
    std::vector<int> lineTags;
    for (const auto &e : edges) {
        lineTags.push_back(gmsh::model::occ::addLine(
            pointTags[e.first - 1], pointTags[e.second - 1]));
    }

    // 3. 定义 6 个面
    std::vector<std::vector<int>> faceLoops = {
        {1, 2, 3, 4},     // 底面
        {5, 6, 7, 8},     // 顶面
        {1, 10, -5, -9},  // 前面
        {2, 11, -6, -10}, // 右面
        {3, 12, -7, -11}, // 后面
        {4, 9, -8, -12}   // 左面
    };
    std::vector<int> surfaceTags;
    for (const auto &loop : faceLoops) {
        int loopTag = gmsh::model::occ::addCurveLoop(loop);
        surfaceTags.push_back(gmsh::model::occ::addPlaneSurface({loopTag}));
    }

    // 4. 定义体
    int surfaceLoopTag = gmsh::model::occ::addSurfaceLoop(surfaceTags);
    gmsh::model::occ::addVolume({surfaceLoopTag});
    gmsh::model::occ::synchronize();
    gmsh::model::mesh::generate(3);
    // 可视化（可选）
    gmsh::fltk::run();
    gmsh::finalize();

    return 0;
}
