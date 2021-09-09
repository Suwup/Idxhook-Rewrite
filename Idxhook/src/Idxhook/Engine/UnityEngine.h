#pragma once

#include "System.h"
#include "Offsets.h"
#include "Utils.h"

namespace Idxhook::UnityEngine {

    namespace Screen {

        static std::int32_t GetWidth() { return Memory::CallFunction<std::int32_t>(Offsets::Methods::Screen::GetWidth); }
        static std::int32_t GetHeight() { return Memory::CallFunction<std::int32_t>(Offsets::Methods::Screen::GetHeight); }

    }

    class Vector3
	{
    public:
        float X, Y, Z;

        static float Distance(Vector3 A, Vector3 B) { return Memory::CallFunction<float, Vector3, Vector3>(Offsets::Methods::Vector3::Distance, A, B); }
        static Vector3 Addition(Vector3 A, Vector3 B) { return Memory::CallFunction<Vector3, Vector3, Vector3>(Offsets::Methods::Vector3::Addition, A, B); }
		Vector3 operator+(const Vector3& other) const { return Addition(*this, other); }
    };

    class Vector2
	{
    public:
        float X, Y;
    };

    class Transform
	{
    public:
        Vector3 GetPosition() { return Memory::CallFunction<Vector3, void*>(Offsets::Methods::Transform::GetPosition, this); }
        void SetPosition(Vector3 Position) { return Memory::CallFunction<void, void*, Vector3>(Offsets::Methods::Transform::SetPosition, this, Position); }
        Vector3 TransformDirection(Vector3 Direction) { return Memory::CallFunction<Vector3, void*, Vector3>(Offsets::Methods::Transform::TransformDirection, this, Direction); }
    };

    class Component
	{
    public:
        Transform* GetTransform() { return Memory::CallFunction<Transform*, void*>(Offsets::Methods::Component::GetTransform, this); }
    };

    class Camera : public Component
	{
    public:
        static Camera* GetMain() { return Memory::CallFunction<Camera*>(Offsets::Methods::Camera::GetMain); }
		float GetFieldOfView() { return Memory::CallFunction<float, void*>(Offsets::Methods::Camera::GetFieldOfView, this); }
        void SetFieldOfView(float Value) { return Memory::CallFunction<void, void*, float>(Offsets::Methods::Camera::SetFieldOfView, this, Value); }
        Vector3 WorldToScreenPoint(Vector3 Position) { return Memory::CallFunction<Vector3, void*, Vector3>(Offsets::Methods::Camera::WorldToScreenPoint, this, Position); }
    };

    class Rigidbody
	{
    public:
        void SetMass(float Value) { return Memory::CallFunction<void, void*, float>(Offsets::Methods::Rigidbody::SetMass, this, Value); }
    };

    class Text
	{
    public:
        System::String* GetText() { return Memory::CallFunction<System::String*, void*>(Offsets::Methods::Text::GetText, this); }
    };

    class Scene
	{
    private:
        int Handle;

    public:
        std::int32_t GetBuildIndexInternal() { return Memory::CallFunction<std::int32_t, std::int32_t>(Offsets::Methods::Scene::GetBuildIndexInternal, this->Handle); }
    };

    enum class HumanBodyBones : int32_t
	{
        Hips = 0x00000000,
        LeftUpperLeg = 0x00000001,
        RightUpperLeg = 0x00000002,
        LeftLowerLeg = 0x00000003,
        RightLowerLeg = 0x00000004,
        LeftFoot = 0x00000005,
        RightFoot = 0x00000006,
        Spine = 0x00000007,
        Chest = 0x00000008,
        UpperChest = 0x00000036,
        Neck = 0x00000009,
        Head = 0x0000000a,
        LeftShoulder = 0x0000000b,
        RightShoulder = 0x0000000c,
        LeftUpperArm = 0x0000000d,
        RightUpperArm = 0x0000000e,
        LeftLowerArm = 0x0000000f,
        RightLowerArm = 0x00000010,
        LeftHand = 0x00000011,
        RightHand = 0x00000012,
        LeftToes = 0x00000013,
        RightToes = 0x00000014,
        LeftEye = 0x00000015,
        RightEye = 0x00000016,
        Jaw = 0x00000017,
        LeftThumbProximal = 0x00000018,
        LeftThumbIntermediate = 0x00000019,
        LeftThumbDistal = 0x0000001a,
        LeftIndexProximal = 0x0000001b,
        LeftIndexIntermediate = 0x0000001c,
        LeftIndexDistal = 0x0000001d,
        LeftMiddleProximal = 0x0000001e,
        LeftMiddleIntermediate = 0x0000001f,
        LeftMiddleDistal = 0x00000020,
        LeftRingProximal = 0x00000021,
        LeftRingIntermediate = 0x00000022,
        LeftRingDistal = 0x00000023,
        LeftLittleProximal = 0x00000024,
        LeftLittleIntermediate = 0x00000025,
        LeftLittleDistal = 0x00000026,
        RightThumbProximal = 0x00000027,
        RightThumbIntermediate = 0x00000028,
        RightThumbDistal = 0x00000029,
        RightIndexProximal = 0x0000002a,
        RightIndexIntermediate = 0x0000002b,
        RightIndexDistal = 0x0000002c,
        RightMiddleProximal = 0x0000002d,
        RightMiddleIntermediate = 0x0000002e,
        RightMiddleDistal = 0x0000002f,
        RightRingProximal = 0x00000030,
        RightRingIntermediate = 0x00000031,
        RightRingDistal = 0x00000032,
        RightLittleProximal = 0x00000033,
        RightLittleIntermediate = 0x00000034,
        RightLittleDistal = 0x00000035,
        LastBone = 0x00000037,
    };

    class Animator
	{
    public:
        Transform* GetBoneTransform(HumanBodyBones boneId) { return Memory::CallFunction<Transform*, void*, HumanBodyBones>(Offsets::Methods::Animator::GetBoneTransform, this, boneId); }
    };
}
