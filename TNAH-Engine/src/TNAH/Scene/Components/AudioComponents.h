#pragma once
#include "TNAH/Core/Core.h"
#include "TNAH/Core/FileStructures.h"

namespace tnah {

	struct AudioSource3D 
	{
		AudioSource3D(Resource file = {"defaultsoundfile.wav"}, float distance = 10.0f, float volume = 1.0f, bool loop = false)
		: m_MinDistance(distance), m_Volume(volume), m_Loop(loop), m_SourceReference(NULL),
		m_PlayReference(NULL), m_Playing(false), m_Loaded(false), m_Shoot(false) {m_File = file;}

		int m_SourceReference;
		int m_PlayReference;
		float m_MinDistance;
		float m_Volume;
		bool m_Loop;
		bool m_Playing;
		bool m_Loaded;
		bool m_Shoot;
		Resource m_File;
	};

	struct AudioListener 
	{
		AudioListener(bool active = false) : m_ActiveListing(active) {}
		bool m_ActiveListing;
	};

}
