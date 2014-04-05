require("app.scenes.CCBLayer")
require("app.scenes.UILayer")


local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    main = self
end

function MainScene:onEnter()
    local layer = CCLayerColor:create(ccc4(230,230,230,255))
    self:addChild(layer,-1)

    self.spritenode = CCNode:create()
    self.spritenode:setPosition(ccp(10,display.height-40))
    self:addChild(self.spritenode,1)

    self.ui = UILayer.new()
    self:addChild(self.ui)
    self.ui:initialize()
    
    init_sprite()
end

function MainScene:onExit()
end

function MainScene:setTexture( file)
    local sprite = CCSprite:create(file)
    sprite:setAnchorPoint(ccp(0,1))
    self.spritenode:addChild(sprite)
end

return MainScene
