--[[
 -- @authors 血染的玩偶 (909585215@qq.com)
 -- @date    2014-03-30 17:47:55
 -- @version 1.0
]]

UILayer = class("UILayer",CCBLayer)

function UILayer:ctor( )
	UILayer.super.ctor(self)
	self:loadCCB("UILayer.ccbi")

	self:setHandler("btn_openfile", self.on_btn_openfile_click)
end

function UILayer:initialize( )
	self:getElement("m_selectFile"):setVisible(true)
	self:getElement("m_selectUnit"):setVisible(false)
end

function UILayer:on_btn_openfile_click( )
	-- local result = device.showInputBox("打开文件", "输入配置文件或图片绝对路径", "temp.jpg")
	-- if result == "" then
	-- 	-- result = "temp.jpg"
	-- else
	-- 	main:setTexture(result)
	-- end
	ruyao()
end
