#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

enum body_type
{
	b_dynamic,
	b_static,
	b_kinematic
};

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}
	
	void SetPosition(int x, int y);
	void SetImpulse(int angle);
	void SetPush(int x, int y, int x_center, int y_center);
	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	//void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

	PhysBody* CreateCircle(int x, int y, int radius, body_type type, float restitiution, bool sensor);
	PhysBody* CreateRectangle(int x, int y, int width, int height);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);
	PhysBody* CreatePolygon(int x, int y, int* points, int size, body_type type, float restitution, bool sensor);
	PhysBody* CreateChain(int x, int y, int* points, int size);
	PhysBody* CreateStaticChain(int x, int y, int* points, int size);

	void DestroyBody(PhysBody* body);

	void CreateRevoluteJoint(b2Body* bodyA, b2Body* bodyB, int anchor1_x, int anchor1_y, int anchor2_x, int anchor2_y, int ref_angle, int max_angle, int min_angle, int speed);
	void CreatePrismaticJoint(b2Body* bodyA, b2Body*bodyB, int axis_x, int axis_y, int anchor1_x, int anchor1_y, int anchor2_x, int anchor2_y, int ref_angle, int max_dist, int min_dist, bool motor, int force, int speed);
	
	// MOTOR_JOINT
	b2MotorJoint* CreateMotorJoint(PhysBody* bodyA, PhysBody* bodyB, int max_force, int max_torque, float correction_factor);

	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

	PhysBody* rectangle;

private:

	bool debug;
	b2World* world;
	b2MouseJoint* mouse_joint;
	b2Body* ground;
};