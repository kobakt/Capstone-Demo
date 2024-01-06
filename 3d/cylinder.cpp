#include "cylinder.h"

Cylinder::Cylinder()
{
    updateData();
}

void Cylinder::setNormals(bool enable)
{
    if (m_hasNormals == enable)
        return;

    m_hasNormals = enable;
    emit normalsChanged();
    updateData();
    update();
}

void Cylinder::setNormalXY(float xy)
{
    if (m_normalXY == xy)
        return;

    m_normalXY = xy;
    emit normalXYChanged();
    updateData();
    update();
}

void Cylinder::setUV(bool enable)
{
    if (m_hasUV == enable)
        return;

    m_hasUV = enable;
    emit uvChanged();
    updateData();
    update();
}

void Cylinder::setUVAdjust(float f)
{
    if (m_uvAdjust == f)
        return;

    m_uvAdjust = f;
    emit uvAdjustChanged();
    updateData();
    update();
}

// Example code provided by Qt:
// a triangle, front face = counter-clockwise
//    *p++ = -1.0f; *p++ = -1.0f; *p++ = 0.0f;
//    if (m_hasNormals) {
//        *p++ = m_normalXY; *p++ = m_normalXY; *p++ = 1.0f;
//    }
//    if (m_hasUV) {
//        *p++ = 0.0f + m_uvAdjust; *p++ = 0.0f + m_uvAdjust;
//    }

//    *p++ = 1.0f; *p++ = -1.0f; *p++ = 0.0f;
//    if (m_hasNormals) {
//        *p++ = m_normalXY; *p++ = m_normalXY; *p++ = 1.0f;
//    }
//    if (m_hasUV) {
//        *p++ = 1.0f - m_uvAdjust; *p++ = 0.0f + m_uvAdjust;
//    }

//    *p++ = 0.0f; *p++ = 1.0f; *p++ = 0.0f;
//    if (m_hasNormals) {
//        *p++ = m_normalXY; *p++ = m_normalXY; *p++ = 1.0f;
//    }
//    if (m_hasUV) {
//        *p++ = 1.0f - m_uvAdjust; *p++ = 1.0f - m_uvAdjust;
//    }



void Cylinder::addPoint(float*& p, QVector3D point) {
    *p++ = point.x(); *p++ = point.y(); *p++ = point.z();
    if (m_hasNormals) {
        *p++ = m_normalXY; *p++ = m_normalXY; *p++ = 1.0f;
    }
    if (m_hasUV) {
        *p++ = 0.0f + m_uvAdjust; *p++ = 0.0f + m_uvAdjust;
    }
}

void Cylinder::addTriangle(float*& p, QVector3D a, QVector3D b, QVector3D c) {
    addPoint(p, a);
    addPoint(p, b);
    addPoint(p, c);
}

void Cylinder::addRectangle(float*& p, QVector3D a, QVector3D b, QVector3D c, QVector3D d) {
    addTriangle(p, a, b, c);
    addTriangle(p, a, c, d);
}

void Cylinder::updateData()
{
    clear();

    int stride = 3 * sizeof(float);
    if (m_hasNormals)
        stride += 3 * sizeof(float);
    if (m_hasUV)
        stride += 2 * sizeof(float);

    int numOfPoints = 4;

    QByteArray vertexData(numOfPoints * stride, Qt::Initialization::Uninitialized);
    float *p = reinterpret_cast<float *>(vertexData.data());

    // Top Right
    QVector3D topRight = QVector3D(1, 1, 0);
    // Top Left
    QVector3D topLeft = QVector3D(1,-1,0);
    // Bottom Left
    QVector3D botLeft = QVector3D(-1,-1,0);
    // Bottom Right
    QVector3D botRight = QVector3D(-1,1,0);
    //addRectangle(p, a, b, c, d);
    // Order doesn't matter because its set
    addPoint(p, topLeft);
    addPoint(p, botLeft);
    addPoint(p, topRight);
    addPoint(p, botRight);


    setVertexData(vertexData);
    setStride(stride);
    setBounds(QVector3D(-1.0f, -1.0f, 0.0f), QVector3D(+1.0f, +1.0f, 0.0f));

    /*add some index stuff here.
    I think each index refers to a set of 3 triangles.
    It allows you to save space by doing back to back triangles that share 1 or more points.
    */
    QByteArray indexData(
//                        2 * sizeof(ushort),
                         2 * 3 * sizeof(ushort) /* 2 triangles, 3 vertices each*/,
                         Qt::Initialization::Uninitialized);
    quint16 *i = reinterpret_cast<ushort *>(indexData.data());
    // value refers to index of points above.
    // set of three creates triangle face.
    // order matters here,
    // a face will only have one side.
    // so clockwise and anticlockwise will set different sides
    // although, when we actually render ariaplane, we'll want it double sided, so I guess we'll set twice going both directions
    *i++ = 0; *i++ = 2; *i++ = 1;
    *i++ = 1; *i++ = 2; *i++ = 3;
//    *i++ = 0; *i++ = 1;
    setIndexData(indexData);

    setPrimitiveType(QQuick3DGeometry::PrimitiveType::Triangles);

    addAttribute(QQuick3DGeometry::Attribute::PositionSemantic,
                 0,
                 QQuick3DGeometry::Attribute::F32Type);
    addAttribute(QQuick3DGeometry::Attribute::IndexSemantic,
                 0,
                 QQuick3DGeometry::Attribute::U16Type);

    if (m_hasNormals) {
        addAttribute(QQuick3DGeometry::Attribute::NormalSemantic,
                     3 * sizeof(float),
                     QQuick3DGeometry::Attribute::F32Type);
    }

    if (m_hasUV) {
        addAttribute(QQuick3DGeometry::Attribute::TexCoordSemantic,
                     m_hasNormals ? 6 * sizeof(float) : 3 * sizeof(float),
                     QQuick3DGeometry::Attribute::F32Type);
    }
}
