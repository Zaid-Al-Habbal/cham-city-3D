// use it to make shapes like ring, see: https://www.songho.ca/opengl/gl_torus.html
///////////////////////////////////////////////////////////////////////////////
// Torus.h
// =======
// Torus geometry for OpenGL with (majorR, minorR, sectors, sides) parameters
// The minimum # of sectors and sides are 2. If the sides=2, the shape is a
// disk with a hole in the ceter.
// - major radius(R): distance from the origin to the centre of the tube
// - minor radius(r): radius of the tube
// - sectors: # of sectors of the tube
// - sides: # of sides of the tube
// - smooth: smooth (default) or flat shading
// - up-axis: facing direction, X=1, Y=2, Z=3(default)
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2023-03-12
// UPDATED: 2024-07-19
///////////////////////////////////////////////////////////////////////////////

#ifndef GEOMETRY_TORUS_H
#define GEOMETRY_TORUS_H

#include <vector>

class Torus
{
public:
    // ctor/dtor
    Torus(float majorRadius=1.0f, float minorRadius=0.5f, int sectorCount=36, int sideCount=18, bool smooth=true, int up=3);
    ~Torus() {}

    // getters/setters
    float getMajorRadius() const            { return majorRadius; }
    float getMinorRadius() const            { return minorRadius; }
    int getSectorCount() const              { return sectorCount; }
    int getSideCount() const                { return sideCount; }
    int getUpAxis() const                   { return upAxis; }
    void set(float majorRadius, float minorRadius, int sectorCount, int sideCount, bool smooth=true, int up=3);
    void setMajorRadius(float radius);
    void setMinorRadius(float radius);
    void setSectorCount(int sectorCount);
    void setSideCount(int sideCount);
    void setSmooth(bool smooth);
    void setUpAxis(int up);
    void reverseNormals();

    // for vertex data
    unsigned int getVertexCount() const     { return (unsigned int)vertices.size() / 3; }
    unsigned int getNormalCount() const     { return (unsigned int)normals.size() / 3; }
    unsigned int getTexCoordCount() const   { return (unsigned int)texCoords.size() / 2; }
    unsigned int getIndexCount() const      { return (unsigned int)indices.size(); }
    unsigned int getLineIndexCount() const  { return (unsigned int)lineIndices.size(); }
    unsigned int getTriangleCount() const   { return getIndexCount() / 3; }
    unsigned int getVertexSize() const      { return (unsigned int)vertices.size() * sizeof(float); }
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

    // draw in VertexArray mode
    void draw() const;                                  // draw surface
    void drawLines(const float lineColor[4]) const;     // draw lines only
    void drawWithLines(const float lineColor[4]) const; // draw surface and lines

    // debug
    void printSelf() const;

protected:

private:
    // member functions
    void buildVerticesSmooth();
    void buildVerticesFlat();
    void buildInterleavedVertices();
    void changeUpAxis(int from, int to);
    void clearArrays();
    void addVertex(float x, float y, float z);
    void addNormal(float x, float y, float z);
    void addTexCoord(float s, float t);
    void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);
    std::vector<float> computeFaceNormal(float x1, float y1, float z1,
                                         float x2, float y2, float z2,
                                         float x3, float y3, float z3);

    // memeber vars
    float majorRadius;
    float minorRadius;
    int sectorCount;                        // # of sectors(rings)
    int sideCount;                          // # of sides
    bool smooth;
    int upAxis;                             // +X=1, +Y=2, +z=3 (default)
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texCoords;
    std::vector<unsigned int> indices;
    std::vector<unsigned int> lineIndices;

    // interleaved
    std::vector<float> interleavedVertices;
    int interleavedStride;                  // # of bytes to hop to the next vertex (should be 32 bytes)

};

#endif
