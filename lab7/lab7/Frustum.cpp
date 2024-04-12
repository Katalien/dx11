#include "frustum.h"

// Function to build frustum
void Frustum::ConstructFrustum(XMMATRIX viewMatrix, XMMATRIX projectionMatrix) {
    XMFLOAT4X4 pMatrix;
    XMStoreFloat4x4(&pMatrix, projectionMatrix);

    float zMinimum = -pMatrix._43 / pMatrix._33;
    float r = m_screenDepth / (m_screenDepth - zMinimum);

    pMatrix._33 = r;
    pMatrix._43 = -r * zMinimum;
    projectionMatrix = XMLoadFloat4x4(&pMatrix);

    XMMATRIX finalMatrix = XMMatrixMultiply(viewMatrix, projectionMatrix);

    XMFLOAT4X4 matrix;
    XMStoreFloat4x4(&matrix, finalMatrix);

    for (int i = 0; i < 6; i++) {
        m_planes[i][0] = (i % 2 == 0) ? matrix._14 + (i < 4 ? matrix._13 : matrix._11) : matrix._14 - (i < 4 ? matrix._13 : matrix._11);
        m_planes[i][1] = (i % 2 == 0) ? matrix._24 + (i < 4 ? matrix._23 : matrix._21) : matrix._24 - (i < 4 ? matrix._23 : matrix._21);
        m_planes[i][2] = (i % 2 == 0) ? matrix._34 + (i < 4 ? matrix._33 : matrix._31) : matrix._34 - (i < 4 ? matrix._33 : matrix._31);
        m_planes[i][3] = (i % 2 == 0) ? matrix._44 + (i < 4 ? matrix._43 : matrix._41) : matrix._44 - (i < 4 ? matrix._43 : matrix._41);

        float length = sqrtf((m_planes[i][0] * m_planes[i][0]) + (m_planes[i][1] * m_planes[i][1]) + (m_planes[i][2] * m_planes[i][2]));
        m_planes[i][0] /= length;
        m_planes[i][1] /= length;
        m_planes[i][2] /= length;
        m_planes[i][3] /= length;
    }
}

// Function to check if a rectangle is inside the frustum
bool Frustum::CheckRectangle(float maxWidth, float maxHeight, float maxDepth, float minWidth, float minHeight, float minDepth)
{
    for (int i = 0; i < 6; i++)
    {
        if (m_planes[i][0] * (minWidth)+m_planes[i][1] * (minHeight)+m_planes[i][2] * (minDepth)+m_planes[i][3] > 0)
            continue;
        if (m_planes[i][0] * (maxWidth)+m_planes[i][1] * (minHeight)+m_planes[i][2] * (minDepth)+m_planes[i][3] > 0)
            continue;
        if (m_planes[i][0] * (minWidth)+m_planes[i][1] * (maxHeight)+m_planes[i][2] * (minDepth)+m_planes[i][3] > 0)
            continue;
        if (m_planes[i][0] * (minWidth)+m_planes[i][1] * (minHeight)+m_planes[i][2] * (maxDepth)+m_planes[i][3] > 0)
            continue;
        if (m_planes[i][0] * (maxWidth)+m_planes[i][1] * (maxHeight)+m_planes[i][2] * (minDepth)+m_planes[i][3] > 0)
            continue;
        if (m_planes[i][0] * (maxWidth)+m_planes[i][1] * (minHeight)+m_planes[i][2] * (maxDepth)+m_planes[i][3] > 0)
            continue;
        if (m_planes[i][0] * (minWidth)+m_planes[i][1] * (maxHeight)+m_planes[i][2] * (maxDepth)+m_planes[i][3] > 0)
            continue;
        if (m_planes[i][0] * (maxWidth)+m_planes[i][1] * (maxHeight)+m_planes[i][2] * (maxDepth)+m_planes[i][3] > 0)
            continue;
        return false;
    }

    return true;
}