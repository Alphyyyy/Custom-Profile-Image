#include <Geode/Geode.hpp>

using namespace geode::prelude;
namespace fs = std::filesystem;
#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}
		auto bottomMenu = this->getChildByIDRecursive("profile-menu");
		auto profileButton = bottomMenu->getChildByIDRecursive("profile-button");
		if (!profileButton) return true;
		auto profileImage = typeinfo_cast<CCSprite*>(profileButton->getChildren()->objectAtIndex(0));
		auto img = Mod::get()->getSettingValue<std::filesystem::path>("image");
		if (img == "") return true;
		if (!fs::exists(img)) return true;
		profileImage->removeFromParent();
		if (Mod::get()->getSettingValue<bool>("circle") == false) { 
			auto newButton = CCSprite::create(img.string().c_str());
			profileButton->addChild(newButton);
			newButton->setPosition({profileImage->getPositionX(),profileImage->getPositionY()});
			if (newButton->getContentSize().height > newButton->getContentSize().width) {
				newButton->setScale(48 / newButton->getContentSize().height);
			}else{
				newButton->setScale(48 / newButton->getContentSize().width);
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
