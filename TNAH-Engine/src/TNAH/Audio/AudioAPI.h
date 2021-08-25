#pragma 
#include "TNAH/Scene/Components/AudioComponents.h"
#include "TNAH/Scene/Components/Components.h"
namespace tnah
{
    class AudioAPI
    {
    public:
        virtual bool SetListener(TransformComponent &transforms) const = 0;
        virtual bool Add3DAudioSource(AudioSource3D &sound) = 0;
        virtual bool UpdateAudioSource(AudioSource3D &sound) = 0;
        virtual bool PlayAudioSource(AudioSource3D& sound, TransformComponent &transforms) = 0;
        virtual void Update() = 0;
        virtual void UpdateSound(AudioSource3D& sound, TransformComponent &transforms) = 0;
        virtual bool Active() const = 0;
    };
}

