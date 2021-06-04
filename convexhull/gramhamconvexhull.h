#ifndef GRAMHAMCONVEXHULL_H
#define GRAMHAMCONVEXHULL_H

#include "point.h"

#include <vector>
/**
 * @brief The GramhamConvexhull class
 *      Gramham ɨ�跨
 ***/
namespace ConvexHull {

using namespace Shape2D;

class GramhamConvexhull
{
public:
    GramhamConvexhull(const Path2D& path);

    //����͹�������ؽ��
    Path2D execute();

    //���
    Path2D result();

    //
    Path2D sortedPoints();

private:

    //1. �ҵ�y��С��������ֶ��ymin, ѡȡ���е�xmin, ��Ϊ�׵�   n
    //2. Angle-X�Ƕ�����   nlogn
    void sort();

    //2. ��˳����͹��    n
    void loop();

    //return true if cross(p0p1, p1p2) > 0 , otherwise return false
    //�ж������Ƿ���ʱ��
    // a. ��ʱ�룬��p1, �ݶ�Ϊ͹����
    // b. ������|p0p1| > |p0p2| �ݶ�Ϊ͹����
    //������
    bool judge(const Shape2D::Point2D& p0, const Shape2D::Point2D& p1, const Shape2D::Point2D& p2) const;

private:
    Path2D convexHull;
    Path2D points;
};

}

#endif // GRAMHAMCONVEXHULL_H
