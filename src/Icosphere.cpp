///////////////////////////////////////////////////////////////////////////////
// Icosphere.cpp
// =============
// Polyhedron subdividing the edge lines of icosahedron (20 tris) to N segments
// The icosphere with N=2 (default) has 80 triangles by subdividing a triangle
// of icosahedron into 4 triangles. If N=1, it is identical to icosahedron.
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2018-07-23
// UPDATED: 2024-09-05
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
#include "Icosphere.h"



// constants //////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
// ctor
///////////////////////////////////////////////////////////////////////////////
Icosphere::Icosphere(float radius, int sub, bool smooth) : radius(radius), subdivision(sub), smooth(smooth), interleavedStride(32)
{
    if(smooth)
        buildVerticesSmooth();
    else
        buildVerticesFlat();
}



///////////////////////////////////////////////////////////////////////////////
// setters
///////////////////////////////////////////////////////////////////////////////
void Icosphere::setRadius(float radius)
{
    this->radius = radius;
    updateRadius(); // update vertex positions only
}

void Icosphere::setSubdivision(int iteration)
{
    this->subdivision = iteration;
    // rebuild vertices
    if(smooth)
        buildVerticesSmooth();
    else
        buildVerticesFlat();
}

void Icosphere::setSmooth(bool smooth)
{
    if(this->smooth == smooth)
        return;

    this->smooth = smooth;
    if(smooth)
        buildVerticesSmooth();
    else
        buildVerticesFlat();
}



///////////////////////////////////////////////////////////////////////////////
// flip the face normals to opposite directions
///////////////////////////////////////////////////////////////////////////////
void Icosphere::reverseNormals()
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



//////////////////////////////////////////////////////////////////////////////
// print itself
///////////////////////////////////////////////////////////////////////////////
void Icosphere::printSelf() const
{

    std::cout << "===== Icosphere =====\n"
              << "        Radius: " << radius << "\n"
              << "   Subdivision: " << subdivision << "\n"
              << "    Smoothness: " << (smooth ? "true" : "false") << "\n"
              << "Triangle Count: " << getTriangleCount() << "\n"
              << "   Index Count: " << getIndexCount() << "\n"
              << "  Vertex Count: " << getVertexCount() << "\n"
              << "  Normal Count: " << getNormalCount() << "\n"
              << "TexCoord Count: " << getTexCoordCount() << std::endl;
}



///////////////////////////////////////////////////////////////////////////////
// draw a icosphere in VertexArray mode
// OpenGL RC must be set before calling it
///////////////////////////////////////////////////////////////////////////////
void Icosphere::draw() const
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
void Icosphere::drawLines(const float lineColor[4]) const
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
// draw a icosphere surfaces and lines on top of it
// the caller must set the line width before call this
///////////////////////////////////////////////////////////////////////////////
void Icosphere::drawWithLines(const float lineColor[4]) const
{
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 1.0f); // move polygon backward
    this->draw();
    glDisable(GL_POLYGON_OFFSET_FILL);

    // draw lines with VA
    drawLines(lineColor);
}



///////////////////////////////////////////////////////////////////////////////
// update vertex positions only
///////////////////////////////////////////////////////////////////////////////
void Icosphere::updateRadius()
{
    float scale = computeScaleForLength(&vertices[0], radius);

    std::size_t i, j;
    std::size_t count = vertices.size();
    for(i = 0, j = 0; i < count; i += 3, j += 8)
    {
        vertices[i]   *= scale;
        vertices[i+1] *= scale;
        vertices[i+2] *= scale;

        // for interleaved array
        interleavedVertices[j]   *= scale;
        interleavedVertices[j+1] *= scale;
        interleavedVertices[j+2] *= scale;
    }
}



///////////////////////////////////////////////////////////////////////////////
// compute 12 vertices of icosahedron using spherical coordinates
// The north pole is at (0, 0, r) and the south pole is at (0,0,-r).
// 5 vertices are placed by rotating 72 deg at elevation 26.57 deg (=atan(1/2))
// 5 vertices are placed by rotating 72 deg at elevation -26.57 deg
///////////////////////////////////////////////////////////////////////////////
std::vector<float> Icosphere::computeIcosahedronVertices()
{
    const float PI = acos(-1.0f);
    const float H_ANGLE = PI / 180 * 72;    // 72 degree = 360 / 5
    const float V_ANGLE = atanf(1.0f / 2);  // elevation = 26.565 degree

    std::vector<float> vertices(12 * 3);    // 12 vertices
    int i1, i2;                             // indices
    float z, xy;                            // coords
    float hAngle1 = -PI / 2 - H_ANGLE / 2;  // start from -126 deg at 2nd row
    float hAngle2 = -PI / 2;                // start from -90 deg at 3rd row

    // the first top vertex (0, 0, r)
    vertices[0] = 0;
    vertices[1] = 0;
    vertices[2] = radius;

    // 10 vertices at 2nd and 3rd rows
    for(int i = 1; i <= 5; ++i)
    {
        i1 = i * 3;         // for 2nd row
        i2 = (i + 5) * 3;   // for 3rd row

        z = radius * sinf(V_ANGLE);             // elevaton
        xy = radius * cosf(V_ANGLE);

        vertices[i1] = xy * cosf(hAngle1);      // x
        vertices[i2] = xy * cosf(hAngle2);
        vertices[i1 + 1] = xy * sinf(hAngle1);  // x
        vertices[i2 + 1] = xy * sinf(hAngle2);
        vertices[i1 + 2] = z;                   // z
        vertices[i2 + 2] = -z;

        // next horizontal angles
        hAngle1 += H_ANGLE;
        hAngle2 += H_ANGLE;
    }

    // the last bottom vertex (0, 0, -r)
    i1 = 11 * 3;
    vertices[i1] = 0;
    vertices[i1 + 1] = 0;
    vertices[i1 + 2] = -radius;

    return vertices;
}



///////////////////////////////////////////////////////////////////////////////
// generate vertices with flat shading
// each triangle is independent (no shared vertices)
///////////////////////////////////////////////////////////////////////////////
void Icosphere::buildVerticesFlat()
{
    //const float S_STEP = 1 / 11.0f;         // horizontal texture step
    //const float T_STEP = 1 / 3.0f;          // vertical texture step
    const float S_STEP = 186 / 2048.0f;     // horizontal texture step
    const float T_STEP = 322 / 1024.0f;     // vertical texture step

    // compute 12 vertices of icosahedron
    std::vector<float> tmpVertices = computeIcosahedronVertices();

    // clear memory of prev arrays
    std::vector<float>().swap(vertices);
    std::vector<float>().swap(normals);
    std::vector<float>().swap(texCoords);
    std::vector<unsigned int>().swap(indices);
    std::vector<unsigned int>().swap(lineIndices);

    const float *v0, *v1, *v2, *v3, *v4, *v11;          // vertex positions
    float n[3];                                         // face normal
    float t0[2], t1[2], t2[2], t3[2], t4[2], t11[2];    // texCoords
    unsigned int index = 0;

    // compute 20 tiangles of icosahedron first
    v0 = &tmpVertices[0];       // 1st vertex (north pole)
    v11 = &tmpVertices[11 * 3]; // 12th vertex (south pole)
    for(int i = 1; i <= 5; ++i)
    {
        // 4 vertices in the 2nd row
        v1 = &tmpVertices[i * 3];
        if(i < 5)
            v2 = &tmpVertices[(i + 1) * 3];
        else
            v2 = &tmpVertices[3];

        v3 = &tmpVertices[(i + 5) * 3];
        if((i + 5) < 10)
            v4 = &tmpVertices[(i + 6) * 3];
        else
            v4 = &tmpVertices[6 * 3];

        // texture coords
        t0[0] = (2 * i - 1) * S_STEP;   t0[1] = 0;
        t1[0] = (2 * i - 2) * S_STEP;   t1[1] = T_STEP;
        t2[0] = (2 * i - 0) * S_STEP;   t2[1] = T_STEP;
        t3[0] = (2 * i - 1) * S_STEP;   t3[1] = T_STEP * 2;
        t4[0] = (2 * i + 1) * S_STEP;   t4[1] = T_STEP * 2;
        t11[0]= 2 * i * S_STEP;         t11[1]= T_STEP * 3;

        // add a triangle in 1st row
        Icosphere::computeFaceNormal(v0, v1, v2, n);
        addVertices(v0, v1, v2);
        addNormals(n, n, n);
        addTexCoords(t0, t1, t2);
        addIndices(index, index+1, index+2);

        // add 2 triangles in 2nd row
        Icosphere::computeFaceNormal(v1, v3, v2, n);
        addVertices(v1, v3, v2);
        addNormals(n, n, n);
        addTexCoords(t1, t3, t2);
        addIndices(index+3, index+4, index+5);

        Icosphere::computeFaceNormal(v2, v3, v4, n);
        addVertices(v2, v3, v4);
        addNormals(n, n, n);
        addTexCoords(t2, t3, t4);
        addIndices(index+6, index+7, index+8);

        // add a triangle in 3rd row
        Icosphere::computeFaceNormal(v3, v11, v4, n);
        addVertices(v3, v11, v4);
        addNormals(n, n, n);
        addTexCoords(t3, t11, t4);
        addIndices(index+9, index+10, index+11);

        // add 6 edge lines per iteration
        //  i
        //  /   /   /   /   /       : (i, i+1)                              //
        // /__ /__ /__ /__ /__                                              //
        // \  /\  /\  /\  /\  /     : (i+3, i+4), (i+3, i+5), (i+4, i+5)    //
        //  \/__\/__\/__\/__\/__                                            //
        //   \   \   \   \   \      : (i+9,i+10), (i+9, i+11)               //
        //    \   \   \   \   \                                             //
        addLineIndices(index, index+1);
        addLineIndices(index+3, index+4);
        addLineIndices(index+3, index+5);
        addLineIndices(index+4, index+5);
        addLineIndices(index+9, index+10);
        addLineIndices(index+9, index+11);

        // next index
        index += 12;
    }

    // subdivide icosahedron
    subdivideVerticesFlat();

    // generate interleaved vertex array as well
    buildInterleavedVertices();
}



///////////////////////////////////////////////////////////////////////////////
// generate vertices with smooth shading
// NOTE: The north and south pole vertices cannot be shared for smooth shading
// because they have same position and normal, but different texcoords per face
// And, the first vertex on each row is also not shared.
///////////////////////////////////////////////////////////////////////////////
void Icosphere::buildVerticesSmooth()
{
    //const float S_STEP = 1 / 11.0f;         // horizontal texture step
    //const float T_STEP = 1 / 3.0f;          // vertical texture step
    const float S_STEP = 186 / 2048.0f;     // horizontal texture step
    const float T_STEP = 322 / 1024.0f;     // vertical texture step

    // compute 12 vertices of icosahedron
    // NOTE: v0 (top), v11(bottom), v1, v6(first vert on each row) cannot be
    // shared for smooth shading (they have different texcoords)
    std::vector<float> tmpVertices = computeIcosahedronVertices();

    // clear memory of prev arrays
    std::vector<float>().swap(vertices);
    std::vector<float>().swap(normals);
    std::vector<float>().swap(texCoords);
    std::vector<unsigned int>().swap(indices);
    std::vector<unsigned int>().swap(lineIndices);
    std::map<std::pair<float, float>, unsigned int>().swap(sharedIndices);

    float v[3];                             // vertex
    float n[3];                             // normal
    float scale;                            // scale factor for normalization

    // smooth icosahedron has 14 non-shared (0 to 13) and
    // 8 shared vertices (14 to 21) (total 22 vertices)
    //  00  01  02  03  04          //
    //  /\  /\  /\  /\  /\          //
    // /  \/  \/  \/  \/  \         //
    //10--14--15--16--17--11        //
    // \  /\  /\  /\  /\  /\        //
    //  \/  \/  \/  \/  \/  \       //
    //  12--18--19--20--21--13      //
    //   \  /\  /\  /\  /\  /       //
    //    \/  \/  \/  \/  \/        //
    //    05  06  07  08  09        //
    // add 14 non-shared vertices first (index from 0 to 13)
    vertices.insert(vertices.end(), {tmpVertices[0], tmpVertices[1], tmpVertices[2]}); // v0 (top)
    normals.insert(normals.end(), {0, 0, 1});
    texCoords.insert(texCoords.end(), {S_STEP, 0});

    vertices.insert(vertices.end(), {tmpVertices[0], tmpVertices[1], tmpVertices[2]}); // v1
    normals.insert(normals.end(), {0, 0, 1});
    texCoords.insert(texCoords.end(), {S_STEP * 3, 0});

    vertices.insert(vertices.end(), {tmpVertices[0], tmpVertices[1], tmpVertices[2]}); // v2
    normals.insert(normals.end(), {0, 0, 1});
    texCoords.insert(texCoords.end(), {S_STEP * 5, 0});

    vertices.insert(vertices.end(), {tmpVertices[0], tmpVertices[1], tmpVertices[2]}); // v3
    normals.insert(normals.end(), {0, 0, 1});
    texCoords.insert(texCoords.end(), {S_STEP * 7, 0});

    vertices.insert(vertices.end(), {tmpVertices[0], tmpVertices[1], tmpVertices[2]}); // v4
    normals.insert(normals.end(), {0, 0, 1});
    texCoords.insert(texCoords.end(), {S_STEP * 9, 0});

    vertices.insert(vertices.end(), {tmpVertices[33], tmpVertices[34], tmpVertices[35]}); // v5 (bottom)
    normals.insert(normals.end(), {0, 0, -1});
    texCoords.insert(texCoords.end(), {S_STEP * 2, T_STEP * 3});

    vertices.insert(vertices.end(), {tmpVertices[33], tmpVertices[34], tmpVertices[35]}); // v6
    normals.insert(normals.end(), {0, 0, -1});
    texCoords.insert(texCoords.end(), {S_STEP * 4, T_STEP * 3});

    vertices.insert(vertices.end(), {tmpVertices[33], tmpVertices[34], tmpVertices[35]}); // v7
    normals.insert(normals.end(), {0, 0, -1});
    texCoords.insert(texCoords.end(), {S_STEP * 6, T_STEP * 3});

    vertices.insert(vertices.end(), {tmpVertices[33], tmpVertices[34], tmpVertices[35]}); // v8
    normals.insert(normals.end(), {0, 0, -1});
    texCoords.insert(texCoords.end(), {S_STEP * 8, T_STEP * 3});

    vertices.insert(vertices.end(), {tmpVertices[33], tmpVertices[34], tmpVertices[35]}); // v9
    normals.insert(normals.end(), {0, 0, -1});
    texCoords.insert(texCoords.end(), {S_STEP * 10, T_STEP * 3});

    v[0] = tmpVertices[3];  v[1] = tmpVertices[4];  v[2] = tmpVertices[5];  // v10 (left)
    Icosphere::computeVertexNormal(v, n);
    vertices.insert(vertices.end(), v, v+3);
    normals.insert(normals.end(), n, n+3);
    texCoords.insert(texCoords.end(), {0, T_STEP});

    vertices.insert(vertices.end(), v, v+3); // v11 (right)
    normals.insert(normals.end(), n, n+3);
    texCoords.insert(texCoords.end(), {S_STEP * 10, T_STEP});

    v[0] = tmpVertices[18]; v[1] = tmpVertices[19]; v[2] = tmpVertices[20]; // v12 (left)
    Icosphere::computeVertexNormal(v, n);
    vertices.insert(vertices.end(), v, v+3);
    normals.insert(normals.end(), n, n+3);
    texCoords.insert(texCoords.end(), {S_STEP, T_STEP * 2});

    vertices.insert(vertices.end(), v, v+3); // v13 (right)
    normals.insert(normals.end(), n, n+3);
    texCoords.insert(texCoords.end(), {S_STEP * 11, T_STEP * 2});

    // add 8 shared vertices to array (index from 14 to 21)
    v[0] = tmpVertices[6];  v[1] = tmpVertices[7];  v[2] = tmpVertices[8];  // v14 (shared)
    Icosphere::computeVertexNormal(v, n);
    vertices.insert(vertices.end(), v, v+3);
    normals.insert(normals.end(), n, n+3);
    texCoords.insert(texCoords.end(), {S_STEP * 2, T_STEP});
    sharedIndices[std::make_pair(S_STEP * 2, T_STEP)] = texCoords.size() / 2 - 1;

    v[0] = tmpVertices[9];  v[1] = tmpVertices[10]; v[2] = tmpVertices[11]; // v15 (shared)
    Icosphere::computeVertexNormal(v, n);
    vertices.insert(vertices.end(), v, v+3);
    normals.insert(normals.end(), n, n+3);
    texCoords.insert(texCoords.end(), {S_STEP * 4, T_STEP});
    sharedIndices[std::make_pair(S_STEP * 4, T_STEP)] = texCoords.size() / 2 - 1;

    v[0] = tmpVertices[12]; v[1] = tmpVertices[13]; v[2] = tmpVertices[14]; // v16 (shared)
    scale = Icosphere::computeScaleForLength(v, 1);
    n[0] = v[0] * scale;    n[1] = v[1] * scale;    n[2] = v[2] * scale;
    vertices.insert(vertices.end(), v, v+3);
    normals.insert(normals.end(), n, n+3);
    texCoords.insert(texCoords.end(), {S_STEP * 6, T_STEP});
    sharedIndices[std::make_pair(S_STEP * 6, T_STEP)] = texCoords.size() / 2 - 1;

    v[0] = tmpVertices[15]; v[1] = tmpVertices[16]; v[2] = tmpVertices[17]; // v17 (shared)
    Icosphere::computeVertexNormal(v, n);
    vertices.insert(vertices.end(), v, v+3);
    normals.insert(normals.end(), n, n+3);
    texCoords.insert(texCoords.end(), {S_STEP * 8, T_STEP});
    sharedIndices[std::make_pair(S_STEP * 8, T_STEP)] = texCoords.size() / 2 - 1;

    v[0] = tmpVertices[21]; v[1] = tmpVertices[22]; v[2] = tmpVertices[23]; // v18 (shared)
    Icosphere::computeVertexNormal(v, n);
    vertices.insert(vertices.end(), v, v+3);
    normals.insert(normals.end(), n, n+3);
    texCoords.insert(texCoords.end(), {S_STEP * 3, T_STEP * 2});
    sharedIndices[std::make_pair(S_STEP * 3, T_STEP * 2)] = texCoords.size() / 2 - 1;

    v[0] = tmpVertices[24]; v[1] = tmpVertices[25]; v[2] = tmpVertices[26]; // v19 (shared)
    Icosphere::computeVertexNormal(v, n);
    vertices.insert(vertices.end(), v, v+3);
    normals.insert(normals.end(), n, n+3);
    texCoords.insert(texCoords.end(), {S_STEP * 5, T_STEP * 2});
    sharedIndices[std::make_pair(S_STEP * 5, T_STEP * 2)] = texCoords.size() / 2 - 1;

    v[0] = tmpVertices[27]; v[1] = tmpVertices[28]; v[2] = tmpVertices[29]; // v20 (shared)
    Icosphere::computeVertexNormal(v, n);
    vertices.insert(vertices.end(), v, v+3);
    normals.insert(normals.end(), n, n+3);
    texCoords.insert(texCoords.end(), {S_STEP * 7, T_STEP * 2});
    sharedIndices[std::make_pair(S_STEP * 7, T_STEP * 2)] = texCoords.size() / 2 - 1;

    v[0] = tmpVertices[30]; v[1] = tmpVertices[31]; v[2] = tmpVertices[32]; // v21 (shared)
    Icosphere::computeVertexNormal(v, n);
    vertices.insert(vertices.end(), v, v+3);
    normals.insert(normals.end(), n, n+3);
    texCoords.insert(texCoords.end(), {S_STEP * 9, T_STEP * 2});
    sharedIndices[std::make_pair(S_STEP * 9, T_STEP * 2)] = texCoords.size() / 2 - 1;

    // build index list for icosahedron (20 triangles)
    addIndices( 0, 10, 14);      // 1st row (5 tris)
    addIndices( 1, 14, 15);
    addIndices( 2, 15, 16);
    addIndices( 3, 16, 17);
    addIndices( 4, 17, 11);
    addIndices(10, 12, 14);      // 2nd row (10 tris)
    addIndices(12, 18, 14);
    addIndices(14, 18, 15);
    addIndices(18, 19, 15);
    addIndices(15, 19, 16);
    addIndices(19, 20, 16);
    addIndices(16, 20, 17);
    addIndices(20, 21, 17);
    addIndices(17, 21, 11);
    addIndices(21, 13, 11);
    addIndices( 5, 18, 12);      // 3rd row (5 tris)
    addIndices( 6, 19, 18);
    addIndices( 7, 20, 19);
    addIndices( 8, 21, 20);
    addIndices( 9, 13, 21);

    // add edge lines of icosahedron
    lineIndices.insert(lineIndices.end(), { 0, 10});    // 00 - 10
    lineIndices.insert(lineIndices.end(), { 1, 14});    // 01 - 14
    lineIndices.insert(lineIndices.end(), { 2, 15});    // 02 - 15
    lineIndices.insert(lineIndices.end(), { 3, 16});    // 03 - 16
    lineIndices.insert(lineIndices.end(), { 4, 17});    // 04 - 17
    lineIndices.insert(lineIndices.end(), {10, 14});    // 10 - 14
    lineIndices.insert(lineIndices.end(), {14, 15});    // 14 - 15
    lineIndices.insert(lineIndices.end(), {15, 16});    // 15 - 16
    lineIndices.insert(lineIndices.end(), {10, 14});    // 10 - 14
    lineIndices.insert(lineIndices.end(), {17, 11});    // 17 - 11
    lineIndices.insert(lineIndices.end(), {10, 12});    // 10 - 12
    lineIndices.insert(lineIndices.end(), {12, 14});    // 12 - 14
    lineIndices.insert(lineIndices.end(), {14, 18});    // 14 - 18
    lineIndices.insert(lineIndices.end(), {18, 15});    // 18 - 15
    lineIndices.insert(lineIndices.end(), {15, 19});    // 15 - 19
    lineIndices.insert(lineIndices.end(), {19, 16});    // 19 - 16
    lineIndices.insert(lineIndices.end(), {16, 20});    // 16 - 20
    lineIndices.insert(lineIndices.end(), {20, 17});    // 20 - 17
    lineIndices.insert(lineIndices.end(), {17, 21});    // 17 - 21
    lineIndices.insert(lineIndices.end(), {21, 11});    // 21 - 11
    lineIndices.insert(lineIndices.end(), {12, 18});    // 12 - 18
    lineIndices.insert(lineIndices.end(), {18, 19});    // 18 - 19
    lineIndices.insert(lineIndices.end(), {19, 20});    // 19 - 20
    lineIndices.insert(lineIndices.end(), {20, 21});    // 20 - 21
    lineIndices.insert(lineIndices.end(), {21, 13});    // 21 - 13
    lineIndices.insert(lineIndices.end(), { 5, 12});    // 05 - 12
    lineIndices.insert(lineIndices.end(), { 6, 18});    // 06 - 18
    lineIndices.insert(lineIndices.end(), { 7, 19});    // 07 - 19
    lineIndices.insert(lineIndices.end(), { 8, 20});    // 08 - 20
    lineIndices.insert(lineIndices.end(), { 9, 21});    // 09 - 21

    // subdivide icosahedron
    subdivideVerticesSmooth();

    // generate interleaved vertex array as well
    buildInterleavedVertices();
}



///////////////////////////////////////////////////////////////////////////////
// divide the edge of a trinagle into N times, vertex/normal/texCoord are not
// shared for flat shading
//       O        O: vertex from  a triangle of icosahedron
//      / \       S: new vertex for subdivision = 3
//     S - S      # of Vertices = (N+1) * (N+2) / 2
//    / \ / \     # of sub-triangles = N^2
//   S   S - S
//  / \ / \ / \   .
// O - S - S - O
///////////////////////////////////////////////////////////////////////////////
void Icosphere::subdivideVerticesFlat()
{
    if(subdivision <= 1)
        return;

    unsigned int subVertexCount = (subdivision + 1) * (subdivision +2 ) / 2;
    std::vector<float> newVs(subVertexCount * 3);
    std::vector<float> newNs(subVertexCount * 3);
    std::vector<float> newTs(subVertexCount * 2);

    std::vector<float> tmpVertices;
    std::vector<float> tmpTexCoords;
    std::vector<unsigned int> tmpIndices;
    const float *v1, *v2, *v3;          // ptr to original vertices of a triangle
    const float *t1, *t2, *t3;          // ptr to original texcoords of a triangle
    float newV1[3], newV2[3], newV3[3]; // new vertex positions
    float newT1[2], newT2[2], newT3[2]; // new texture coords
    float normal[3];                    // new face normal
    int i, j, k;
    float a;                            // lerp alpha
    unsigned int index = 0;             // new index value
    unsigned int i1, i2;                // indices

    // copy prev arrays
    tmpVertices = vertices;
    tmpTexCoords = texCoords;
    tmpIndices = indices;

    // clear prev arrays
    vertices.clear();
    normals.clear();
    texCoords.clear();
    indices.clear();
    lineIndices.clear();

    int indexCount = (int)tmpIndices.size();
    for(i = 0; i < indexCount; i += 3)
    {
        // get 3 vertice and texcoords of a triangle of icosahedron
        v1 = &tmpVertices[tmpIndices[i] * 3];
        v2 = &tmpVertices[tmpIndices[i + 1] * 3];
        v3 = &tmpVertices[tmpIndices[i + 2] * 3];
        t1 = &tmpTexCoords[tmpIndices[i] * 2];
        t2 = &tmpTexCoords[tmpIndices[i + 1] * 2];
        t3 = &tmpTexCoords[tmpIndices[i + 2] * 2];

        // add top vertex and textcoord (x,y,z), (s,t)
        newVs.clear();
        newTs.clear();
        newVs.insert(newVs.end(), v1, v1+3);
        newTs.insert(newTs.end(), t1, t1+2);

        // find new vertices by subdividing edges
        for(j = 1; j <= subdivision; ++j)
        {
            a = (float)j / subdivision;    // lerp alpha

            // find 2 end vertices on the edges of the current row
            //          v1           //
            //         / \           // if N = 3,
            //        *---*          // lerp alpha = 1 / N
            //       / \ / \         //
            // newV1*---*---* newV2  // lerp alpha = 2 / N
            //     / \newV3/ \       //
            //    v2--*---*---v3     //
            Icosphere::interpolateVertex(v1, v2, a, radius, newV1);
            Icosphere::interpolateVertex(v1, v3, a, radius, newV2);
            Icosphere::interpolateTexCoord(t1, t2, a, newT1);
            Icosphere::interpolateTexCoord(t1, t3, a, newT2);
            for(k = 0; k <= j; ++k)
            {
                if(k == 0)      // new vertex on the left edge, newV1
                {
                    newVs.insert(newVs.end(), newV1, newV1+3);
                    newTs.insert(newTs.end(), newT1, newT1+2);
                }
                else if(k == j) // new vertex on the right edge, newV2
                {
                    newVs.insert(newVs.end(), newV2, newV2+3);
                    newTs.insert(newTs.end(), newT2, newT2+2);
                }
                else            // new vertices between newV1 and newV2
                {
                    a = (float)k / j;
                    Icosphere::interpolateVertex(newV1, newV2, a, radius, newV3);
                    Icosphere::interpolateTexCoord(newT1, newT2, a, newT3);
                    newVs.insert(newVs.end(), newV3, newV3+3);
                    newTs.insert(newTs.end(), newT3, newT3+2);
                }
            }
        }

        // compute sub-triangles from new vertices
        //      /           //
        //   V1*---*-       // prev row
        //    / \ /         //
        // V2*---*V3-       // curr row
        //  /               //
        for(j = 1; j <= subdivision; ++j)
        {
            for(k = 0; k < j; ++k)
            {
                // indices
                i1 = (j - 1) * j / 2 + k;   // index from prev row
                i2 = j * (j + 1) / 2 + k;   // index from curr row

                v1 = &newVs[i1 * 3];
                v2 = &newVs[i2 * 3];
                v3 = &newVs[(i2+1) * 3];
                addVertices(v1, v2, v3);

                Icosphere::computeFaceNormal(v1, v2, v3, normal);
                addNormals(normal, normal, normal);

                t1 = &newTs[i1 * 2];
                t2 = &newTs[i2 * 2];
                t3 = &newTs[(i2+1) * 2];
                addTexCoords(t1, t2, t3);

                // add indices
                addIndices(index, index+1, index+2);

                // add indices for edge lines
                addLineIndices(index, index+1);
                addLineIndices(index+1, index+2);

                index += 3; // next index

                // if K is not the last, add adjacent triangle
                if(k < (j-1))
                {
                    i2 = i1 + 1; // next of the prev row
                    v2 = &newVs[i2 * 3];
                    addVertices(v1, v3, v2);
                    Icosphere::computeFaceNormal(v1, v3, v2, normal);
                    addNormals(normal, normal, normal);
                    t2 = &newTs[i2 * 2];
                    addTexCoords(t1, t3, t2);
                    addIndices(index, index+1, index+2);
                    addLineIndices(index, index+1);
                    addLineIndices(index, index+2);
                    index += 3;
                }
            }
        }
    }
}



///////////////////////////////////////////////////////////////////////////////
// divide the edge of a trinagle into N times, vertex/normal/texCoord can be
// shared for smooth shading
// If subdivision=1, do nothing
//       O        // O: vertex from  a triangle of icosahedron
//      / \       // S: new vertex for subdivision = 3
//     S - S      //
//    / \ / \     //
//   S   S - S    //
//  / \ / \ / \   //
// O - S - S - O  //
///////////////////////////////////////////////////////////////////////////////
void Icosphere::subdivideVerticesSmooth()
{
    if(subdivision < 2)
        return;

    std::vector<float> tmpVertices, tmpTexCoords;
    std::vector<unsigned int> tmpIndices;
    unsigned int i1, i2, i3, i4;        // indices of triangle
    float a;                            // lerp alpha
    int i, j, k;
    // original vertex attribs from icosahedron
    const float *icoV1, *icoV2, *icoV3;
    const float *icoT1, *icoT2, *icoT3;
    unsigned int icoI1, icoI2, icoI3;
    std::vector<unsigned int> prevIs;   // indices of prev row
    std::vector<unsigned int> currIs;   // indices of curr row
    // vertex attribs on left/right edges
    float edgeV1[3], edgeV2[3], edgeN1[3], edgeN2[3], edgeT1[2], edgeT2[2];
    unsigned int edgeI1, edgeI2;

    // copy prev indices
    tmpIndices = indices;
    tmpVertices = vertices;
    tmpTexCoords = texCoords;

    // clear prev arrays
    indices.clear();
    lineIndices.clear();

    int indexCount = (int)tmpIndices.size();
    for(i = 0; i < indexCount; i += 3)
    {
        // get 3 indices of each icosahedron triangle
        icoI1 = tmpIndices[i];
        icoI2 = tmpIndices[i+1];
        icoI3 = tmpIndices[i+2];

        // get 3 vertex attribs from icosahedron triangle
        icoV1 = &tmpVertices[icoI1 * 3];
        icoV2 = &tmpVertices[icoI2 * 3];
        icoV3 = &tmpVertices[icoI3 * 3];
        icoT1 = &tmpTexCoords[icoI1 * 2];
        icoT2 = &tmpTexCoords[icoI2 * 2];
        icoT3 = &tmpTexCoords[icoI3 * 2];

        // reset and remember previous indices
        prevIs.clear();
        prevIs.push_back(icoI1);  // initial prev indices

        // find new vertices by subdividing edges
        for(j = 1; j <= subdivision; ++j)
        {
            // find 2 end vertex attribs on the edges of the current row
            if(j == subdivision)
            {
                edgeV1[0] = icoV2[0]; edgeV1[1] = icoV2[1]; edgeV1[2] = icoV2[2];
                edgeV2[0] = icoV3[0]; edgeV2[1] = icoV3[1]; edgeV2[2] = icoV3[2];
                edgeT1[0] = icoT2[0]; edgeT1[1] = icoT2[1];
                edgeT2[0] = icoT3[0]; edgeT2[1] = icoT3[1];
                edgeI1 = icoI2;
                edgeI2 = icoI3;
            }
            else
            {
                a = (float)j / subdivision;    // lerp alpha
                Icosphere::interpolateVertex(icoV1, icoV2, a, radius, edgeV1);
                Icosphere::interpolateVertex(icoV1, icoV3, a, radius, edgeV2);
                Icosphere::interpolateTexCoord(icoT1, icoT2, a, edgeT1);
                Icosphere::interpolateTexCoord(icoT1, icoT3, a, edgeT2);
                computeVertexNormal(edgeV1, edgeN1);
                computeVertexNormal(edgeV2, edgeN2);
                edgeI1 = addSubVertexAttribs(edgeV1, edgeN1, edgeT1);
                edgeI2 = addSubVertexAttribs(edgeV2, edgeN2, edgeT2);
            }

            // build indices of the current row first
            currIs.clear();
            for(k = 0; k <= j; ++k)
            {
                if(k == 0)
                    currIs.push_back(edgeI1);
                else if(k == j)
                    currIs.push_back(edgeI2);
                else
                {
                    float newV[3], newN[3], newT[2];
                    a = (float)k / j;
                    Icosphere::interpolateVertex(edgeV1, edgeV2, a, radius, newV);
                    Icosphere::interpolateTexCoord(edgeT1, edgeT2, a, newT);
                    computeVertexNormal(newV, newN);
                    unsigned int newI = addSubVertexAttribs(newV, newN, newT);
                    currIs.push_back(newI);
                }
            }

            for(k = 0; k < j; ++k)
            {
                // index from prev row
                i1 = prevIs[k];

                // new 2 vertices on current row
                i2 = currIs[k];
                i3 = currIs[k+1];

                // add indices
                addIndices(i1, i2, i3);

                // add indices for edge lines
                addLineIndices(i1, i2);
                addLineIndices(i2, i3);

                if(k < j-1)
                {
                    i4 = prevIs[k+1];
                    addIndices(i3, i4, i1);
                    addLineIndices(i1, i3);
                    addLineIndices(i1, i4);
                }
            }
            // for next row
            prevIs.swap(currIs);
        }
    }
}



///////////////////////////////////////////////////////////////////////////////
// generate interleaved vertices: V/N/T
// stride must be 32 bytes
///////////////////////////////////////////////////////////////////////////////
void Icosphere::buildInterleavedVertices()
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
// add 3 vertices of a triangle to array
///////////////////////////////////////////////////////////////////////////////
void Icosphere::addVertices(const float v1[3], const float v2[3], const float v3[3])
{
    vertices.insert(vertices.end(), v1, v1+3);
    vertices.insert(vertices.end(), v2, v2+3);
    vertices.insert(vertices.end(), v3, v3+3);
}



///////////////////////////////////////////////////////////////////////////////
// add 3 normals of a triangle to array
///////////////////////////////////////////////////////////////////////////////
void Icosphere::addNormals(const float n1[3], const float n2[3], const float n3[3])
{
    normals.insert(normals.end(), n1, n1+3);
    normals.insert(normals.end(), n2, n2+3);
    normals.insert(normals.end(), n3, n3+3);
}



///////////////////////////////////////////////////////////////////////////////
// add 3 texture coords of a triangle to array
///////////////////////////////////////////////////////////////////////////////
void Icosphere::addTexCoords(const float t1[2], const float t2[2], const float t3[2])
{
    texCoords.insert(texCoords.end(), t1, t1+2);
    texCoords.insert(texCoords.end(), t2, t2+2);
    texCoords.insert(texCoords.end(), t3, t3+2);
}



///////////////////////////////////////////////////////////////////////////////
// add 3 indices to array
///////////////////////////////////////////////////////////////////////////////
void Icosphere::addIndices(unsigned int i1, unsigned int i2, unsigned int i3)
{
    indices.push_back(i1);
    indices.push_back(i2);
    indices.push_back(i3);
}



///////////////////////////////////////////////////////////////////////////////
// add edge line indices
///////////////////////////////////////////////////////////////////////////////
void Icosphere::addLineIndices(unsigned int i1, unsigned int i2)
{
    lineIndices.push_back(i1);
    lineIndices.push_back(i2);
}



///////////////////////////////////////////////////////////////////////////////
// add a subdivided vertex attribs (vertex, normal, texCoord) to arrays, then
// return its index value
// If it is a shared vertex, remember its index, so it can be re-used
///////////////////////////////////////////////////////////////////////////////
unsigned int Icosphere::addSubVertexAttribs(const float v[3], const float n[3], const float t[2])
{
    unsigned int index;     // return value;

    // check if is shared vertex or not first
    if(Icosphere::isSharedTexCoord(t))
    {
        // find if it does already exist in sharedIndices map using (s,t) key
        // if not in the list, add the vertex attribs to arrays and return its index
        // if exists, return the current index
        std::pair<float, float> key = std::make_pair(t[0], t[1]);
        std::map<std::pair<float, float>, unsigned int>::iterator iter = sharedIndices.find(key);
        if(iter == sharedIndices.end())
        {
            vertices.insert(vertices.end(), v, v+3);
            normals.insert(normals.end(), n, n+3);
            texCoords.insert(texCoords.end(), t, t+2);
            index = texCoords.size() / 2 - 1;
            sharedIndices[key] = index;
        }
        else
        {
            index = iter->second;
        }
    }
    // not shared
    else
    {
        vertices.insert(vertices.end(), v, v+3);
        normals.insert(normals.end(), n, n+3);
        texCoords.insert(texCoords.end(), t, t+2);
        index = texCoords.size() / 2 - 1;
    }

    return index;
}




// static functions ===========================================================
///////////////////////////////////////////////////////////////////////////////
// return face normal (4th param) of a triangle v1-v2-v3
// if a triangle has no surface (normal length = 0), then return a zero vector
///////////////////////////////////////////////////////////////////////////////
void Icosphere::computeFaceNormal(const float v1[3], const float v2[3], const float v3[3], float n[3])
{
    const float EPSILON = 0.000001f;

    // default return value (0, 0, 0)
    n[0] = n[1] = n[2] = 0;

    // find 2 edge vectors: v1-v2, v1-v3
    float ex1 = v2[0] - v1[0];
    float ey1 = v2[1] - v1[1];
    float ez1 = v2[2] - v1[2];
    float ex2 = v3[0] - v1[0];
    float ey2 = v3[1] - v1[1];
    float ez2 = v3[2] - v1[2];

    // cross product: e1 x e2
    float nx, ny, nz;
    nx = ey1 * ez2 - ez1 * ey2;
    ny = ez1 * ex2 - ex1 * ez2;
    nz = ex1 * ey2 - ey1 * ex2;

    // normalize only if the length is > 0
    float length = sqrtf(nx * nx + ny * ny + nz * nz);
    if(length > EPSILON)
    {
        // normalize
        float lengthInv = 1.0f / length;
        n[0] = nx * lengthInv;
        n[1] = ny * lengthInv;
        n[2] = nz * lengthInv;
    }
}



///////////////////////////////////////////////////////////////////////////////
// return vertex normal (2nd param) by mormalizing the vertex vector
///////////////////////////////////////////////////////////////////////////////
void Icosphere::computeVertexNormal(const float v[3], float normal[3])
{
    // normalize
    float scale = Icosphere::computeScaleForLength(v, 1);
    normal[0] = v[0] * scale;
    normal[1] = v[1] * scale;
    normal[2] = v[2] * scale;
}



///////////////////////////////////////////////////////////////////////////////
// get the scale factor for vector to resize to the given length of vector
///////////////////////////////////////////////////////////////////////////////
float Icosphere::computeScaleForLength(const float v[3], float length)
{
    // and normalize the vector then re-scale to new radius
    return length / sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}



///////////////////////////////////////////////////////////////////////////////
// find interpolate vertex between 2 vertices at given alpha
// NOTE: new vertex must be resized, so the length is equal to the given length
///////////////////////////////////////////////////////////////////////////////
void Icosphere::interpolateVertex(const float v1[3], const float v2[3], float t, float length, float newV[3])
{
    newV[0] = Icosphere::lerp(v1[0], v2[0], t);
    newV[1] = Icosphere::lerp(v1[1], v2[1], t);
    newV[2] = Icosphere::lerp(v1[2], v2[2], t);
    float scale = Icosphere::computeScaleForLength(newV, length);
    newV[0] *= scale;
    newV[1] *= scale;
    newV[2] *= scale;
}



///////////////////////////////////////////////////////////////////////////////
// find interpolate coord between 2 tex coords at a given alpha value and
// return new coord
///////////////////////////////////////////////////////////////////////////////
void Icosphere::interpolateTexCoord(const float t1[2], const float t2[2], float a, float newT[2])
{
    newT[0] = Icosphere::lerp(t1[0], t2[0], a);
    newT[1] = Icosphere::lerp(t1[1], t2[1], a);
}



///////////////////////////////////////////////////////////////////////////////
// linear interpolation = (1-t)*P1 + t*P2
///////////////////////////////////////////////////////////////////////////////
float Icosphere::lerp(float from, float to, float alpha)
{
    return from + alpha * (to - from);
}



///////////////////////////////////////////////////////////////////////////////
// This function used 20 non-shared line segments to determine if the given
// texture coordinate is shared or no. If it is on the line segments, it is also
// non-shared point
//   00  01  02  03  04         //
//   /\  /\  /\  /\  /\         //
//  /  \/  \/  \/  \/  \        //
// 05  06  07  08  09   \       //
//   \   10  11  12  13  14     //
//    \  /\  /\  /\  /\  /      //
//     \/  \/  \/  \/  \/       //
//      15  16  17  18  19      //
///////////////////////////////////////////////////////////////////////////////
bool Icosphere::isSharedTexCoord(const float t[2])
{
    // 20 non-shared line segments
    //const float S = 1.0f / 11;  // texture steps
    //const float T = 1.0f / 3;
    const float S = 186 / 2048.0f;     // horizontal texture step
    const float T = 322 / 1024.0f;     // vertical texture step
    static float segments[] = { S, 0,       0, T,       // 00 - 05
                                S, 0,       S*2, T,     // 00 - 06
                                S*3, 0,     S*2, T,     // 01 - 06
                                S*3, 0,     S*4, T,     // 01 - 07
                                S*5, 0,     S*4, T,     // 02 - 07
                                S*5, 0,     S*6, T,     // 02 - 08
                                S*7, 0,     S*6, T,     // 03 - 08
                                S*7, 0,     S*8, T,     // 03 - 09
                                S*9, 0,     S*8, T,     // 04 - 09
                                S*9, 0,     1, T*2,     // 04 - 14
                                0, T,       S*2, 1,     // 05 - 15
                                S*3, T*2,   S*2, 1,     // 10 - 15
                                S*3, T*2,   S*4, 1,     // 10 - 16
                                S*5, T*2,   S*4, 1,     // 11 - 16
                                S*5, T*2,   S*6, 1,     // 11 - 17
                                S*7, T*2,   S*6, 1,     // 12 - 17
                                S*7, T*2,   S*8, 1,     // 12 - 18
                                S*9, T*2,   S*8, 1,     // 13 - 18
                                S*9, T*2,   S*10, 1,    // 13 - 19
                                1, T*2,     S*10, 1 };  // 14 - 19

    // check the point with all 20 line segments
    // if it is on the line segment, it is non-shared
    int count = (int)(sizeof(segments) / sizeof(segments[0]));
    for(int i = 0, j = 2; i < count; i+=4, j+=4)
    {
        if(Icosphere::isOnLineSegment(&segments[i], &segments[j], t))
            return false;   // not shared
    }

    return true;
}



///////////////////////////////////////////////////////////////////////////////
// determine a point c is on the line segment a-b
///////////////////////////////////////////////////////////////////////////////
bool Icosphere::isOnLineSegment(const float a[2], const float b[2], const float c[2])
{
    const float EPSILON = 0.0001f;

    // cross product must be 0 if c is on the line
    float cross = ((b[0] - a[0]) * (c[1] - a[1])) - ((b[1] - a[1]) * (c[0] - a[0]));
    if(cross > EPSILON || cross < -EPSILON)
        return false;

    // c must be within a-b
    if((c[0] > a[0] && c[0] > b[0]) || (c[0] < a[0] && c[0] < b[0]))
        return false;
    if((c[1] > a[1] && c[1] > b[1]) || (c[1] < a[1] && c[1] < b[1]))
        return false;

    return true;    // all passed, it is on the line segment
}
