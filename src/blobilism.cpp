/**
* Assignment 01: Blobilism
*
* This program is a painting tool that implements functionality
* for changing brush size, transparency, and color, as well as 
* clearing the screen through the use of UI 
* and keyboard controls.
*
* @author: S. Gavin Sears
* @version: January 26, 2023
*/

#include <iostream>
#include <vector>
#include "tinygl-cpp.h"
#include <math.h>
using namespace tinygl;

class Circle
{
    // Qualities of a Drawn Circle
    protected:
    float x;
    float y;
    float alpha;
    float radius;
    std::vector<float> RGB;

    // Constructor
    public:
    Circle(float cX, float cY, float cA, float cR, std::vector<float> cRGB) 
    {
        x = cX;
        y = cY;
        alpha = cA;
        radius = cR;
        RGB = cRGB;
    }

    // Getters
    float getx(){return x;}
    float gety(){return y;}
    float getAlpha(){return alpha;}
    float getRadius(){return radius;}
    std::vector<float> getRGB(){return RGB;}
};

class MyWindow : public Window {
 public:
  MyWindow(int w, int h) : Window(w, h) {}

  void setup() override {
    std::cout << "Window size: " << width() << ", " << height() << std::endl;
  }

  virtual void mouseMotion(int x, int y, int dx, int dy) {
    if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
      mx = mouseX();  // current mouse pos x
      my = mouseY();  // current mouse pos y

      if (my > 70.0f)
      {
        mCircles.push_back(Circle(mx, my, mAlpha, mRadius, mRGB));
      }
    }
  }
  
  virtual void mouseDown(int button, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      mx = mouseX();  // current mouse pos x
      my = mouseY();  // current mouse pos y

      for (int i=0; i < pallet.size(); i++)
      {
        
        if (sqrt(pow(((35.0f + (i * 70.0f)) - mx), 2) + pow((35.0f - my), 2)) < 35.0f)
        {
            mRGB = {pallet[i][0], pallet[i][1], pallet[i][2]};
            std::cout << "Setting color to " << mRGB[0] << " " << mRGB[1] << " " << mRGB[2] << std::endl;

        }
      }
    }
  }

  void keyDown(int key, int mods) {
    if (key == GLFW_KEY_UP) {
      // increase size of circle
      if (mRadius < 100)
      {
        mRadius += 5;
        std::cout << "Pressed UP: Increase size " << mRadius << std::endl;
      }
      else
      {
        std::cout << "Pressed UP: Maximum size reached " << mRadius << std::endl;
      }
    } 
    else if (key == GLFW_KEY_DOWN) {
      // decrease size of circle
      if (mRadius > 5)
      {
        mRadius -= 5;
        std::cout << "Pressed DOWN: Decrease size " << mRadius << std::endl;
      }
      else
      {
        std::cout << "Pressed DOWN: Minimum size reached " << mRadius << std::endl;
      }
    }
    else if (key == GLFW_KEY_LEFT) {
      // decrease alpha
      if (mAlpha > 0.05f)
      {
        mAlpha -= 0.05;
        std::cout << "Pressed LEFT: Decrease alpha " << mAlpha << std::endl;
      }
      else if (mAlpha > 0.045 && mAlpha < 0.055)
      {
        mAlpha = 0.0f;
        std::cout << "Pressed LEFT: Decrease alpha " << mAlpha << std::endl;
      }
      else
      {
        std::cout << "Pressed LEFT: Minimum alpha reached " << mAlpha << std::endl;
      }
    }
    else if (key == GLFW_KEY_RIGHT) {
      // increase alpha
      if (mAlpha < 1.0f)
      {
        mAlpha += 0.05;
        std::cout << "Pressed RIGHT: Increase alpha " << mAlpha << std::endl;
      }
      else 
      {
        std::cout << "Pressed RIGHT: Maximum alpha reached " << mAlpha << std::endl;
      }
    }
    else if (key == GLFW_KEY_C) {
      // clear vector of circles
      mCircles.clear();
      std::cout << "Clear Screen" << std::endl;
    }
  }

  void draw() override {
    background(0.95f, 0.95f, 0.95f); // parameters: r, g, b

    // Drawn circles
    for (int i=0; i < mCircles.size(); i++)
    {
      std::vector<float> iRGB = mCircles[i].getRGB();
      color(iRGB[0], iRGB[1], iRGB[2], mCircles[i].getAlpha());
      circle(mCircles[i].getx(), mCircles[i].gety(), mCircles[i].getRadius());
    }

    // Pallet base
    color(0.2f, 0.2f, 0.2f);
    square(width()/2.0f, 35, width(), 70); 

    // Paint types
    for (int i=0; i < pallet.size(); i++)
    {
      color(pallet[i][0], pallet[i][1], pallet[i][2]);
      circle((35.0f + (i * 70.0f)),35.0f, 50.0f);
    }

  }
 private:

  // mouse position
  float mx;
  float my;
  // current circle size
  float mRadius = 35.0f;
  // current transparency
  float mAlpha = 1.0f;
  // list of circles to draw each frame
  std::vector<Circle> mCircles;

  // "Cyberpunk Synthware Color Palette" from colorpalettes.io
  std::vector<std::vector<float>> pallet = {
  // "Clean Pool Blue" (altered for better contrast)
  {0.40f, 0.85f, 0.96f}, 
  // "Maldives" (altered for better contrast)
  {0.00f, 0.70f, 0.84f}, 
  // "Pink Bite"
  {0.91f, 0.24f, 0.67f}, 
  // "Sapphire Splendor"
  {0.12f, 0.13f, 0.67f}, 
  // "Shadown Planet"
  {0.13f, 0.08f, 0.28f}, 
  // "Midnight Dreams"
  {0.02f, 0.11f, 0.17f}
  };

  // current color
  std::vector<float> mRGB = pallet[0];

};

int main() {
  MyWindow window(500, 500);
  window.run();
}
