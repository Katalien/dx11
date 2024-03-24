#include "Camera.hpp"

Camera::Camera() {
    focus_ = XMFLOAT3(0.0f, 0.0f, 0.0f);
    r_ = 8.0f;
    theta_ = 0.3;
    phi_ = -100;
    position_ = XMFLOAT3(focus_.x - cosf(theta_) * cosf(phi_) * r_,
        focus_.y - sinf(theta_) * r_,
        focus_.z - cosf(theta_) * sinf(phi_) * r_);

    UpdateViewMatrix();
}

void Camera::Rotate(float dphi, float dtheta) {
    phi_ -= dphi;
    theta_ -= dtheta;
    theta_ = min(max(theta_, -XM_PIDIV2), XM_PIDIV2);
    UpdateViewMatrix();
}


void Camera::UpdateViewMatrix() {
    position_.x = focus_.x + r_ * cosf(theta_) * cosf(phi_);
    position_.y = focus_.y + r_ * sinf(theta_);
    position_.z = focus_.z + r_ * cosf(theta_) * sinf(phi_);

    XMVECTOR position = XMLoadFloat3(&position_);
    XMVECTOR focus = XMLoadFloat3(&focus_);
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f); 

    viewMatrix_ = XMMatrixLookAtLH(position, focus, up);
}