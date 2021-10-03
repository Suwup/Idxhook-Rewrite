#pragma once

#include "System.h"
#include "Utils.h"
#include "Il2cpp.h"

namespace Idxhook::UnityEngine {

    namespace Screen {

        static std::int32_t GetWidth() { CALL_METHOD(int32_t, (), (), ("UnityEngine.CoreModule", "UnityEngine", "Screen", "get_width", 0)); }
        static std::int32_t GetHeight() { CALL_METHOD(int32_t, (), (), ("UnityEngine.CoreModule", "UnityEngine", "Screen", "get_height", 0)); }

    }

    class Vector3
	{
    public:
        float X, Y, Z;

		float Magnitude() { CALL_METHOD(float, (Vector3), (*this), ("UnityEngine.CoreModule", "UnityEngine", "Vector3", "Magnitude", 1)); }
		float Distance(const Vector3& other) { CALL_METHOD(float, (Vector3, Vector3), (*this, other), ("UnityEngine.CoreModule", "UnityEngine", "Vector3", "Distance", 2)); }
		Vector3 Addition(const Vector3& other) { CALL_METHOD(Vector3, (Vector3, Vector3), (*this, other), ("UnityEngine.CoreModule", "UnityEngine", "Vector3", "op_Addition", 2)); }
    };

    class Vector2
	{
    public:
        float X, Y;
    };

    class Transform
	{
    public:
        Vector3 GetPosition() { CALL_METHOD(Vector3, (void*), (this), ("UnityEngine.CoreModule", "UnityEngine", "Transform", "get_position", 0)); }
        void SetPosition(const Vector3& Position) { CALL_METHOD(void, (void*, Vector3), (this, Position), ("UnityEngine.CoreModule", "UnityEngine", "Transform", "set_position", 1)); }
        Vector3 TransformDirection(const Vector3& Direction) { CALL_METHOD(Vector3, (void*, Vector3), (this, Direction), ("UnityEngine.CoreModule", "UnityEngine", "Transform", "TransformDirection", 1)); }
        Vector3 TransformPoint(const Vector3& Position) { CALL_METHOD(Vector3, (void*, Vector3), (this, Position), ("UnityEngine.CoreModule", "UnityEngine", "Transform", "TransformPoint", 1)); }
    };

    class Component
	{
    public:
        Transform* GetTransform() { CALL_METHOD(Transform*, (void*), (this), ("UnityEngine.CoreModule", "UnityEngine", "Component", "get_transform", 0)); }
    };

    class Camera : public Component
	{
    public:
        static Camera* GetMain() { CALL_METHOD(Camera*, (), (), ("UnityEngine.CoreModule", "UnityEngine", "Camera", "get_main", 0)); }
		float GetFieldOfView() { CALL_METHOD(float, (void*), (this), ("UnityEngine.CoreModule", "UnityEngine", "Camera", "get_fieldOfView", 0)); }
        void SetFieldOfView(float Value) { CALL_METHOD(void, (void*, float), (this, Value), ("UnityEngine.CoreModule", "UnityEngine", "Camera", "set_fieldOfView", 1)); }
        Vector3 WorldToScreenPoint(const Vector3& Position) { CALL_METHOD(Vector3, (void*, Vector3), (this, Position), ("UnityEngine.CoreModule", "UnityEngine", "Camera", "WorldToScreenPoint", 1)); }
    };

    class Rigidbody
	{
    public:
        void SetMass(float Value) { CALL_METHOD(void, (void*, float), (this, Value), ("UnityEngine.CoreModule", "UnityEngine", "Rigidbody", "set_mass", 1)); }
    };

    class Text
	{
    public:
        System::String* GetText() { CALL_METHOD(System::String*, (void*), (this), ("UnityEngine.UI", "UnityEngine.UI", "Text", "get_text", 0)); }
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
		float GetFloat(const System::String* name) { CALL_METHOD(float, (void*, const System::String*), (this, name), ("UnityEngine.AnimationModule", "UnityEngine", "Animator", "GetFloat", 1)); }
		void SetFloat(const System::String* name, float value) { CALL_METHOD(void, (void*, const System::String*, float), (this, name, value), ("UnityEngine.AnimationModule", "UnityEngine", "Animator", "SetFloat", 2)); }
		bool GetBool(const System::String* name) { CALL_METHOD(bool, (void*, const System::String*), (this, name), ("UnityEngine.AnimationModule", "UnityEngine", "Animator", "GetBool", 1)); }
		void SetBool(const System::String* name, bool value) { CALL_METHOD(void, (void*, const System::String*, bool), (this, name, value), ("UnityEngine.AnimationModule", "UnityEngine", "Animator", "SetBool", 2)); }
		int32_t GetInteger(const System::String* name) { CALL_METHOD(int32_t, (void*, const System::String*), (this, name), ("UnityEngine.AnimationModule", "UnityEngine", "Animator", "GetInteger", 1)); }
		void SetInteger(const System::String* name, int32_t value) { CALL_METHOD(void, (void*, const System::String*, int32_t), (this, name, value), ("UnityEngine.AnimationModule", "UnityEngine", "Animator", "SetInteger", 2)); }
        Transform* GetBoneTransform(HumanBodyBones boneId) { CALL_METHOD(Transform*, (void*, HumanBodyBones), (this, boneId), ("UnityEngine.AnimationModule", "UnityEngine", "Animator", "GetBoneTransform", 1)); }
    };

	class CharacterController
	{
	public:
		bool SimpleMove(const Vector3& speed) { CALL_METHOD(bool, (void*, Vector3), (this, speed), ("UnityEngine.PhysicsModule", "UnityEngine", "CharacterController", "SimpleMove", 1)); }
		Vector3 GetVelocity() { CALL_METHOD(Vector3, (void*), (this), ("UnityEngine.PhysicsModule", "UnityEngine", "CharacterController", "get_velocity", 0)); }
	};

	class Renderer : public Component
	{
	public:
		bool GetEnabled() { CALL_METHOD(bool, (void*), (this), ("UnityEngine.CoreModule", "UnityEngine", "Renderer", "get_enabled", 0)); }
		void SetEnabled(bool Value) { CALL_METHOD(void, (void*, bool), (this, Value), ("UnityEngine.CoreModule", "UnityEngine", "Renderer", "set_enabled", 1)); }
	};
	
	class Cursor
	{
	public:
		enum class LockMode : int32_t
		{
			None, Locked, Confined,
		};
	public:
		static LockMode GetLockState() { CALL_METHOD(LockMode, (), (), ("UnityEngine.CoreModule", "UnityEngine", "Cursor", "get_lockState", 0)); }
		static void SetLockState(LockMode Value) { CALL_METHOD(void, (LockMode), (Value), ("UnityEngine.CoreModule", "UnityEngine", "Cursor", "set_lockState", 1)); }
	};
}
