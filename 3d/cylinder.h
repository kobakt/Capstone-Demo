#ifndef CYLINDER_H
#define CYLINDER_H

#include <QQuick3DGeometry>
#include <QVector3D>
#include <QtQML>

class Cylinder : public QQuick3DGeometry
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool normals READ normals WRITE setNormals NOTIFY normalsChanged)
    Q_PROPERTY(float normalXY READ normalXY WRITE setNormalXY NOTIFY normalXYChanged)
    Q_PROPERTY(bool uv READ uv WRITE setUV NOTIFY uvChanged)
    Q_PROPERTY(float uvAdjust READ uvAdjust WRITE setUVAdjust NOTIFY uvAdjustChanged)
public:
    Cylinder();
    bool normals() const { return m_hasNormals; }
    void setNormals(bool enable);

    float normalXY() const { return m_normalXY; }
    void setNormalXY(float xy);

    bool uv() const { return m_hasUV; }
    void setUV(bool enable);

    float uvAdjust() const { return m_uvAdjust; }
    void setUVAdjust(float f);
signals:
    void normalsChanged();
    void normalXYChanged();
    void uvChanged();
    void uvAdjustChanged();
private:
    void addPoint(float*& p, QVector3D point);
    void addTriangle(float*& p, QVector3D a, QVector3D b, QVector3D c);
    void addRectangle(float*& p, QVector3D a, QVector3D b, QVector3D c, QVector3D d);
    void updateData();
    bool m_hasNormals = false;
    float m_normalXY = 0.0f;
    bool m_hasUV = false;
    float m_uvAdjust = 0.0f;
};

#endif // CYLINDER_H
