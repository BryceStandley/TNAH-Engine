#pragma once
#include "TNAH/Core/Core.h"
#include "TNAH/Core/FileStructures.h"
#include "ComponentBase.h"

namespace tnah {

	class AudioSourceComponent : public Component
	{
	public:
		AudioSourceComponent(Resource file = {"defaultsoundfile.wav"}, float minDistance = 1.0f, float volume = 1.0f, bool threeDim = true, bool loop = false)
		: m_MinDistance(minDistance), m_Volume(volume), m_Loop(loop), m_SourceReference(0),
		m_PlayReference(0), m_Playing(false), m_Loaded(false), m_Shoot(false), m_3D(threeDim),m_StartLoad(false), m_Paused(false) {m_File = file;}

		bool GetStartLoad() const {return m_StartLoad;}
		void SetStartLoad(const bool b) {m_StartLoad = b;}
		int m_SourceReference;
		int m_PlayReference;
		float m_MinDistance;
		float m_Volume;
		bool m_Loop;
		bool m_Playing;
		bool m_Paused;
		bool m_Loaded;
		bool m_Shoot;
		bool m_3D;
		Resource m_File;

	private:
		bool m_StartLoad;
		friend class EditorUI;
		inline static std::string s_SearchString = "audio source component";
	};

	class AudioListenerComponent : public Component
	{
	public:
		AudioListenerComponent(bool active = false) : m_ActiveListing(active) {}
		bool m_ActiveListing;

	private:
		friend class EditorUI;
		inline static std::string s_SearchString = "audio listener component";
	};

}
