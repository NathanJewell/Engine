#pragma once
#include <SFML/Graphics.hpp>
#include "..\Utility\Utilities.hpp"

class Layer
{

public:

	Layer();	
	~Layer();


	void create();


	void setScrollSpeed(const sf::Vector2f& fspeed);	//set the scrolling speed of the layer; should be pairs of numbers bewtween 0 and 1 inclusive

	sf::Vector2f getScrollSpeed();						//get scroll speed



	void setScrollBounds(const double& nsBound, const unsigned int& index);
														//sets a specific scrollBound


	void setScrollBounds(std::vector<const double> nsBound);	//set all scrollBounds

	double getScrollBound(const unsigned int& index);	//gets a scroll bound by index


	void setScrollBoundedness(const bool& nscrollBounded);

	bool getScrollBoundedness();



	std::pair<unsigned int, unsigned int> getScrollLock();

	void setScrollLock(const unsigned int& lockState, const unsigned char& lockAxis);

	void setTrackLocking(const bool& b);



	void setExtremeCorners(const sf::Vector2f& fTLCorner, const sf::Vector2f& fBRCorner);

	void setExtremeCornersAlt(const sf::Vector2f& fBLCorner, const sf::Vector2f& fTRCorner);

	void setTopLeftCorner(const sf::Vector2f& fTLCorner);

	void setBottomRightCorner(const sf::Vector2f& fBRCorner);

	void setBottomLeftCorner(const sf::Vector2f& fBLCorner);

	void setTopRightCorner(const sf::Vector2f& fTRCorner);


	float getMinWindowX();
	float getMaxWindowX();
	float getMinWindowY();
	float getMaxWindowY();

	std::pair<sf::Vector2f, sf::Vector2f> getWindowCorners();

	void interpretViewPos(const sf::Vector2f& scrollDist);



	sf::RenderTexture* getRenderTexture();





private:

	void moveBoundCorners(const sf::Vector2f& dist);
	void moveTrackCorners(const sf::Vector2f& dist);

	sf::Vector2f getCorrectiveDistance();

	sf::Vector2f scrollSpeed;							//the fraction of the "normal" scroll speed at which a layer will scroll; a layer with
														//.5 scroll speed will scroll half as quickly as a layer with 1 scroll speed; a layer with 0
														//scroll speed will be stationary.

	double scrollBounds[4];								//the purpose is that a layer should not be able to scroll forever. see http://imgur.com/SzH03Ju for a lack of scroll bounds.

	bool scrollBounded;									//true if the layer has active scrolling bounds.
	bool mapSizeLock;									//true if the layer's scroll bounds should always be equal to map size


	bool trackLocking;

	//sf::Vector2f scrollTracker;							//keeps track of the scrolling

	//sf::Vector2f oldScrollTracker;


	sf::Vector2f boundTLCorner;
	sf::Vector2f boundBRCorner;

	sf::Vector2f trackTLCorner;
	sf::Vector2f trackBRCorner;
	

	

	sf::RenderTexture renderTex;

	sf::View view;

	enum boundPositions { Top = 0, Left, Bottom, Right };

	

	unsigned int scrollLockX;
	unsigned int scrollLockY;

	enum lockState {Lockless = 0, Unlocked, Locked};

};

