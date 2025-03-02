#ifndef SHAPETOVOLUME_H
#define SHAPETOVOLUME_H

#if defined(_WIN32) && defined(_MSC_VER) // Microsoft Visual Studio Compiler
#elif (defined(__linux__) || defined(_WIN32)) && defined(__GNUC__) // GNU Compiler (gcc,g++) for Linux, Unix, and MinGW (Windows)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-Wdeprecated-copy"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#elif defined(__APPLE__) // Clang Compiler (Apple)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-Wint-in-bool-context"
#endif
#include <view/amkglcamera.h>
#if defined(_WIN32) && defined(_MSC_VER)
#elif (defined(__linux__) || defined(_WIN32)) && defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(__APPLE__)
#pragma GCC diagnostic pop
#endif

#include "picker/geometry/triangleplane.h"

#include <QVector>
#include <QPolygon>

class ShapeToVolume
{
public:
    /**
     * @brief Convert a polygon to a collection of triangle
     * @warning The polygon must have point ordered in clockwise !
     */
    static QVector<QPolygon> staticConvertPolygonToTriangle(const QPolygon &polygon);

    /**
     * @brief Convert a polygon to a collection of planes.
     * @warning The polygon must have point ordered in clockwise !
     */
    static QVector<TrianglePlane> staticTriangulatePolygonAndConvertItToPlanes(const QPolygon &polygon,
                                                                               const AMKglCamera &camera);

    /**
     * @brief Returns triangles transformed by the matrix
     */
    template<typename Scalar>
    static QVector<TrianglePlaneT<Scalar> > staticGetTransformedTriangles(const QVector<TrianglePlaneT<Scalar> > &triangles,
                                                                          const Eigen::Matrix4d &matrix)
    {
        int n = triangles.size();

        QVector<TrianglePlaneT<Scalar> > res(n);

        for(int i=0; i<n; ++i) {
            const TrianglePlaneT<Scalar> &tr = triangles[i];
            TrianglePlaneT<Scalar> &tRes = res[i];

            for(int j=0; j<3; ++j) {
                tRes.planes[j] = tr.planes[j].getTransformed(matrix);
            }
        }

        return res;
    }
    /**
     * @brief Returns triangles transformed by the matrix
     */
    template<typename Scalar>
    static QVector<PlaneT<Scalar> > staticGetTransformedPlanes(const QVector<PlaneT<Scalar> > &planes,
                                                               const Eigen::Matrix4d &matrix)
    {
        QVector<PlaneT<Scalar> > res;

        int n = planes.size();

        for(int i=0; i<n; ++i)
            res.append(planes[i].getTransformed(matrix));

        return res;
    }

    /**
     * @brief Convert a collection of planes to another collection with another scalar
     */
    template<typename NewScalar, typename Scalar>
    static QVector<PlaneT<NewScalar > > staticConvertPlaneCollectionTo(const QVector<PlaneT<Scalar > > &planes)
    {
        int size = planes.size();

        QVector<PlaneT<NewScalar > > pt(size);

        if(size > 0) {
            do {
                --size;
                pt[size] = planes[size].template cast<NewScalar >();
            } while(size != 0);
        }

        return pt;
    }

    /**
     * @brief Convert a collection of triangles to another collection with another scalar
     */
    template<typename NewScalar, typename Scalar>
    static QVector<TrianglePlaneT<NewScalar> > staticConvertTrianglePlaneCollectionTo(const QVector<TrianglePlaneT<Scalar> > &triangles)
    {
        int size = triangles.size();

        QVector<TrianglePlaneT<NewScalar> > tt(size);

        if(size > 0) {
            do {
                --size;
                tt[size] = triangles[size].template cast<NewScalar>();
            } while(size != 0);
        }

        return tt;
    }

    /**
     * @brief Convert a polygon to a collection of planes.
     * @warning The polygon must have point ordered in clockwise !
     */
    static QVector<Plane> staticConvertPolygonToPlanes(const QPolygon &polygon,
                                                       const AMKglCamera& camera);

    /**
     * @brief Convert a 2D point to a 3D line that begin at zNear of the camera and end on the zFar of the camera
     */
    static void staticConvert2DPointTo3DLine(const AMKglCamera &camera,
                                             const QPoint &pos,
                                             Eigen::Vector3d& nearV,
                                             Eigen::Vector3d& farV);

    /**
     * @brief Get the camera near and far plane
     * @param camera : camera to get plane
     * @param nearPlane : (out) near plane computed
     * @param farPlane :  (out)far plane computed
     */
    static void staticGetCameraPlane(const AMKglCamera &camera, Plane& nearPlane, Plane& farPlane);
};

#endif // SHAPETOVOLUME_H
