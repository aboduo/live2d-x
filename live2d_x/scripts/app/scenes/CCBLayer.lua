
CCBLayer = class("CCBLayer", function ()
	return LuaProxy:create()
end)

function CCBLayer:ctor( )
	self:setAnchorPoint(ccp(0,0))
	self.mElement = {}
end

local _ccproxy = CCBProxy:new_local()
function CCBLayer:loadCCB( filePath )
	local repath = CCFileUtils:sharedFileUtils():fullPathForFilename(filePath)
	if io.exists(repath) == false then
		print("File exsit [CCBLayer:loadCCB]"..filePath)
		return
	end
	self.mRootNode = self:readCCBFromFile(repath)
	self:addChild(self.mRootNode)
	self:setContentSize(self.mRootNode:getContentSize())
	self.mAnimManager = tolua.cast(self.mRootNode:getUserObject(),"CCBAnimationManager")
	self.mHasAnimCallBack = false

	local function on_touch(event,x,y)
		return true
	end
	self:registerScriptTouchHandler(on_touch,false,1,true)
end

function CCBLayer:reSizeByDisplay( name )
	local node = self:getNode(name)
	if node then
		local size = node:getContentSize()
		size.height = display.height-(960-size.height)
		if self:typeof(name) == "CCScrollView" then
			node:setViewSize(size)
		else
			node:setContentSize(size)
		end
	end
end

function CCBLayer:getElement( name )
	local newnode = self.mElement[name]
	if newnode ~= nil then
		return newnode
	end
	local node = self:getNode(name)
	local type = _ccproxy:getNodeTypeName(node)
	if type ~= "No Support" then
		newnode = tolua.cast(node,type)
	else
		newnode = node
	end
	self.mElement[name] = newnode
	return newnode
end

function CCBLayer:typeof( name )
	local node = self:getElement(name)
	return _ccproxy:getNodeTypeName(node)
end

function CCBLayer:getLayer(name)
	return self:getElement(name)
end

function CCBLayer:getSprite(name)
	return self:getElement(name)
end

function CCBLayer:getLabel(name)
	return self:getElement(name)
end

function CCBLayer:getMenu( name )
	return self:getElement(name)
end

function CCBLayer:getButton( name )
	return self:getElement(name)
end

function CCBLayer:getList( name )
	return self:getElement(name)
end

function CCBLayer:getPage( name )
	return self:getElement(name)
end

function CCBLayer:swallowTouch( value )
	self:setTouchEnabled(value)
end

function CCBLayer:createListLayer(name,data)
	data = data or {}
	local node = self:getElement(name)
	local list = ListLayer.new(self,data.type)
	list:setParent(node)
	self.mElement[name] = list
	if data.itemLoader then
		list:setItemLoader(data.itemLoader)
	end
	if data.x and data.y then
		list:setDefaultCount(data.x,data.y)
	end
end

function CCBLayer:createPageLayer( name,data )
	if data == nil or data.itemLoader == nil then
		dm("[CCBLayer:createPageLayer]itemLoader is nil")
		return
	end
	local node = self:getElement(name)
	local size = node:getContentSize()
	local page = PageLayer.new(size.width,size.height,data.itemLoader)
	node:addChild(page)
	self.mElement[name] = page
end

function CCBLayer:getParticle( name )
	return self:getElement(name)
end

function CCBLayer:setButtonTitle( name, title )
	local button = self:getButton(name)
	button:setTitleForState(CCString:create(title),CCControlStateNormal)
	button:setTitleForState(CCString:create(title),CCControlStateHighlighted)
	button:setTitleForState(CCString:create(title),CCControlStateDisabled)
	button:setTitleForState(CCString:create(title),CCControlStateSelected)
end

function CCBLayer:createCCProgressTimer( name ,data)
	local sprite = self:getSprite(name)
	if data == nil then data = {} end
	if sprite then
		local prog = CCProgressTimer:create(sprite)
		sprite:getParent():addChild(prog)
		prog:setAnchorPoint(sprite:getAnchorPoint())
		prog:setVisible(sprite:isVisible())
		prog:setPosition(sprite:getPosition())
		prog:setScaleX(sprite:getScaleX())
		prog:setScaleY(sprite:getScaleY())
		sprite:setVisible(false)
		if not data.type or data.type == "bar" then
			prog:setType(1)
			prog:setMidpoint(CCPoint(0,0.5))
			prog:setBarChangeRate(CCPoint(1,0))
		elseif data.type == "range" then
			prog:setType(0)
			prog:setMidpoint(CCPoint(0.5,0.5))
			prog:setBarChangeRate(CCPoint(1,0))
		end
		if data.value==nil then data.value=0 end
		prog:setPercentage(data.value)
		self.mElement[name] = prog
	else
		print("[CCBLayer:createCCProgressTimer]node is nil:"..name)
	end
end

function CCBLayer:createCCEditBox(name, data )
	local node = self:getElement(name)
	if node then
		local size = node:getContentSize()
		local edit = ui.newEditBox({
	        image = "none.png",
	        size = CCSize(size.width-40,size.height-40),
	        x = size.width/2,
	        y = size.height/2,
	        listener = function(event, editbox)
	            if event == "began" then
	            	if self["on_edit_"..name.."_began"] then
		                self["on_edit_"..name.."_began"](editbox)
		            end
	            elseif event == "ended" then
	            	if self["on_edit_"..name.."_ended"] then
		                self["on_edit_"..name.."_ended"](editbox)
		            end
	            elseif event == "return" then
	            	if self["on_edit_"..name.."_return"] then
		                self["on_edit_"..name.."_return"](editbox)
		            end
	            elseif event == "changed" then
	            	if self["on_edit_"..name.."_changed"] then
		                self["on_edit_"..name.."_changed"](editbox)
		            end
	            else
	                printf("EditBox event %s", tostring(event))
	            end
	        end
	    })
		node:addChild(edit)
		edit:setScaleX(node:getScaleX())
		edit:setScaleY(node:getScaleY())
		if data and data.isPassWord then
			-- edit:
		end
	else
		print("[CCBLayer:createCCEditBoxLayer]node is nil:"..name)
	end
end

function CCBLayer:setHandler( menuName, hand,tag )
	local object = self:getElement(menuName)
	if object == nil then
		print("[SetHandler]object",menuName," is nil")
		return
	end
	if self:typeof(menuName) == "CCControlButton" then
		if tag == nil then
			tag = CCControlEventTouchUpInside
		end
		self:handleControlEvent(object,handler(self,hand),tag)
	else
		self:handleMenuEvent(object,handler(hand))
	end
end

--和上一个相比，传入的是临时函数，即不用self的handler
function CCBLayer:setHandlerLocal( menuName, hand,tag )
	local object = self:getElement(menuName)
	if object == nil then
		print("[SetHandler]object",menuName," is nil")
		return
	end
	if self:typeof(menuName) == "CCControlButton" then
		if tag == nil then
			tag = CCControlEventTouchUpInside
		end
		self:handleControlEvent(object,hand,tag)
	else
		self:handleMenuEvent(object,hand)
	end
end

function CCBLayer:runAnimation( name )
	-- body
	self.mAnimManager:runAnimationsForSequenceNamed(name)
	if self.mHasAnimCallBack == false then
		self.mHasAnimCallBack = true
		self:handleAnimationComplate(self.mAnimManager,handler(self,self.onAnimationComplate))
	end
end

function CCBLayer:onAnimationComplate( animManager , animName )
	-- print("[CCBLayer:onAnimationComplate]函数需要重载,animName = "..animName)
end

function CCBLayer:onSwitchOut()
	self:setVisible(false)
end

function CCBLayer:onSwitchIn()
	self:setVisible(true)
end

function CCBLayer:initialize( )
	-- body
end

