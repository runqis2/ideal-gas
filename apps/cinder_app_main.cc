
#include <core/particle.h>

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <cinder/app/RendererGl.h>

using namespace ci;
using namespace ci::app;

class MyApp : public App {
 public:
  void setup() override;

  void update() override;

  void draw() override;

  static void prepareSettings(MyApp::Settings* settings) {
    settings->setResizable(true);
    settings->setFrameRate(30.0f);
  }

  void DrawParticles();

 private:
  std::vector<gas::Particle> particles;
};

void MyApp::setup() {  //initialize particles randomly
  int num = 0;
  for (int i = 0; i < 10; i++) {
    float pos_x = (arc4random() % 2 ? 1 : -1) * (rand() % 200) * 1.0f;
    float pos_y = (arc4random() % 2 ? 1 : -1) * (rand() % 150) * 1.0f;
    float rand_x_speed = (arc4random() % 2 ? 1 : -1) * (rand() % 2 - 0.1);
    float rand_y_speed = (arc4random() % 2 ? 1 : -1) * (rand() % 2 + 0.1);
    particles.push_back(gas::Particle(
        glm::vec2(getWindowWidth() / 2 + pos_x, getWindowWidth() / 2 + pos_y - 100),
        glm::vec2(rand_x_speed, rand_y_speed), 0.2, 5.0, cinder::Color(0, 1, 0), num));
  }
  for (int i = 0; i < 10; i++) {
    float pos_x = (arc4random() % 2 ? 1 : -1) * (rand() % 200) * 1.0f;
    float pos_y = (arc4random() % 2 ? 1 : -1) * (rand() % 150) * 1.0f;
    float rand_x_speed = (arc4random() % 2 ? 1 : -1) * (rand() % 2 + 0.1);
    float rand_y_speed = (arc4random() % 2 ? 1 : -1) * (rand() % 2 + 0.1);
    //std::cout << glm::vec2(rand_x_speed, rand_y_speed)<< "\n";
    particles.push_back(gas::Particle(glm::vec2(getWindowWidth()/2 + pos_x,getWindowWidth()/2 + pos_y - 100),
                                      glm::vec2(rand_x_speed, rand_y_speed), 0.5, 8.0,
                                      cinder::Color(1,1,0), num));
    num++;
  }
}
void MyApp::update() {
  //checking for particles that hit the wall and update their velocity
  for (int i = 0; i < 20; i++) {
    //x axis
    if (particles[i].get_position()[0] <= getWindowWidth() / 2 - 200 || particles[i].get_position()[0] >= getWindowWidth() / 2 + 200 ) {
      float x_speed = particles[i].get_velocity()[0];
      float y_speed = particles[i].get_velocity()[1];
      particles[i].set_velocity(glm::vec2(-x_speed, y_speed));
    }
    if (particles[i].get_position()[1] <= getWindowWidth()/2 - 300 || particles[i].get_position()[1] >= getWindowWidth()/2 + 100) {
      float x_speed = particles[i].get_velocity()[0];
      float y_speed = particles[i].get_velocity()[1];
      particles[i].set_velocity(glm::vec2(x_speed, -y_speed));
    }
  }
  //checking for collision
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      if (particles[i].get_number() != particles[j].get_number() && particles[i].is_collided(particles[j])) {
        //std::cout<< particles[i].get_velocity() << "\n";
        //std::cout<< "_>_>_>_>_>>_>_>_>>_>_>_>_>_>>_" << "\n";
        particles[i].collision(particles[j]);
      }
    }
  }

  //updating position
  for (int i = 0; i < 20; i++) {
    particles[i].move();
  }

  //std::cout << particles[1].get_velocity() << "\n";

}
void MyApp::draw() {
  gl::clear();
  gl::color(0, 0, 2);
  gl::drawStrokedRect(Rectf( getWindowWidth()/2- 200.0f,
                             getWindowHeight()/2-200.0f,
                             getWindowWidth()/2+200.0f,
                             getWindowHeight()/2+200.0f ) );
  DrawParticles();
}
void MyApp::DrawParticles() {
  for (gas::Particle p : particles) {
    gl::color(p.get_color());
    gl::drawSolidCircle(p.get_position(), p.get_radius());
  }
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(MyApp, ci::app::RendererGl, MyApp::prepareSettings);
