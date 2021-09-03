#pragma once

#include "AssimpGLMHelpers.h"
#include "TNAH/Core/Core.h"
#include <Assimp/scene.h>

#include "Bone.h"
#include "BoneInfo.h"

namespace tnah  {
	struct AssimpNodeData 
	{
		glm::mat4 transformation;
		std::string name;
		int childrenCount;
		std::vector<AssimpNodeData> children;
	};

	class Animation
	{
	public:
		
		Animation() = default;
		Animation(const aiScene* scene) 
		{
			m_Animation = scene->mAnimations[0];
			m_Duration = m_Animation->mDuration;
			m_TicksPerSecond = m_Animation->mTicksPerSecond;
			ReadHeirarchyData(m_RootNode, scene->mRootNode);
		}

		~Animation() {}

		Bone* FindBone(const std::string& name) 
		{
			auto iter = std::find_if(m_Bones.begin(), m_Bones.end(),
				[&](const Bone& Bone)
				{
					return Bone.GetBoneName() == name;
				}
			);
			if (iter == m_Bones.end()) return nullptr;
			else return &(*iter);
		}

		inline float GetTicksPerSecond() { return m_TicksPerSecond; }
		inline float GetDuration() { return m_Duration; }
		inline const AssimpNodeData& GetRootNode() { return m_RootNode; }
		inline const std::map<std::string, BoneInfo>& GetBoneIDMap() 
		{
			return m_BoneInfoMap;
		}

	
		void ReadMissingBones(std::map<std::string, BoneInfo>& boneInfoMap, int& boneCount) 
		{
			int size = m_Animation->mNumChannels;

			//reading channels (bone engaged in an animation and their keyframes)
			for (int i = 0; i < size; i++) 
			{
				auto channel = m_Animation->mChannels[i];
				std::string boneName = channel->mNodeName.data;
				
				if (boneInfoMap.find(boneName) == boneInfoMap.end())
				{
					boneInfoMap[boneName].id = boneCount;
					boneCount++;
				}
				m_Bones.push_back(Bone(channel->mNodeName.data, boneInfoMap[channel->mNodeName.data].id, channel));
			}

			m_BoneInfoMap = boneInfoMap;
		}
	
	private:
		void ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src) 
		{
			assert(src);

			dest.name = src->mName.data;
			dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
			dest.childrenCount = src->mNumChildren;

			for (int i = 0; i < src->mNumChildren; i++) 
			{
				AssimpNodeData newData;
				ReadHeirarchyData(newData, src->mChildren[i]);
				dest.children.push_back(newData);
			}
		}

		float m_Duration = 0.0f;
		int m_TicksPerSecond = 0.0f;
		std::vector<Bone> m_Bones;
		AssimpNodeData m_RootNode;
		std::map<std::string, BoneInfo> m_BoneInfoMap;
		aiAnimation* m_Animation;
		

	};
}
