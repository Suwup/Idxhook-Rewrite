#pragma once

#include "System.h"
#include "Offsets.h"
#include "Utils.h"

namespace Idxhook::UnityEngine {

    namespace Screen {

        static std::int32_t GetWidth() { return Memory::CallFunction<std::int32_t>(Offsets::Methods::Screen::get_width); }
        static std::int32_t GetHeight() { return Memory::CallFunction<std::int32_t>(Offsets::Methods::Screen::get_height); }

    }

    class Vector3
	{
    public:
        float X, Y, Z;

		float Magnitude() { return Memory::CallFunction<float, Vector3>(Offsets::Methods::Vector3::Magnitude, *this); }
		float Distance(const Vector3& other) { return Memory::CallFunction<float, Vector3, Vector3>(Offsets::Methods::Vector3::Distance, *this, other); }
		Vector3 Addition(const Vector3& other) { return Memory::CallFunction<Vector3, Vector3, Vector3>(Offsets::Methods::Vector3::op_Addition, *this, other); }
    };

    class Vector2
	{
    public:
        float X, Y;
    };

    class Transform
	{
    public:
        Vector3 GetPosition() { return Memory::CallFunction<Vector3, void*>(Offsets::Methods::Transform::get_position, this); }
        void SetPosition(const Vector3& Position) { return Memory::CallFunction<void, void*, Vector3>(Offsets::Methods::Transform::set_position, this, Position); }
        Vector3 TransformDirection(const Vector3& Direction) { return Memory::CallFunction<Vector3, void*, Vector3>(Offsets::Methods::Transform::TransformDirection, this, Direction); }
        Vector3 TransformPoint(const Vector3& Position) { return Memory::CallFunction<Vector3, void*, Vector3>(Offsets::Methods::Transform::TransformPoint, this, Position); }
    };

    class Component
	{
    public:
        Transform* GetTransform() { return Memory::CallFunction<Transform*, void*>(Offsets::Methods::Component::get_transform, this); }
    };

    class Camera : public Component
	{
    public:
        static Camera* GetMain() { return Memory::CallFunction<Camera*>(Offsets::Methods::Camera::get_main); }
		float GetFieldOfView() { return Memory::CallFunction<float, void*>(Offsets::Methods::Camera::get_fieldOfView, this); }
        void SetFieldOfView(float Value) { return Memory::CallFunction<void, void*, float>(Offsets::Methods::Camera::set_fieldOfView, this, Value); }
        Vector3 WorldToScreenPoint(const Vector3& Position) { return Memory::CallFunction<Vector3, void*, Vector3>(Offsets::Methods::Camera::WorldToScreenPoint, this, Position); }
    };

    class Rigidbody
	{
    public:
        void SetMass(float Value) { return Memory::CallFunction<void, void*, float>(Offsets::Methods::Rigidbody::set_mass, this, Value); }
    };

    class Text
	{
    public:
        System::String* GetText() { return Memory::CallFunction<System::String*, void*>(Offsets::Methods::Text::get_text, this); }
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
		Hips = 0,
		LeftUpperLeg = 1,
		RightUpperLeg = 2,
		LeftLowerLeg = 3,
		RightLowerLeg = 4,
		LeftFoot = 5,
		RightFoot = 6,
		Spine = 7,
		Chest = 8,
		UpperChest = 54,
		Neck = 9,
		Head = 10,
		LeftShoulder = 11,
		RightShoulder = 12,
		LeftUpperArm = 13,
		RightUpperArm = 14,
		LeftLowerArm = 15,
		RightLowerArm = 16,
		LeftHand = 17,
		RightHand = 18,
		LeftToes = 19,
		RightToes = 20,
		LeftEye = 21,
		RightEye = 22,
		Jaw = 23,
		LeftThumbProximal = 24,
		LeftThumbIntermediate = 25,
		LeftThumbDistal = 26,
		LeftIndexProximal = 27,
		LeftIndexIntermediate = 28,
		LeftIndexDistal = 29,
		LeftMiddleProximal = 30,
		LeftMiddleIntermediate = 31,
		LeftMiddleDistal = 32,
		LeftRingProximal = 33,
		LeftRingIntermediate = 34,
		LeftRingDistal = 35,
		LeftLittleProximal = 36,
		LeftLittleIntermediate = 37,
		LeftLittleDistal = 38,
		RightThumbProximal = 39,
		RightThumbIntermediate = 40,
		RightThumbDistal = 41,
		RightIndexProximal = 42,
		RightIndexIntermediate = 43,
		RightIndexDistal = 44,
		RightMiddleProximal = 45,
		RightMiddleIntermediate = 46,
		RightMiddleDistal = 47,
		RightRingProximal = 48,
		RightRingIntermediate = 49,
		RightRingDistal = 50,
		RightLittleProximal = 51,
		RightLittleIntermediate = 52,
		RightLittleDistal = 53,
		LastBone = 55
    };

    class Animator
	{
    public:
		float GetFloat(const System::String* name) { return Memory::CallFunction<float, void*, const System::String*>(Offsets::Methods::Animator::GetFloat, this, name); }
		void SetFloat(const System::String* name, float value) { return Memory::CallFunction<void, void*, const System::String*, float>(Offsets::Methods::Animator::SetFloat, this, name, value); }
		bool GetBool(const System::String* name) { return Memory::CallFunction<bool, void*, const System::String*>(Offsets::Methods::Animator::GetBool, this, name); }
		void SetBool(const System::String* name, bool value) { return Memory::CallFunction<void, void*, const System::String*, bool>(Offsets::Methods::Animator::SetBool, this, name, value); }
		int32_t GetInteger(const System::String* name) { return Memory::CallFunction<int32_t, void*, const System::String*>(Offsets::Methods::Animator::GetInteger, this, name); }
		void SetInteger(const System::String* name, int32_t value) { return Memory::CallFunction<void, void*, const System::String*, int32_t>(Offsets::Methods::Animator::SetInteger, this, name, value); }
        Transform* GetBoneTransform(HumanBodyBones boneId) { return Memory::CallFunction<Transform*, void*, HumanBodyBones>(Offsets::Methods::Animator::GetBoneTransform, this, boneId); }
    };
}
