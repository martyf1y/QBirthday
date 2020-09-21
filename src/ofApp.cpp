#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);

    messagePositionX = ofGetWidth()/2;
    messagePositionY = ofGetHeight()/2;
    messageWidth = ofGetWidth()/1.5;
    messageHeight = ofGetHeight()/1.5;
    
    // Easily register for all search events.
    client.registerSearchEvents(this);
    
    client.setCredentialsFromFile("credentials.json");
    // Set the polling interval for 6 seconds.
    client.setPollingInterval(6000);
    ofxTwitter::SearchQuery query(searchString);
    query.setResultType(ofx::Twitter::SearchQuery::ResultType::RECENT);
    client.search(query);
 
    currentTweet = 0;

    // thread("refreshTweets");
    paragraph.setFont("verdana.ttf", fontSize);

    defaultMessage = "SHARE YOUR BIRTHDAY WISH FOR Q! Here is a short story about my friend carl. You see carl likes to east pinapples at the beach which isn't the best thing to do even though pineapples grow on beaches. Too much sand ya see? Anyway goodbye.";
    
    QColor[0] = ofColor(35, 177, 221);
    QColor[1] = ofColor(118, 61, 144);
    QColor[2] = ofColor(250, 198, 0);
    QColor[3] = ofColor(238, 237, 238);
    QColor[4] = ofColor(224, 0, 105);
    
    // loadtxt = loadStrings("bday.txt");
    //   txtMessages = split(loadtxt[0], '*' );
    ofBuffer buffer = ofBufferFromFile("bday.txt");
    int count = 0;
    //  string list[3];
    
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        txtMessages.push_back(line);
        count ++;
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    updateMessage();

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    
    
    
    if (runAway && !waitType) {
        bool checkDeyAllDead = true;
        for (int x = arrayDustParticles.size ()-1; x > -1; x--) {
            // Simulate and draw pixels
            if(!arrayDustParticles[x].isKilled){
                arrayDustParticles[x].move();
                checkDeyAllDead = false;
            }
            arrayDustParticles[x].draw(drawAsPoints);
        }
        if(checkDeyAllDead){
            for (int x = arrayDustParticles.size ()-1; x > -1; x--) {
                arrayDustParticles.erase(arrayDustParticles.begin()+x);
                
            }
            waitType = true;
            runAway = false;
            cout << "TRUE??" << endl;
            message = thisTwit;
        }
    }
    if (waitType) {
       // paragraph = ofxParagraph(message, messageWidth);
        paragraph.setText(message);
        paragraph.setWidth(messageWidth);
        paragraph.setColor(ofColor(newColor));
        paragraph.draw(messagePositionX-messageWidth/2, messagePositionY-messageHeight/2);
        
        if(!runAway){
            wordTimer = ofGetElapsedTimeMillis(); // resets timer
        }
    }
    
    cout << "Frames: " << ofGetFrameRate() << endl;;
}


// Makes all particles draw the next word
void ofApp::nextWord(string word) {
    // Draw word in memory
    pg.allocate(messageWidth, messageHeight);
    //paragraph = ofxParagraph(word, messageWidth);
    paragraph.setText(word);
    paragraph.setWidth(messageWidth);

    pg.begin();
    ofClear(0,0,0,0);
    //ofSetColor(255, 255, 255);
    // font.drawString(word, 0, fontSize);
    paragraph.setColor(ofColor(255, 255, 255));
    paragraph.draw(0,20);
    pg.end();
    
    ofPixels pixels;
    pg.readToPixels(pixels);
    ofSaveImage(pixels,"hello.jpg");     // Next color for all pixels to change to
    ofColor realQColor = ofColor(239, 193, 57);
    
    for (int i = 0; i < (messageWidth*messageHeight)-1; i++) {
        // Convert index to its coordinates
        int x = i % pixels.getWidth();
        int y = i / pixels.getWidth();
        
        // Only continue if the pixel is not blank
        if (pixels.getColor(x, y) != ofColor(0,0,0,0)) {
            
            
            dustParticle newParticle;
            // cout << particleIndex<< particleCount << "YENS" << endl;
            // newParticle.dustParticle();
            
            newParticle.target.x = x + messagePositionX-messageWidth/2;
            newParticle.target.y = y + messagePositionY-messageHeight/2 - fontSize;
            newParticle.pos.x = int(ofRandom(-particleWidth/2 + 65, particleWidth/2 - 75));
            
            float radiusSquared = int(((particleWidth/2-58)) * ((particleWidth/2-58)));
            float xSquared = int((newParticle.pos.x) * (newParticle.pos.x));
            newParticle.pos.y = int(sqrt((radiusSquared - xSquared)));
            newParticle.pos.x += ofGetWidth()/2;
            int ran = int(ofRandom(0,2));
            if(ran==1){
                newParticle.pos.y*=-1;
            }
            newParticle.pos.y += ofGetHeight()/2 - 28;
            newParticle.maxSpeed = ofRandom(5.0, 8.0);
            newParticle.maxForce = newParticle.maxSpeed*0.025;
            newParticle.particleSize = ofRandom(3, 6);
            newParticle.colorBlendRate = ofRandom(0.0025, 0.03);
            
            // Blend it from its current color
            newParticle.startColor = realQColor;
            newParticle.targetColor = newColor;
            newParticle.colorWeight = 0;
            
            arrayDustParticles.push_back(newParticle);
            
        }
    }
    sizepercent = arrayDustParticles.size();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    drawAsPoints = (! drawAsPoints);
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (button == 0 && !runAway) {
        runAway = true;
        if (runAway) {
            nextWord(message);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

void ofApp::onStatus(const ofxTwitter::Status& status){
    count++;
    stringNum ++;
    if(stringNum>19){stringNum = 0;}
    ofLogNotice("NEW TWEET #") << count <<  " :" << status.text();
    alltweets.push_back(status.text());
    newTweet = true;
}
void ofApp::onError(const ofxTwitter::Error& error){
    ofLogError("ofApp::onError") << "Error: " << error.code() << " " << error.message();
    checkConnected = false;
}
void ofApp::onException(const std::exception& notice){
    ofLogError("ofApp::onException") << "Exception: " << notice.what();
}
void ofApp::onMessage(const ofJson& json){
    // This is the raw message json and is ignored here.
}
