
require("helpers/Utility")
require("helpers/NodeUtility")

sceneMainMenu = director:createScene()
sceneMainMenu.name = "menu"

useQuitButton =  device:getInfo("platform") ~= "IPHONE"

local btnW = 500
local btnHScale = 0.4 

--------------------------------------------------------

function sceneMainMenu:setUp(event)
    
    system:addEventListener({"suspend", "resume", "update"}, self)
    virtualResolution:applyToScene(self)

    -- background
    self.background = director:createSprite(0, 0, "textures/sky.png")
    self.background.defaultScale = appHeight/self.background.h
    self.background.xScale = self.background.defaultScale
    self.background.yScale = self.background.defaultScale

    -- title
    self.mainMenu = director:createNode({x=appWidth/2,y=appHeight-170})
    local titleOutline = director:createLines({x=0, y=0,
            coords={-240,-50, -240,50, 240,50, 240,-50, -240,-50},
            strokeWidth=4, strokeColor=color.white, alpha=0})
    self.mainMenu:addChild(titleOutline)
    local titleText = director:createLabel({x=-214, y=-15, w=400, h=100,
            hAlignment="left", vAlignment="bottom", text="Google Services: The Game!", color=color.white, xScale=1.2, yScale=1.2})
    self.mainMenu:addChild(titleText)
    
    self.mainMenu.adLabel = director:createLabel({x=20, y=150, w=appWidth-20, h=50,
            hAlignment="left", vAlignment="bottom", text="Ad IDs loaded:", color=color.black})
    
    self.mainMenu.adLoadLabel = director:createLabel({x=20, y=110, w=appWidth-20, h=50,
            hAlignment="left", vAlignment="bottom", text="Interstitial ad: not loaded", color=color.black})


    -- buttons
    self.btns = {}
    local btnY = -150
    sceneMainMenu:addButton("start", "Start Game", btnY, touchStart, 20)

    btnY = btnY - 100
    sceneMainMenu:addButton("topBanner", "show new top banner", btnY, touchTop, 20)

    btnY = btnY - 100
    sceneMainMenu:addButton("bottomBanner", "show new bottom banner", btnY, touchBottom, 20)
    
    btnY = btnY - 100
    sceneMainMenu:addButton("interstitial", "load new interstitial", btnY, touchInterstitial, 20)

    if useQuitButton then
        btnY = btnY - 100
        sceneMainMenu:addButton("quit", "Quit", btnY, touchQuit, 20)
    end

    enableMainMenu()
    
    --TODO: initialise GPS hee
    
    --TODO: login and load data
end

--TODO: GPS event sgo here

function sceneMainMenu:exitPreTransition(event)
    system:removeEventListener({"suspend", "resume", "update"}, self)
end

function sceneMainMenu:exitPostTransition(event)
    destroyNodesInTree(self, false)
    self.mainMenu = nil
    self.btns = nil
    self.background = nil

    self:releaseResources()
    collectgarbage("collect")
    director:cleanupTextures()
end

sceneMainMenu:addEventListener({"setUp", "exitPreTransition", "exitPostTransition"}, sceneMainMenu)


---- Button helpers -----------------------------------------------------------

function sceneMainMenu:addButton(name, text, btnY, touchListener, textX)
    self.btns[name] = director:createSprite({x=0, y=btnY, xAnchor=0.5, yAnchor=0.5, source="textures/bigwhitebutton.png"})

    local btnScale = btnW/self.btns.start.w
    local btnH = self.btns.start.h * btnScale * btnHScale

    self.btns[name].xScale = btnScale
    self.btns[name].yScale = btnScale * btnHScale
    self.btns[name].defaultScale = btnScale
    self.mainMenu:addChild(self.btns[name])
    self.btns[name].label = director:createLabel({x=textX, y=30, w=btnW, h=btnH, hAlignment="left", vAlignment="bottom", text=text, color=color.black, xScale=1.2, yScale=1.2/btnHScale})
    self.btns[name]:addChild(self.btns[name].label)

    self.btns[name].touch = touchListener
end

function enableMainMenu(target)
    for k,v in pairs(sceneMainMenu.btns) do
        v:addEventListener("touch", v)
    end
end

function disableMainMenu(target)
    for k,v in pairs(sceneMainMenu.btns) do
        v:removeEventListener("touch", v)
    end
end

function startGame()
    director:moveToScene(sceneGame, {transitionType="slideInR", transitionTime=0.8})
end

---- Pause/resume logic/anims on app suspend/resume ---------------------------

function sceneMainMenu:suspend(event)
    if not pauseflag then
        system:pauseTimers()
        pauseNodesInTree(self)
        saveUserData()
    end
end

function sceneMainMenu:resume(event)
    pauseflag = true
end

function sceneMainMenu:update(event)
    if pauseflag then
        pauseflag = false
        system:resumeTimers()
        resumeNodesInTree(self)
    end
    
    self.mainMenu.adLabel.text = "Ad IDs loaded: top=" .. adIds.top .. " btm=" .. adIds.bottom .. " inter=" .. adIds.interstitial
end

---- Button handlers ----------------------------------------------------------

function touchStart(self, event)
    if event.phase == "ended" then
        disableMainMenu()
        startGame()
    end
end

function touchQuit(self, event)
    if event.phase == "ended" then
        --terminate GPS here
        shutDownApp()
    end
end
