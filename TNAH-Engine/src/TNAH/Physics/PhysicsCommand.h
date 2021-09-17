#pragma once
#include "PhysicsAPI.h"

namespace tnah
{
    class PhysicsCommand
    {
    public:
        inline static void Init()
        {
            s_PhysicsAPI->Init();
        }

        inline static void Destroy()
        {
            s_PhysicsAPI->Destroy();
        }

        inline static bool& GetColliderRendererHandler()
        {
            return s_PhysicsAPI->GetColliderRendererHandle();
        }

        inline static TransformComponent GetColliderRendererTransform()
        {
            return s_PhysicsAPI->GetColliderRendererTransform();
        }

        inline static void OnFixedUpdate(PhysicsTimestep timestep)
        {
            s_PhysicsAPI->OnFixedUpdate(timestep);
        }

        inline static Ref<RigidBody> CreateRigidBody(const TransformComponent& transform)
        {
            return s_PhysicsAPI->CreateRigidBody(transform);
        }

        inline static void CreateBoxShape(const glm::vec3& halfValues, Ref<RigidBody> rb)
        {
            s_PhysicsAPI->CreateBoxShape(halfValues, rb);
        }

        inline static void CreateSphereShape(const float& radius, Ref<RigidBody> rb)
        {
            s_PhysicsAPI->CreateSphereShape(radius, rb);
        }

        inline static void CreateCapsuleShape(const float& radius, const float& height, Ref<RigidBody> rb)
        {
            s_PhysicsAPI->CreateCapsuleShape(radius, height, rb);
        }

        inline static void CreateTerrainCollider(tnah::Terrain* terrain)
        {
            s_PhysicsAPI->CreateTerrainCollider(terrain);
        }

        inline static std::pair<std::pair<Ref<VertexArray>, Ref<VertexBuffer>>, std::pair<Ref<VertexArray>, Ref<VertexBuffer>>> GetColliderRenderObjects()
        {
            return s_PhysicsAPI->GetColliderRenderObjects();
        }

        inline static bool IsColliderRenderingEnabled()
        {
            return s_PhysicsAPI->IsColliderRenderingEnabled();
        }

        inline static void EnableLogging()
        {
            s_PhysicsAPI->EnableLogging();
        }

        inline static Ref<Shader> GetColliderShader()
        {
            return s_PhysicsAPI->GetColliderShader();
        }

        inline static void CreateColliderRenderer()
        {
            s_PhysicsAPI->CreateColliderRenderer();
        }

        inline static int GetLines()
        {
            return s_PhysicsAPI->GetLines();
        }
        inline static int GetTriangles()
        {
            return s_PhysicsAPI->GetTriangles();
        }
    
    private:
        static PhysicsAPI * s_PhysicsAPI;
    };
}
