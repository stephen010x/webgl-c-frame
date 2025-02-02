#include <stdio.h>
#include "main.h"
#include "physics.h"


// can change, so don't set to const
vec3 gravity = GRAVITY;





// calculate projected values
// can be used to set them too
void setprojected(BEHAVE* b, float dt, vec3 vel, vec3 pos) {

    vec3 deltap, deltav;
    
    // scale delta-v by dt and add it to velocity
    glm_vec3_scale(b->deltav, dt, deltav);
    glm_vec3_add(b->vel, deltav, vel);

    // add impulse to velocity
    glm_vec3_add(vel, b->impulse, vel);

    // add shift to position
    glm_vec3_add(b->pos, b->shift, pos);
    
    // scale velocity by dt and add to position
    glm_vec3_scale(vel, dt, deltap);
    glm_vec3_add(pos, deltap, pos);
}




// for some reason this works better than cglm's distance calculator?
float getdist(vec3 p1, vec3 p2) {
    float dx = p2[0] - p1[0];
    float dy = p2[1] - p1[1];
    float dz = p2[2] - p1[2];
    return sqrt(dx*dx + dy*dy + dz*dz);
}




void behave_apply(BEHAVE* b, double t, float dt) {

    // apply vectors to states
    /*glm_vec3_add(b->vel, b->deltav,  b->vel);
    glm_vec3_add(b->vel, b->impulse, b->vel);
    glm_vec3_add(b->pos, b->shift,   b->pos);
    vec3 vel;
    glm_vec3_scale(b->vel, dt, vel);
    glm_vec3_add(b->pos, vel, b->pos);*/
    // apply vectors to states
    setprojected(b, dt, b->vel, b->pos);
    
    // reset vectors
    glm_vec3_zero(b->impulse);
    glm_vec3_zero(b->deltav);
    glm_vec3_zero(b->shift);

    // TODO: I could have objects have a list of vector forces that
    //       apply to them. Only they are pointer, so many different
    //       objects could be affected by the same force.
    // apply gravity for next frame
    glm_vec3_add(b->deltav, gravity, b->deltav);
}





void collision_impulse(BEHAVE* b1, BEHAVE* b2, vec3 normin) {
    // get masses
    register float m1 = b1->mass;
    register float m2 = b2->mass;
    
    // enforce normal to be unit vector
    vec3 norm, anorm;
    glm_vec3_normalize_to(normin, norm);
    glm_vec3_negate_to(norm, anorm);

    // perform dot product between velocities and normal
    float dot1 = glm_vec3_dot(b1->vel, norm);
    float dot2 = glm_vec3_dot(b2->vel, anorm);

    // calculate magnitudes of new velocity
    // https://en.wikipedia.org/wiki/Inelastic_collision
    float v1x, v2x;
    if (m2 == INFINITY) {
        v1x = -(ELASTICITY*(dot2-dot1) + dot2);
        v2x = -dot2;
    } else {
        v1x = -(ELASTICITY*m2*(dot2-dot1) + m1*dot1 + m2*dot2) / (m1+m2);
        v2x = -(ELASTICITY*m1*(dot1-dot2) + m2*dot2 + m1*dot1) / (m1+m2);
    }

    // create output sum vector using new velocity minus old normal
    // this cancels out the old normal velocity for the new one via impulse
    vec3 v1add, v2add;
    glm_vec3_scale(norm, -v1x - dot1, v1add);
    glm_vec3_scale(norm, -v2x - dot2, v2add);

    // add our adjusted velocity normals back into the output impulse
    glm_vec3_add(b1->impulse, v1add, b1->impulse);
    glm_vec3_add(b2->impulse, v2add, b2->impulse);
}




// this uses previous deltav vector and adjusts it
// so make sure to call this after other changes to deltav
void collision_deltav(BEHAVE* b1, BEHAVE* b2, vec3 norm) {
    // I mean, this is pretty straightforward. It just cancels out the 
    // delta-v on the normal.

    // get magnitude of delta-v normal
    float dot1 = glm_vec3_dot(b1->deltav, norm);
    float dot2 = glm_vec3_dot(b2->deltav, norm);

    // scale normal units by magnitude
    vec3 nd1, nd2;
    glm_vec3_scale_as(norm, dot1, nd1);
    glm_vec3_scale_as(norm, dot2, nd2);

    // subtract inverted normal delta-v from original delta-v
    glm_vec3_sub(b1->deltav, nd1, b1->deltav);
    glm_vec3_sub(b2->deltav, nd2, b2->deltav);
}




// this one might actually be a bit complicated, as it needs to use the proposed
// position for both objects before shifting them.
// as a result, this needs to be called first.
void collision_shift(BEHAVE* b1, BEHAVE* b2, vec3 norm, float overlap) {

    // TODO
    // For some reason if m2 is greater than m1, then the normal needs to be 
    // reversed. Find out why this is and try to repair it.
    // Until then just stick with this ducktape solution
    // SOLUTION: I think I just needed to take the absolute value
    // of the difference of masses

    register float m1 = b1->mass;
    register float m2 = b2->mass;

    // ducktape here
    float sign = (m1 >= m2) ? -1 : 1;

    float r1, r2;

    if (m2 == INFINITY) {
        r1 = overlap;
        r2 = 0;
    } else if (m1 == m2) { // TODO: test this
        r1 = overlap / 2;
        r2 = overlap / 2;
    } else {
        r1 =  m2*overlap/ABS(m2-m1);
        r2 = -m1*overlap/ABS(m1-m2);
    }

    // scale norm by magnintude of r's
    vec3 p1o, p2o;
    glm_vec3_scale_as(norm, -r1, p1o);
    glm_vec3_scale_as(norm,  r2, p2o);

    // add scaled norm to shift
    glm_vec3_add(p1o, b1->shift, b1->shift);
    glm_vec3_add(p2o, b2->shift, b2->shift);
}




// remember to use projected position, not current position
bool sphere_collision_detect
    (BEHAVE* b1, BEHAVE* b2, float dt, float* overlap, vec3 normout) {

    // get projected states
    vec3 vel1, vel2, pos1, pos2;
    setprojected(b1, dt, vel1, pos1);
    setprojected(b2, dt, vel2, pos2);

    // calculate distance
    float dist = getdist(pos1, pos2);

    // get radius for each
    register float rad1 = b1->scale;
    register float rad2 = b2->scale;

    // calculate overlap
    *overlap = rad1 + rad2 - dist;

    if (*overlap < 0)
        return false;

    // calculate normal of collision
    glm_vec3_sub(pos2, pos1, normout);

    return true;
}



void sphere_collide_eval(BEHAVE* b1, BEHAVE* b2, float dt) {
    float overlap;
    vec3 norm;
    // if sphere collision is detected, then apply collision transformations
    if (sphere_collision_detect(b1, b2, dt, &overlap, norm)) {
        collision_shift(b1, b2, norm, overlap);
        //collision_impulse(b1, b2, norm);
        //collision_deltav(b1, b2, norm);
    }
}



void _wall_collide(BEHAVE* b, vec3 norm, float overlap);


// TODO: find a more vectorized solution to this rather than expanding them
void wall_collide_eval(BEHAVE* b, vec3 start, vec3 end, float dt) {

    // get projected state
    vec3 vel, pos;
    setprojected(b, dt, vel, pos);

    // expand start and ends to convenient values
    register float sx = start[0];
    register float sy = start[1];
    register float sz = start[2];
    register float ex = end[0];
    register float ey = end[1];
    register float ez = end[2];

    // expand behave values to convenient values
    register float rad = b->scale;
    register float x = pos[0];
    register float y = pos[1];
    register float z = pos[2];

    // test wall collisions
    if (x + rad > ex) _wall_collide(b, (vec3){ 1, 0, 0},  x+rad-ex);
    if (x - rad < sx) _wall_collide(b, (vec3){-1, 0, 0}, -x+rad+sx);
    if (y + rad > ey) _wall_collide(b, (vec3){ 0, 1, 0},  y+rad-ey);
    if (y - rad < sy) _wall_collide(b, (vec3){ 0,-1, 0}, -y+rad+sy);
    if (z + rad > ez) _wall_collide(b, (vec3){ 0, 0, 1},  z+rad-ez);
    if (z - rad < sz) _wall_collide(b, (vec3){ 0, 0,-1}, -z+rad+sz);
}


void _wall_collide(BEHAVE* b, vec3 norm, float overlap) {

    // dummy wall behavior
    static BEHAVE wall = {
        .mass = INFINITY,
    };

    // apply collision transformations
    collision_shift(b, &wall, norm, overlap);
    collision_impulse(b, &wall, norm);
    //collision_deltav(b, &wall, norm);
}
