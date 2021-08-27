#pragma once
#include "TNAH/Core/Core.h"
#include "TNAH/Core/FileStructures.h"

namespace tnah {

	struct AudioSource
	{
		AudioSource(Resource file = {"defaultsoundfile.wav"}, float minDistance = 1.0f, float volume = 1.0f, bool threeDim = true, bool loop = false)
		: m_MinDistance(minDistance), m_Volume(volume), m_Loop(loop), m_SourceReference(NULL),
		m_PlayReference(NULL), m_Playing(false), m_Loaded(false), m_Shoot(false), m_3D(threeDim), m_Paused(false) {m_File = file;}

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
	};

	struct AudioListener 
	{
		AudioListener(bool active = false) : m_ActiveListing(active) {}
		bool m_ActiveListing;
	};

}
