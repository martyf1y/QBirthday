//
//  twitterMessages.cpp
//  QBday
//
//  Created by Matt Martin on 8/07/17.
//
//

#include "ofApp.h"
//--------------------------------------------------------------

void ofApp::updateMessage() {
    
        if (!waitType && !runAway) {
            newColor = QColor[int(ofRandom(0, 5))];
            
            if(newTweet && alltweets.size() != currentTweet){
                thisTwit = alltweets[currentTweet];
                currentTweet ++;
            }
            else{
                thisTwit = defaultMessage;
                newTweet = false;
            }
            stringCount = thisTwit.length();
            nextWord(thisTwit);
            //waitType = true;
            runAway = true;
        } else {
            // waitType = false;
            // runAway = false;
            goAgain = true;
        }
    
    if (waitType && !runAway) {
        waitType = printMessage();
        fade = 255;
    }
}

bool ofApp::printMessage() {
    if (stringCount > 0 && ofGetFrameNum()%2 == 0) {
        stringCount --;
        string typeTwit = thisTwit.substr(0, stringCount);
        message = typeTwit;
    } else if (stringCount <= 0) {
        return false;
    }
    // println("Still?");
    return true;
}

/*void getNewTweets()
{
    try {
        // try to get tweets here
        Query query = new Query(searchString);
        query.setCount(10);
        QueryResult result = twitter.search(query);
        tweets = result.getTweets();
        updateCount++ ;
        int i = 0;
        for (Status status : tweets) {
            System.out.println("@" + status.getUser().getScreenName() + ":" + status.getText());
            theTweets[i] = "@" + status.getUser().getScreenName() + " - " + status.getText();
            i++;
        }
    }
    catch (TwitterException te) {
        // deal with the case where we can't get them here
        System.out.println("Failed to search tweets: " + te.getMessage());
        System.exit(-1);
    }
    counterTwit ++;
}

void refreshTweets()
{
    if (goAgain) {
        // while (true) {
        getNewTweets();
        println("Updated Tweets");
        println("currentzzzz" + tweets.size());
        
        //delay(100);
        goAgain = false;
        // }
    }
}*/
