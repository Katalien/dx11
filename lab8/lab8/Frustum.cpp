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
        m_planes[i].x = (i % 2 == 0) ? matrix._14 + (i < 4 ? matrix._13 : matrix._11) : matrix._14 - (i < 4 ? matrix._13 : matrix._11);
        m_planes[i].y = (i % 2 == 0) ? matrix._24 + (i < 4 ? matrix._23 : matrix._21) : matrix._24 - (i < 4 ? matrix._23 : matrix._21);
        m_planes[i].z = (i % 2 == 0) ? matrix._34 + (i < 4 ? matrix._33 : matrix._31) : matrix._34 - (i < 4 ? matrix._33 : matrix._31);
        m_planes[i].w = (i % 2 == 0) ? matrix._44 + (i < 4 ? matrix._43 : matrix._41) : matrix._44 - (i < 4 ? matrix._43 : matrix._41);

        float length = sqrtf((m_planes[i].x * m_planes[i].x) + (m_planes[i].y * m_planes[i].y) + (m_planes[i].z * m_planes[i].z));
        m_planes[i].x /= length;
        m_planes[i].y /= length;
        m_planes[i].z /= length;
        m_planes[i].w /= length;
    }
}