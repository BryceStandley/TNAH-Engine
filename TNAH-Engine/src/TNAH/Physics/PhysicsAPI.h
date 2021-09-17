#pragma once
#include "TNAH/Physics/RigidBody.h"
namespace tnah
{
    class PhysicsAPI
    {
        enum API
        {
            none = 0, tnah = 1, react = 2
        };
    
    public:
        
        enum Collider
        {
            box = 0, sphere = 1, capsule = 2, heightmap = 3, concaveMesh = 4, convexMesh = 5
        };
        virtual void Init() = 0;
        virtual ~PhysicsAPI() = default;

        virtual void Destroy() = 0;

        virtual bool& GetColliderRendererHandle() = 0;

        virtual TransformComponent GetColliderRendererTransform() = 0;

        static Scope<PhysicsAPI> Create();

        virtual void OnFixedUpdate(PhysicsTimestep timestep) = 0;
        
        virtual Ref<RigidBody> CreateRigidBody(const TransformComponent& transform) = 0;
        
        virtual void CreateBoxShape(const glm::vec3& halfValues, Ref<RigidBody> rb) = 0;

        virtual void CreateSphereShape(const float& radius, Ref<RigidBody> rb) = 0;

        virtual void CreateCapsuleShape(const float& radius, const float& height, Ref<RigidBody> rb) = 0;

        virtual void CreateTerrainCollider(tnah::Terrain* terrain) = 0;

        virtual std::pair<std::pair<Ref<VertexArray>, Ref<VertexBuffer>>, std::pair<Ref<VertexArray>, Ref<VertexBuffer>>> GetColliderRenderObjects() = 0;

        virtual bool IsColliderRenderingEnabled() = 0;

        virtual void EnableLogging() = 0;

        virtual Ref<Shader> GetColliderShader() = 0;

        virtual void CreateColliderRenderer() = 0;

        virtual int GetLines() = 0;
        
        virtual int GetTriangles() = 0;
        
    private:
        static API p_Api;
    };
}
