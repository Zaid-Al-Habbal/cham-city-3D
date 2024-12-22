//Use it for make a Cube(set the subdivision=1) or a ball of squares, see: https://www.songho.ca/opengl/gl_sphere.html
///////////////////////////////////////////////////////////////////////////////
// Cubesphere.h
// ============
// cube-based sphere dividing the spherical surface into 6 equal-area faces of
// a cube (+X, -X, +Y, -Y, +Z, -Z)
// If N=1, it is identical to a cube, which is inscribed in a sphere.
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2018-09-20
// UPDATED: 2024-09-06
///////////////////////////////////////////////////////////////////////////////

#ifndef GEOMETRY_CUBESPHERE_H
#define GEOMETRY_CUBESPHERE_H

#include <vector>
#include <map>
#include <cmath>

class Cubesphere
{
public:
    // ctor/dtor
    Cubesphere(float radius=1.0f, int subdivision=3, bool smooth=true);
    ~Cubesphere() {}

    // getters/setters
    float getRadius() const                 { return radius; }
    void setRadius(float radius);
    float getSideLength() const             { return radius * 2 / sqrt(3.0f); }
    void setSideLength(float side);
    int getSubdivision() const              { return subdivision; }
    void setSubdivision(int subdivision);
    bool getSmooth() const                  { return smooth; }
    void setSmooth(bool smooth);
    void reverseNormals();

    // for vertex data
    unsigned int getVertexCount() const     { return (unsigned int)vertices.size() / 3; }
    unsigned int getNormalCount() const     { return (unsigned int)normals.size() / 3; }
    unsigned int getTexCoordCount() const   { return (unsigned int)texCoords.size() / 2; }
    unsigned int getIndexCount() const      { return (unsigned int)indices.size(); }
    unsigned int getLineIndexCount() const  { return (unsigned int)lineIndices.size(); }
    unsigned int getTriangleCount() const   { return getIndexCount() / 3; }

    unsigned int getVertexSize() const      { return (unsigned int)vertices.size() * sizeof(float); }   // # of bytes
    unsigned int getNormalSize() const      { return (unsigned int)normals.size() * sizeof(float); }
    unsigned int getTexCoordSize() const    { return (unsigned int)texCoords.size() * sizeof(float); }
    unsigned int getIndexSize() const       { return (unsigned int)indices.size() * sizeof(unsigned int); }
    unsigned int getLineIndexSize() const   { return (unsigned int)lineIndices.size() * sizeof(unsigned int); }

    const float* getVertices() const        { return vertices.data(); }
    const float* getNormals() const         { return normals.data(); }
    const float* getTexCoords() const       { return texCoords.data(); }
    const unsigned int* getIndices() const  { return indices.data(); }
    const unsigned int* getLineIndices() const  { return lineIndices.data(); }

    // for interleaved vertices: V/N/T
    unsigned int getInterleavedVertexCount() const  { return getVertexCount(); }    // # of vertices
    unsigned int getInterleavedVertexSize() const   { return (unsigned int)interleavedVertices.size() * sizeof(float); }    // # of bytes
    int getInterleavedStride() const                { return interleavedStride; }   // should be 32 bytes
    const float* getInterleavedVertices() const     { return interleavedVertices.data(); }

    // for face
    unsigned int getVertexCountForFace() const  { return getVertexCount() / 6; }
    unsigned int getIndexCountForFace() const { return getIndexCount() / 6; }
    const float* getVerticesForFace(int faceId) const;
    const float* getNormalsForFace(int faceId) const;
    const float* getTexCoordsForFace(int faceId) const;
    const float* getInterleavedVerticesForFace(int faceId) const;
    const unsigned int* getIndicesForFace(int faceId) const { return indices.data(); }  // always the begining of index array

    // draw in VertexArray mode
    void draw() const;
    void drawLines(const float lineColor[4]) const;
    void drawWithLines(const float lineColor[4]) const;
    void drawFace(int faceId) const;    // draw only single face, valid ID is 0~5

    // debug
    void printSelf() const;

protected:

private:
    // static functions
    static void computeFaceNormal(const float v1[3], const float v2[3], const float v3[3], float normal[3]);
    static float computeScaleForLength(const float v[3], float length);
    static std::vector<float> getUnitPositiveX(unsigned int pointsPerRow);
    static void scaleVertex(float v[3], float scale);

    // member functions
    void clearArrays();
    //@@void updateRadius();
    void buildVerticesFlat();
    void buildVerticesSmooth();
    void buildInterleavedVertices();
    void addVertex(float x, float y, float z);
    void addVertices(const float v1[3], const float v2[3], const float v3[3], const float v4[3]);
    void addNormal(float nx, float ny, float nz);
    void addNormals(const float n1[3], const float n2[3], const float n3[3], const float n4[3]);
    void addTexCoord(float s, float t);
    void addTexCoords(const float t1[2], const float t2[2], const float t3[2], const float t4[2]);
    void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);

    // memeber vars
    float radius;                           // circumscribed radius
    int subdivision;                        // # of segments of each edge line
    bool smooth;
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texCoords;
    std::vector<unsigned int> indices;
    std::vector<unsigned int> lineIndices;

    // interleaved
    std::vector<float> interleavedVertices;
    int interleavedStride;                  // # of bytes to hop to the next vertex (should be 32 bytes)

    // for face
    unsigned int vertexCountPerRow;
    unsigned int vertexCountPerFace;
};

#endif
