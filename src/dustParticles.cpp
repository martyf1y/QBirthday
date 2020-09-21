//
//  dustParticles.cpp
//  particlesForOF
//
//  Created by Matt Martin on 2/07/17.
//
//

#include "dustParticles.h"

//------------------------------------------------------------------
dustParticle::dustParticle(){
    pos.set(0, 0);
    vel.set(0, 0);
    target.set(0, 0);
    acc.set(0, 0);
    
    closeEnoughTarget = 40;
    maxSpeed = 4.0;
    maxForce = 0.1;
    particleSize = 5;
    isKilled = false;
    
   // startColor = newColor;
    targetColor = ofColor(0);
    colorWeight = 0;
    colorBlendRate = 0.025;
    
}

void dustParticle::move() {
    
    // Check if particle is close enough to its target to slow down
    float proximityMult = 1.0;
    float distance = ofDist(pos.x, pos.y, target.x, target.y);
    if (distance < closeEnoughTarget) {
        proximityMult = distance/closeEnoughTarget;
    }
    
    // Add force towards target
    ofVec2f towardsTarget(target.x, target.y);
    //   towardsTarget.ofSub(pos);
    towardsTarget -= pos;
    towardsTarget.normalize();
    towardsTarget *= (maxSpeed*proximityMult);
    
    ofVec2f steer(towardsTarget.x, towardsTarget.y);
    steer -= vel;
    steer.normalize();
    steer *= maxForce;
    acc += steer;
    
    // Move particle
    vel += acc;
    pos += vel;
    acc *= 0;
    
    if (distance <= 3) {
        kill();
        pos = target;
    }
    
}

void dustParticle::draw(bool drawAsPoints) {
    // Draw particle
    
    
    ofColor currentColor = startColor.lerp(targetColor, colorWeight);
    //ofColor currentColor = targetColor;
    //ofcolor
     if (drawAsPoints) {
      ofSetColor(currentColor);
    ofDrawCircle(pos.x, pos.y, 1);
    } else {
    ofSetColor(currentColor);
    ofDrawEllipse(pos.x, pos.y, particleSize, particleSize);
    }
    
    // Blend towards its target color
    if (colorWeight < 1.0) {
        colorWeight = MIN(colorWeight+colorBlendRate, 1.0);
    }
}

void dustParticle::kill() {
    if (! isKilled) {
        // Set its target outside the scene
       // ofPoint randomPos = generateRandomPos(ofGetWidth()/2, ofGetHeight()/2, (ofGetWidth()+ofGetHeight())/2);
      //  target.x = randomPos.x;
       // target.y = randomPos.y;
        
        // Begin blending its color to black
      //  startColor = startColor.lerp(targetColor, colorWeight);
      //  targetColor = ofColor(0);
      //  colorWeight = 0;
        particleSize = 1;
        isKilled = true;
    }
}

