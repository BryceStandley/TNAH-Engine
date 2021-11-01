#include "tnahpch.h"
#include "Rigidbody.h"

namespace tnah::Physics {
	
	RigidBody::RigidBody()
	{

	}

	RigidBody::RigidBody(TransformComponent& transform, BodyMass mass)
		:bodyMass(mass)
	{
		centralPosition = transform.Position;
		Orientation = glm::quat(transform.QuatRotation);
	}

	Ref<RigidBody> RigidBody::Create(TransformComponent& transform, BodyMass mass)
	{
		return Ref<RigidBody>::Create(transform, mass);
	}

	void RigidBody::OnUpdate(TransformComponent& transform)
	{
		Orientation = glm::normalize(Orientation + transform.QuatRotation);
		bodyMass.WorldCentreOfMass = transform.Position - bodyMass.LocalCentreOfMass;
		centralPosition = bodyMass.WorldCentreOfMass;
	}

	void RigidBody::AddForce(const glm::vec3& force)
	{
			Force += force;
	}

	void RigidBody::AddTorque(const glm::vec3& torque)
	{
			Torque += torque;
	}

	void RigidBody::AddCollider(Ref<Collider> collider)	
	{
		Colliders[TotalColliders] = collider;
		TotalColliders++;
		UpdateBodyProperties();
	}

	void RigidBody::UpdateBodyProperties()
	{
		//Get and update the Centre of Mass for the body. Both local and world
		const auto oldWorldCOM = bodyMass.WorldCentreOfMass;
		const auto localCOM = CalculateCentreOfMass();
		const glm::vec3 worldCOM = (Orientation * localCOM) + centralPosition;
		bodyMass.WorldCentreOfMass = worldCOM;

		linearVelocity.Velocity += glm::cross(angularVelocity.Velocity, worldCOM - oldWorldCOM);
		
		CalculateLocalInertiaTensor();
	}

	void RigidBody::RecalculateWorldInertiaTensor()
	{
		glm::mat3 rot = glm::mat3_cast(Orientation);
		InertiaTensor.WorldInverseInertiaTensor[0][0] = rot[0][0] * InertiaTensor.LocalInverseInertiaTensor.x;
		InertiaTensor.WorldInverseInertiaTensor[0][1] = rot[1][0] * InertiaTensor.LocalInverseInertiaTensor.x;
		InertiaTensor.WorldInverseInertiaTensor[0][2] = rot[2][0] * InertiaTensor.LocalInverseInertiaTensor.x;
		
		InertiaTensor.WorldInverseInertiaTensor[1][0] = rot[0][1] * InertiaTensor.LocalInverseInertiaTensor.y;
		InertiaTensor.WorldInverseInertiaTensor[1][1] = rot[1][1] * InertiaTensor.LocalInverseInertiaTensor.y;
		InertiaTensor.WorldInverseInertiaTensor[1][2] = rot[2][1] * InertiaTensor.LocalInverseInertiaTensor.y;
		
		InertiaTensor.WorldInverseInertiaTensor[2][0] = rot[0][2] * InertiaTensor.LocalInverseInertiaTensor.z;
		InertiaTensor.WorldInverseInertiaTensor[2][1] = rot[1][2] * InertiaTensor.LocalInverseInertiaTensor.z;
		InertiaTensor.WorldInverseInertiaTensor[2][2] = rot[2][2] * InertiaTensor.LocalInverseInertiaTensor.z;

		InertiaTensor.WorldInverseInertiaTensor = rot * InertiaTensor.WorldInverseInertiaTensor;
	}

	void RigidBody::ApplyCollisionImpulse(const glm::vec3& lV, const glm::vec3& aV)
	{
		linearVelocity.Velocity = lV;
		angularVelocity.Velocity = aV;
	}

	void RigidBody::ResetValues()
	{
		Force = {0.0f, 0.0f, 0.0f};
		Torque = {0.0f, 0.0f, 0.0f};
		linearVelocity = {0.0f, 0.0f, 0.0f};
		angularVelocity = {0.0f, 0.0f, 0.0f};
		centralPosition = {0,0,0};
		Orientation = {0,0,0,0};
	}

	glm::vec3 RigidBody::CalculateLocalInertiaTensor()
	{
		auto localCOM = bodyMass.LocalCentreOfMass;
		glm::mat3 tempLocalInertiaTensor = glm::mat3(1.0f);

		// calc inertia tensor using colliders
		for(auto c : Colliders)
		{
			auto col = c.second;

			glm::vec3 shapeInertiaTensor = col->GetLocalColliderInertiaTensor();
			auto rot = glm::mat3_cast(col->GetColliderOrientation());
			auto rotTranspose = glm::transpose(rot);
			rotTranspose[0] *= shapeInertiaTensor.x;
			rotTranspose[1] *= shapeInertiaTensor.y;
			rotTranspose[2] *= shapeInertiaTensor.z;
			glm::mat3 inertiaTensor = rot * rotTranspose;

			// shift to the rigidbody COM with parallel axis theorem
			glm::vec3 offset = col->GetColliderPosition() - localCOM;
			auto offsetSqr = glm::length2(offset);
			glm::mat3 offsetMatrix = glm::mat3(0.0f);
			offsetMatrix[0][0] = offsetSqr;
			offsetMatrix[1][1] = offsetSqr;
			offsetMatrix[2][2] = offsetSqr;

			offsetMatrix[0] += offset * (-offset.x);
			offsetMatrix[1] += offset * (-offset.y);
			offsetMatrix[2] += offset * (-offset.z);
			offsetMatrix *= col->GetColliderMass().Mass;

			tempLocalInertiaTensor += inertiaTensor + offsetMatrix;
		}

		float x = tempLocalInertiaTensor[0][0];
		float y = tempLocalInertiaTensor[1][1];
		float z = tempLocalInertiaTensor[2][2];
		InertiaTensor.SetLocalInertiaTensor({x,y,z});
		return InertiaTensor.LocalInertiaTensor;
	}

	glm::vec3 RigidBody::CalculateCentreOfMass()
	{
		float totalMass = 0;
		glm::vec3 localCOM = {0,0,0};
		for(auto col : Colliders)
		{
			auto mass =  col.second->GetColliderMass().Mass;
			totalMass += mass;
			localCOM += mass * col.second->GetColliderPosition();
		}

		if(totalMass > 0.0f)
		{
			bodyMass.SetMass(totalMass);
		}

		bodyMass.LocalCentreOfMass = localCOM;
		return localCOM;

	}
}
