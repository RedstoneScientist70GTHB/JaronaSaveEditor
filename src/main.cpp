#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// ===========================================================================
// Placeholder editor screen. The real save-editing features go here.
// ===========================================================================
class SaveEditorLayer : public CCLayer {
public:
    static SaveEditorLayer* create() {
        auto ret = new SaveEditorLayer();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    static CCScene* scene() {
        auto scene = CCScene::create();
        scene->addChild(SaveEditorLayer::create());
        return scene;
    }

    bool init() override {
        if (!CCLayer::init()) return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        this->addChild(CCLayerColor::create({30, 30, 40, 255}), -10);

        auto title = CCLabelBMFont::create("Jarona Save Editor", "goldFont.fnt");
        title->setPosition({winSize.width / 2, winSize.height - 30.f});
        this->addChild(title);

        auto note = CCLabelBMFont::create("Editing tools coming soon.", "bigFont.fnt");
        note->setScale(0.6f);
        note->setPosition(winSize / 2);
        this->addChild(note);

        auto menu = CCMenu::create();
        menu->setPosition({0.f, 0.f});
        this->addChild(menu);

        auto back = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
            this, menu_selector(SaveEditorLayer::onBack)
        );
        back->setPosition({25.f, winSize.height - 25.f});
        menu->addChild(back);

        this->setKeypadEnabled(true);
        return true;
    }

    void onBack(CCObject*) {
        CCDirector::sharedDirector()->popScene();
    }

    void keyBackClicked() override {
        this->onBack(nullptr);
    }
};

// ===========================================================================
// Main menu button
// ==========================================================================
class $modify(JSEMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        if (auto menu = this->getChildByID("bottom-menu")) {
            auto spr = ButtonSprite::create("Saves");
            spr->setScale(0.7f);
            auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(JSEMenuLayer::onOpenSaveEditor));
            btn->setID("save-editor-button"_spr);
            menu->addChild(btn);
            menu->updateLayout();
        }

        return true;
    }

    void onOpenSaveEditor(CCObject*) {
        CCDirector::sharedDirector()->pushScene(
            CCTransitionFade::create(0.3f, SaveEditorLayer::scene())
        );
    }
};
