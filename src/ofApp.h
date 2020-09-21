#pragma once

#include "ofMain.h"
#include "dustParticles.h"
#include "ofxParagraph.h"
#include "ofxTwitter.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void updateMessage();
        void nextWord(string word);
        bool printMessage();
    void onStatus(const ofxTwitter::Status& status);
    void onError(const ofxTwitter::Error& error);
    void onException(const std::exception& exception);
    void onMessage(const ofJson& json);
    
        void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
    
    ////////// Twitter stuff ///////////
    ofxTwitter::SearchClient client;
    
    uint64_t count = 0;
    uint64_t countMissed = 0;
    
    //////////// Twitter fangs! ///////////
    
    int tweetNum = 20;
    string searchString = "hi filter:safe";
    // List<Status> tweets;
    //   Status status;
    vector <string> alltweets;
    Boolean Tweet = false;
    Boolean moveMoon = true;
    
    int stringNum = 0;
    bool checkConnected = true;
    
    
    
    
    vector <dustParticle> arrayDustParticles;
    ofxParagraph paragraph;
  //  vector <fireFly> arrayFireFlies; // ArrayList poop; // Star Particles
    //oneLargeMoon bigMoon;
    
    // tweets
    bool newTweet = false;
    // particles
    bool isOneDead = false;
    bool drawAsPoints = false;
    bool runAway = false;
    bool goFree = false; // This is the variable saying if the particles should be added
    
    bool changeMoon = false;
    
    // words
    bool waitType = false;
    
    // tweet
    int tweetCounter = 0;
    int tweetPacket = 12;
    int currentTweet;
    
    //// Moon sizes
    int fullMoonSize = 620;
    const int moonAdjust = int(ofMap(fullMoonSize, 150, 1500, 250, 2500));
    const int moonShift = 0;
    int leftMoonSize = 0;
    int heightPos;
    
    float maskSize = 468;
    float moonRotation = 0;
    
    // Word particle variables
    int pixelSteps = 1; // Amount of pixels to skip
    int wordIndex = 0;
    int messageWidth;
    int messageHeight;
    int messagePositionX;
    int messagePositionY;
    int messageSize = 22;
    float sizepercent = 0;
    
    ///// Word timers
    int tweetCheckEndTimer = 11000;
    int tweetCheckTimer;
    int cycleEndTime = 11000; // This IS THE MAIN end TIME
    int cycleTimer; // This is the main timer
    int wordEndTime = 3000; // This IS THE MAIN end TIME
    int longTimer;
    int stringCount = 0;
    int minuteTimer = 0;
    int removeMoonCounter = 0;
    float longEndTime = 65000;
    
    
    // Tweets
    string theTweets[30];
    string thisTwit;
    
    // Messages
    string message;
    string defaultMessage;
    
    ofColor bgColor = ofColor(255, 100);
    ofColor newColor;
    ofColor QColor[7];
    /// BG
    ofColor b1, b2, c1, c2;
    
   // ofTrueTypeFont font;
    
    
    ofFbo BG;
    ofFbo pg;
    const int Y_AXIS = 1;
    
    ofImage gradBackground;
   
    int fontSize = 20;
    
    int counterTwit = 0;
 
    
    float particleWidth = maskSize;
//    Twitter twitter;
 //   List<Status>tweets;
    
    //Status status;
    bool goAgain = true;
    int updateCount = 0;
    
    ///// Word timers
    int wordTimer;
    bool fadeQ = false;
    int fade = 255;
    
    /// txt stuff
    vector <string> loadtxt;
    vector <string> txtMessages;
    int txtcount = 0;
		
};
