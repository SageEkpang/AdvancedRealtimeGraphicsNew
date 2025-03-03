#ifndef CAMERA_H
#define CAMERA_H

#include "structures.h"
#include "constants.h"

class Camera
{
private:

    // NEW VARIABLE(s)
    XMFLOAT3 m_Eye;
    XMFLOAT3 m_At;
    XMFLOAT3 m_Up;

    float m_WindowWidth;
    float m_WindowHeight;

    float m_NearDepth;
    float m_FarDepth;


    // CAMERA VARIABLE(s)
    float m_Speed;
    float m_RotationSpeed;

    XMFLOAT3 m_ForwardVector;

    XMFLOAT4X4* m_World;
    XMFLOAT4X4 m_ViewMatrix;
    XMFLOAT4X4 m_ProjectionMatrix;

private:

    // void ResetToDefault();

public:
        
    // CLASS FUNCTION(s)
    Camera(XMFLOAT3 position, XMFLOAT3 at, XMFLOAT3 up, int windowWidth, int windowHeight, int nearDepth, int farDepth);
    ~Camera();


    // BASE FUNCTION(s)
    void Update(const float deltaTime);
    void Draw() { };

    
    // GETTER FUNCTION(s)
    inline const XMFLOAT4X4& GetView() const { return m_ViewMatrix; }
    inline const XMFLOAT4X4& GetProjection() const { return m_ProjectionMatrix; }

    inline XMFLOAT3 GetPosition() const { return m_Eye; }
    inline XMFLOAT3 GetLookAt() const { return m_At; }
    inline XMFLOAT3 GetUp() const { return m_Up; }

    XMMATRIX& GetCameraMatrix();

    // SETTER FUNCTION(s)
    inline void SetPosition(XMFLOAT3 position) { m_Eye = position; }
    inline void SetLookAt(XMFLOAT3 lookAt) { m_At = lookAt; }
    inline void SetUp(XMFLOAT3 up) { m_Up = up; }

    void SetCameraPosition(float x, float y, float z);



    // HELPER FUNCTION(s)
    void Reshape(float windowWidth, float windowHeight, float nearDepth, float farDepth);


};

#endif
