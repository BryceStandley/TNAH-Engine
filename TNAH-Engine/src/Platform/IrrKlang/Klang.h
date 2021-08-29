#pragma once
#include "TNAH/Audio/AudioAPI.h"
#include <IrrKlang/irrKlang.h>
#include <vector>
#include <string>
#include <map>

typedef std::vector<irrklang::ISoundSource*> AudioSources;
//typedef std::pair<std::string, irrklang::ISoundSource*> AudioSourcePair;
typedef std::vector<irrklang::ISound*> AudioPlaying;

//TODO Add pause and loop functionality
namespace  tnah
{
    class Klang final : public AudioAPI
    {
    public:
        Klang();
        virtual ~Klang();

        bool SetListener(TransformComponent &transform) const override;//Updated to take trasnform, look = foward
        bool AddAudioSource(AudioSource&sound) override;
        bool UpdateAudioSource(AudioSource&sound) override;
        void OnUpdate() override;
        void UpdateSound(AudioSource& sound, TransformComponent &transform) override;
        bool Active() const override {return m_Engine;}
        void Clear() override;
        
    private:
        bool PlayAudioSource(AudioSource& sound, TransformComponent &transform);
        AudioSources m_Source;
        AudioPlaying m_Playing;
        irrklang::ISoundEngine* m_Engine;
    };    
};

