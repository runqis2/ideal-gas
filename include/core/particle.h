#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H


#include <string>
#include <vector>

#include "cinder/Color.h"
#include "glm/glm.hpp"


namespace gas {

class Particle {
 public:
  /**
   * Constructor for Particle
   * @param pos position
   * @param vel velocity
   * @param mass
   * @param radius
   * @param color
   * @param num number of the particle for distinguishing
   */
  Particle(glm::vec2 pos, glm::vec2 vel, float mass, float radius,
           cinder::Color color, int num);

  float get_distance(Particle other);

  /**
   * Function that tells if two particles are collided or not
   * @param other
   * @return
   */
  bool is_collided(Particle other);

  /**
   * Function that update particle's settings after collision
   * @param other
   */
  void collision(Particle other);

  void set_position(glm::vec2 pos);

  void set_velocity(glm::vec2 vel);

  void set_mass(float new_mass);

  glm::vec2 get_position();

  glm::vec2 get_velocity();

  float get_mass();

  float get_radius();

  int get_number();

  cinder::Color get_color();

  void move();

 private:

  glm::vec2 position;
  glm::vec2 velocity;
  float particle_radius;
  float particle_mass;
  cinder::Color particle_color;
  float number;
  std::vector<Particle> has_met;

};

}  // namespace gas

#endif