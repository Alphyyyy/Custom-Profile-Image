#include <Geode/Geode.hpp>

using namespace geode::prelude;
namespace fs = std::filesystem;
#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}
		auto winSize = CCDirector::sharedDirector()->getWinSize();
		auto bottomMenu = this->getChildByIDRecursive("profile-menu");
		auto profileButton = bottomMenu->getChildByIDRecursive("profile-button");
		if (!profileButton) return true;
		auto profileImage = typeinfo_cast<CCSprite*>(profileButton->getChildren()->objectAtIndex(0));
		auto img = Mod::get()->getSettingValue<std::filesystem::path>("image");
		//if (img == "") return true;
		if (!fs::exists(img)) return true;
		profileImage->removeFromParent();
		if (Mod::get()->getSettingValue<bool>("circle") == false) { 
			auto newButton = CCSprite::create(img.string().c_str());
			//profileButton->addChild(newButton);
			newButton->setPosition({profileImage->getPositionX(),profileImage->getPositionY()});
			newButton->setScale(48 / newButton->getContentSize().height);
			if (Mod::get()->getSettingValue<bool>("circleb") == true) {
				auto clippingNode = CCClippingNode::create();
				auto mask = CCDrawNode::create();
				mask->drawCircle(newButton->getPosition(),24,ccc4FFromccc3B({ 255, 255, 255 }),0.f,ccc4FFromccc3B({ 255, 255, 255 }),23);
				clippingNode->setStencil(mask);
				clippingNode->setPosition(mask->getPosition());
				clippingNode->addChild(newButton);
				profileButton->addChild(clippingNode);
				CCSprite* border = CCSprite::create("borderProfile.png"_spr);
				border->setPosition(newButton->getPosition());
				border->setZOrder(1);
				profileButton->addChild(border);
			}else{
				profileButton->addChild(newButton);
			}
			
		}else{
			auto newButton = CircleButtonSprite::createWithSprite(img.string().c_str());
			profileButton->addChild(newButton);
			newButton->setPosition({profileImage->getPositionX(),profileImage->getPositionY()});
			newButton->setScale(1.2f);
		}
		return true;
	}
};
