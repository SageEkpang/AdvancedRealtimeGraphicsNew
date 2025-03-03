#include "GraphicsManager.h"

GraphicsManager::GraphicsManager(HINSTANCE hInstance, int nCmdShow, int windowWidth, int windowHeight)
{
    // GRAPHICS MANAGER INSTANCE

    // SET UP FUNCTION(s)
    HRESULT t_HR = S_OK;

    t_HR = InitWindow(hInstance, nCmdShow);
    t_HR = InitDevice();
    t_HR = InitGUI();
    t_HR = InitRunTimeParameters();

    // GENERAL SET UP(s)

    // CAMERA SET-UP
    m_Camera = new Camera(XMFLOAT3(0.0f, 0.f, 3.f), XMFLOAT3(0.f, 0.f, 1.0f), XMFLOAT3(0.f, 1.f, 0.f), windowWidth, windowHeight, 1, 100);

    // Create index buffer
    WORD ObjectIndices[] =
    {
        0,1,2,
        3,4,5,

        6,7,8,
        9,10,11,

        12,13,14,
        15,16,17,

        18,19,20,
        21,22,23,

        24,25,26,
        27,28,29,

        30,31,32,
        33,34,35
    };

    // Create vertex buffer
    SimpleVertex ObjectVertices[] =
    {
        // top
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f)}, // 3 // 0
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 1 // 1
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 0 // 2

        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 2 // 3
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 1 // 4
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 3 // 5

        // bottom
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 6 // 6
        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 4 // 7
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 5 // 8

        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 7 // 9
        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 4 // 10 
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 6 // 11

        // left
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 11 // 12
        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 9 // 13
        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 8 // 14

        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 10 // 15
        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 9 // 16
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 11 // 17

        // right
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 14 // 18
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 12 // 19
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 13 // 20

        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 15 // 21
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 12 // 22
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 14 // 23

        // front
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 19 // 24
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) , XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 17 // 25
        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 16 // 26 

        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 18 // 27
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) , XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 17 // 28
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 19 // 29

        // back
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 22
        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 20s
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 21

        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 23
        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 20
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) }, // 22
    };


    // DEFAULT OBJECET
    {
        DrawableGameObject* t_GameObject = new DrawableGameObject("RenderTarget");

        // TRANSFORM
        Transform* t_GameObjectTransform = new Transform(Tag("Transform"), m_d3dDevice);
        t_GameObject->SetTransformComponent(t_GameObjectTransform);
        t_GameObjectTransform->SetPosition(-10.0f, 0.0f, 0.0f);
        t_GameObjectTransform->SetScale(1.0f, 1.0f, 1.0f);

        // RENDER
        Render* t_GameObjectRender = new Render(Tag("Render"), m_d3dDevice);
        t_GameObject->SetRenderComponent(t_GameObjectRender);
   
        // MESH
        Mesh::CalculateModelVectors(ObjectVertices, 36);
        Mesh* t_GameObjectMesh = new Mesh(Tag("Mesh"), ObjectIndices, ObjectVertices, ARRAYSIZE(ObjectIndices), m_ImmediateContext, m_d3dDevice);
        t_GameObject->SetMeshComponent(t_GameObjectMesh);

        m_Objects.push_back(t_GameObject);
    }

    // Rendered and Textured Cubes
    {
        DrawableGameObject* t_GameObject = new DrawableGameObject("Default");

        // TRANSFORM
        Transform* t_GameObjectTransform = new Transform(Tag("Transform"), m_d3dDevice);
        t_GameObject->SetTransformComponent(t_GameObjectTransform);
        t_GameObjectTransform->SetPosition(0.0f, 0.0f, 0.0f);
        t_GameObjectTransform->SetScale(1.0f, 1.0f, 1.0f);

        // RENDER
        Render* t_GameObjectRender = new Render(Tag("Render"), m_d3dDevice);
        t_GameObject->SetRenderComponent(t_GameObjectRender);
        t_GameObjectRender->SetBaseTexture(L"Resources\\maps\\Crate_COLOR.dds", m_d3dDevice);
        t_GameObjectRender->SetNormalTexture(L"Resources\\maps\\Crate_NRM.dds", m_d3dDevice);
        t_GameObjectRender->SetSpecularTexture(L"Resources\\maps\\Crate_SPEC.dds", m_d3dDevice);

        // MESH
        Mesh::CalculateModelVectors(ObjectVertices, 36);
        Mesh* t_GameObjectMesh = new Mesh(Tag("Mesh"), ObjectIndices, ObjectVertices, ARRAYSIZE(ObjectIndices), m_ImmediateContext, m_d3dDevice);
        t_GameObject->SetMeshComponent(t_GameObjectMesh);

        m_Objects.push_back(t_GameObject);
    }

    // Alternative Cube
    {
        DrawableGameObject* t_GameObject = new DrawableGameObject("Alt Cube");

        // TRANSFORM
        Transform* t_GameObjectTransform = new Transform(Tag("Transform"), m_d3dDevice);
        t_GameObject->SetTransformComponent(t_GameObjectTransform);
        t_GameObjectTransform->SetPosition(5.0f, 0.0f, 5.0f);
        t_GameObjectTransform->SetScale(1.0f, 1.0f, 1.0f);

        // RENDER
        Render* t_GameObjectRender = new Render(Tag("Render"), m_d3dDevice);
        t_GameObject->SetRenderComponent(t_GameObjectRender);
        t_GameObjectRender->SetBaseTexture(L"Resources\\maps\\stone.dds", m_d3dDevice);
        t_GameObjectRender->SetNormalTexture(L"Resources\\maps\\conenormal.dds", m_d3dDevice);

        // MESH
        Mesh::CalculateModelVectors(ObjectVertices, 36);
        Mesh* t_GameObjectMesh = new Mesh(Tag("Mesh"), ObjectIndices, ObjectVertices, ARRAYSIZE(ObjectIndices), m_ImmediateContext, m_d3dDevice);
        t_GameObject->SetMeshComponent(t_GameObjectMesh);

        m_Objects.push_back(t_GameObject);
    }

    // MONKEY
    {
        // GAME OBJECT
        DrawableGameObject* t_MonkeyObject = new DrawableGameObject("Monkey");

        // TRANSFORM
        Transform* t_MonkeyTransform = new Transform(Tag("Transform"), m_d3dDevice);
        t_MonkeyObject->SetTransformComponent(t_MonkeyTransform);
        t_MonkeyTransform->SetPosition(5.0f, 0.0f, 0.0f);
        t_MonkeyTransform->SetScale(1.0f, 1.0f, 1.0f);

        // RENDER
        Render* t_MonkeyRender = new Render(Tag("Render"), m_d3dDevice);
        t_MonkeyObject->SetRenderComponent(t_MonkeyRender); 

        // MESH
        LoadMesh* t_MonkeyModel = MeshLoader::LoadObj((char*)"Resources/Meshes/monkey.obj");
        Mesh::CalculateModelVectors(t_MonkeyModel->Vertices, t_MonkeyModel->IndexCount);
        Mesh* t_MonkeyMesh = new Mesh(Tag("Mesh"), t_MonkeyModel->indices, t_MonkeyModel->Vertices, (UINT)t_MonkeyModel->IndexCount, m_ImmediateContext, m_d3dDevice);
        t_MonkeyObject->SetMeshComponent(t_MonkeyMesh);
        m_Objects.push_back(t_MonkeyObject);
    }

    // KRAB
    {
        DrawableGameObject* t_GameObject = new DrawableGameObject("Krab");

        // TRANSFORM
        Transform* t_GameObjectTransform = new Transform(Tag("Transform"), m_d3dDevice);
        t_GameObject->SetTransformComponent(t_GameObjectTransform);
        t_GameObjectTransform->SetPosition(-3.0f, 0.0f, 0.0f);
        t_GameObjectTransform->SetScale(2.0f, 2.0f, 2.0f);

        // RENDER
        Render* t_GameObjectRender = new Render(Tag("Render"), m_d3dDevice);
        t_GameObject->SetRenderComponent(t_GameObjectRender);
        t_GameObjectRender->SetBaseTexture(L"Resources\\maps\\Krab_COLOR.dds", m_d3dDevice);

        // MESH
        LoadMesh* t_KrabModel = MeshLoader::LoadObj((char*)"Resources/Meshes/krab.obj");
        Mesh::CalculateModelVectors(t_KrabModel->Vertices, t_KrabModel->IndexCount);
        Mesh* t_KrabMesh = new Mesh(Tag("Mesh"), t_KrabModel->indices, t_KrabModel->Vertices, (UINT)t_KrabModel->IndexCount, m_ImmediateContext, m_d3dDevice);
        t_GameObject->SetMeshComponent(t_KrabMesh);
        m_Objects.push_back(t_GameObject);
    }

    // BOWL
    {
        DrawableGameObject* t_GameObject = new DrawableGameObject("Bowl");

        // TRANSFORM
        Transform* t_GameObjectTransform = new Transform(Tag("Transform"), m_d3dDevice);
        t_GameObject->SetTransformComponent(t_GameObjectTransform);
        t_GameObjectTransform->SetPosition(5.0f, 0.0f, 10.0f);
        t_GameObjectTransform->SetScale(0.1f, 0.1f, 0.1f);

        // RENDER
        Render* t_GameObjectRender = new Render(Tag("Render"), m_d3dDevice);
        t_GameObject->SetRenderComponent(t_GameObjectRender);
        t_GameObjectRender->SetBaseTexture(L"Resources\\maps\\Bowl_COLOR.dds", m_d3dDevice);
        t_GameObjectRender->SetNormalTexture(L"Resources\\maps\\Bowl_NORM.dds", m_d3dDevice);

        // MESH
        LoadMesh* t_BowlModel = MeshLoader::LoadObj((char*)"Resources/Meshes/bowl.obj");
        Mesh::CalculateModelVectors(t_BowlModel->Vertices, t_BowlModel->IndexCount);
        Mesh* t_BowlMesh = new Mesh(Tag("Mesh"), t_BowlModel->indices, t_BowlModel->Vertices, (UINT)t_BowlModel->IndexCount, m_ImmediateContext, m_d3dDevice);
        t_GameObject->SetMeshComponent(t_BowlMesh);
        m_Objects.push_back(t_GameObject);
    }

    // BOX
    {
        DrawableGameObject* t_GameObject = new DrawableGameObject("Box");

        // TRANSFORM
        Transform* t_GameObjectTransform = new Transform(Tag("Transform"), m_d3dDevice);
        t_GameObject->SetTransformComponent(t_GameObjectTransform);
        t_GameObjectTransform->SetPosition(10.0f, 0.0f, 0.0f);
        t_GameObjectTransform->SetScale(1.f, 1.f, 1.0f);

        // RENDER
        Render* t_GameObjectRender = new Render(Tag("Render"), m_d3dDevice);
        t_GameObject->SetRenderComponent(t_GameObjectRender);
        t_GameObjectRender->SetBaseTexture(L"Resources\\maps\\Box_COLOR.dds", m_d3dDevice);
        t_GameObjectRender->SetNormalTexture(L"Resources\\maps\\Box_NORM.dds", m_d3dDevice);

        // MESH
        LoadMesh* t_ObjectModel = MeshLoader::LoadObj((char*)"Resources/Meshes/Box.obj");
        Mesh::CalculateModelVectors(t_ObjectModel->Vertices, t_ObjectModel->IndexCount);
        Mesh* t_ObjectMesh = new Mesh(Tag("Mesh"), t_ObjectModel->indices, t_ObjectModel->Vertices, (UINT)t_ObjectModel->IndexCount, m_ImmediateContext, m_d3dDevice);
        t_GameObject->SetMeshComponent(t_ObjectMesh);
        m_Objects.push_back(t_GameObject);
    }

    // GUN
    {
        // GAME OBJECT
        DrawableGameObject* t_GunObject = new DrawableGameObject("Gun");

        // TRANSFORM
        Transform* t_GunTransform = new Transform(Tag("Transform"), m_d3dDevice);
        t_GunObject->SetTransformComponent(t_GunTransform);
        t_GunTransform->SetPosition(0.5f, 0.0f, 0.0f);
        t_GunTransform->SetScale(30.0f, 30.0f, 30.0f);

        // RENDER
        Render* t_GunRender = new Render(Tag("Render"), m_d3dDevice);
        t_GunObject->SetRenderComponent(t_GunRender);
        t_GunRender->SetBaseTexture(L"Resources\\Gun_COLOR.dds", m_d3dDevice);

        // MESH
        LoadMesh* t_GunModel = MeshLoader::LoadObj((char*)"Resources/Models/GunMagazine.obj");
        Mesh::CalculateModelVectors(t_GunModel->Vertices, t_GunModel->IndexCount);
        Mesh* t_GunMesh = new Mesh(Tag("Mesh"), t_GunModel->indices, t_GunModel->Vertices, (UINT)t_GunModel->IndexCount, m_ImmediateContext, m_d3dDevice);
        t_GunObject->SetMeshComponent(t_GunMesh);
        // m_Objects.push_back(t_GunObject);
    }

    // PLANE
    {
        // PLANE OBJECT
        DrawableGameObject* t_PlaneObject = new DrawableGameObject("Plane");

        // TRANSFORM
        Transform * t_PlaneTransform = new Transform(Tag("Transform"), m_d3dDevice);
        t_PlaneObject->SetTransformComponent(t_PlaneTransform);
        t_PlaneTransform->SetPosition(0.0f, -1.0f, 0.0f);
        t_PlaneTransform->SetScale(30.0f, 1.0f, 30.0f);

        // RENDER
        Render* t_PlaneRender = new Render(Tag("Render"), m_d3dDevice);
        t_PlaneObject->SetRenderComponent(t_PlaneRender);

        // MESH
        LoadMesh* t_PlaneModel = MeshLoader::LoadObj((char*)"Resources/Meshes/plane.obj");
        Mesh::CalculateModelVectors(t_PlaneModel->Vertices, t_PlaneModel->IndexCount);
        Mesh* t_PlaneMesh = new Mesh(Tag("Mesh"), t_PlaneModel->indices, t_PlaneModel->Vertices, (UINT)t_PlaneModel->IndexCount, m_ImmediateContext, m_d3dDevice);
        t_PlaneObject->SetMeshComponent(t_PlaneMesh);
        m_Objects.push_back(t_PlaneObject);
    }



    // Full Screen Quad
    SimpleVertex vertices[] =
    {
        { XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) }
    };

    WORD indices[] =
    {
        0,1,2,
        0,2,3,
    };

    // QUAD MESH SET UP
    m_QuadMesh = new Mesh(Tag("Mesh"), indices, vertices, ARRAYSIZE(indices), m_ImmediateContext, m_d3dDevice);
}

HRESULT GraphicsManager::InitRunTimeParameters()
{
    HRESULT hr = S_OK;

    // Create the constant buffer
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(ConstantBuffer);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    hr = m_d3dDevice->CreateBuffer(&bd, nullptr, &m_ConstantBuffer);
    if (FAILED(hr))
        return hr;

    // Create the light constant buffer
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(LightPropertiesConstantBuffer);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    hr = m_d3dDevice->CreateBuffer(&bd, nullptr, &m_LightConstantBuffer);
    if (FAILED(hr))
        return hr;

    // TIMER VARIABLE
    m_Timer = new Timer();

    // BASE SHADER
    D3D11_INPUT_ELEMENT_DESC t_BaseLayout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    m_BaseShader = new Shader(L"BaseShader.fx", t_BaseLayout, ARRAYSIZE(t_BaseLayout), m_ImmediateContext, m_d3dDevice);
    m_NewNormalShader = new Shader(L"NormalShader.fx", t_BaseLayout, ARRAYSIZE(t_BaseLayout), m_ImmediateContext, m_d3dDevice);

    // QUAD SHADER
    D3D11_INPUT_ELEMENT_DESC t_DefaultLayout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    m_QuadShader = new Shader(L"QuadShader.fx", t_DefaultLayout, ARRAYSIZE(t_DefaultLayout), m_ImmediateContext, m_d3dDevice);

    // POST-PROCESSING
    m_DepthOfFieldShader = new Shader(L"DepthOfFieldShader.fx", t_DefaultLayout, ARRAYSIZE(t_DefaultLayout), m_ImmediateContext, m_d3dDevice);
    m_RenderTargetShader = new Shader(L"RenderToTargetShader.fx", t_DefaultLayout, ARRAYSIZE(t_DefaultLayout), m_ImmediateContext, m_d3dDevice);

    // GBUFFER SHADER(s)
    m_DepthBufferShader = new Shader(L"DepthShader.fx", t_DefaultLayout, ARRAYSIZE(t_DefaultLayout), m_ImmediateContext, m_d3dDevice);
    m_GbufferShader = new Shader(L"GBufferShader.fx", t_DefaultLayout, ARRAYSIZE(t_DefaultLayout), m_ImmediateContext, m_d3dDevice);
    m_PositionShader = new Shader(L"PositionShader.fx", t_DefaultLayout, ARRAYSIZE(t_DefaultLayout), m_ImmediateContext, m_d3dDevice);
    m_ColourShader = new Shader(L"ColourShader.fx", t_DefaultLayout, ARRAYSIZE(t_DefaultLayout), m_ImmediateContext, m_d3dDevice);
    m_SpecularShader = new Shader(L"SpecularShader.fx", t_DefaultLayout, ARRAYSIZE(t_DefaultLayout), m_ImmediateContext, m_d3dDevice);

    // LIGHTS
    // NOTE: Init Light Variables
    for (int i = 0; i < m_Lights.size(); ++i) { m_Lights[i] = new LightObject(m_d3dDevice); }

    // Light Creation
    LightObject* t_FirstLight = new LightObject(m_d3dDevice);
    t_FirstLight->SetEnabled(true);
    t_FirstLight->SetLightType(PointLight);
    t_FirstLight->SetPosition(-7.0f, 0.0f, 0.0f, 1.0f);
    t_FirstLight->SetDirection(1.0f, 0.0f, 1.0f, 1.0f);
    t_FirstLight->SetColor(5.0f, 0.0f, 0.0f, 1.0f);
    t_FirstLight->SetSpotAngle(XMConvertToRadians(0.0f));
    t_FirstLight->SetConstantAttenuation(1.0f);
    t_FirstLight->SetLinearAttenuation(1.0f);
    t_FirstLight->SetQuadraticAttenuation(1.0f);

    m_Lights[0]->SetLightData(t_FirstLight);


    LightObject* t_SecondLight = new LightObject(m_d3dDevice);
    t_SecondLight->SetEnabled(true);
    t_SecondLight->SetLightType(PointLight);
    t_SecondLight->SetPosition(7.2f, 1.1f, 2.5f, 1.0f);
    t_SecondLight->SetDirection(1.0f, 0.0f, 1.0f, 1.0f);
    t_SecondLight->SetColor(0.0f, 5.0f, 5.0f, 1.0f);
    t_SecondLight->SetSpotAngle(XMConvertToRadians(45.0f));
    t_SecondLight->SetConstantAttenuation(1.0f);
    t_SecondLight->SetLinearAttenuation(1.0f);
    t_SecondLight->SetQuadraticAttenuation(1.0f);

    m_Lights[1]->SetLightData(t_SecondLight);


    LightObject* t_ThirdLight = new LightObject(m_d3dDevice);
    t_ThirdLight->SetEnabled(true);
    t_ThirdLight->SetLightType(PointLight);
    t_ThirdLight->SetPosition(0.0f, 0.0f, 5.0f, 1.0f);
    t_ThirdLight->SetDirection(1.0f, 0.0f, 1.0f, 1.0f);
    t_ThirdLight->SetColor(5.0f, 0.0f, 5.0f, 1.0f);
    t_ThirdLight->SetSpotAngle(XMConvertToRadians(45.0f));
    t_ThirdLight->SetConstantAttenuation(1.0f);
    t_ThirdLight->SetLinearAttenuation(1.0f);
    t_ThirdLight->SetQuadraticAttenuation(1.0f);

    m_Lights[2]->SetLightData(t_ThirdLight);

    return hr;
}

GraphicsManager::~GraphicsManager()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    // Remove any bound render target or depth/stencil buffer
    ID3D11RenderTargetView* nullViews[] = { nullptr };
    m_ImmediateContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    if (m_ImmediateContext) m_ImmediateContext->ClearState();
    // Flush the immediate context to force cleanup
    if (m_ImmediateContext1) m_ImmediateContext1->Flush();
    m_ImmediateContext->Flush();
    if (m_LightConstantBuffer) m_LightConstantBuffer->Release();
    if (m_ConstantBuffer) m_ConstantBuffer->Release();
    if (m_DepthStencil) m_DepthStencil->Release();
    if (m_DepthStencilView) m_DepthStencilView->Release();
    if (m_RenderTargetView) m_RenderTargetView->Release();
    if (m_SwapChain1) m_SwapChain1->Release();
    if (m_SwapChain) m_SwapChain->Release();
    if (m_ImmediateContext1) m_ImmediateContext1->Release();
    if (m_ImmediateContext) m_ImmediateContext->Release();

    // SHADER DELETE(s)
    m_VertexShader = nullptr;
    m_PixelShader = nullptr;

    delete m_NewNormalEffect;
    delete m_DepthEffect;

    delete m_BaseShader;
    delete m_DepthBufferShader;
    delete m_QuadShader;

    // GENERIC DELETE(s)

    std::array<LightObject*, 3>::iterator t_LightItr = m_Lights.begin();
    for (t_LightItr; t_LightItr != m_Lights.end(); ++t_LightItr) { delete* t_LightItr; }

    delete m_Camera;
    delete m_Timer;


    // DEVICE DELETE
    ID3D11Debug* debugDevice = nullptr;
    m_d3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDevice));

    if (m_d3dDevice1) m_d3dDevice1->Release();
    if (m_d3dDevice) m_d3dDevice->Release();

    // handy for finding dx memory leaks
    debugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);

    if (debugDevice) debugDevice->Release();
}

void GraphicsManager::Process()
{
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Showcase();
        }
    }
}

LRESULT CALLBACK GraphicsManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    static bool mouseDown = false;

    extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    float t_Speed = 1;

    switch (message)
    {

    case WM_KEYDOWN:

        switch (wParam)
        {

        }
        break;

    case WM_RBUTTONDOWN:
        mouseDown = true;
        break;

    case WM_RBUTTONUP:
        mouseDown = false;
        break;

    case WM_MOUSEMOVE:
    {
        if (!mouseDown)
        {
            break;
        }
        // Get the dimensions of the window
        RECT rect;
        GetClientRect(hWnd, &rect);

        // Calculate the center position of the window
        POINT windowCenter;
        windowCenter.x = (rect.right - rect.left) / 2;
        windowCenter.y = (rect.bottom - rect.top) / 2;

        // Convert the client area point to screen coordinates
        ClientToScreen(hWnd, &windowCenter);

        // Get the current cursor position
        POINTS mousePos = MAKEPOINTS(lParam);
        POINT cursorPos = { mousePos.x, mousePos.y };
        ClientToScreen(hWnd, &cursorPos);

        // Calculate the delta from the window center
        POINT delta;
        delta.x = cursorPos.x - windowCenter.x;
        delta.y = cursorPos.y - windowCenter.y;

        // Update the camera with the delta
        // (You may need to convert POINT to POINTS or use the deltas as is)
        // m_Camera->UpdateLookAt({ static_cast<short>(delta.x), static_cast<short>(delta.y) });

        // Recenter the cursor
        SetCursorPos(windowCenter.x, windowCenter.y);
    }
    break;

    case WM_ACTIVATE:
        if (LOWORD(wParam) != WA_INACTIVE) {
            CenterMouseInWindow(hWnd);
        }
        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

        // Note that this tutorial does not handle resizing (WM_SIZE) requests,
        // so we created the window without the resize border.

    default:

        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

void GraphicsManager::Showcase()
{
    float t_DeltaTime = m_Timer->GetDeltaTime();
    if (t_DeltaTime == 0) return;

    // TODO: Move this at the bottom so that shader resources can be passed into the ImGUI display, the reason it returns null is because the effects get set after
    BeginGUI();
    ProcessGUI();

    m_Camera->Update(t_DeltaTime);

    // BASE RENDER AFFECT
    m_BaseEffect->StartEffect(Colors::MidnightBlue, m_ImmediateContext);
    {
        for (auto& v : m_Objects)
        {
            v->update(t_DeltaTime, m_ImmediateContext);
    
            ConstantBuffer cb1;
            cb1.mWorld = XMMatrixTranspose(v->GetTransformComponent()->GetWorld());
            cb1.mView = XMMatrixTranspose(XMLoadFloat4x4(&m_Camera->GetView()));
            cb1.mProjection = XMMatrixTranspose(XMLoadFloat4x4(&m_Camera->GetProjection()));
            cb1.vOutputColor = XMFLOAT4(0, 0, 0, 0);
            m_ImmediateContext->UpdateSubresource(m_ConstantBuffer, 0, nullptr, &cb1, 0, 0);
    
            // Update Lights
            LightPropertiesConstantBuffer t_LitBuff;
            for (int i = 0; i < m_Lights.size(); ++i)
            {
                t_LitBuff.EyePosition = m_Lights[i]->GetPosition();
                t_LitBuff.Lights[i] = m_Lights[i]->GetLightData();
            }

            LightObject::UpdateLightResource(m_LightConstantBuffer, t_LitBuff, m_ImmediateContext, m_d3dDevice);

            Shader::SetInputLayout(m_BaseShader->GetInputLayout(), m_ImmediateContext);
            Shader::SetVertexShader(m_BaseShader->GetVertexShader(), m_ConstantBuffer, m_ImmediateContext);
            Shader::SetPixelShader(m_BaseShader->GetPixelShader(), m_LightConstantBuffer, m_ImmediateContext);
    
            ID3D11Buffer* materialCB = v->GetRenderComponent()->GetMaterialBuffer();
            m_ImmediateContext->PSSetConstantBuffers(1, 1, &materialCB);

            v->draw(m_ImmediateContext);
        }
    }
    m_BaseEffect->EndEffect(m_ImmediateContext);

    // RENDER TO TEXTURE OBJECTS // TODO: Add this object in
    m_OutputEffect->StartEffect(Colors::Green, m_ImmediateContext);
    {
        int t_index = 0;
        for (auto& v : m_Objects)
        {
            ++t_index;
            ConstantBuffer cb1;
            cb1.mWorld = XMMatrixTranspose(v->GetTransformComponent()->GetWorld());
            cb1.mView = XMMatrixTranspose(XMLoadFloat4x4(&m_Camera->GetView()));
            cb1.mProjection = XMMatrixTranspose(XMLoadFloat4x4(&m_Camera->GetProjection()));
            cb1.vOutputColor = XMFLOAT4(0, 0, 0, 0);
            m_ImmediateContext->UpdateSubresource(m_ConstantBuffer, 0, nullptr, &cb1, 0, 0);
            
            if (t_index == 1) { v->GetRenderComponent()->SetShaderBaseTexture(m_BaseEffect->GetShaderResourceView()); }

            Shader::SetInputLayout(m_RenderTargetShader->GetInputLayout(), m_ImmediateContext);
            Shader::SetVertexShader(m_RenderTargetShader->GetVertexShader(), m_ConstantBuffer, m_ImmediateContext);
            Shader::SetPixelShader(m_RenderTargetShader->GetPixelShader(), m_ImmediateContext);
     
            v->update(t_DeltaTime, m_ImmediateContext);
            v->draw(m_ImmediateContext);
        }
    }
    m_OutputEffect->EndEffect(m_ImmediateContext);

    // NORMAL TEXTURE
    m_NewNormalEffect->StartEffect(Colors::Black, m_ImmediateContext);
    {
        for (auto* v : m_Objects)
        {
            v->update(t_DeltaTime, m_ImmediateContext);

            NormalBuffer t_ConstantNorm;
            t_ConstantNorm.world = XMMatrixTranspose(v->GetTransformComponent()->GetWorld());
            t_ConstantNorm.view = XMMatrixTranspose(XMLoadFloat4x4(&m_Camera->GetView()));
            t_ConstantNorm.projection = XMMatrixTranspose(XMLoadFloat4x4(&m_Camera->GetProjection()));
            t_ConstantNorm.HasNormalTexture = v->GetRenderComponent()->GetHasNormal();
            m_ImmediateContext->UpdateSubresource(m_ConstantBuffer, 0, nullptr, &t_ConstantNorm, 0, 0);
            
            Shader::SetInputLayout(m_NewNormalShader->GetInputLayout(), m_ImmediateContext);
            Shader::SetVertexShader(m_NewNormalShader->GetVertexShader(), m_ConstantBuffer, m_ImmediateContext);
            Shader::SetPixelShader(m_NewNormalShader->GetPixelShader(), m_ImmediateContext);

            v->draw(m_ImmediateContext);
        }
    }
    m_NewNormalEffect->EndEffect(m_ImmediateContext);

    // COLOUR / ALBEDO TEXTURE
    m_ColourEffect->StartEffect(Colors::Black, m_ImmediateContext);
    {
        for (auto& v : m_Objects)
        {
            v->update(t_DeltaTime, m_ImmediateContext);

            ColourBuffer t_ConstantColourBuffer;
            t_ConstantColourBuffer.world = XMMatrixTranspose(v->GetTransformComponent()->GetWorld());
            t_ConstantColourBuffer.view = XMMatrixTranspose(XMLoadFloat4x4(&m_Camera->GetView()));
            t_ConstantColourBuffer.projection = XMMatrixTranspose(XMLoadFloat4x4(&m_Camera->GetProjection()));
            m_ImmediateContext->UpdateSubresource(m_ConstantBuffer, 0, nullptr, &t_ConstantColourBuffer, 0, 0);

            Shader::SetInputLayout(m_ColourShader->GetInputLayout(), m_ImmediateContext);
            Shader::SetVertexShader(m_ColourShader->GetVertexShader(), m_ConstantBuffer, m_ImmediateContext);
            Shader::SetPixelShader(m_ColourShader->GetPixelShader(), m_ImmediateContext);

            v->draw(m_ImmediateContext);
        }
    }
    m_ColourEffect->EndEffect(m_ImmediateContext);

    // DEPTH TEXTURE
    m_DepthEffect->StartEffect(Colors::Black, m_ImmediateContext);
    {
        for (auto& v : m_Objects)
        {
            v->update(t_DeltaTime, m_ImmediateContext);

            DepthBuffer t_ConstantDepthBuffer;
            t_ConstantDepthBuffer.world = XMMatrixTranspose(v->GetTransformComponent()->GetWorld());
            t_ConstantDepthBuffer.view = XMMatrixTranspose(XMLoadFloat4x4(&m_Camera->GetView()));
            t_ConstantDepthBuffer.projection = XMMatrixTranspose(XMLoadFloat4x4(&m_Camera->GetProjection()));
            m_ImmediateContext->UpdateSubresource(m_ConstantBuffer, 0, nullptr, &t_ConstantDepthBuffer, 0, 0);

            Shader::SetInputLayout(m_DepthBufferShader->GetInputLayout(), m_ImmediateContext);
            Shader::SetVertexShader(m_DepthBufferShader->GetVertexShader(), m_ConstantBuffer, m_ImmediateContext);
            Shader::SetPixelShader(m_DepthBufferShader->GetPixelShader(), m_ImmediateContext);

            v->draw(m_ImmediateContext);
        }
    }
    m_DepthEffect->EndEffect(m_ImmediateContext);

    // POSITION TEXTURE
    m_PositionEffect->StartEffect(Colors::Black, m_ImmediateContext);
    {
        for (auto& v : m_Objects)
        {
            v->update(t_DeltaTime, m_ImmediateContext);

            PositionBuffer t_ConstantPositionBuffer;
            t_ConstantPositionBuffer.world = XMMatrixTranspose(v->GetTransformComponent()->GetWorld());
            t_ConstantPositionBuffer.view = XMMatrixTranspose(XMLoadFloat4x4(&m_Camera->GetView()));
            t_ConstantPositionBuffer.projection = XMMatrixTranspose(XMLoadFloat4x4(&m_Camera->GetProjection()));
            m_ImmediateContext->UpdateSubresource(m_ConstantBuffer, 0, nullptr, &t_ConstantPositionBuffer, 0, 0);

            Shader::SetInputLayout(m_PositionShader->GetInputLayout(), m_ImmediateContext);
            Shader::SetVertexShader(m_PositionShader->GetVertexShader(), m_ConstantBuffer, m_ImmediateContext);
            Shader::SetPixelShader(m_PositionShader->GetPixelShader(), m_ImmediateContext);

            v->draw(m_ImmediateContext);
        }
    }
    m_PositionEffect->EndEffect(m_ImmediateContext);

    // SPECULAR TEXTURE
    m_SpecularEffect->StartEffect(Colors::Black, m_ImmediateContext);
    {
        for (auto& v : m_Objects)
        {
            SpecularBuffer t_ConstantSpecBuffer;
            t_ConstantSpecBuffer.world = XMMatrixTranspose(v->GetTransformComponent()->GetWorld());
            t_ConstantSpecBuffer.view = XMMatrixTranspose(XMLoadFloat4x4(&m_Camera->GetView()));
            t_ConstantSpecBuffer.projection = XMMatrixTranspose(XMLoadFloat4x4(&m_Camera->GetProjection()));
            t_ConstantSpecBuffer.HasSpecularTexture = v->GetRenderComponent()->GetHasSpecular();
            m_ImmediateContext->UpdateSubresource(m_ConstantBuffer, 0, nullptr, &t_ConstantSpecBuffer, 0, 0);

            Shader::SetInputLayout(m_SpecularShader->GetInputLayout(), m_ImmediateContext);
            Shader::SetVertexShader(m_SpecularShader->GetVertexShader(), m_ConstantBuffer, m_ImmediateContext);
            Shader::SetPixelShader(m_SpecularShader->GetPixelShader(), m_ImmediateContext);

            v->draw(m_ImmediateContext);
        }
    }
    m_SpecularEffect->EndEffect(m_ImmediateContext);

    ShowcaseGUI();
    EndGUI();

    m_GbufferEffect->StartEffect(Colors::Black, m_ImmediateContext);
    {
        for (auto& v : m_Objects)
        {
            // TEXTURE(s)
            m_ImmediateContext->PSSetShaderResources(0, 1, m_ColourEffect->GetShaderResourceView());
            m_ImmediateContext->PSSetSamplers(0, 1, m_ColourEffect->GetSamplerState());

            m_ImmediateContext->PSSetShaderResources(1, 1, m_NewNormalEffect->GetShaderResourceView());
            m_ImmediateContext->PSSetSamplers(1, 1, m_NewNormalEffect->GetSamplerState());

            m_ImmediateContext->PSSetShaderResources(2, 1, m_PositionEffect->GetShaderResourceView());
            m_ImmediateContext->PSSetSamplers(2, 1, m_PositionEffect->GetSamplerState());

            m_ImmediateContext->PSSetShaderResources(3, 1, m_SpecularEffect->GetShaderResourceView());
            m_ImmediateContext->PSSetSamplers(3, 1, m_SpecularEffect->GetSamplerState());

            GeoBuffer t_ConstantPositionBuffer;
            t_ConstantPositionBuffer.world = XMMatrixTranspose(v->GetTransformComponent()->GetWorld());
            t_ConstantPositionBuffer.view = XMMatrixTranspose(XMLoadFloat4x4(&m_Camera->GetView()));
            t_ConstantPositionBuffer.projection = XMMatrixTranspose(XMLoadFloat4x4(&m_Camera->GetProjection()));
            m_ImmediateContext->UpdateSubresource(m_ConstantBuffer, 0, nullptr, &t_ConstantPositionBuffer, 0, 0);
        
            // Update Lights
            LightPropertiesConstantBuffer t_LitBuff;
            for (int i = 0; i < m_Lights.size(); ++i)
            {
                t_LitBuff.EyePosition = m_Lights[i]->GetPosition();
                t_LitBuff.Lights[i] = m_Lights[i]->GetLightData();
            }

            LightObject::UpdateLightResource(m_LightConstantBuffer, t_LitBuff, m_ImmediateContext, m_d3dDevice);

            Shader::SetInputLayout(m_GbufferShader->GetInputLayout(), m_ImmediateContext);
            Shader::SetVertexShader(m_GbufferShader->GetVertexShader(), m_ConstantBuffer, m_ImmediateContext);
            Shader::SetPixelShader(m_GbufferShader->GetPixelShader(), m_LightConstantBuffer, m_ImmediateContext);

            ID3D11Buffer* materialCB = v->GetRenderComponent()->GetMaterialBuffer();
            m_ImmediateContext->PSSetConstantBuffers(1, 1, &materialCB);
        }

        // DRAW FULLSCREEN QUAD
        m_QuadMesh->Draw(m_ImmediateContext);
    }
    m_GbufferEffect->EndEffect(m_ImmediateContext);

    // QUAD / GBUFFER DISPLAY
    ShaderEffect* t_PresentEffect = nullptr;
    ShaderEffect::S_StartEffect(&m_RenderTargetView, m_DepthStencilView, m_DefaultBlendState, Colors::White, m_ImmediateContext);
    {
        if (m_RenderAlternative == true)
        { 
            m_ImmediateContext->PSSetShaderResources(0, 1, m_GbufferEffect->GetShaderResourceView());
            m_ImmediateContext->PSSetSamplers(0, 1, m_GbufferEffect->GetSamplerState());
            t_PresentEffect = m_GbufferEffect;
        }
        else
        {
             // NOTE: This is for the none deferred scene
            m_ImmediateContext->PSSetShaderResources(0, 1, m_BaseEffect->GetShaderResourceView());
            m_ImmediateContext->PSSetSamplers(0, 1, m_BaseEffect->GetSamplerState());
            t_PresentEffect = m_BaseEffect;
        }

        Shader::SetInputLayout(m_QuadShader->GetInputLayout(), m_ImmediateContext);
        Shader::SetVertexShader(m_QuadShader->GetVertexShader(), m_ImmediateContext);
        Shader::SetPixelShader(m_QuadShader->GetPixelShader(), m_ImmediateContext);

        // DRAW FULLSCREEN QUAD
        m_QuadMesh->Draw(m_ImmediateContext);
    }
    ShaderEffect::S_EndEffect(m_ImmediateContext);

    // NOTE: Depth of Field
    if (m_RenderDepthOfField == true)
    {
        // NOTE: Depth of Field
        m_DepthOfFieldEffect->StartEffect(Colors::Black, m_ImmediateContext);
        {
            // NOTE: Scene Texture
            m_ImmediateContext->PSSetShaderResources(0, 1, t_PresentEffect->GetShaderResourceView());
            m_ImmediateContext->PSSetSamplers(0, 1, t_PresentEffect->GetSamplerState());

            // NOTE: Depth Test
            m_ImmediateContext->PSSetShaderResources(1, 1, m_DepthEffect->GetShaderResourceView());
            m_ImmediateContext->PSSetSamplers(1, 1, m_DepthEffect->GetSamplerState());

            // NOTE: DO SHADER STUFF
            Shader::SetInputLayout(m_DepthOfFieldShader->GetInputLayout(), m_ImmediateContext);
            Shader::SetVertexShader(m_DepthOfFieldShader->GetVertexShader(), m_ImmediateContext);
            Shader::SetPixelShader(m_DepthOfFieldShader->GetPixelShader(), m_ImmediateContext);

            m_QuadMesh->Draw(m_ImmediateContext);
        }
        m_DepthEffect->EndEffect(m_ImmediateContext);

        m_ImmediateContext->PSSetShaderResources(0, 1, m_DepthOfFieldEffect->GetShaderResourceView());
        m_ImmediateContext->PSSetSamplers(0, 1, m_DepthOfFieldEffect->GetSamplerState());
    }

    // NOTE: POST-PROCESSING START
    m_ShaderEffectsManager->Draw(SCREEN_WIDTH, SCREEN_WIDTH, m_ImmediateContext, m_d3dDevice, m_QuadMesh);


        // Clear and Draw Quad
        ShaderEffect::S_StartEffect(&m_RenderTargetView, m_DepthStencilView, m_DefaultBlendState, Colors::Black, m_ImmediateContext);
        {
            m_QuadMesh->Draw(m_ImmediateContext);

            ImGui::Render();
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        }
        ShaderEffect::S_EndEffect(m_ImmediateContext);


    // POST-PROCESSING END
    m_ShaderEffectsManager->ClearShaderManager();


    // Present our back buffer to our front buffer
    m_SwapChain->Present(0, 0);
}

HRESULT GraphicsManager::InitDevice()
{
    // Sets Up Device
    HRESULT hr = S_OK;

    // MSAA Anti Alisaing Activation
    UINT t_MaxQuality = 0;
    UINT t_SampleCount = 1;

    #pragma region Device Set Up

    RECT rc;
    GetClientRect(m_HWnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        m_DriverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDevice(nullptr, m_DriverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
            D3D11_SDK_VERSION, &m_d3dDevice, &m_FeatureLevel, &m_ImmediateContext);

        if (hr == E_INVALIDARG)
        {
            // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
            hr = D3D11CreateDevice(nullptr, m_DriverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
                D3D11_SDK_VERSION, &m_d3dDevice, &m_FeatureLevel, &m_ImmediateContext);
        }

        if (SUCCEEDED(hr))
            break;
    }
    if (FAILED(hr))
        return hr;

    // Obtain DXGI factory from device (since we used nullptr for pAdapter above)
    IDXGIFactory1* dxgiFactory = nullptr;
    {
        IDXGIDevice* dxgiDevice = nullptr;
        hr = m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
        if (SUCCEEDED(hr))
        {
            IDXGIAdapter* adapter = nullptr;
            hr = dxgiDevice->GetAdapter(&adapter);
            if (SUCCEEDED(hr))
            {
                hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
                adapter->Release();
            }
            dxgiDevice->Release();
        }
    }
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"Failed to create device.", L"Error", MB_OK);
        return hr;
    }

    // Create swap chain
    IDXGIFactory2* dxgiFactory2 = nullptr;
    hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
    if (dxgiFactory2)
    {
        // DirectX 11.1 or later
        hr = m_d3dDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&m_d3dDevice1));
        if (SUCCEEDED(hr))
        {
            (void)m_ImmediateContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&m_ImmediateContext1));
        }

        DXGI_SWAP_CHAIN_DESC1 sd = {};
        sd.Width = width;
        sd.Height = height;
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//  DXGI_FORMAT_R16G16B16A16_FLOAT;////DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 1;

        hr = dxgiFactory2->CreateSwapChainForHwnd(m_d3dDevice, m_HWnd, &sd, nullptr, nullptr, &m_SwapChain1);
        if (SUCCEEDED(hr))
        {
            hr = m_SwapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&m_SwapChain));
        }

        dxgiFactory2->Release();
    }
    else
    {
        // DirectX 11.0 systems
        DXGI_SWAP_CHAIN_DESC sd = {};
        sd.BufferCount = 1;
        sd.BufferDesc.Width = width;
        sd.BufferDesc.Height = height;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = m_HWnd;
        sd.SampleDesc.Count = t_SampleCount;

        hr = m_d3dDevice->CheckMultisampleQualityLevels(sd.BufferDesc.Format, sd.SampleDesc.Count, &t_MaxQuality);
        t_MaxQuality = 1; // Check > 0
        sd.SampleDesc.Quality = t_MaxQuality;
        sd.Windowed = TRUE;

        hr = dxgiFactory->CreateSwapChain(m_d3dDevice, &sd, &m_SwapChain);
    }

    // Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
    dxgiFactory->MakeWindowAssociation(m_HWnd, DXGI_MWA_NO_ALT_ENTER);

    dxgiFactory->Release();

    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"Failed to create swapchain.", L"Error", MB_OK);
        return hr;
    }

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_ImmediateContext->RSSetViewports(1, &vp);

    // Back Buffer Getter
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"Failed to create a back buffer.", L"Error", MB_OK);
        return hr;
    }

    #pragma endregion

    t_MaxQuality = 0;
    ShaderEffect::S_MakeRenderTargetViewAlt(&m_RenderTargetView, pBackBuffer, m_d3dDevice);
    ShaderEffect::S_MakeDepthTexture2D(&m_DepthStencil, DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_USAGE_DEFAULT, D3D11_BIND_DEPTH_STENCIL, width, height, t_SampleCount, t_MaxQuality, m_d3dDevice);
    ShaderEffect::S_MakeDepthStencilView(&m_DepthStencilView, m_DepthStencil, DXGI_FORMAT_D24_UNORM_S8_UINT, m_d3dDevice);

    // SHADER MANAGER
    m_ShaderEffectsManager = new ShaderEffectsManager(m_ImmediateContext, m_d3dDevice);

    m_BaseEffect = new ShaderEffect(width, height, m_d3dDevice);
    m_OutputEffect = new ShaderEffect(width, height, m_d3dDevice);
    m_DepthEffect = new ShaderEffect(width, height, m_d3dDevice);
    m_BloomEffect = new ShaderEffect(width, height, m_d3dDevice);
    m_DepthOfFieldEffect = new ShaderEffect(width, height, m_d3dDevice);

    // GBUFFER SHADER EFFECT(s)
    m_GbufferEffect = new ShaderEffect(width, height, m_d3dDevice);

    m_ColourEffect = new ShaderEffect(width, height, m_d3dDevice);
    m_PositionEffect = new ShaderEffect(width, height, m_d3dDevice);
    m_NewNormalEffect = new ShaderEffect(width, height, m_d3dDevice);
    m_SpecularEffect = new ShaderEffect(width, height, m_d3dDevice);

    #pragma region Rasterizer State SetUp

    HRESULT t_HR = S_OK;

    // RASTERIZER STATE
    D3D11_RASTERIZER_DESC t_RastDesc = { };
    t_RastDesc.FillMode = D3D11_FILL_SOLID;
    t_RastDesc.CullMode = D3D11_CULL_BACK;
    t_HR = m_d3dDevice->CreateRasterizerState(&t_RastDesc, &m_DefaultRasterizer);
    if (FAILED(t_HR)) return t_HR;

    D3D11_RASTERIZER_DESC t_WireDesc = { };
    t_WireDesc.FillMode = D3D11_FILL_WIREFRAME;
    t_WireDesc.CullMode = D3D11_CULL_NONE;
    t_HR = m_d3dDevice->CreateRasterizerState(&t_WireDesc, &m_WireframeRasterizer);
    if (FAILED(t_HR)) return t_HR;

    D3D11_DEPTH_STENCIL_DESC t_SkyBoxDesc = { };
    t_SkyBoxDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    t_SkyBoxDesc.DepthEnable = true;
    t_SkyBoxDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    t_HR = m_d3dDevice->CreateDepthStencilState(&t_SkyBoxDesc, &m_SkyBoxState);
    if (FAILED(t_HR)) return t_HR;

    #pragma endregion

    #pragma region Blend State Setup

    // BLEND RENDER STATE
    D3D11_BLEND_DESC t_DefaultBlendDesc = { };
    t_DefaultBlendDesc.AlphaToCoverageEnable = false;
    t_DefaultBlendDesc.RenderTarget[0].BlendEnable = false;
    t_DefaultBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_COLOR;
    t_DefaultBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_BLEND_FACTOR;
    t_DefaultBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    t_DefaultBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    t_DefaultBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    t_DefaultBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    t_DefaultBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    t_HR = m_d3dDevice->CreateBlendState(&t_DefaultBlendDesc, &m_DefaultBlendState);
    if (FAILED(t_HR)) return t_HR;

    #pragma endregion

    return S_OK;
}

HRESULT GraphicsManager::InitGUI()
{
    HRESULT hr = S_OK;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(m_HWnd);
    ImGui_ImplDX11_Init(m_d3dDevice, m_ImmediateContext);

    return hr;
}

HRESULT GraphicsManager::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = GraphicsManager::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"lWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
    if (!RegisterClassEx(&wcex))
        return E_FAIL;

    // Create window
    m_HInst = hInstance;
    RECT rc = { 0, 0, 1920, 1080 };

    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    m_HWnd = CreateWindow(L"lWindowClass", L"DirectX 11",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
        nullptr);
    if (!m_HWnd)
        return E_FAIL;

    ShowWindow(m_HWnd, nCmdShow);

    return S_OK;
}

void GraphicsManager::CenterMouseInWindow(HWND hWnd)
{
    // Get the dimensions of the window
    RECT rect;
    GetClientRect(hWnd, &rect);

    // Calculate the center position
    POINT center;
    center.x = (rect.right - rect.left) / 2;
    center.y = (rect.bottom - rect.top) / 2;

    // Convert the client area point to screen coordinates
    ClientToScreen(hWnd, &center);

    // Move the cursor to the center of the screen
    SetCursorPos(center.x, center.y);
}

void GraphicsManager::BeginGUI()
{
    // ImGui::ShowDebugLogWindow();
    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();


    ImGuiStyle& t_Style = ImGui::GetStyle();
    t_Style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1, 0.1, 0.3, 0.5);

    // YOU will want to modify this for your own debug, controls etc - comment it out to hide the window
    

    ImGui::Begin("Attribute Window");
    ImGui::BeginTabBar("General");
}

void GraphicsManager::ProcessGUI()
{
    //if (ImGui::BeginTabItem("Rendering Effects"))
    //{
    //    ImGui::Text("Rendering Select");
    //    if (ImGui::Button("Forward Shading")) { m_RenderAlternative = false; }
    //    if (ImGui::Button("Deferred Shading")) { m_RenderAlternative = true; }
    //    ImGui::EndTabItem();
    //}

    if (ImGui::BeginTabItem("Post-Process Effects"))
    {
        // NOTE: Depth of Field
        ImGui::Text("Activate Depth of Field");
        ImGui::Checkbox("Depth of Field", &m_RenderDepthOfField);

        // NOTE: POST-PROCESSING
        ImGui::Text("Post-Processing");
        for (auto& s : m_ShaderEffectsManager->GetShaderStorageArray())
        {
            _bstr_t t_Convert = s.name;
            const char* t_Name = t_Convert;
            ImGui::Checkbox(t_Name, &s.isActive);
        }
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Object Attributes"))
    {
        int ItemIndex = 0;
        for (auto& v : m_Objects)
        {

            std::string Name = v->GetName();
            if (ImGui::TreeNode(Name.c_str()))
            {
                ImGui::DragFloat3(" : Position", v->GetTransformComponent()->GetPosition(), 0.1f);
                ImGui::DragFloat3(" : Rotation", v->GetTransformComponent()->GetRotation(), 0.1f);
                ImGui::DragFloat3(" : Scale", v->GetTransformComponent()->GetScale(), 0.1f);
                ImGui::TreePop();
            }
        }

        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Light Attributes"))
    {
        int ItemIndex = 0;
        for (auto& v : m_Lights)
        {
            std::string Name = "Light " + std::to_string(++ItemIndex);
            if (ImGui::TreeNode(Name.c_str()))
            {
                // NOTE: LIGHT ATTRIBUTES
                ImGui::DragFloat3(" : Light Position", v->GetPositionArray(), 0.1);
                ImGui::DragFloat3(" : Light Direction", v->GetDirectionArray(), 0.1);
                ImGui::DragFloat3(" : Light Colour", v->GetColorArray(), 0.01f, 0.0f, 10.0f);
                ImGui::TreePop();
            }
        }

        ImGui::EndTabItem();
    }
}

void GraphicsManager::ShowcaseGUI()
{
    if (ImGui::BeginTabItem("GBuffer Outputs"))
    {
        // NOTE: Albedo and Normal
        ImGui::Text("Albedo/ Colour");
        ImGui::SameLine(315);
        ImGui::Text("Normal");
        ImGui::Image(*m_ColourEffect->GetShaderResourceView(), ImVec2(300, 200));

        ImGui::SameLine();
        ImGui::Image(*m_NewNormalEffect->GetShaderResourceView(), ImVec2(300, 200));

        // NOTE: Position and Specular
        ImGui::Text("Position");
        ImGui::SameLine(315);
        ImGui::Text("Specular");
        ImGui::Image(*m_PositionEffect->GetShaderResourceView(), ImVec2(300, 200));

        ImGui::SameLine();
        ImGui::Image(*m_SpecularEffect->GetShaderResourceView(), ImVec2(300, 200));

        // NOTE: Depth
        ImGui::Text("Depth");
        ImGui::Image(*m_DepthEffect->GetShaderResourceView(), ImVec2(300, 200));
        ImGui::EndTabItem();
    }
}

void GraphicsManager::EndGUI()
{
    ImGui::EndTabBar();
    ImGui::End();
}
