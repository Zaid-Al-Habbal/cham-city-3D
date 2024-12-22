///////////////////////////////////////////////////////////////////////////////
// Cubesphere.cpp
// ==============
// cube-based sphere dividing the spherical surface into 6 equal-area faces of
// a cube (+X, -X, +Y, -Y, +Z, -Z)
// If N=1, it is identical to a cube, which is inscribed in a sphere.
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2018-09-20
// UPDATED: 2024-09-06
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
#include "Cubesphere.h"



///////////////////////////////////////////////////////////////////////////////
// ctor
// The radius is circumscribed sphere
///////////////////////////////////////////////////////////////////////////////
Cubesphere::Cubesphere(float radius, int sub, bool smooth) : radius(radius), subdivision(sub), smooth(smooth), interleavedStride(32)
{
    if(subdivision < 1)
        subdivision = 1;

    vertexCountPerRow = (unsigned int)subdivision + 1;
    vertexCountPerFace = vertexCountPerRow * vertexCountPerRow;

    if(smooth)
        buildVerticesSmooth();
    else
        buildVerticesFlat();
}



///////////////////////////////////////////////////////////////////////////////
// setters
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::setRadius(float radius)
{
    this->radius = radius;
    if(smooth)
        buildVerticesSmooth();
    else
        buildVerticesFlat();

    //@@ NOT USED
    //@@updateRadius(); // update vertex positions only
}

void Cubesphere::setSideLength(float side)
{
    float radius = side * sqrt(3.0f) / 2;   // convert side length to radius
    setRadius(radius);
}

void Cubesphere::setSubdivision(int segments)
{
    subdivision = segments;
    if(subdivision < 1)
        subdivision = 1;

    vertexCountPerRow = (unsigned int)subdivision + 1;
    vertexCountPerFace = vertexCountPerRow * vertexCountPerRow;

    // rebuild vertices
    if(smooth)
        buildVerticesSmooth();
    else
        buildVerticesFlat();
}

void Cubesphere::setSmooth(bool smooth)
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
void Cubesphere::reverseNormals()
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
void Cubesphere::printSelf() const
{

    std::cout << "===== Cubesphere =====\n"
              << "        Radius: " << radius << "\n"
              << "   Side Length: " << getSideLength() << "\n"
              << "   Subdivision: " << subdivision << "\n"
              << "    Smoothness: " << (smooth ? "true" : "false") << "\n"
              << "Triangle Count: " << getTriangleCount() << "\n"
              << "   Index Count: " << getIndexCount() << "\n"
              << "  Vertex Count: " << getVertexCount() << "\n"
              << "  Normal Count: " << getNormalCount() << "\n"
              << "TexCoord Count: " << getTexCoordCount() << std::endl;
}



///////////////////////////////////////////////////////////////////////////////
// draw a cubesphere in VertexArray mode
// OpenGL RC must be set before calling it
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::draw() const
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
void Cubesphere::drawLines(const float lineColor[4]) const
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
// draw a cubesphere surfaces and lines on top of it
// the caller must set the line width before call this
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::drawWithLines(const float lineColor[4]) const
{
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0f, 1.0f);    // move polygon backward
    this->draw();
    glDisable(GL_POLYGON_OFFSET_FILL);

    // draw lines with VA
    drawLines(lineColor);
}



///////////////////////////////////////////////////////////////////////////////
// draw only a single face
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::drawFace(int faceId) const
{
    if(faceId < 0 || faceId >= 6) return;

    // interleaved array
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    unsigned int index = faceId * (unsigned int)interleavedVertices.size() / 6;
    glVertexPointer(3, GL_FLOAT, interleavedStride, &interleavedVertices[index]);
    glNormalPointer(GL_FLOAT, interleavedStride, &interleavedVertices[index+3]);
    glTexCoordPointer(2, GL_FLOAT, interleavedStride, &interleavedVertices[index+6]);

    unsigned int indexCount = (unsigned int)indices.size() / 6;
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, indices.data());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


/*@@ NOT USED
///////////////////////////////////////////////////////////////////////////////
// update vertex positions only
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::updateRadius()
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
*/



///////////////////////////////////////////////////////////////////////////////
// dealloc vectors
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::clearArrays()
{
    std::vector<float>().swap(vertices);
    std::vector<float>().swap(normals);
    std::vector<float>().swap(texCoords);
    std::vector<unsigned int>().swap(indices);
    std::vector<unsigned int>().swap(lineIndices);
}



///////////////////////////////////////////////////////////////////////////////
// generate vertices with flat shading
// each triangle is independent (no shared vertices)
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::buildVerticesFlat()
{
    // generate unit-length verties in +X face
    std::vector<float> unitVertices = Cubesphere::getUnitPositiveX(vertexCountPerRow);

    // clear memory of prev arrays
    clearArrays();

    unsigned int k = 0, k1, k2, i1, i2; // indices
    float v1[3], v2[3], v3[3], v4[3];   // tmp vertices
    float t1[2], t2[2], t3[2], t4[2];   // texture coords
    float n[3];                         // normal vector

    // +X face
    for(unsigned int i = 0; i < vertexCountPerRow - 1; ++i)
    {
        k1 = i * vertexCountPerRow;              // index at curr row
        k2 = k1 + vertexCountPerRow;             // index at next row

        // vertical tex coords
        t1[1] = t3[1] = (float)i / (vertexCountPerRow - 1);
        t2[1] = t4[1] = (float)(i+1) / (vertexCountPerRow - 1);

        for(unsigned int j = 0; j < vertexCountPerRow - 1; ++j, ++k1, ++k2)
        {
            i1 = k1 * 3;
            i2 = k2 * 3;

            // 4 vertices of a quad
            // v1--v3
            // | / |
            // v2--v4
            v1[0] = unitVertices[i1];
            v1[1] = unitVertices[i1+1];
            v1[2] = unitVertices[i1+2];
            v2[0] = unitVertices[i2];
            v2[1] = unitVertices[i2+1];
            v2[2] = unitVertices[i2+2];
            v3[0] = unitVertices[i1+3];
            v3[1] = unitVertices[i1+4];
            v3[2] = unitVertices[i1+5];
            v4[0] = unitVertices[i2+3];
            v4[1] = unitVertices[i2+4];
            v4[2] = unitVertices[i2+5];

            // compute face nornal
            Cubesphere::computeFaceNormal(v1, v2, v3, n);

            // resize vertices by sphere radius
            Cubesphere::scaleVertex(v1, radius);
            Cubesphere::scaleVertex(v2, radius);
            Cubesphere::scaleVertex(v3, radius);
            Cubesphere::scaleVertex(v4, radius);

            // compute horizontal tex coords
            t1[0] = t2[0] = (float)j / (vertexCountPerRow - 1);
            t3[0] = t4[0] = (float)(j+1) / (vertexCountPerRow - 1);

            // add 4 vertex attributes
            addVertices(v1, v2, v3, v4);
            addNormals(n, n, n, n);
            addTexCoords(t1, t2, t3, t4);

            // add indices of 2 triangles
            addIndices(k, k+1, k+2);
            addIndices(k+2, k+1, k+3);

            // add line indices; top and left
            lineIndices.push_back(k);       // left
            lineIndices.push_back(k+1);
            lineIndices.push_back(k);       // top
            lineIndices.push_back(k+2);

            k += 4;     // next
        }
    }

    // array size and index for building next face
    unsigned int startIndex;                    // starting index for next face
    int vertexSize = (int)vertices.size();      // vertex array size of +X face
    int indexSize = (int)indices.size();        // index array size of +X face
    int lineIndexSize = (int)lineIndices.size(); // line index size of +X face

    // build -X face by negating x and z values
    startIndex = vertices.size() / 3;
    for(int i = 0, j = 0; i < vertexSize; i += 3, j += 2)
    {
        addVertex(-vertices[i], vertices[i+1], -vertices[i+2]);
        addTexCoord(texCoords[j], texCoords[j+1]);
        addNormal(-normals[i], normals[i+1], -normals[i+2]);
    }
    for(int i = 0; i < indexSize; ++i)
    {
        indices.push_back(startIndex + indices[i]);
    }
    for(int i = 0; i < lineIndexSize; i += 4)
    {
        // left and bottom lines
        lineIndices.push_back(startIndex + i);      // left
        lineIndices.push_back(startIndex + i + 1);
        lineIndices.push_back(startIndex + i + 1);  // bottom
        lineIndices.push_back(startIndex + i + 3);
    }

    // build +Y face by swapping x=>y, y=>-z, z=>-x
    startIndex = vertices.size() / 3;
    for(int i = 0, j = 0; i < vertexSize; i += 3, j += 2)
    {
        addVertex(-vertices[i+2], vertices[i], -vertices[i+1]);
        addTexCoord(texCoords[j], texCoords[j+1]);
        addNormal(-normals[i+2], normals[i], -normals[i+1]);
    }
    for(int i = 0; i < indexSize; ++i)
    {
        indices.push_back(startIndex + indices[i]);
    }
    for(int i = 0; i < lineIndexSize; ++i)
    {
        // top and left lines (same as +X)
        lineIndices.push_back(startIndex + lineIndices[i]);
    }

    // build -Y face by swapping x=>-y, y=>z, z=>-x
    startIndex = vertices.size() / 3;
    for(int i = 0, j = 0; i < vertexSize; i += 3, j += 2)
    {
        addVertex(-vertices[i+2], -vertices[i], vertices[i+1]);
        addTexCoord(texCoords[j], texCoords[j+1]);
        addNormal(-normals[i+2], -normals[i], normals[i+1]);
    }
    for(int i = 0; i < indexSize; ++i)
    {
        indices.push_back(startIndex + indices[i]);
    }
    for(int i = 0; i < lineIndexSize; i += 4)
    {
        // top and right lines
        lineIndices.push_back(startIndex + i);      // top
        lineIndices.push_back(startIndex + i + 2);
        lineIndices.push_back(startIndex + 2 + i);  // right
        lineIndices.push_back(startIndex + 3 + i);
    }

    // build +Z face by swapping x=>z, z=>-x
    startIndex = vertices.size() / 3;
    for(int i = 0, j = 0; i < vertexSize; i += 3, j += 2)
    {
        addVertex(-vertices[i+2], vertices[i+1], vertices[i]);
        addTexCoord(texCoords[j], texCoords[j+1]);
        addNormal(-normals[i+2], normals[i+1], normals[i]);
    }
    for(int i = 0; i < indexSize; ++i)
    {
        indices.push_back(startIndex + indices[i]);
    }
    for(int i = 0; i < lineIndexSize; ++i)
    {
        // top and left lines (same as +X)
        lineIndices.push_back(startIndex + lineIndices[i]);
    }

    // build -Z face by swapping x=>-z, z=>x
    startIndex = vertices.size() / 3;
    for(int i = 0, j = 0; i < vertexSize; i += 3, j += 2)
    {
        addVertex(vertices[i+2], vertices[i+1], -vertices[i]);
        addTexCoord(texCoords[j], texCoords[j+1]);
        addNormal(normals[i+2], normals[i+1], -normals[i]);
    }
    for(int i = 0; i < indexSize; ++i)
    {
        indices.push_back(startIndex + indices[i]);
    }
    for(int i = 0; i < lineIndexSize; i += 4)
    {
        // left and bottom lines
        lineIndices.push_back(startIndex + i);      // left
        lineIndices.push_back(startIndex + i + 1);
        lineIndices.push_back(startIndex + i + 1);  // bottom
        lineIndices.push_back(startIndex + i + 3);
    }

    // generate interleaved vertex array as well
    buildInterleavedVertices();
}



///////////////////////////////////////////////////////////////////////////////
// generate vertices with smooth shading
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::buildVerticesSmooth()
{
    // generate unit-length verties in +X face
    std::vector<float> unitVertices = Cubesphere::getUnitPositiveX(vertexCountPerRow);

    // clear memory of prev arrays
    clearArrays();

    float x, y, z, s, t;
    int k = 0, k1, k2;

    // build +X face
    for(unsigned int i = 0; i < vertexCountPerRow; ++i)
    {
        k1 = i * vertexCountPerRow;     // index for curr row
        k2 = k1 + vertexCountPerRow;    // index for next row
        t = (float)i / (vertexCountPerRow - 1);

        for(unsigned int j = 0; j < vertexCountPerRow; ++j, k += 3, ++k1, ++k2)
        {
            x = unitVertices[k];
            y = unitVertices[k+1];
            z = unitVertices[k+2];
            s = (float)j / (vertexCountPerRow - 1);
            addVertex(x*radius, y*radius, z*radius);
            addNormal(x, y, z);
            addTexCoord(s, t);

            // add indices
            if(i < (vertexCountPerRow-1) && j < (vertexCountPerRow-1))
            {
                addIndices(k1, k2, k1+1);
                addIndices(k1+1, k2, k2+1);
                // lines: left and top
                lineIndices.push_back(k1);  // left
                lineIndices.push_back(k2);
                lineIndices.push_back(k1);  // top
                lineIndices.push_back(k1+1);
            }
        }
    }

    // array size and index for building next face
    unsigned int startIndex;                    // starting index for next face
    int vertexSize = (int)vertices.size();      // vertex array size of +X face
    int indexSize = (int)indices.size();        // index array size of +X face
    int lineIndexSize = (int)lineIndices.size(); // line index size of +X face

    // build -X face by negating x and z
    startIndex = vertices.size() / 3;
    for(int i = 0, j = 0; i < vertexSize; i += 3, j += 2)
    {
        addVertex(-vertices[i], vertices[i+1], -vertices[i+2]);
        addTexCoord(texCoords[j], texCoords[j+1]);
        addNormal(-normals[i], normals[i+1], -normals[i+2]);
    }
    for(int i = 0; i < indexSize; ++i)
    {
        indices.push_back(startIndex + indices[i]);
    }
    for(int i = 0; i < lineIndexSize; i += 4)
    {
        // left and bottom lines
        lineIndices.push_back(startIndex + lineIndices[i]);     // left
        lineIndices.push_back(startIndex + lineIndices[i+1]);
        lineIndices.push_back(startIndex + lineIndices[i+1]);  // bottom
        lineIndices.push_back(startIndex + lineIndices[i+1] + 1);
    }

    // build +Y face by swapping x=>y, y=>-z, z=>-x
    startIndex = vertices.size() / 3;
    for(int i = 0, j = 0; i < vertexSize; i += 3, j += 2)
    {
        addVertex(-vertices[i+2], vertices[i], -vertices[i+1]);
        addTexCoord(texCoords[j], texCoords[j+1]);
        addNormal(-normals[i+2], normals[i], -normals[i+1]);
    }
    for(int i = 0; i < indexSize; ++i)
    {
        indices.push_back(startIndex + indices[i]);
    }
    for(int i = 0; i < lineIndexSize; ++i)
    {
        // top and left lines (same as +X)
        lineIndices.push_back(startIndex + lineIndices[i]);
    }

    // build -Y face by swapping x=>-y, y=>z, z=>-x
    startIndex = vertices.size() / 3;
    for(int i = 0, j = 0; i < vertexSize; i += 3, j += 2)
    {
        addVertex(-vertices[i+2], -vertices[i], vertices[i+1]);
        addTexCoord(texCoords[j], texCoords[j+1]);
        addNormal(-normals[i+2], -normals[i], normals[i+1]);
    }
    for(int i = 0; i < indexSize; ++i)
    {
        indices.push_back(startIndex + indices[i]);
    }
    for(int i = 0; i < lineIndexSize; i += 4)
    {
        // top and right lines
        lineIndices.push_back(startIndex + lineIndices[i]); // top
        lineIndices.push_back(startIndex + lineIndices[i+3]);
        lineIndices.push_back(startIndex + lineIndices[i] + 1); // right
        lineIndices.push_back(startIndex + lineIndices[i+1] + 1);
    }

    // build +Z face by swapping x=>z, z=>-x
    startIndex = vertices.size() / 3;
    for(int i = 0, j = 0; i < vertexSize; i += 3, j += 2)
    {
        addVertex(-vertices[i+2], vertices[i+1], vertices[i]);
        addTexCoord(texCoords[j], texCoords[j+1]);
        addNormal(-normals[i+2], normals[i+1], normals[i]);
    }
    for(int i = 0; i < indexSize; ++i)
    {
        indices.push_back(startIndex + indices[i]);
    }
    for(int i = 0; i < lineIndexSize; ++i)
    {
        // top and left lines (same as +X)
        lineIndices.push_back(startIndex + lineIndices[i]);
    }

    // build -Z face by swapping x=>-z, z=>x
    startIndex = vertices.size() / 3;
    for(int i = 0, j = 0; i < vertexSize; i += 3, j += 2)
    {
        addVertex(vertices[i+2], vertices[i+1], -vertices[i]);
        addTexCoord(texCoords[j], texCoords[j+1]);
        addNormal(normals[i+2], normals[i+1], -normals[i]);
    }
    for(int i = 0; i < indexSize; ++i)
    {
        indices.push_back(startIndex + indices[i]);
    }
    for(int i = 0; i < lineIndexSize; i += 4)
    {
        // left and bottom lines
        lineIndices.push_back(startIndex + lineIndices[i]);     // left
        lineIndices.push_back(startIndex + lineIndices[i+1]);
        lineIndices.push_back(startIndex + lineIndices[i+1]);   // bottom
        lineIndices.push_back(startIndex + lineIndices[i+1] + 1);
    }

    // generate interleaved vertex array
    buildInterleavedVertices();
}



///////////////////////////////////////////////////////////////////////////////
// generate interleaved vertices: V/N/T
// stride must be 32 bytes
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::buildInterleavedVertices()
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
// add single vertex to array
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::addVertex(float x, float y, float z)
{
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
}



///////////////////////////////////////////////////////////////////////////////
// add 4 vertices of a quad (v1-v2-v3-v4) to array
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::addVertices(const float v1[3], const float v2[3], const float v3[3], const float v4[3])
{
    vertices.insert(vertices.end(), v1, v1 + 3);    // v1
    vertices.insert(vertices.end(), v2, v2 + 3);    // v2
    vertices.insert(vertices.end(), v3, v3 + 3);    // v3
    vertices.insert(vertices.end(), v4, v4 + 3);    // v4
}



///////////////////////////////////////////////////////////////////////////////
// add single normal to array
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::addNormal(float nx, float ny, float nz)
{
    normals.push_back(nx);
    normals.push_back(ny);
    normals.push_back(nz);
}



///////////////////////////////////////////////////////////////////////////////
// add 4 normals of a quad to array
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::addNormals(const float n1[3], const float n2[3], const float n3[3], const float n4[3])
{
    normals.insert(normals.end(), n1, n1 + 3);  // n1
    normals.insert(normals.end(), n2, n2 + 3);  // n2
    normals.insert(normals.end(), n3, n3 + 3);  // n3
    normals.insert(normals.end(), n4, n4 + 3);  // n4
}



///////////////////////////////////////////////////////////////////////////////
// add single texture coord to array
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::addTexCoord(float s, float t)
{
    texCoords.push_back(s);
    texCoords.push_back(t);
}



///////////////////////////////////////////////////////////////////////////////
// add 3 texture coords of a quad to array
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::addTexCoords(const float t1[2], const float t2[2], const float t3[2], const float t4[2])
{
    texCoords.insert(texCoords.end(), t1, t1 + 2);  // t1
    texCoords.insert(texCoords.end(), t2, t2 + 2);  // t2
    texCoords.insert(texCoords.end(), t3, t3 + 2);  // t3
    texCoords.insert(texCoords.end(), t4, t4 + 2);  // t4
}



///////////////////////////////////////////////////////////////////////////////
// add 3 indices to array
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::addIndices(unsigned int i1, unsigned int i2, unsigned int i3)
{
    indices.push_back(i1);
    indices.push_back(i2);
    indices.push_back(i3);
}


///////////////////////////////////////////////////////////////////////////////
// return the ptr to the vertices for the face ID
///////////////////////////////////////////////////////////////////////////////
const float* Cubesphere::getVerticesForFace(int faceId) const
{
    if(faceId >= 0 && faceId <= 5)
    {
        return &vertices[faceId * vertices.size() / 6];
    }
    else
    {
        // invalid ID, return the beginging of array
        return vertices.data();
    }
}

const float* Cubesphere::getNormalsForFace(int faceId) const
{
    if(faceId >= 0 && faceId <= 5)
    {
        return &normals[faceId * normals.size() / 6];
    }
    else
    {
        // invalid ID, return the beginging of array
        return normals.data();
    }
}

const float* Cubesphere::getTexCoordsForFace(int faceId) const
{
    if(faceId >= 0 && faceId <= 5)
    {
        return &texCoords[faceId * texCoords.size() / 6];
    }
    else
    {
        // invalid ID, return the beginging of array
        return texCoords.data();
    }
}

const float* Cubesphere::getInterleavedVerticesForFace(int faceId) const
{
    if(faceId >= 0 && faceId <= 5)
    {
        return &interleavedVertices[faceId * interleavedVertices.size() / 6];
    }
    else
    {
        // invalid ID, return the beginging of array
        return interleavedVertices.data();
    }
}








// static functions ===========================================================
///////////////////////////////////////////////////////////////////////////////
// return face normal (4th param) of a triangle v1-v2-v3
// if a triangle has no surface (normal length = 0), then return a zero vector
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::computeFaceNormal(const float v1[3], const float v2[3], const float v3[3], float n[3])
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
// get the scale factor for vector to resize to the given length of vector
///////////////////////////////////////////////////////////////////////////////
float Cubesphere::computeScaleForLength(const float v[3], float length)
{
    // and normalize the vector then re-scale to new radius
    return length / sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}



///////////////////////////////////////////////////////////////////////////////
// generate vertices for +X face only by intersecting 2 circular planes
// (longitudinal and latitudinal) at the longitude/latitude angles
///////////////////////////////////////////////////////////////////////////////
std::vector<float> Cubesphere::getUnitPositiveX(unsigned int pointsPerRow)
{
    const float DEG2RAD = acos(-1.0f) / 180.0f;

    std::vector<float> vertices;
    float n1[3];        // normal of longitudinal plane rotating along Y-axis
    float n2[3];        // normal of latitudinal plane rotating along Z-axis
    float v[3];         // direction vector intersecting 2 planes, n1 x n2
    float a1;           // longitudinal angle along y-axis
    float a2;           // latitudinal angle
    float scale;

    // rotate latitudinal plane from 45 to -45 degrees along Z-axis
    for(unsigned int i = 0; i < pointsPerRow; ++i)
    {
        // normal for latitudinal plane
        a2 = DEG2RAD * (45.0f - 90.0f * i / (pointsPerRow - 1));
        n2[0] = -sin(a2);
        n2[1] = cos(a2);
        n2[2] = 0;

        // rotate longitudinal plane from -45 to 45 along Y-axis
        for(unsigned int j = 0; j < pointsPerRow; ++j)
        {
            // normal for longitudinal plane
            a1 = DEG2RAD * (-45.0f + 90.0f * j / (pointsPerRow - 1));
            n1[0] = -sin(a1);
            n1[1] = 0;
            n1[2] = -cos(a1);

            // find direction vector of intersected line, n1 x n2
            v[0] = n1[1] * n2[2] - n1[2] * n2[1];
            v[1] = n1[2] * n2[0] - n1[0] * n2[2];
            v[2] = n1[0] * n2[1] - n1[1] * n2[0];

            // normalize direction vector
            scale = Cubesphere::computeScaleForLength(v, 1);
            v[0] *= scale;
            v[1] *= scale;
            v[2] *= scale;

            vertices.push_back(v[0]);
            vertices.push_back(v[1]);
            vertices.push_back(v[2]);

            // DEBUG
            //std::cout << "vertex: (" << v[0] << ", " << v[1] << ", " << v[2] << "), "
            //          << sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]) << std::endl;
        }
    }

    return vertices;
}



///////////////////////////////////////////////////////////////////////////////
// rescale vertex length
///////////////////////////////////////////////////////////////////////////////
void Cubesphere::scaleVertex(float v[3], float scale)
{
    v[0] *= scale;
    v[1] *= scale;
    v[2] *= scale;
}
