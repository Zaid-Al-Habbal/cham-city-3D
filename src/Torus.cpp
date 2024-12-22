///////////////////////////////////////////////////////////////////////////////
// Torus.cpp
// =========
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

#ifdef _WIN32
#include <windows.h>    // include windows.h to avoid thousands of compile errors even though this class is not depending on Windows
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <iostream>
#include <iomanip>
#include <cmath>
#include "Torus.h"



// constants //////////////////////////////////////////////////////////////////
const int MIN_SECTOR_COUNT = 3;
const int MIN_SIDE_COUNT  = 2;



///////////////////////////////////////////////////////////////////////////////
// ctor
///////////////////////////////////////////////////////////////////////////////
Torus::Torus(float majorR, float minorR, int sectors, int sides, bool smooth, int up) : interleavedStride(32)
{
    set(majorR, minorR, sectors, sides, smooth, up);
}



///////////////////////////////////////////////////////////////////////////////
// setters
///////////////////////////////////////////////////////////////////////////////
void Torus::set(float majorR, float minorR, int sectors, int sides, bool smooth, int up)
{
    if(majorR > 0)
        this->majorRadius = majorR;
    if(minorR > 0)
        this->minorRadius = minorR;
    this->sectorCount = sectors;
    if(sectors < MIN_SECTOR_COUNT)
        this->sectorCount = MIN_SECTOR_COUNT;
    this->sideCount = sides;
    if(sides < MIN_SIDE_COUNT)
        this->sideCount = MIN_SIDE_COUNT;
    this->smooth = smooth;
    this->upAxis = up;
    if(up < 1 || up > 3)
        this->upAxis = 3;

    if(smooth)
        buildVerticesSmooth();
    else
        buildVerticesFlat();
}

void Torus::setMajorRadius(float majorRadius)
{
    if(majorRadius != this->majorRadius)
        set(majorRadius, minorRadius, sectorCount, sideCount, smooth, upAxis);
}

void Torus::setMinorRadius(float minorRadius)
{
    if(minorRadius != this->minorRadius)
        set(majorRadius, minorRadius, sectorCount, sideCount, smooth, upAxis);
}

void Torus::setSectorCount(int sectors)
{
    if(sectors != this->sectorCount)
        set(majorRadius, minorRadius, sectors, sideCount, smooth, upAxis);
}

void Torus::setSideCount(int sides)
{
    if(sides != this->sideCount)
        set(majorRadius, minorRadius, sectorCount, sides, smooth, upAxis);
}

void Torus::setSmooth(bool smooth)
{
    if(this->smooth == smooth)
        return;

    this->smooth = smooth;
    if(smooth)
        buildVerticesSmooth();
    else
        buildVerticesFlat();
}

void Torus::setUpAxis(int up)
{
    if(this->upAxis == up || up < 1 || up > 3)
        return;

    changeUpAxis(this->upAxis, up);
    this->upAxis = up;
}



///////////////////////////////////////////////////////////////////////////////
// flip the face normals to opposite directions
///////////////////////////////////////////////////////////////////////////////
void Torus::reverseNormals()
{
    std::size_t i, j;
    std::size_t count = normals.size();
    for(i = 0, j = 3; i < count; i+=3, j+=8)
    {
        normals[i]   *= -1;
        normals[i+1] *= -1;
        normals[i+2] *= -1;

        // update interleaved array
        interleavedVertices[j]   = normals[i];
        interleavedVertices[j+1] = normals[i+1];
        interleavedVertices[j+2] = normals[i+2];
    }

    // also reverse triangle windings
    unsigned int tmp;
    count = indices.size();
    for(i = 0; i < count; i+=3)
    {
        tmp = indices[i];
        indices[i]   = indices[i+2];
        indices[i+2] = tmp;
    }
}



///////////////////////////////////////////////////////////////////////////////
// print itself
///////////////////////////////////////////////////////////////////////////////
void Torus::printSelf() const
{
    std::cout << "===== Torus =====\n"
              << "  Major Radius: " << majorRadius << "\n"
              << "  Minor Radius: " << minorRadius << "\n"
              << "  Sector Count: " << sectorCount << "\n"
              << "    Side Count: " << sideCount << "\n"
              << "Smooth Shading: " << (smooth ? "true" : "false") << "\n"
              << "       Up Axis: " << (upAxis == 1 ? "X" : (upAxis == 2 ? "Y" : "Z")) << "\n"
              << "Triangle Count: " << getTriangleCount() << "\n"
              << "   Index Count: " << getIndexCount() << "\n"
              << "  Vertex Count: " << getVertexCount() << "\n"
              << "  Normal Count: " << getNormalCount() << "\n"
              << "TexCoord Count: " << getTexCoordCount() << std::endl;
}



///////////////////////////////////////////////////////////////////////////////
// draw a torus in VertexArray mode
// OpenGL RC must be set before calling it
///////////////////////////////////////////////////////////////////////////////
void Torus::draw() const
{
    // interleaved array
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(3, GL_FLOAT, interleavedStride, &interleavedVertices[0]);
    glNormalPointer(GL_FLOAT, interleavedStride, &interleavedVertices[3]);
    glTexCoordPointer(2, GL_FLOAT, interleavedStride, &interleavedVertices[6]);

    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, indices.data());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}



///////////////////////////////////////////////////////////////////////////////
// draw lines only
// the caller must set the line width before call this
///////////////////////////////////////////////////////////////////////////////
void Torus::drawLines(const float lineColor[4]) const
{
    // set line colour
    glColor4fv(lineColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   lineColor);

    // draw lines with VA
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices.data());

    glDrawElements(GL_LINES, (unsigned int)lineIndices.size(), GL_UNSIGNED_INT, lineIndices.data());

    glDisableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}



///////////////////////////////////////////////////////////////////////////////
// draw a torus surfaces and lines on top of it
// the caller must set the line width before call this
///////////////////////////////////////////////////////////////////////////////
void Torus::drawWithLines(const float lineColor[4]) const
{
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 1.0f); // move polygon backward
    this->draw();
    glDisable(GL_POLYGON_OFFSET_FILL);

    // draw lines with VA
    drawLines(lineColor);
}



///////////////////////////////////////////////////////////////////////////////
// dealloc vectors
///////////////////////////////////////////////////////////////////////////////
void Torus::clearArrays()
{
    std::vector<float>().swap(vertices);
    std::vector<float>().swap(normals);
    std::vector<float>().swap(texCoords);
    std::vector<unsigned int>().swap(indices);
    std::vector<unsigned int>().swap(lineIndices);
}



///////////////////////////////////////////////////////////////////////////////
// build vertices of torus with smooth shading using parametric equation
// x = (R + r * cos(u)) * cos(v) = R * cos(v) + r * cos(u) * cos(v)
// y = (R + r * cos(u)) * sin(v) = R * sin(v) + r * cos(u) * sin(v)
// z = r * sin(u)
// where u: side angle (-180 <= u <= 180)
//       v: sector angle (0 <= v <= 360)
///////////////////////////////////////////////////////////////////////////////
void Torus::buildVerticesSmooth()
{
    const float PI = acos(-1.0f);

    // clear memory of prev arrays
    clearArrays();

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz;                               // normal
    float lengthInv = 1.0f / minorRadius;           // to normalize normals
    float s, t;                                     // texCoord

    float sectorStep = 2 * PI / sectorCount;
    float sideStep = 2 * PI / sideCount;
    float sectorAngle, sideAngle;

    for(int i = 0; i <= sideCount; ++i)
    {
        // start the tube side from the inside where sideAngle = pi
        sideAngle = PI - i * sideStep;              // starting from pi to -pi
        xy = minorRadius * cosf(sideAngle);         // r * cos(u)
        z = minorRadius * sinf(sideAngle);          // r * sin(u)

        // add (sectorCount+1) vertices per side
        // the first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // tmp x and y to compute normal vector
            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);

            // add normalized vertex normal first
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            addNormal(nx, ny, nz);

            // shift x & y, and vertex position
            x += majorRadius * cosf(sectorAngle);   // (R + r * cos(u)) * cos(v)
            y += majorRadius * sinf(sectorAngle);   // (R + r * cos(u)) * sin(v)
            addVertex(x, y, z);

            // vertex tex coord between [0, 1]
            s = (float)j / sectorCount;
            t = (float)i / sideCount;
            addTexCoord(s, t);
        }
    }

    // indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    unsigned int k1, k2;
    for(int i = 0; i < sideCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current side
        k2 = k1 + sectorCount + 1;      // beginning of next side

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector
            addIndices(k1, k2, k1+1);   // k1---k2---k1+1
            addIndices(k1+1, k2, k2+1); // k1+1---k2---k2+1

            // vertical lines for all sides
            lineIndices.push_back(k1);
            lineIndices.push_back(k2);
            // horizontal lines for all sides
            lineIndices.push_back(k1);
            lineIndices.push_back(k1 + 1);
        }
    }

    // generate interleaved vertex array as well
    buildInterleavedVertices();

    // change up axis from Z-axis to the given
    if(this->upAxis != 3)
        changeUpAxis(3, this->upAxis);
}



///////////////////////////////////////////////////////////////////////////////
// generate vertices with flat shading
// each triangle is independent (no shared vertices)
///////////////////////////////////////////////////////////////////////////////
void Torus::buildVerticesFlat()
{
    const float PI = acos(-1.0f);

    // tmp vertex definition (x,y,z,s,t)
    struct Vertex
    {
        float x, y, z, s, t;
    };
    std::vector<Vertex> tmpVertices;

    float sectorStep = 2 * PI / sectorCount;
    float sideStep = 2 * PI / sideCount;
    float sectorAngle, sideAngle;

    // compute all vertices first, each vertex contains (x,y,z,s,t) except normal
    for(int i = 0; i <= sideCount; ++i)
    {
        // start the tube side from the inside where sideAngle = pi
        sideAngle = PI - i * sideStep;              // starting from pi to -pi
        float xy = majorRadius + minorRadius * cosf(sideAngle); // R + r * cos(u)
        float z = minorRadius * sinf(sideAngle);    // r * sin(u)

        // add (sectorCount+1) vertices per side
        // the first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            Vertex vertex;
            vertex.x = xy * cosf(sectorAngle);      // x = r * cos(u) * cos(v)
            vertex.y = xy * sinf(sectorAngle);      // y = r * cos(u) * sin(v)
            vertex.z = z;                           // z = r * sin(u)
            vertex.s = (float)j/sectorCount;        // s
            vertex.t = (float)i/sideCount;         // t
            tmpVertices.push_back(vertex);
        }
    }

    // clear memory of prev arrays
    clearArrays();

    Vertex v1, v2, v3, v4;                          // 4 vertex positions and tex coords
    std::vector<float> n;                           // 1 face normal

    int i, j, k, vi1, vi2;
    int index = 0;                                  // index for vertex
    for(i = 0; i < sideCount; ++i)
    {
        vi1 = i * (sectorCount + 1);                // index of tmpVertices
        vi2 = (i + 1) * (sectorCount + 1);

        for(j = 0; j < sectorCount; ++j, ++vi1, ++vi2)
        {
            // get 4 vertices per side
            //  v1--v3
            //  |    |
            //  v2--v4
            v1 = tmpVertices[vi1];
            v2 = tmpVertices[vi2];
            v3 = tmpVertices[vi1 + 1];
            v4 = tmpVertices[vi2 + 1];

            // store 2 triangles (quad) per side
            // put quad vertices: v1-v2-v3-v4
            addVertex(v1.x, v1.y, v1.z);
            addVertex(v2.x, v2.y, v2.z);
            addVertex(v3.x, v3.y, v3.z);
            addVertex(v4.x, v4.y, v4.z);

            // put tex coords of quad
            addTexCoord(v1.s, v1.t);
            addTexCoord(v2.s, v2.t);
            addTexCoord(v3.s, v3.t);
            addTexCoord(v4.s, v4.t);

            // put normal
            n = computeFaceNormal(v1.x,v1.y,v1.z, v2.x,v2.y,v2.z, v3.x,v3.y,v3.z);
            for(k = 0; k < 4; ++k)  // same normals for 4 vertices
            {
                addNormal(n[0], n[1], n[2]);
            }

            // put indices of quad (2 triangles)
            addIndices(index, index+1, index+2);
            addIndices(index+2, index+1, index+3);

            // indices for lines
            lineIndices.push_back(index);
            lineIndices.push_back(index+1);
            lineIndices.push_back(index);
            lineIndices.push_back(index+2);

            index += 4;     // for next
        }
    }

    // generate interleaved vertex array as well
    buildInterleavedVertices();

    // change up axis from Z-axis to the given
    if(this->upAxis != 3)
        changeUpAxis(3, this->upAxis);
}



///////////////////////////////////////////////////////////////////////////////
// generate interleaved vertices: V/N/T
// stride must be 32 bytes
///////////////////////////////////////////////////////////////////////////////
void Torus::buildInterleavedVertices()
{
    std::vector<float>().swap(interleavedVertices);

    std::size_t i, j;
    std::size_t count = vertices.size();
    for(i = 0, j = 0; i < count; i += 3, j += 2)
    {
        interleavedVertices.push_back(vertices[i]);
        interleavedVertices.push_back(vertices[i+1]);
        interleavedVertices.push_back(vertices[i+2]);

        interleavedVertices.push_back(normals[i]);
        interleavedVertices.push_back(normals[i+1]);
        interleavedVertices.push_back(normals[i+2]);

        interleavedVertices.push_back(texCoords[j]);
        interleavedVertices.push_back(texCoords[j+1]);
    }
}



///////////////////////////////////////////////////////////////////////////////
// transform vertex/normal (x,y,z) coords
// assume from/to values are validated: 1~3 and from != to
///////////////////////////////////////////////////////////////////////////////
void Torus::changeUpAxis(int from, int to)
{
    // initial transform matrix cols
    float tx[] = {1.0f, 0.0f, 0.0f};    // x-axis (left)
    float ty[] = {0.0f, 1.0f, 0.0f};    // y-axis (up)
    float tz[] = {0.0f, 0.0f, 1.0f};    // z-axis (forward)

    // X -> Y
    if(from == 1 && to == 2)
    {
        tx[0] =  0.0f; tx[1] =  1.0f;
        ty[0] = -1.0f; ty[1] =  0.0f;
    }
    // X -> Z
    else if(from == 1 && to == 3)
    {
        tx[0] =  0.0f; tx[2] =  1.0f;
        tz[0] = -1.0f; tz[2] =  0.0f;
    }
    // Y -> X
    else if(from == 2 && to == 1)
    {
        tx[0] =  0.0f; tx[1] = -1.0f;
        ty[0] =  1.0f; ty[1] =  0.0f;
    }
    // Y -> Z
    else if(from == 2 && to == 3)
    {
        ty[1] =  0.0f; ty[2] =  1.0f;
        tz[1] = -1.0f; tz[2] =  0.0f;
    }
    //  Z -> X
    else if(from == 3 && to == 1)
    {
        tx[0] =  0.0f; tx[2] = -1.0f;
        tz[0] =  1.0f; tz[2] =  0.0f;
    }
    // Z -> Y
    else
    {
        ty[1] =  0.0f; ty[2] = -1.0f;
        tz[1] =  1.0f; tz[2] =  0.0f;
    }

    std::size_t i, j;
    std::size_t count = vertices.size();
    float vx, vy, vz;
    float nx, ny, nz;
    for(i = 0, j = 0; i < count; i += 3, j += 8)
    {
        // transform vertices
        vx = vertices[i];
        vy = vertices[i+1];
        vz = vertices[i+2];
        vertices[i]   = tx[0] * vx + ty[0] * vy + tz[0] * vz;   // x
        vertices[i+1] = tx[1] * vx + ty[1] * vy + tz[1] * vz;   // y
        vertices[i+2] = tx[2] * vx + ty[2] * vy + tz[2] * vz;   // z

        // transform normals
        nx = normals[i];
        ny = normals[i+1];
        nz = normals[i+2];
        normals[i]   = tx[0] * nx + ty[0] * ny + tz[0] * nz;   // nx
        normals[i+1] = tx[1] * nx + ty[1] * ny + tz[1] * nz;   // ny
        normals[i+2] = tx[2] * nx + ty[2] * ny + tz[2] * nz;   // nz

        // trnasform interleaved array
        interleavedVertices[j]   = vertices[i];
        interleavedVertices[j+1] = vertices[i+1];
        interleavedVertices[j+2] = vertices[i+2];
        interleavedVertices[j+3] = normals[i];
        interleavedVertices[j+4] = normals[i+1];
        interleavedVertices[j+5] = normals[i+2];
    }
}



///////////////////////////////////////////////////////////////////////////////
// add single vertex to array
///////////////////////////////////////////////////////////////////////////////
void Torus::addVertex(float x, float y, float z)
{
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
}



///////////////////////////////////////////////////////////////////////////////
// add single normal to array
///////////////////////////////////////////////////////////////////////////////
void Torus::addNormal(float nx, float ny, float nz)
{
    normals.push_back(nx);
    normals.push_back(ny);
    normals.push_back(nz);
}



///////////////////////////////////////////////////////////////////////////////
// add single texture coord to array
///////////////////////////////////////////////////////////////////////////////
void Torus::addTexCoord(float s, float t)
{
    texCoords.push_back(s);
    texCoords.push_back(t);
}



///////////////////////////////////////////////////////////////////////////////
// add 3 indices to array
///////////////////////////////////////////////////////////////////////////////
void Torus::addIndices(unsigned int i1, unsigned int i2, unsigned int i3)
{
    indices.push_back(i1);
    indices.push_back(i2);
    indices.push_back(i3);
}



///////////////////////////////////////////////////////////////////////////////
// return face normal of a triangle v1-v2-v3
// if a triangle has no surface (normal length = 0), then return a zero vector
///////////////////////////////////////////////////////////////////////////////
std::vector<float> Torus::computeFaceNormal(float x1, float y1, float z1,  // v1
                                            float x2, float y2, float z2,  // v2
                                            float x3, float y3, float z3)  // v3
{
    const float EPSILON = 0.000001f;

    std::vector<float> normal(3, 0.0f);     // default return value (0,0,0)
    float nx, ny, nz;

    // find 2 edge vectors: v1-v2, v1-v3
    float ex1 = x2 - x1;
    float ey1 = y2 - y1;
    float ez1 = z2 - z1;
    float ex2 = x3 - x1;
    float ey2 = y3 - y1;
    float ez2 = z3 - z1;

    // cross product: e1 x e2
    nx = ey1 * ez2 - ez1 * ey2;
    ny = ez1 * ex2 - ex1 * ez2;
    nz = ex1 * ey2 - ey1 * ex2;

    // normalize only if the length is > 0
    float length = sqrtf(nx * nx + ny * ny + nz * nz);
    if(length > EPSILON)
    {
        // normalize
        float lengthInv = 1.0f / length;
        normal[0] = nx * lengthInv;
        normal[1] = ny * lengthInv;
        normal[2] = nz * lengthInv;
    }

    return normal;
}
