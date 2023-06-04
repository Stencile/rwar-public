#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Bitset.h>
#include <Shared/Entity.h>
#include <Shared/Vector.h>
#include <Shared/Utilities.h>

#ifdef RR_CLIENT
#include <Client/Game.h>
#endif

struct rr_simulation;
struct proto_bug;

struct rr_component_physical_spatial_hash_bounds
{
    uint32_t sx;
    uint32_t ex;
    uint32_t sy;
    uint32_t ey;
    uint8_t inserted;
};

// check if there's rr_component_physical_set function before setting a field
struct rr_component_physical
{
                   struct rr_vector velocity;
    RR_CLIENT_ONLY(struct rr_vector lerp_velocity;)
    RR_SERVER_ONLY(struct rr_vector acceleration;)
    RR_SERVER_ONLY(uint64_t protocol_state;)
    RR_SERVER_ONLY(uint32_t query_id;)
    RR_SERVER_ONLY(struct rr_component_physical_spatial_hash_bounds bounds;)
                   uint32_t deletion_tick;
    RR_SERVER_ONLY(float mass;)
    RR_SERVER_ONLY(float restitution;)
    RR_SERVER_ONLY(float friction;)
                   float angle;
    RR_CLIENT_ONLY(float lerp_angle;)
                   float x;
    RR_CLIENT_ONLY(float lerp_x;)
                   float y;
    RR_CLIENT_ONLY(float lerp_y;)
                   float radius;
    RR_CLIENT_ONLY(float lerp_radius;)
    RR_CLIENT_ONLY(float animation;)
                   EntityIdx parent_id;
    // RR_SERVER_ONLY(uint8_t has_collisions;)
    // RR_SERVER_ONLY(uint8_t collisions[RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)];)
    RR_SERVER_ONLY(uint32_t colliding_with_size;)
    RR_SERVER_ONLY(EntityIdx colliding_with[RR_MAX_COLLISION_COUNT];)
};

void rr_component_physical_init(struct rr_component_physical *);
void rr_component_physical_free(struct rr_component_physical *, struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_physical_write(struct rr_component_physical *, struct proto_bug *, int);)
RR_CLIENT_ONLY(void rr_component_physical_read(struct rr_component_physical *, struct proto_bug *);)

RR_DECLARE_PUBLIC_FIELD(physical, float, x)
RR_DECLARE_PUBLIC_FIELD(physical, float, y)
RR_DECLARE_PUBLIC_FIELD(physical, float, angle)
RR_DECLARE_PUBLIC_FIELD(physical, float, radius)
RR_DECLARE_PUBLIC_FIELD(physical, uint32_t, deletion_tick)