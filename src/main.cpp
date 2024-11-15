#include <Geode/Geode.hpp>
using namespace geode::prelude;
namespace fs = std::filesystem;
#include <Geode/modify/MenuLayer.hpp>
bool isValidSprite(CCNode* obj) {
	return obj && !obj->getUserObject("geode.texture-loader/fallback");
}
class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}
		bool isValidImage = false;
		auto winSize = CCDirector::sharedDirector()->getWinSize();
		auto bottomMenu = this->getChildByIDRecursive("profile-menu");
		auto profileButton = bottomMenu->getChildByIDRecursive("profile-button");
		if (!profileButton) return true;
		auto profileImage = typeinfo_cast<CCSprite*>(profileButton->getChildren()->objectAtIndex(0));
		auto img = Mod::get()->getSettingValue<std::filesystem::path>("image");
		//if (img == "") return true;
		if (!fs::exists(img)) return true;
		
		CCSprite* newButton = CCSprite::create(img.string().c_str());
		isValidImage = newButton;
		if (isValidImage) isValidImage = isValidSprite(newButton);
		//profileButton->addChild(newButton);
		if (isValidImage) {
			profileImage->removeFromParent();
			newButton->setPosition({profileImage->getPositionX(),profileImage->getPositionY()});
			newButton->setScale(48 / newButton->getContentSize().width);
			if (Mod::get()->getSettingValue<bool>("circleb") == true) {
				auto clippingNode = CCClippingNode::create();
				clippingNode->setContentSize(newButton->getContentSize());
				clippingNode->setAnchorPoint({0.5f,0.5f});
				clippingNode->ignoreAnchorPointForPosition(true);
				clippingNode->setZOrder(0);
				clippingNode->setInverted(false);
				clippingNode->setAlphaThreshold(0.7f);
				auto mask = CCSprite::createWithSpriteFrameName("d_circle_02_001.png");
				mask->setAnchorPoint({0.5f,0.5f});
				mask->setColor({255,255,255});
				mask->setPosition(newButton->getPosition());
				mask->setScale(.9f);
				//mask->setScale(0.8f);
				mask->setZOrder(1);
				clippingNode->addChild(newButton);
				clippingNode->setStencil(mask);
				//clippingNode->setPosition(mask->getPosition());
				profileButton->addChild(clippingNode);
				CCSprite* border = CCSprite::create("borderProfile.png"_spr);
				border->setPosition(newButton->getPosition());
				border->setZOrder(2);
				profileButton->addChild(border);
			}else{
				profileButton->addChild(newButton);
			}
		}else{
			if (Mod::get()->getSettingValue<bool>("showerror") == true) {
				auto alert = FLAlertLayer::create(
					"Custom Profile Image",
					"The loaded image doesn't seem to be valid. Please try with another image.",
					"OK"
				);
				alert->m_scene = this;
				alert->show();
			}
		}
		return true;
	}
};
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/utils/web.hpp>
class $modify(ExtendedProfilePage, ProfilePage) {
	bool init(int accountID, bool ownProfile) {
        if (!ProfilePage::init(accountID, ownProfile)) return false;
		if (Mod::get()->getSettingValue<bool>("profile") == true) {
			bool isValidImage = false;
			auto winSize = CCDirector::sharedDirector()->getWinSize();
			auto username = static_cast<cocos2d::CCMenu *>(this->getChildByIDRecursive("username-menu"));
			auto name = static_cast<cocos2d::CCLabelBMFont *>(username->getChildByIDRecursive("username-label"));
			
			auto img = Mod::get()->getSettingValue<std::filesystem::path>("image");
			if (!fs::exists(img)) return true;
			CCSprite* newButton = CCSprite::create(img.string().c_str());
			isValidImage = newButton;
			if (isValidImage) isValidImage = isValidSprite(newButton);
			if (isValidImage) {
				newButton->setID("profile-image");
				
				newButton->setScale(32 / newButton->getContentSize().width);
			
				if (Mod::get()->getSettingValue<bool>("circleb") == true) {
					newButton->setScale(16 / newButton->getContentSize().width);
					auto clippingNode = CCClippingNode::create();
					clippingNode->setContentWidth(newButton->getScaledContentSize().width);
					clippingNode->setZOrder(0);
					clippingNode->setInverted(false);
					clippingNode->setAlphaThreshold(0.7f);
					clippingNode->setID("clipping-image");
					newButton->setScale(32 / newButton->getContentSize().width);
					//clippingNode->setPosition(newButton->getPosition());
					auto mask = CCSprite::createWithSpriteFrameName("d_circle_02_001.png");
					
					mask->setColor({255,255,255});
					mask->setScale(.7f);
					//mask->setScale(0.8f);
					
					mask->setZOrder(1);
					clippingNode->addChild(newButton);
					clippingNode->setStencil(mask);
					
					CCSprite* border = CCSprite::create("borderProfile.png"_spr);
					border->setScale(.7f);
					border->setZOrder(2);
					clippingNode->addChild(border);
					
					if (this->m_ownProfile) {
						username->addChild(clippingNode);
					}
				}else{
					if (m_ownProfile) {
						//changepfp->setAnchorPoint({0.5f,0.5f});
						username->addChild(newButton);
					}
				}
				username->updateLayout();
				this->updateLayout();
			}
		}
		return true; 
    }
	
};
