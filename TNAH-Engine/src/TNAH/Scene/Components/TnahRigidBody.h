#pragma once

namespace tnah
{
    enum BodyType
    {
        Dynamic, Static
    };
    
    struct TnahRigidBodyComponent
    {
        TnahRigidBodyComponent();
        TnahRigidBodyComponent(const TransformComponent& transform);
        rp3d::CollisionBody* Body = nullptr;
        rp3d::Collider* AddCollider(rp3d::CollisionShape* collider, const rp3d::Transform &transform);
        //Add it to constructors
        tnah::BodyType type = BodyType::Dynamic;
    private:
        std::list<rp3d::CollisionShape*> m_ColliderList;
        inline static std::string s_SearchString = "tnah Rigid Body component";

        /*inline static ComponentTypes s_Types = {
            {ComponentVariations::CollisionBody},
    {{ComponentCategory::Physics}}
        };
        friend class EditorUI;*/
    };
}
