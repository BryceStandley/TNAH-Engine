#pragma once
#include "TNAH/Audio/AudioAPI.h"
#include <IrrKlang/irrKlang.h>
#include <vector>
#include <string>

typedef std::vector<irrklang::ISoundSource*> AudioSource;
typedef std::vector<irrklang::ISound*> AudioPlaying;

namespace  tnah
{
    class Klang : public AudioAPI
    {
    public:
        Klang();
        ~Klang();

        bool SetListener(TransformComponent &transform) const;//Updated to take trasnform, look = foward
        bool Add3DAudioSource(AudioSource3D&sound);
        bool UpdateAudioSource(AudioSource3D&sound);
        bool PlayAudioSource(AudioSource3D& sound, TransformComponent &transform);
        void Update();
        void UpdateSound(AudioSource3D& sound, TransformComponent &transform);
        bool Active() const {return m_Engine;}
        
    private:
        AudioSource m_Source;
        AudioPlaying m_Playing;
        irrklang::ISoundEngine* m_Engine;
    };    
};

