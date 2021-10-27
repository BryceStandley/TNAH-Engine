#pragma once

#include "TNAH/Physics/PhysicsEngine.h"

#include "TNAH/Renderer/Mesh.h"
#include "ComponentIdentification.h"

namespace tnah{

class GameObject;
	
	/**********************************************************************************************//**
 * @class	RigidBodyComponent
 *
 * @brief	A physics rigidbody allows physics to be simulated on a object
 *
 * @author	Bryce Standley
 * @date	20/07/2021
 * 			
 * @author	Christopher Logan
 * @date	05/09/2021
 **************************************************************************************************/

	struct RigidBodyComponent
	{
		Ref<Physics::RigidBody> Body = nullptr;
		
		/** @brief	True to edit */
		bool Edit = false;
		/** @brief	True to use edit */
		bool UseEdit = false;

		/**********************************************************************************************//**
		 * @fn	RigidBodyComponent::RigidBodyComponent();
		 *
		 * @brief	Default constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		RigidBodyComponent();

		/**********************************************************************************************//**
		 * @fn	RigidBodyComponent::RigidBodyComponent(const RigidBodyComponent& other) = default;
		 *
		 * @brief	Defaulted copy constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	other	The other.
		 **************************************************************************************************/

		RigidBodyComponent(const RigidBodyComponent& other) = default;

		/**********************************************************************************************//**
		 * @fn	RigidBodyComponent::RigidBodyComponent(const TransformComponent& transform, rp3d::BodyType type);
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	transform	The transform.
		 * @param 	type	 	The type.
		 **************************************************************************************************/

		RigidBodyComponent(GameObject& gameObject, const Physics::BodyType& type = Physics::BodyType::Dynamic);
		

		/**********************************************************************************************//**
		* @fn	RigidBodyComponent::void OnUpdate(const TransformComponent& transform);
		*
		* @brief	Update function for the Rigidbody component. Updates the Rigidbody with the current transform and orientation.
		*
		* @author	Bryce Standley
		* @date	10/10/2021
		*
		**************************************************************************************************/
		void OnUpdate(TransformComponent& transform);
		
		/**********************************************************************************************//**
		 * @fn	void RigidBodyComponent::ApplyForce(const ForceType& forceType, const glm::vec3& direction, const glm::vec3& force, const glm::vec3& forcePoint) const;
		 *
		 * @brief	Applies the force
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	forceType 	Type of the force.
		 * @param 	direction 	The direction.
		 * @param 	force	  	The force.
		 * @param 	forcePoint	The force point.
		 **************************************************************************************************/

		void ApplyForce(const glm::vec3& direction, const glm::vec3& force);

		/**********************************************************************************************//**
		 * @fn	void RigidBodyComponent::ApplyTorque(const glm::vec3& torque) const;
		 *
		 * @brief	Applies the torque described by torque
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	torque	The torque.
		 **************************************************************************************************/

		void ApplyTorque(const glm::vec3& direction, const glm::vec3& torque);

		
		/**
		 * @fn Ref<Physics::Collider> ::tnah::RigidBodyComponent::AddCollider(const glm::vec3& boxSize)
		 * 
		 * @brief Adds a collider to the current active rigidbody on the component.
		 *
		 * @author Bryce Standley
		 * @date Thursday, 14 October 2021
		 * 
		 * @param boxSize Full size of each dimension of the box
		 *
		 * @returns  Collider Ref or nullptr if adding the collider failed.
		 *
		 */
		Ref<Physics::Collider> AddCollider(const glm::vec3& boxSize);

		
		/**
		 * @fn Ref<Physics::Collider> ::tnah::RigidBodyComponent::AddCollider(const float& sphereRadius)
		 * 
		 * @brief Adds a collider to the current active rigidbody on the component.
		 *
		 * @author Bryce Standley
		 * @date Thursday, 14 October 2021
		 * 
		 * @param sphereRadius The radius of the sphere
		 *
		 * @returns  Collider Ref or nullptr if adding the collider failed.
		 *
		 */
		Ref<Physics::Collider> AddCollider(const float& sphereRadius);

		
		/**
		 * @fn Ref<Physics::Collider> ::tnah::RigidBodyComponent::AddCollider(const float& capsuleRadius)
		 * @fn Ref<Physics::Collider> ::tnah::RigidBodyComponent::AddCollider(const float& capsuleHeight)
		 * 
		 * @brief Adds a collider to the current active rigidbody on the component.
		 *
		 * @author Bryce Standley
		 * @date Thursday, 14 October 2021
		 * 
		 * @param capsuleRadius The radius of the capsule
		 * @param capsuleHeight The height of the capsule
		 *
		 * @returns  Collider Ref or nullptr if adding the collider failed.
		 *
		 */
		Ref<Physics::Collider> AddCollider(const float& capsuleRadius, const float& capsuleHeight);
	
		
	private:
		/** @brief	Search string for the component in the editor */
		inline static std::string s_SearchString = "rigidbody component";
		/** @brief	Component search types and groupings  */
		inline static ComponentTypes s_Types = {
			{ComponentVariations::RigidBody},
		{{ComponentCategory::Physics}}
		};
		
		friend class EditorUI;
	};

}
